#include "Inclusion.h"
#include <RooFitResult.h>

void risoluzione_star() {
        gROOT->SetBatch(kFALSE);
        gROOT->Reset();
        gROOT->Clear();
        cout.precision(8);

        TH1::SetDefaultSumw2();
  
       // Importazione file e tree
	TChain *datatree_star_rec= new TChain("DecayTree");
	datatree_star_rec->Add("/home/akurzina/Analisi/Selezione_jpsikstar/B02JpsiKstar_2016_magDown_MC_Selected.root");
      	
	datatree_star_rec->SetBranchStatus("*",0);
	datatree_star_rec->SetBranchStatus("time", 1);
	datatree_star_rec->SetBranchStatus("Bd_LOKI_MASS_JpsiConstr", 1);
        
        TH1D *hmr_star=new TH1D("Risoluzione_star", "", 100,-0.5, 0.5);
        
       	double t_true_star;
	float  t_rec_star;
	double res_star; //variabile per il calcolo della risoluzione
	
	datatree_star_rec->SetBranchAddress("time",&t_rec_star);
        datatree_star_rec->SetBranchAddress("Bd_TRUETAU",&t_true_star);
	
      	
	//Risoluzione star
	for (int i=0; i<datatree_star_rec->GetEntries(); i++) {
	  datatree_star_rec->GetEntry(i);	  
          t_true_star = t_true_star * 1000;
          res_star = t_rec_star - t_true_star;
          hmr_star->Fill(res_star);
         }
	 	
       TCanvas *can=new TCanvas("can", "can", 1600, 1000);
       hmr_star->SetXTitle("t_rec - t_true [ps]");
       hmr_star->SetYTitle("Events");
       hmr_star->SetStats(0);
       hmr_star->GetYaxis()->SetTitleOffset(1.1);
       hmr_star->GetXaxis()->SetTitleOffset(1);
       hmr_star->GetYaxis()->SetTitleSize(0.048);
       hmr_star->GetXaxis()->SetTitleSize(0.048);
       hmr_star->Draw();
       can->SaveAs("risoluzione_star.pdf");
	
	
       //fit
       RooRealVar t("res", "Time Resolution", -0.5, 0.5, "ps");
       RooRealVar mean("mean", "Mean of Gaus", 0, -0.5, 0.5);
       RooRealVar sigma1("sigma1", "Width of gaus1", 0.5,0, 2.5);
       RooRealVar sigma2("sigma2", "Width of gaus2", 0.5, 0, 2);	
       RooRealVar sigma3("sigma3", "Width of gaus3", 0.5, 0, 2);
       RooRealVar fsig("fsig", "signal fraction", 0.5, 0, 1);
       RooRealVar fsig2("fsig2", "signal fraction", 0.5, 0, 1);

       RooGaussian gauss1("gauss1", "gauss1(t,mean,sigma1)",t, mean, sigma1);
       RooGaussian gauss2("gauss2", "gauss2(t,mean,sigma2)",t, mean, sigma2);
       RooGaussian gauss3("gauss3", "gauss3(t,mean,sigma3)",t, mean, sigma3);
        
       RooAddPdf model("model", "model", RooArgList(gauss1,gauss2,gauss3), RooArgList(fsig, fsig2));
       //RooAddPdf model2("model2", "model2", RooArgList(gauss1,gauss2), RooArgList(fsig, fsig2));
	
       RooDataHist data_star("data", "data res", t, hmr_star);
	
       //model.fitTo(data_star);
       RooFitResult* fitResult = model.fitTo(data_star, RooFit::Save());
       cout<< "FINE FIT STAR \n \n \n \n  ";
     
	//Plot_star
	TCanvas *c=new TCanvas("c", "c");
	RooPlot *xframe = t.frame(Title("Time resolution [ps]"),Bins(100));
	//Plot Residuals
        TLatex lat;
        lat.SetTextSize(0.06);
        lat.SetTextAlign(13);
        double xLat = xframe->GetXaxis()->GetXmin() + 0.80 *(xframe->GetXaxis()->GetXmax()- xframe->GetXaxis()->GetXmin() );
        cout << "xLat: " << xLat << endl;
        double yLat = 0.8*xframe->GetMaximum();
        cout << "yLat: " << yLat << endl;
        gStyle->SetOptTitle(0);
      	c->Divide(2);
        c->GetPad(1)->SetPad(0.0,0.2,1.0,1.0);
        c->GetPad(2)->SetPad(0.0,0.0,1.0,0.2);
        c->GetPad(1)->SetLeftMargin(0.10);
        c->GetPad(2)->SetLeftMargin(0.10);
        c->GetPad(1)->SetRightMargin(0.10);
        c->GetPad(2)->SetRightMargin(0.10);
        c->GetPad(1)->SetBottomMargin(0.01);
        c->GetPad(2)->SetTopMargin(0.01);
        c->GetPad(2)->SetBottomMargin(0.55);
        c->cd(1);
	
	//Questo plotta i dati come punti con errore
	data_star.plotOn(xframe);
	model.plotOn(xframe);
	//model.plotOn(xframe, Components("gauss1"), LineColor(kRed), LineStyle(kDashed));
	//model.plotOn(xframe, Components("gauss2"), LineStyle(kDashed));	
	//model.plotOn(xframe, Components("gauss3"), LineColor(kOrange), LineStyle(kDashed));
	//model.plotOn(xframe, Components("gauss4"), LineColor(kGreen), LineStyle(kDashed));
	xframe->GetYaxis()->SetTitleOffset(1.1);
        xframe->GetXaxis()->SetTitleOffset(1);
        //xframe->GetXaxis()->SetTitle("Risoluzione [ps]");
        xframe->GetYaxis()->SetTitleSize(0.048);
        xframe->GetXaxis()->SetTitleSize(0.048);
        xframe->SetTitle("");
        //xframe->GetYaxis()->SetTitle("Events / ( 0.05 ps)");
	xframe->Draw();
	
	TLegend* legend = new TLegend(0.15, 0.75, 0.45, 0.88);
	legend->SetFillColor(kWhite);
	legend->SetLineColor(kWhite);
	TLegendEntry* entry1= legend->AddEntry("hypatia", "Fit", "L");
	entry1->SetLineColor(kBlue);
	TLegendEntry* entry2= legend->AddEntry("mc", "MC", "lpe");
        legend->Draw();
        
          c->cd(2);
          //Plot residuals
          //RooPlot *frameRes = PlotResiduals(xframe, hypatia);
          RooPlot *frameRes = (RooPlot*)xframe->emptyClone("pull");//getPlotVar()->xframe();
          RooHist *resHist = (RooHist*)xframe->pullHist();
          //RooHist *resHist = (RooHist*)xframe->pullHist("datahistogram","hypatia", kTRUE);
          // for (int i = 0; i < resHist->GetN(); i++)
          // resHist->SetPointError(i,0.,0.,0.,0.);
          resHist->SetFillColor(kBlue-9); //here
          frameRes->addObject(resHist,"E3") ;
          frameRes->SetMinimum(-6) ;
          frameRes->SetMaximum(+6) ;
          frameRes->SetTitle("");
          frameRes->GetXaxis()->SetTitle(xframe->GetXaxis()->GetTitle());

          frameRes->GetYaxis()->SetNdivisions(110);
          frameRes->GetYaxis()->SetLabelSize(0.);
          frameRes->GetYaxis()->SetTitle("Pull");

          frameRes->GetYaxis()->CenterTitle();
          frameRes->GetYaxis()->SetTitleSize(0.22);
          frameRes->GetYaxis()->SetTitleOffset(0.20);
          frameRes->GetXaxis()->SetNdivisions(xframe->GetXaxis()->GetNdivisions() );
          //  frameRes->Draw();
          TGaxis *xup = new TGaxis(-0.05,5.,0.05,5.,-0.05,0.05,510,"-");
          xup->SetLabelSize(0.);
          xup->SetNdivisions(xframe->GetXaxis()->GetNdivisions() );
          //  xup->Draw();
          TGaxis *yright = new TGaxis(0.05,-5.,0.05,5.,-5.,5.,510,"+L");
          yright->SetLabelSize(0.);
          yright->SetNdivisions(110);
            //  yright->Draw();
          TLine *lResup5 = new TLine(frameRes->GetXaxis()->GetXmin(),5.,
                                    frameRes->GetXaxis()->GetXmax(),5.);
          lResup5->SetLineColor(kRed+2);
          TLine *lResup = new TLine( frameRes->GetXaxis()->GetXmin(),3.,
                                    frameRes->GetXaxis()->GetXmax(),3.);
          lResup->SetLineColor(kRed+2);
          lResup->SetLineStyle(2);
          //  lResup->Draw();
          TLine *lResdw = new TLine( frameRes->GetXaxis()->GetXmin(), -3.,
                                    frameRes->GetXaxis()->GetXmax(),-3.);
          lResdw->SetLineColor(kRed+2);
          lResdw->SetLineStyle(2);

          TLine *lResdw5 = new TLine( frameRes->GetXaxis()->GetXmin(), -5.,
                                    frameRes->GetXaxis()->GetXmax(),-5.);
          lResdw5->SetLineColor(kRed+2);

          frameRes->addObject(lResup) ;
          frameRes->addObject(lResdw) ;
          frameRes->addObject(lResup5) ;
          frameRes->addObject(lResdw5) ;

          //TLatex lat;
          lat.SetTextSize(0.16);
          lat.SetTextAlign(32);

          frameRes->GetYaxis()->SetLabelSize(0.15);
          frameRes->GetYaxis()->SetNdivisions(505);
          //  frameRes->SetMinimum(0.85);
          //  frameRes->SetMaximum(1.15);
          frameRes->GetXaxis()->SetTitleOffset(1.1);
          frameRes->GetXaxis()->SetLabelSize(xframe->GetXaxis()->GetLabelSize()*4);

          frameRes->GetXaxis()->SetTitleSize(xframe->GetXaxis()->GetTitleSize()*4);
          frameRes->GetXaxis()->SetTitle(xframe->GetXaxis()->GetTitle());
          frameRes->Draw();
      
	  c->SaveAs("ris_fit_star.pdf");
	  
        //sigma_eff
        double sigma_star = (fsig.getVal() * sigma1.getVal() + fsig2.getVal() * sigma2.getVal()  +(1- fsig.getVal() - fsig2.getVal()) *sigma3.getVal());       
         
         
        double err_sigma_1 = fsig.getVal() * sigma1.getError() + fsig2.getVal() * sigma2.getError() + ((1- fsig.getVal() - fsig2.getVal()) * sigma3.getError());
           
        double err_sigma_2 = sqrt(pow((sigma1.getVal()-sigma3.getVal()),2)*pow(fsig.getError(),2) + pow(fsig.getVal(),2)*pow(sigma1.getError(),2) + pow((sigma2.getVal()-sigma3.getVal()),2)*pow(fsig2.getError(),2) + pow(fsig2.getVal(),2)*pow(sigma2.getError(),2)+pow((1-fsig.getVal()-fsig2.getVal()),2)*pow(sigma3.getError(),2));
                   
          
          cout<<"err_sigma_1 "<<err_sigma_1<<"\n \n ";
          cout<<"err_sigma_2 "<<err_sigma_2<<"\n \n ";
          
          
          
          cout<<"Sigma star " <<sigma_star<<"\n \n ";
          cout<< "Mean" <<mean.getVal()<<" Error "<<mean.getError()<<"\n \n";

}
	


