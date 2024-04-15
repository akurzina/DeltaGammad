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
  TChain *datatree_s = new TChain("DecayTree");
  datatree_s->Add("/home/akurzina/Analisi/Selezione_jpsikshort/Bd2JpsiKshort_MC_selected.root");

//RooDataSet data("data", "dataset with Bd MM", datatree, Bd_LOKI_MASS_JpsiConstr);
//  RooDataSet data_selected("data selected", "dataset selected with Bd MM", datatree_s,Bd_LOKI_MASS_JpsiConstr);

  RooRealVar Bd_LOKI_MASS_JpsiConstr("Bd_LOKI_MASS_JpsiConstr", "m(J/#psi(#mu^{+}#mu^{-}) #pi^{+}#pi^{-})", 5280.,5150, 5340,"MeV/c^{2}");

  //TCut sanity = "!(mass!=mass)";
  RooArgList phaseSpace(Bd_LOKI_MASS_JpsiConstr);
  RooArgList fitArgs(Bd_LOKI_MASS_JpsiConstr);
  //fitArgs->add(*);

  RooDataSet data_selected("data selected","dataset selected with Bd MM",datatree_s,phaseSpace);

  //Parametri Ipatia
	RooRealVar lambda("lambda", "lambda", -8.85640e-04, -8.85640e-04, -8.85640e-04);
	RooRealVar zeta("zeta", "zeta", 1.7, 0., 3.);
	RooRealVar beta("beta", "beta", -0.01, -1000, 1000);
	RooRealVar sigma("sigma", "sigma", 8.1, 7.15956e+00, 10.);
	RooRealVar mu("mu", "mu", 5.28011e+03, 5275, 5285);
	RooRealVar a("a", "a",2.27877e+00, 2.27877e+00, 2.27877e+00);
	RooRealVar n("n", "n", 1.70881e+00, 0, 4);
	RooRealVar a2("a2", "a2", 2.26681e+00, 0, 5);
	RooRealVar n2("n2", "n2", 3.20017e+00, 2, 5);

	RooHypatia2 hypatia("hypatia", "Hypatia", Bd_LOKI_MASS_JpsiConstr, lambda, zeta, beta, sigma, mu, a, n, a2, n2);



  //Gaussiana

      	RooRealVar sigma_gauss("sigma_gauss", "sigma_gauss", 8.1, 7.15956e+00, 10.);
	RooRealVar mean("mean", "mean", 5.28011e+03, 5275, 5285);
	RooGaussian gauss("gauss","gauss", Bd_LOKI_MASS_JpsiConstr, mean, sigma_gauss);

        //Fit
	hypatia.fitTo(data_selected,Save(kTRUE));

//  RooFitResult * rs;
//  rs = hypatia.fitTo(data_selected, Minos(kTRUE), NumCPU(1),Strategy(1), Save()); //Extended()


	//Plot
	TCanvas *can= new TCanvas("can", "can");
	RooPlot *frame = Bd_LOKI_MASS_JpsiConstr.frame(Title("B^{0}_{d} invariant mass"),Bins(80));
	//data.plotOn(xframe);
	data_selected.plotOn(frame);
	hypatia.plotOn(frame,LineColor(kRed),LineWidth(2));  //LineStyle(3),
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
   TLegendEntry* entry1= legend1->AddEntry("hypatia", "Fit", "L");
   entry1->SetLineColor(kRed);
   TLegendEntry* entry2= legend1->AddEntry("mc", "MC", "lpe");
   legend1->Draw();      


   if(log) gPad->SetLogy();

  lat.DrawLatex(xLat,yLat,"LHCb MC");
  c->cd(2);
  //Plot residuals
  //RooPlot *frameRes = PlotResiduals(frame, hypatia);
  RooPlot *frameRes = (RooPlot*)frame->emptyClone("pull");//getPlotVar()->frame();
  RooHist *resHist = (RooHist*)frame->pullHist();
  //RooHist *resHist = (RooHist*)frame->pullHist("datahistogram","hypatia", kTRUE);
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


  cout<< "--> The End <-- " << endl;
  theApp.Run();
  return 0;
}
