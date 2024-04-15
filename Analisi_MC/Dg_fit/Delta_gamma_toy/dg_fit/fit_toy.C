#include "Inclusion.h"


void fit_toy(){
  
  gROOT->SetBatch(kFALSE);
  gROOT->Reset();
  gROOT->Clear();
  cout.precision(8);
  TH1::SetDefaultSumw2();  



 // TH1D * hist_dg = new TH1F("hist_dg", "hist_dg" , 80, -7, 7);
  TFile* file = new TFile("dg_histo.root", "READ");
  TH1F* hist_dg = (TH1F*)file->Get("dg_hist");
  hist_dg->Draw();
 

/* //Alternativa per leggere
  std::unique_ptr<TFile> myFile( TFile::Open("dg_histo.root") );
  std::unique_ptr<TH1> hist(myFile->Get<TH1>("dg_hist;1"));
  
  hist->Draw(); 
*/ 
 
 //dg_histo->Rebin(2); 

      
  /*
  //scaling the data
  double tot = dg_histo->Integral();
  dg_histo->Scale(1.0/tot);
  */
  
  

  
  RooRealVar dg("dg", "dg", 0, -1e-1, 1e-1 ,"ps");
  RooRealVar mean("mean", "Mean of Gaus", 0, -2e-4, 2e-4);
  RooRealVar sigma("sigma", "Width of gaus1", 2e-2 ,0.5e-2, 3e-2);
  RooGaussian gauss("gauss", "gauss(dg,mean,sigma)",dg, mean, sigma);

  RooDataHist data("data", "data", dg, hist_dg);
  RooFitResult* fitResult = gauss.fitTo(data, RooFit::Save());

  //plot
  TCanvas *c=new TCanvas("c", "c");
  RooPlot *xframe = dg.frame(Title("dg [ps]"), Bins(80));
  data.plotOn(xframe);
  gauss.plotOn(xframe);
  xframe->GetYaxis()->SetTitleOffset(1.1);
  xframe->GetXaxis()->SetTitleOffset(1);
  xframe->GetYaxis()->SetTitleSize(0.048);
  xframe->GetXaxis()->SetTitleSize(0.048);
  xframe->SetTitle("");	
  TLegend* legend = new TLegend(0.15, 0.75, 0.45, 0.88);
  legend->SetFillColor(kWhite);
  legend->SetLineColor(kWhite);
  TLegendEntry* entry1= legend->AddEntry("gaus", "Fit", "L");
  entry1->SetLineColor(kBlue);
  TLegendEntry* entry2= legend->AddEntry("toy mc", "toyMC", "lpe");
  
  xframe->Draw();
  legend->Draw();


//  file->Close();


}





