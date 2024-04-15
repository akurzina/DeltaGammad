#include "Inclusion.h"


void TrigAccStar() {

        gROOT->SetBatch(kTRUE);
        gROOT->Reset();
        gROOT->Clear();
        cout.precision(8);

        TH1::SetDefaultSumw2();

//KSTAR
       // Importazione file e tree
	TChain *datatree1 = new TChain("DecayTree");
	datatree1->Add("/home/akurzina/Analisi_MC/Selezione_jpsikstar/B02JpsiKstar_2016_magDown_MC_soloselec.root");
	
	TChain *datatree2 = new TChain("Bd2JpsiKstzMC/MCDecayTree;1");
	datatree2->Add("/home/akurzina/Analisi_MC/Selezione_jpsikstar/B02JpsiKstar_2016_magDown_MC.root");
  
	datatree1->SetBranchStatus("*",0);
	datatree1->SetBranchStatus("Bd_TRUETAU", 1);
	datatree1->SetBranchStatus("time", 1);
	datatree1->SetBranchStatus("Bd_LOKI_MASS_JpsiConstr", 1);
	datatree2->SetBranchStatus("*",0);
	datatree2->SetBranchStatus("B0_TRUETAU", 1);
   	
   	//Larghezze bin
	const int nbins=8;
        Double_t        xbins[nbins+1]={0.0005*1000,0.0007*1000,0.0010*1000,0.0013*1000,0.0016*1000,0.002*1000,0.0025*1000,0.0035*1000,0.014*1000};
        
    
         //Accettanza
        //Creazione istogrammi
        TH1D *num1=new TH1D("TrueSelectionTrig", "TrueSelectionTrig", nbins, xbins);
        TH1D *num2=new TH1D("TrueSelectionTrig2", "TrueSelectionTrig2", nbins, xbins);
 	TH1D *den1=new TH1D("TrueSelection", "TrueSelection", nbins, xbins);
 	TH1D *den2=new TH1D("Selection", "Selection", nbins, xbins);

       	double true_trig_selection;
	double  true_selection;
	float selection;
	
	datatree1->SetBranchAddress("Bd_TRUETAU",&true_selection);
	datatree1->SetBranchAddress("time",&selection);
	datatree2->SetBranchAddress("B0_TRUETAU",&true_trig_selection);
	
       
       
       for (int i=0; i<datatree2->GetEntries(); i++) {
	  datatree2->GetEntry(i);
	  num1->Fill(true_trig_selection * 1000);
          num2->Fill(true_trig_selection * 1000);
         }
         
	for (int i=0; i<datatree1->GetEntries(); i++) {
	  datatree1->GetEntry(i);
          true_selection = true_selection * 1000;
          den1->Fill(true_selection);
          den2->Fill(selection);
          
          }
       
        
     //True
      
        num1->Divide(den1);
        
        TCanvas *can15=new TCanvas("can15", "can15",1600, 1000);
        
        num1->SetXTitle("tempo di decadimento [ps]");
	num1->SetYTitle("Accettanza [a.u.]");
	//hm_acceptance->SetBins(nbins, xbins);
	//hm_acceptance->GetYaxis()->SetRangeUser(0.3, 0.4);
	can15->SetLogx();
	num1->SetStats(0);
	num1->GetYaxis()->SetTitleOffset(1.1);
        num1->GetXaxis()->SetTitleOffset(1);
        num1->GetYaxis()->SetTitleSize(0.048);
        num1->GetXaxis()->SetTitleSize(0.048);
	num1->DrawNormalized();
        
        can15->SaveAs("trig_acc_true_starnum.pdf");
  
      
      //Notrue
       
        num2->Divide(den2);
        
        TCanvas *can1=new TCanvas("c", "c",1600, 1000);
        
        num2->SetXTitle("tempo di decadimento [ps]");
	num2->SetYTitle("Accettanza [a.u.]");
	//hm_acceptance->SetBins(nbins, xbins);
	//hm_acceptance->GetYaxis()->SetRangeUser(0.3, 0.4);
	can1->SetLogx();
	num2->SetStats(0);
	num2->GetYaxis()->SetTitleOffset(1.1);
        num2->GetXaxis()->SetTitleOffset(1);
        num2->GetYaxis()->SetTitleSize(0.048);
        num2->GetXaxis()->SetTitleSize(0.048);
	num2->DrawNormalized();
        
        can1->SaveAs("trig_acc_starnum.pdf");
     
     
     
     
    }
