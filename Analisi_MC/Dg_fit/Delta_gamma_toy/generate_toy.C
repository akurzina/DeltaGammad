#include "Inclusion.h"

void generate_toy(){
        
    gROOT->SetBatch(kFALSE);
    gROOT->Reset();
    gROOT->Clear();
    cout.precision(8);
    
    TH1::SetDefaultSumw2();
   
    double g = 0.6583;    
        
    TRandom3 randomGenerator;
        
    //Creare i due file -  choose one
    //TFile* file1= new TFile("res_histo_star_toy.root", "RECREATE");
    
    const int num = 500; //numero di istogrammi
    const int nbins=9;
    Double_t  xbins[nbins]={0.0005*1000,0.0007*1000,0.0010*1000,0.0013*1000,0.0016*1000,0.002*1000,0.0025*1000,0.0035*1000,0.014*1000};
    
    TFile* file1= new TFile("res_histo_short_toy.root", "RECREATE");
  
    for(int j=0; j<num; j++){
        int nDataPoints = randomGenerator.Gaus(300000,50000);
        TString name_hist = Form("istogramma_%d", j);

        // Crea un istogramma con il nome univoco
        TH1F* toy_hist = new TH1F(name_hist, Form("Titolo %s", name_hist.Data()), nbins-1, xbins);
        //TH1F* toy_hist = new TH1F(name_hist, Form("Titolo %s", name_hist.Data()), 80, 0.5, 14);
    
    // Genera dati casuali che seguono la funzione exp
            for (int i = 0; i < nDataPoints; ++i) {
                double x = randomGenerator.Exp(1/g) + randomGenerator.Gaus(0,0.1); // Genera x casualmente nell'intervallo desiderato
                //double x = randomGenerator.Exp(1/g);
                
                if(x > 0.5 && x < 14){
                     toy_hist->Fill(x);  
                }        
            }
           toy_hist->Write();
    } 
  
    file1->Close();
   
   TFile* file2= new TFile("res_histo_short_toy.root", "RECREATE");
  
    for(int j=0; j<num; j++){
        int nDataPoints2 = randomGenerator.Gaus(300000,50000);
        TString name_hist = Form("istogramma_%d", j);

        // Crea un istogramma con il nome univoco
        TH1F* toy_hist = new TH1F(name_hist, Form("Titolo %s", name_hist.Data()), nbins-1, xbins);
        //TH1F* toy_hist = new TH1F(name_hist, Form("Titolo %s", name_hist.Data()), 80, 0.5, 14);
    
    // Genera dati casuali che seguono la funzione exp con un errore
            for (int i = 0; i < nDataPointsw; ++i) {
                double x = randomGenerator.Exp(1/g) + randomGenerator.Gaus(0,0.1); // Genera x casualmente nell'intervallo desiderato
                //double x = randomGenerator.Exp(1/g);
                
                if(x > 0.5 && x < 14){
                     toy_hist->Fill(x);  
                }        
            }
           toy_hist->Write();
    } 
  
    file2->Close();





}

































/*
   TH1F* kshort_hist = new TH1F("rndm_kshort", "Dati Generati", nbins-1, xbins);

   int nDataPoints2 = randomGenerator.Gaus(100000,9000);
    for (int i = 0; i < nDataPoints2; ++i) {
        double x_short = randomGenerator.Exp(1/g) + randomGenerator3.Gaus(0,2); // Genera x casualmente nell'intervallo desiderato

        
        if(x_short > 0.5 && x_short < 14){
            kshort_hist->Fill(x_short);  
        }

    }
              
          
    TH1F* ratio = (TH1F*)toy_hist->Clone("star/short");
    ratio->Divide(kshort_hist);

     TCanvas *can=new TCanvas("can", "can");
     ratio->Draw();
  */








