#include "Inclusion.h"

double customPDF(double t, double g, double s, double m){
  
    double z = g *s/sqrt(2); 
    double x  = (t - m) / (sqrt(2) * s); 
 
    return exp(-pow(x,2)+pow(z-x,2)) * 0.5 * RooMath::erfc(z-x); 
 }
  

void generate_toy_res(){
        
    gROOT->SetBatch(kFALSE);
    gROOT->Reset();
    gROOT->Clear();
    cout.precision(8);
    
    TH1::SetDefaultSumw2();
   
    const int num = 10000; //numero di istogrammmi 
    const int nbins=9;
    Double_t  xbins[nbins]={0.0005*1000,0.0007*1000,0.0010*1000,0.0013*1000,0.0016*1000,0.002*1000,0.0025*1000,0.0035*1000,0.014*1000};
    double g = 0.6583;
    double s_short = 4.43e-2; //effective sigma   
    double m_short = -1.1e-4; //mean of gauss //-3.0e-4
    double s_star = 3.88e-2; //effective sigma   
    double m_star = -3.3e-4; //mean of gauss //-3.0e-4    
        
    TRandom3 randomGenerator;
        
    
    TFile* file1= new TFile("res_histo_short_toy.root", "RECREATE");
  
   
    for(int j=0; j<num; j++){
        int nDataPoints = randomGenerator.Gaus(300000,50000); //numero eventi
        TString name_hist = Form("istogramma_%d", j);

        // Crea un istogramma con il nome univoco
        TH1F* toy_hist = new TH1F(name_hist, Form("Titolo %s", name_hist.Data()), nbins-1, xbins);
        //TH1F* toy_hist = new TH1F(name_hist, Form("Titolo %s", name_hist.Data()), 80, 0.5, 14);
    
           // Genera dati casuali che seguono la funzione 
            for (int i = 0; i < nDataPoints; ++i) {
                double t = randomGenerator.Uniform(0.5, 14); // Genera un dato casuale in un intervallo
                double y = randomGenerator.Uniform(0, 1);  // Genera un valore tra 0 e 1 per confrontare con la tua PDF
                if (y <= customPDF(t, g, s_short, m_short)) {
                      toy_hist->Fill(t); 
                }
            }
           
           toy_hist->Write();
    } 
  
    file1->Close();

    TFile* file2= new TFile("res_histo_star_toy.root", "RECREATE");
  
   
    for(int j=0; j<num; j++){
        int nDataPoints = randomGenerator.Gaus(300000,50000); //numero eventi
        TString name_hist = Form("istogramma_%d", j);

        // Crea un istogramma con il nome univoco
        TH1F* toy_hist2 = new TH1F(name_hist, Form("Titolo %s", name_hist.Data()), nbins-1, xbins);
        //TH1F* toy_hist2 = new TH1F(name_hist, Form("Titolo %s", name_hist.Data()), 80, 0.5, 14);
    
           // Genera dati casuali che seguono la funzione 
            for (int i = 0; i < nDataPoints; ++i) {
                double t = randomGenerator.Uniform(0.5, 14); // Genera un dato casuale in un intervallo
                double y = randomGenerator.Uniform(0, 1);  // Genera un valore tra 0 e 1 per confrontare con la tua PDF
                if (y <= customPDF(t, g, s_star, m_star)) {
                      toy_hist2->Fill(t); 
                }
            }
           
           toy_hist2->Write();
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








