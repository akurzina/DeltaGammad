//////////////////////////////////////////////////////////////////////////
// to use it:
// make Hypatia_fit_selection
// ./Hypatia_fit_selection
/////////////////////////////////////////////////////////////////////////



#include "Inclusion.h"
#include "TGaxis.h"


//Fit massa del Bd con dati selezionati
int main(int argc, char **argv){
  TApplication theApp("App", &argc, argv);

  gROOT->SetBatch(kFALSE);
  gROOT->Reset();
  gROOT->Clear();
  cout.precision(8);

  TH1::SetDefaultSumw2();

  bool log = false;

  //Selected data
  TChain *datatree_s = new TChain("DecayTree;1");
  datatree_s->Add("/home/akurzina/Analisi_data/Selection_Kstar/B0JpsiKstar2016Up_Data_43_Selected.root");

//RooDataSet data("data", "dataset with Bd MM", datatree, Bd_LOKI_MASS_JpsiConstr);
//  RooDataSet data_selected("data selected", "dataset selected with Bd MM", datatree_s,Bd_LOKI_MASS_JpsiConstr);

  RooRealVar Bd_LOKI_MASS_JpsiConstr("Bd_LOKI_MASS_JpsiConstr", "m(J/#psi(#mu^{+}#mu^{-}) #K^{+}#pi^{-})", 5280, 5150, 5340,"MeV/c^{2}");

  //TCut sanity = "!(mass!=mass)";
  RooArgList phaseSpace(Bd_LOKI_MASS_JpsiConstr);
  RooArgList fitArgs(Bd_LOKI_MASS_JpsiConstr);
  //fitArgs->add(*);

  RooDataSet data_selected("data_selected","dataset selected with Bd MM",datatree_s,phaseSpace);

  TFile* inputFile = new TFile("fitresult.root");
  RooFitResult *fitResult = (RooFitResult*)inputFile->Get("fitresult_hypatia_data_selected;1");

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

    inputFile->Close();
    
  //Parametri Ipatia
/*
        RooRealVar lambda("lambda", "lambda", -8.85640e-04, -8.85640e-04, -8.85640e-04);
	RooRealVar zeta("zeta", "zeta", fitted_zeta, fitted_zeta - fitted_zeta* 0.1 , fitted_zeta + fitted_zeta* 0.1);
	RooRealVar beta("beta", "beta", fitted_beta, fitted_beta - fitted_beta * 0.1, fitted_beta + fitted_beta * 0.1);
	RooRealVar sigma("sigma", "sigma", 8.1, 7.15956e+00, 10.);
	RooRealVar mu("mu", "mu", 5.28011e+03, 5275, 5285);
	RooRealVar a("a", "a",2.27877e+00, 2.27877e+00, 2.27877e+00);
	RooRealVar n("n", "n", fitted_n, fitted_n - fitted_n* 0.1, fitted_n + fitted_n *0.1);
	RooRealVar a2("a2", "a2", fitted_a2, fitted_a2 - fitted_a2 * 0.1, fitted_a2 + fitted_a2 * 0.1);
	RooRealVar n2("n2", "n2", fitted_n2, fitted_n2 - fitted_n2 * 0.1, fitted_n2 + fitted_n2 * 0.1);
*/
  RooRealVar lambda("lambda", "lambda", -8.85640e-04, -8.85640e-04, -8.85640e-04);
	RooRealVar zeta("zeta", "zeta", fitted_zeta, 0.,3.);
	RooRealVar beta("beta", "beta", fitted_beta, -1, 1);
	RooRealVar sigma("sigma", "sigma", fitted_sigma, 7., 10.);
	RooRealVar mu("mu", "mu", 5.28011e+03, 5275, 5287);
	RooRealVar a("a", "a",2.27877e+00, 2.27877e+00, 2.27877e+00);
	RooRealVar n("n", "n", fitted_n, fitted_n , fitted_n);
	RooRealVar a2("a2", "a2", fitted_a2, fitted_a2, fitted_a2 );
	RooRealVar n2("n2", "n2", fitted_n2, fitted_n2, fitted_n2);


/*
        RooRealVar lambda("lambda", "lambda", -8.85640e-04, -8.85640e-04, -8.85640e-04);
	RooRealVar zeta("zeta", "zeta", 1.7, 0., 3.);
	RooRealVar beta("beta", "beta", -0.01, -1000, 1000);
	RooRealVar sigma("sigma", "sigma", 8.1, 7.15956e+00, 10.);
	RooRealVar mu("mu", "mu", 5.28011e+03, 5275, 5285);
	RooRealVar a("a", "a",2.27877e+00, 2.27877e+00, 2.27877e+00);
	RooRealVar n("n", "n", 1.70881e+00, 0, 4);
	RooRealVar a2("a2", "a2", 2.26681e+00, 0, 5);
	RooRealVar n2("n2", "n2", 3.20017e+00, 2, 5);
*/


	RooHypatia2 hypatia("hypatia", "Hypatia", Bd_LOKI_MASS_JpsiConstr, lambda, zeta, beta, sigma, mu, a, n, a2, n2);

          
      //Fit solo hypatia
     // hypatia.fitTo(data_selected,Save(kTRUE));
     
        
        RooRealVar coeff("coeff", "exp coeff", -1e-3, -1e-7, 0.);
        RooExponential exp("exp", "Exp Background", Bd_LOKI_MASS_JpsiConstr, coeff);
    
        RooRealVar fsig("fsig", "fsig", 0.5, 0, 1);
       // RooRealVar fbkg("fbkg", "fbkg", 0.5, 0, 1);
      
      
        RooAddPdf model("model", "Total PDF", RooArgList(hypatia, exp), RooArgList(fsig));
        // Fit the model to the data
        RooFitResult* result = model.fitTo(data_selected, RooFit::Save());


      std::cout << "\n\n------------------------------------------\nThe dataset before creating sWeights:\n";
      data_selected.Print();
      

        TFile f("fitresult_data.root","RECREATE");
        result->Write();
        f.Close();




//  RooFitResult * rs;
//  rs = hypatia.fitTo(data_selected, Minos(kTRUE), NumCPU(1),Strategy(1), Save()); //Extended()


	//Plot
	TCanvas *can= new TCanvas("can", "can");
	RooPlot *frame = Bd_LOKI_MASS_JpsiConstr.frame(Title("B^{0}_{d} invariant mass"),Bins(80));
	//data.plotOn(xframe);
	data_selected.plotOn(frame);
	model.plotOn(frame, Components("hypatia"), LineColor(kRed), LineStyle(kDashed));
	model.plotOn(frame, Components("exp"), LineStyle(kDashed));
      	model.plotOn(frame,LineColor(kRed),LineWidth(2));  //LineStyle(3),
      	frame->Draw();
        can->Print("B_mass.pdf");

       //Plot Residuals
       TLatex lat;
       lat.SetTextSize(0.06);
       lat.SetTextAlign(13);
       double xLat = frame->GetXaxis()->GetXmin() + 0.80 *( frame->GetXaxis()->GetXmax()- frame->GetXaxis()->GetXmin() );
       cout << "xLat: " << xLat << endl;
       double yLat = 0.8*frame->GetMaximum();
       cout << "yLat: " << yLat << endl;
       gStyle->SetOptTitle(0);

       TCanvas *c = new TCanvas("cfitres", "", 1600,1000);
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
       // c->Divide(2);
       // c->GetPad(1)->SetPad(0.0,0.2,1.0,1.0);
       // c->GetPad(2)->SetPad(0.0,0.0,1.0,0.2);
       // c->GetPad(1)->SetLeftMargin(0.15);
       // c->GetPad(2)->SetLeftMargin(0.15);
       // c->GetPad(1)->SetBottomMargin(0.1);
       // c->GetPad(2)->SetTopMargin(0.1);
       // c->cd(1);
     
       frame->GetXaxis()->SetTitleOffset(1);
       frame->GetYaxis()->SetTitleSize(0.048);
       frame->GetXaxis()->SetTitleSize(0.048);
       frame->GetYaxis()->SetTitleOffset(1);
       cout << "y offset: " << frame->GetYaxis()->GetTitleOffset() << endl;
       if(log){frame->SetMinimum(0.5);}else{frame->SetMinimum(0.1);}
       frame->Draw();
   
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


       if(log) gPad->SetLogy();

      lat.DrawLatex(xLat,yLat,"LHCb");
      c->cd(2);
      //Plot residuals
      //RooPlot *frameRes = PlotResiduals(frame, hypatia);
      RooPlot *frameRes = (RooPlot*)frame->emptyClone("pull");//getPlotVar()->frame();
      RooHist *resHist = (RooHist*)frame->pullHist();
      //RooHist *resHist = (RooHist*)frame->pullHist("data_selected","model", kTRUE);
      //   for (int i = 0; i < resHist->GetN(); i++)
      //     resHist->SetPointError(i,0.,0.,0.,0.);
      resHist->SetFillColor(kBlue-9); //here
      frameRes->addObject(resHist,"E3") ;
      frameRes->SetMinimum(-6) ;
      frameRes->SetMaximum(+6) ;
      frameRes->SetTitle("");
      frameRes->GetXaxis()->SetTitle(frame->GetXaxis()->GetTitle());

      frameRes->GetYaxis()->SetNdivisions(110);
      frameRes->GetYaxis()->SetLabelSize(0.);
      frameRes->GetYaxis()->SetTitle("Pull");

      frameRes->GetYaxis()->CenterTitle();
      frameRes->GetYaxis()->SetTitleSize(0.22);
      frameRes->GetYaxis()->SetTitleOffset(0.20);
      frameRes->GetXaxis()->SetNdivisions( frame->GetXaxis()->GetNdivisions() );
      //  frameRes->Draw();
      TGaxis *xup = new TGaxis(-0.05,5.,0.05,5.,-0.05,0.05,510,"-");
      xup->SetLabelSize(0.);
      xup->SetNdivisions( frame->GetXaxis()->GetNdivisions() );
      //  xup->Draw();
      TGaxis *yright = new TGaxis(0.05,-5.,0.05,5.,-5.,5.,510,"+L");
      yright->SetLabelSize(0.);
      yright->SetNdivisions(110);
        //  yright->Draw();
      TLine *lResup5 = new TLine( frameRes->GetXaxis()->GetXmin(),5.,
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
      frameRes->GetXaxis()->SetLabelSize(frame->GetXaxis()->GetLabelSize()*4);

      frameRes->GetXaxis()->SetTitleSize(frame->GetXaxis()->GetTitleSize()*4);
      frameRes->GetXaxis()->SetTitle(frame->GetXaxis()->GetTitle());
      frameRes->Draw();

      c->Print("B_mass_with_pull.pdf");

      //Number of signal events
      
      cout<<" \n aaaa  "<<data_selected.sumEntries()<<"\n";
     /*
     RooAbsReal* Nsig2 = hypatia.createIntegral(Bd_LOKI_MASS_JpsiConstr, data_selected);
      RooAbsReal* Nc = model.createIntegral(Bd_LOKI_MASS_JpsiConstr, data_selected);
      cout<<"\n num candidati "<<Nc->getVal();
      */
      double Nsig1 = data_selected.sumEntries() * fsig.getVal();
      
      cout<<"\n \n \n Number of Events1 "<<Nsig1;
/*
    // Create a RooStats SPlot object
       RooStats::SPlot sData("sData", "SPlot Data", data_selected, &model, RooArgList(fsig));
          
       std::cout << "\n\nThe dataset after creating sWeights:\n";
       data_selected.Print();

        TCanvas *canv= new TCanvas("canv", "canv");
	RooPlot *sframe = Bd_LOKI_MASS_JpsiConstr.frame(Title("B^{0}_{d} invariant mass"),Bins(80));
	//data.plotOn(xframe);
	data_selected.plotOn(sframe);
        sframe->Draw();

*/

      cout<< "--> The End <-- " << endl;
      theApp.Run();
      return 0;
}
