#include "Inclusion.h"

void BinRmv(){

    int const nbins = 7;
    double_t xbins[nbins+1] = {700.0f/1000.0f, 1000.0f/1000.0f, 1.30f, 1.60f, 2.00f, 2.50f, 3.50f, 14.00f};
    
    TFile* file = new TFile("rapporto_accettanze.root");
    TH1F* acchist = (TH1F*)file->Get("Rapporto_accettanze");
    file->Close();
    TH1F *acchistnew = new TH1F("acc", "acc",nbins,xbins);
    
    for (int i = 0; i<nbins;i++ ){
      acchistnew->SetBinContent(i+1,acchist->GetBinContent(i+2));    
      acchistnew->SetBinError(i+1,acchist->GetBinError(i+2));   
    }
    
    TFile* file2 = new TFile("res_histo_short.root");
    TH1F* resshort = (TH1F*)file->Get("res_histo_short");
    file2->Close();
    TH1F *resshortnew = new TH1F("short", "short",nbins,xbins);
    
    for (int i = 0; i<nbins;i++ ){
      resshortnew->SetBinContent(i+1,acchist->GetBinContent(i+2));    
      resshortnew->SetBinError(i+1,acchist->GetBinError(i+2));   
    }
    
    TFile* file3 = new TFile("res_histo_star.root");
    TH1F* resstar = (TH1F*)file->Get("res_histo_star");
    file3->Close();
    TH1F *resstarnew = new TH1F("star", "star",nbins,xbins);
    
    for (int i = 0; i<nbins;i++ ){
      resstarnew->SetBinContent(i+1,acchist->GetBinContent(i+2));    
      resstarnew->SetBinError(i+1,acchist->GetBinError(i+2));   
    }
    
    TFile* file4 = new TFile("newacc.root", "RECREATE");
    acchistnew->Write();
    file4->Close();
    
    TFile* file5 = new TFile("star.root", "RECREATE");
    resstarnew->Write();
    file5->Close();
    
    TFile* file6 = new TFile("short.root", "RECREATE");
    resshortnew->Write();
    file6->Close();
    

}
