#include "Inclusion.h"


void fit_res(){
  
  gROOT->SetBatch(kFALSE);
  gROOT->Reset();
  gROOT->Clear();
  cout.precision(8);
  TH1::SetDefaultSumw2();  



 // TH1D * hist_dg = new TH1F("hist_dg", "hist_dg" , 80, -7, 7);
  TFile* file = new TFile("dg_pull.root", "READ");
  TH1F* hist_pull = (TH1F*)file->Get("pull");
  hist_pull->Draw();
 

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
  
  RooRealVar dg_pull("dg", "dg pull ", 0, -7, 7);
  RooDataHist data("data", "data", dg_pull, hist_pull);
  //Gaussiane
  
  RooRealVar mean("mean", "Mean of Gaus", 0, -0.1, 0.1);
  RooRealVar sigma("sigma", "Width of gaus1", 1 ,0.1, 2);
  RooGaussian gauss("gauss", "gauss(dg,mean,sigma)",dg_pull, mean, sigma);
 RooFitResult* fitResult = gauss.fitTo(data, RooFit::Save());

  //plot
  TCanvas *c=new TCanvas("c", "c");
  RooPlot *xframe = dg_pull.frame(Title("residuals"), Bins(80));
  data.plotOn(xframe);
  gauss.plotOn(xframe);
  xframe->GetYaxis()->SetTitleOffset(1.1);
  xframe->GetXaxis()->SetTitleOffset(1);
  xframe->GetYaxis()->SetTitleSize(0.048);
  xframe->GetXaxis()->SetTitleSize(0.048);
  //xframe->SetTitle("dg pull");	
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





