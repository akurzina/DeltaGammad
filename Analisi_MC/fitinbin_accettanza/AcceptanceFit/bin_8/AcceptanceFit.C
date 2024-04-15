#include "Inclusion.h"

void AcceptanceFit(){

        gROOT->SetBatch(kFALSE);
        gROOT->Reset();
        gROOT->Clear();
        cout.precision(8);

      //  TH1::SetDefaultSumw2();
       
       
        TFile* file = new TFile("rapporto_accettanze.root");
        TH1F* acchist = (TH1F*)file->Get("Rapporto_accettanze;1");

   
       const int nbins=8; //16
        Double_t xbins[nbins+1]={0.50f, 700.0f/1000.0f, 1000.0f/1000.0f, 1.30f, 1.60f, 2.00f, 2.50f, 3.50f, 14.00f};
    
      
        const  int n=3;
        TString modi[n] = {"linear", "pol2", "pol3"};
        
          
      for(int i=0; i<n; i++){
          if(modi[i]=="linear"){
           TCanvas *c1=new TCanvas("c1", "c1");
            acchist->Fit("pol1");
            acchist->SetTitle("acclinear");
            acchist->GetXaxis()->SetTitle("time (ps)");
            acchist->GetYaxis()->SetTitle("acceptance ratio(a.u.)");
            acchist->Draw();
            c1->SaveAs("acclinear.pdf");
            TFile* file1= new TFile("acc_lin.root", "RECREATE");
            acchist->Write();
            file1->Close(); 
        
            TF1 *lin_func = acchist->GetFunction("pol1");
            TH1F* lin_acc = new TH1F("lin_acc", "lin_acc", nbins, xbins);
            
            //AGGIUSTA I NOMI
            for(int i=0;i<nbins;i++){
              float scale_bin= lin_func->Eval(acchist->GetBinCenter(i+1));
              lin_acc->SetBinContent(i+1,scale_bin);
              lin_acc->SetBinError(i+1,acchist->GetBinError(i+1));
            }
            TCanvas *can1=new TCanvas("can1", "can1");
            lin_acc->DrawNormalized();
            TFile* file4= new TFile("acc_lin_hist.root", "RECREATE");
            lin_acc->Write();
            file4->Close();
         
        
        }
   	
         if(modi[i]=="pol2"){
           TCanvas *c2=new TCanvas("c2", "c2");
            acchist->Fit("pol2");
            acchist->SetTitle("accparab");
            acchist->GetXaxis()->SetTitle("time (ps)");
            acchist->GetYaxis()->SetTitle("acceptance ratio(a.u.)");
            acchist->Draw();
            c2->SaveAs("accparab.pdf");
            TFile* file2= new TFile("acc_quad.root", "RECREATE");
            acchist->Write();
            file2->Close(); 
            TF1 *parab_func = acchist->GetFunction("pol2");
            TH1F* parab_acc = new TH1F("parab_acc", "parab_acc", nbins, xbins);
            
            //AGGIUSTA I NOMI
            for(int i=0;i<nbins;i++){
              float bin= parab_func->Eval(acchist->GetBinCenter(i+1));
              parab_acc->SetBinContent(i+1,bin);
              parab_acc->SetBinError(i+1,acchist->GetBinError(i+1));
            }
            TCanvas *can2=new TCanvas("can2", "can2");
            parab_acc->DrawNormalized();
            TFile* file5= new TFile("acc_parab_hist.root", "RECREATE");
            parab_acc->Write();
            file5->Close();
        
        }
        
        /*
          if(modi[i]=="pol3"){
           TCanvas *c3=new TCanvas("c3", "c3");
            acchist->Fit("pol3");
            acchist->SetTitle("accpol3");
            acchist->GetXaxis()->SetTitle("time (ps)");
            acchist->GetYaxis()->SetTitle("acceptance ratio(a.u.)");
            acchist->Draw();
            c3->SaveAs("accpol3.pdf");
            TFile* file3= new TFile("acc_pol3.root", "RECREATE");
            acchist->Write();
            file3->Close(); 
        }
   	*/
   	
   	}
   	
   	
}

