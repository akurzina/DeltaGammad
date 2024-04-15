#include "Inclusion.h"
//funzione principale fit()



double FitPlot(double t1, double t2, int indice, TH1* mass_hist, bool kshort){
        
         TFile* inputFile = new TFile("fitresult_data.root");
        RooFitResult *fitResult = (RooFitResult*)inputFile->Get("fitresult_model_data_selected;1");

      // fixed vals
          RooRealVar *sigmaVar = dynamic_cast<RooRealVar*>(fitResult->floatParsFinal().find("sigma"));  
          double fitted_sigma = sigmaVar->getVal();

          RooRealVar *zetaVar = dynamic_cast<RooRealVar*>(fitResult->floatParsFinal().find("zeta"));  
          double fitted_zeta = zetaVar->getVal();
         
          RooRealVar *betaVar = dynamic_cast<RooRealVar*>(fitResult->floatParsFinal().find("beta"));  
          double fitted_beta = betaVar->getVal();

          RooRealVar *nVar = dynamic_cast<RooRealVar*>(fitResult->floatParsFinal().find("n"));  
          double fitted_n = nVar->getVal();
        
            RooRealVar *n2Var = dynamic_cast<RooRealVar*>(fitResult->floatParsFinal().find("n2"));  
          double fitted_n2 = n2Var->getVal();
          
          RooRealVar *a2Var = dynamic_cast<RooRealVar*>(fitResult->floatParsFinal().find("a2"));  
          double fitted_a2 = a2Var->getVal();

          RooRealVar *coeffVar = dynamic_cast<RooRealVar*>(fitResult->floatParsFinal().find("coeff"));  
          double fitted_coeff = coeffVar->getVal();

          inputFile->Close();
          
        
       //Parametri Ipatia
       RooRealVar BdMass("BdMass", "Bd Mass", 5280,5150, 5340,"MeV/c^{2}");
       RooRealVar lambda("lambda", "lambda", -8.85640e-04, -8.85640e-04, -8.85640e-04);
	RooRealVar zeta("zeta", "zeta", fitted_zeta, 0.,3.);
	RooRealVar beta("beta", "beta", fitted_beta, -1, 1);
	RooRealVar sigma("sigma", "sigma", fitted_sigma, 7., 10.);
	RooRealVar mu("mu", "mu", 5.28011e+03, 5275, 5287);
	RooRealVar a("a", "a",2.27877e+00, 2.27877e+00, 2.27877e+00);
	RooRealVar n("n", "n", fitted_n, fitted_n , fitted_n);
	RooRealVar a2("a2", "a2", fitted_a2, fitted_a2, fitted_a2 );
	RooRealVar n2("n2", "n2", fitted_n2, fitted_n2, fitted_n2);
        
        RooDataHist data1("data", "data", BdMass, mass_hist);	
        
        RooHypatia2 hypatia("hypatia", "Hypatia", BdMass, lambda, zeta, beta, sigma, mu, a, n, a2, n2);

          
      //Fit solo hypatia
     // hypatia.fitTo(data_selected,Save(kTRUE));
     
        
        RooRealVar coeff("coeff", "exp coeff", fitted_coeff, fitted_coeff, fitted_coeff);
        RooExponential exp("exp", "Exp Background", BdMass, coeff);
    
        RooRealVar fsig("fsig", "fsig", 0.5, 0, 1);
       // RooRealVar fbkg("fbkg", "fbkg", 0.5, 0, 1);
      
      
        RooAddPdf model("model", "Total PDF", RooArgList(hypatia, exp), RooArgList(fsig));
        // Fit the model to the data
        RooFitResult* result = model.fitTo(data1, RooFit::Save());
        
        std::cout << "Candidati ";
        data1.Print();
      
      double events = fsig.getVal() * data1.sumEntries();
     
     
     TString format = ".root";
    TString  name = Form("FitinBinResult%d", indice);
      TString nome_file = name + format;
        TFile f(nome_file,"RECREATE");
        result->Write();
        f.Close();


       
       //Plot
	TCanvas *c=new TCanvas("c", "c");
	RooPlot *xframe = BdMass.frame();
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
	
	data1.plotOn(xframe);
	model.plotOn(xframe, Components("hypatia"), LineColor(kRed), LineStyle(kDashed));
	model.plotOn(xframe, Components("exp"), LineStyle(kDashed));
      	model.plotOn(xframe,LineColor(kRed),LineWidth(2));  //LineStyle(3),
      	
	
	xframe->GetYaxis()->SetTitleOffset(1.1);
        xframe->GetXaxis()->SetTitleOffset(1);
        xframe->GetYaxis()->SetTitleSize(0.048);
        xframe->GetXaxis()->SetTitleSize(0.048);
        xframe->SetTitle("");
	xframe->Draw();
	
	 //legend
      TLegend* legend1 = new TLegend(0.15, 0.75, 0.45, 0.88);
       legend1->SetFillColor(kWhite);
       legend1->SetLineColor(kWhite);
       TLegendEntry* entry2= legend1->AddEntry("data", "data", "lpe");
       TLegendEntry* entry1= legend1->AddEntry("model", "Fit", "L");
       entry1->SetLineColor(kRed);
       TLegendEntry* entry3 = legend1->AddEntry("hypatia", "Signal", "l");
       entry3->SetLineColor(kRed);
       entry3->SetLineStyle(2);
       TLegendEntry* entry4= legend1->AddEntry("exp", "Background", "l");
       entry4->SetLineColor(kBlue);
       entry4->SetLineStyle(2);
       legend1->Draw(); 
	
	
	c->cd(2);
        //Plot residuals
        //RooPlot *frameRes = PlotResiduals(xframe, hypatia);
        RooPlot *frameRes = (RooPlot*)xframe->emptyClone("pull");//getPlotVar()->xframe();
        RooHist *resHist = (RooHist*)xframe->pullHist();
        //RooHist *resHist = (RooHist*)xframe->pullHist("datahistogram","hypatia", kTRUE);
        //   for (int i = 0; i < resHist->GetN(); i++)
        //     resHist->SetPointError(i,0.,0.,0.,0.);
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
	
	

        
        TString name_plot_file;
        if (kshort == true){
           name_plot_file = Form("mass_fit_short_%d.pdf", indice);
        }

        if (kshort == false) {
           name_plot_file = Form("mass_fit_star_%d.pdf", indice);
        }
        
        
        
        c->SaveAs(name_plot_file);      
        return events;

}

void PlotEvents(TH1* event_hist, TString nome_canv){
      TCanvas *can_events= new TCanvas("can_events", nome_canv, 1600, 1000);
      event_hist->GetXaxis()->SetTitle("time (ps)");
      event_hist->GetYaxis()->SetTitle("Number of Events");
      event_hist->Draw();
      TString format = ".pdf";
      TString nome_file = nome_canv + format;
      can_events->SaveAs(nome_file);

}


void PlotAcceptance(TH1* acc_hist, TString nome_canv) {
      TCanvas *canacc= new TCanvas("canacc", nome_canv, 1600, 1000);
      acc_hist->GetXaxis()->SetTitle("time (ps)");
      acc_hist->GetYaxis()->SetTitle("Acceptance (a.u)");
      acc_hist->DrawNormalized();
      TString format = ".pdf";
      TString nome_file = nome_canv + format;
      canacc->SaveAs(nome_file);
}




void fit() {
        
        gROOT->SetBatch(kFALSE);
        gROOT->Reset();
        gROOT->Clear();
        cout.precision(8);
        
        TH1::SetDefaultSumw2();
        TLatex latt;


        cout<<"\n \n \n Importazione";

       // Importazione file e tree
        TChain *datatree1= new TChain("DecayTree;1");
        datatree1->Add("/home/akurzina/Analisi_data/Selection_Kstar/B0JpsiKstar2016Up_Data_43_Selected.root");
	
	datatree1->SetBranchStatus("*",0);
      	datatree1->SetBranchStatus("Bd_LOKI_MASS_JpsiConstr", 1);
      	datatree1->SetBranchStatus("time", 1);   	
  	   	
   	double Bd_mass;
        float time;
        bool  kshort = false;
   	
   	//Larghezze bin
        const int nbins=13; //16
        Double_t xbins[nbins+1]={0.0005*1000,0.0007*1000,0.0009*1000,0.0011*1000,0.0013*1000,0.0015*1000,0.0017*1000,0.0019*1000,0.0021*1000,0.0024*1000,0.0028*1000,0.0035*1000,0.0050*1000,0.015*1000};
 
   	datatree1->SetBranchAddress("Bd_LOKI_MASS_JpsiConstr", &Bd_mass);
   	datatree1->SetBranchAddress("time", &time);

        double_t segnale_star[nbins];  
        for(int i=0; i<nbins; i++){
                double time1 = xbins[i];
                double time2 = xbins[i+1];
     
                TH1D *mass_hist=new TH1D("mass_hist", "mass_hist", 100,5100,5600);
                
                cout<<"\n \n \n Ho definito l'istogramma";
                for (int iEntry = 0; iEntry < datatree1->GetEntries(); iEntry++) {
                      datatree1->GetEntry(iEntry);
                      // Applica la selezione temporale
                      if (time > time1 && time < time2) {
                          //cout<<"Riempo "<<iEntry;
                          mass_hist->Fill(Bd_mass);
                      }
                } 
                
                cout<<" \n \n \n prima di fitplot "<<i;
                segnale_star[i] = FitPlot(time1,time2,i,mass_hist, kshort);
                cout<<" \n \n \n dopo  fitplot "<<i;
          }

        //istogramma eventi segnale 
       TH1F *res_histo_star=new TH1F("res_histo_star", "res_histo_star",nbins, xbins);

       for(int k=0; k<nbins; k++){
            //Importante che gli indici siano così
            res_histo_star->SetBinContent(k+1,segnale_star[k]);
            res_histo_star->SetBinError(k+1,sqrt(segnale_star[k]));
        }

       //"Numero di eventi B_{d} #rightarrow J/#psi K*"
        TString name_hist_star = Form("Number_of_events_B_{d}_#rightarrow_J/#psi_K^{*}");
        PlotEvents(res_histo_star, name_hist_star);  

        TFile* file1= new TFile("res_histo_star.root", "RECREATE");
        res_histo_star->Write();
        file1->Close();  

        
    
}




