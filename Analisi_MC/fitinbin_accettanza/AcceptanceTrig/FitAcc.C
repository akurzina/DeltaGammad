#include "Inclusion.h"

//fitto le accettanze e genero il file contenente i risultati


void FitAcc() {

        gROOT->SetBatch(kFALSE);
        gROOT->Reset();
        gROOT->Clear();
        cout.precision(8);

        TH1::SetDefaultSumw2();
	
   	//Larghezze bin
	const int nbins=8;
        Double_t        xbins[nbins+1]={0.0005*1000,0.0007*1000,0.0010*1000,0.0013*1000,0.0016*1000,0.002*1000,0.0025*1000,0.0035*1000,0.014*1000};
          
        //importo quelle complessive
        TFile* fileshort = new TFile("acc_short.root");
        TH1F *accshort = (TH1F*)fileshort->Get("AccShort");
        accshort->Scale( 1./accshort->Integral());
       
        TFile* filestar = new TFile("acc_star.root");
        TH1F  *accstar = (TH1F*)filestar->Get("AccStar");
        accstar->Scale( 1./accstar->Integral());
        
        
        /*     
        TFile* fileratio = new TFile("rapporto_accettanze.root");
        TH1F *RatOverall = (TH1F*)fileratio->Get("Rapporto_accettanze");
        */
    
//Funzione da fittare
        TF1 *faccShort = new TF1("faccShort","[0]*(1+[1]*x)/(1+pow([2]*x,[3]))",0.5,14.);
        faccShort->SetParLimits(0,0.0001,10);
        faccShort->SetParLimits(1,-1e-6,1e6);
        faccShort->SetParLimits(2,0.1,100);
        faccShort->SetParLimits(3,1,2);
        
           
        TF1 *faccStar = new TF1("faccStar","[0] + x*[1]",0.5,14.);
        faccStar->SetParLimits(0,0.0827,0.084);
        faccStar->SetParLimits(1,-100,100);
      
 
        TCanvas *cshort = new TCanvas("cshort","cshort", 1020, 720);
        TLegend* legend = new TLegend(0.7, 0.7, 0.85, 0.85);
        //TLegend* legend = new TLegend(0.1, 0.1, 0.8, 0.8);
        legend->SetFillColor(kWhite);
        legend->SetLineColor(kWhite);
        TLegendEntry* entry1= legend->AddEntry("1", "Overall Acceptance", "L");
        entry1->SetLineColor(kBlue);
        TLegendEntry* entry2= legend->AddEntry("2", "Fit", "L");
        entry2->SetLineColor(kRed);
       // cshort->SetLogx();
        //accshort->SetLineColor(8);
        accshort->Fit("faccShort");
        TF1 *fshort = accshort->GetFunction("faccShort");
        cout<<"chi2 "<<fshort->GetChisquare();
	accshort->SetYTitle("(a.u.)");
	accshort->SetStats(0);
      	accshort->GetYaxis()->SetTitleOffset(1.1);
        accshort->GetXaxis()->SetTitleOffset(1);
        accshort->GetYaxis()->SetTitleSize(0.048);
        accshort->GetXaxis()->SetTitleSize(0.048);
	accshort->Draw();
        legend->Draw();     
         
       cshort->SaveAs("FittedAccShort.pdf");
        
        TCanvas *cstar  = new TCanvas("cstar","cstar", 1020,720);
        accstar->Fit("pol1");
        TF1 *fstar = accstar->GetFunction("pol1");
        //cout<<"chi2 "<<fstar->GetChisquare();
        accstar->SetXTitle("time (ps)");
	 accstar->SetYTitle("Acceptance (a.u.)");
	 accstar->SetStats(0);
      	 accstar->GetYaxis()->SetTitleOffset(1.1);
         accstar->GetXaxis()->SetTitleOffset(1);
         accstar->GetYaxis()->SetTitleSize(0.048);
         accstar->GetXaxis()->SetTitleSize(0.048);
        accstar->Draw();
        legend->Draw();
       // cstar->SetLogx();
        cstar->SaveAs("FittedAccStar.pdf");
   
   
   //salvo i risulati
        
        TFile* SaveShort= new TFile("AccShortFit.root", "RECREATE");
        fshort->Write();
        SaveShort->Close();
        
        
        TFile* SaveStar= new TFile("AccStarFit.root", "RECREATE");
        fstar->Write();
        SaveStar->Close();

}
