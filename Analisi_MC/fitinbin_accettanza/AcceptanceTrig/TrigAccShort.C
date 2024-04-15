#include "Inclusion.h"


void TrigAccShort() {

        gROOT->SetBatch(kTRUE);
        gROOT->Reset();
        gROOT->Clear();
        cout.precision(8);

        TH1::SetDefaultSumw2();

//Kshort
       // Importazione file e tree
	TChain *datatree1 = new TChain("DecayTree;1");
	datatree1->Add("/home/akurzina/Analisi_MC/Selezione_jpsikshort/Bd2JpsiKshort_MC_soloselec.root");
	
	TChain *datatree2 = new TChain("Bd2JpsiKstzMC/MCDecayTree;11");
	datatree2->Add("/home/akurzina/Analisi_MC/Selezione_jpsikshort/Bd2JpsiKshort_MC_final.root");
	
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
	
       
       	for (int i=0; i<datatree1->GetEntries(); i++) {
	  datatree1->GetEntry(i);
          true_selection = true_selection * 1000;
          den1->Fill(true_selection);
          den2->Fill(selection);
          
          }
       
       for (int i=0; i<datatree2->GetEntries(); i++) {
	  datatree2->GetEntry(i);
	  num1->Fill(true_trig_selection * 1000);
	  num2->Fill(true_trig_selection * 1000);
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
        
        can15->SaveAs("trig_acc_true_shortnum.pdf");
  
      
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
        
        can1->SaveAs("trig_acc_shortnum.pdf");
      
      
      
      
      
      
      //KSHORT
      
   /*   
      // Importazione file e tree
	TChain *datatree1_short = new TChain("DecayTree;1");
	datatree1_short->Add("/home/akurzina/Analisi_MC/Selezione_jpsikshort/Bd2JpsiKshort_MC_trig.root");
	
	TChain *datatree2_short = new TChain("Bd2JpsiKstzMC/MCDecayTree;11");
	datatree2_short->Add("/home/akurzina/Analisi_MC/Selezione_jpsikshort/Bd2JpsiKshort_MC_final.root");
  
  
	datatree1_short->SetBranchStatus("*",0);
	datatree1_short->SetBranchStatus("Bd_TRUETAU", 1);
	datatree1_short->SetBranchStatus("time", 1);
	datatree1_short->SetBranchStatus("Bd_LOKI_MASS_JpsiConstr", 1);
	datatree2_short->SetBranchStatus("*",0);
	datatree2_short->SetBranchStatus("B0_TRUETAU", 1);
   	

  
         //Accettanza
        //Creazione istogrammi
        TH1D *hm1_short=new TH1D("Istogramma1", "h1", nbins, xbins);
 	TH1D *hm_true_short=new TH1D("Bdtruetau", "Bdtruetaushort", nbins, xbins);
 	 	

       	double t_true_selected_short;
	double  t_true_MC_short;
	
	datatree1_short->SetBranchAddress("Bd_TRUETAU",&t_true_selected_short);
	datatree2_short->SetBranchAddress("B0_TRUETAU",&t_true_MC_short);
	
        for (int i=0; i<datatree1_short->GetEntries(); i++) {
	  datatree1_short->GetEntry(i);
	  hm1_short->Fill(t_true_selected_short * 1000);
          }
         
	for (int i=0; i<datatree2_short->GetEntries(); i++) {
	  datatree2_short->GetEntry(i);
          t_true_MC_short = t_true_MC_short * 1000;
          hm_true_short->Fill(t_true_MC_short);
         }
          
        TH1D *hm_acceptance_short = (TH1D*)hm1_short->Clone("TrigAccShort");
        hm_acceptance_short->Divide(hm_true_short);
	
        
        TCanvas *can15_short=new TCanvas("can15_short", "can15_short",1600, 1000);
        
        hm_acceptance_short->SetXTitle("time [ps]");
	hm_acceptance_short->SetYTitle("Acceptance [a.u.]");
	hm_acceptance_short->SetStats(0);
	//hm_acceptance->SetBins(nbins, xbins);
	//hm_acceptance->GetYaxis()->SetRangeUser(0.3, 0.4);
	can15_short->SetLogx();
	hm_acceptance_short->GetYaxis()->SetTitleOffset(1.1);
        hm_acceptance_short->GetXaxis()->SetTitleOffset(1);
        hm_acceptance_short->GetYaxis()->SetTitleSize(0.048);
        hm_acceptance_short->GetXaxis()->SetTitleSize(0.048);
	hm_acceptance_short->DrawNormalized();
        can15_short->SaveAs("accettanza_short_trig.pdf");
        
        //Rapporto accettanze 
        TH1D *rapporto_accettanze = (TH1D*)hm_acceptance->Clone("Rapporto_accettanze");
        rapporto_accettanze->Divide(hm_acceptance_short);
        rapporto_accettanze->SetTitle("Rapporto Accettanze");
        TCanvas *can_acc=new TCanvas("can_acc", "can_acc");
        rapporto_accettanze->GetXaxis()->SetTitle("time [ps]");
        rapporto_accettanze->SetStats(0);
        rapporto_accettanze->DrawNormalized();
        rapporto_accettanze->SaveAs("ratio_acc_trig.pdf");


//Salvo i file 
        
        TFile* file3= new TFile("rapporto_accettanze_trig.root", "RECREATE");
        rapporto_accettanze->Write();
        file3->Close();   
        
        
        //importo quelle complessive
        TFile* fileshort = new TFile("acc_short.root");
        TH1F *accshort = (TH1F*)fileshort->Get("AccShort");

        TFile* filestar = new TFile("acc_star.root");
        TH1F  *accstar = (TH1F*)filestar->Get("AccStar");
        
        
        TFile* fileratio = new TFile("rapporto_accettanze.root");
        TH1F *RatOverall = (TH1F*)fileratio->Get("Rapporto_accettanze");

         Double_t factor = 1.;
       //  accshort->Scale(factor/accshort->Integral());

         
         //hm_acceptance_short->Scale(factor/hm_acceptance_short->Integral());

     gROOT->SetBatch(kFALSE);
        
        //legend
       TLegend* legend = new TLegend(0.7, 0.7, 0.85, 0.85);
      //TLegend* legend = new TLegend(0.1, 0.1, 0.8, 0.8);
      legend->SetFillColor(kWhite);
      legend->SetLineColor(kWhite);
      TLegendEntry* entry1= legend->AddEntry("1", "Trigger", "L");
      entry1->SetLineColor(kBlue);
      TLegendEntry* entry2= legend->AddEntry("2", "Overall", "L");
      entry2->SetLineColor(kGreen);
        
        
        
//Plot confronto accettanze
        TCanvas *cshort = new TCanvas("cshort","cshort", 1020, 720);
        cshort->SetLogx();
        accshort->SetLineColor(8);
	hm_acceptance_short->SetYTitle("Acceptance (a.u.)");
	hm_acceptance_short->SetStats(0);
      	hm_acceptance_short->GetYaxis()->SetTitleOffset(1.1);
        hm_acceptance_short->GetXaxis()->SetTitleOffset(1);
        hm_acceptance_short->GetYaxis()->SetTitleSize(0.048);
        hm_acceptance_short->GetXaxis()->SetTitleSize(0.048);
	hm_acceptance_short->DrawNormalized();
        accshort->DrawNormalized("SAME");
      legend->Draw();     
      //  hs->Draw();
      //  cshort->SaveAs("confronto_short.pdf");
        
        
        TCanvas *cstar  = new TCanvas("cstar","cstar", 1020,720);
        accstar->SetLineColor(8);

        hm_acceptance->SetXTitle("time (ps)");
	 hm_acceptance->SetYTitle("Acceptance (a.u.)");
	 hm_acceptance->SetStats(0);
	  accstar->SetStats(0);
      	 hm_acceptance->GetYaxis()->SetTitleOffset(1.1);
         hm_acceptance->GetXaxis()->SetTitleOffset(1);
         hm_acceptance->GetYaxis()->SetTitleSize(0.048);
         hm_acceptance->GetXaxis()->SetTitleSize(0.048);
	
        accstar->DrawNormalized();
        hm_acceptance->DrawNormalized("SAME");
        legend->Draw();
        cstar->SetLogx();
        cstar->SaveAs("confronto_star.pdf");
        

       TCanvas *cratio  = new TCanvas("cratio","cratio", 1020,720);
        RatOverall->SetLineColor(8);

        rapporto_accettanze->SetXTitle("time (ps)");
	 rapporto_accettanze->SetYTitle("Acceptance ratio(a.u.)");
	 rapporto_accettanze->SetStats(0);
      	 rapporto_accettanze->GetYaxis()->SetTitleOffset(1.1);
         rapporto_accettanze->GetXaxis()->SetTitleOffset(1);
         rapporto_accettanze->GetYaxis()->SetTitleSize(0.048);
         rapporto_accettanze->GetXaxis()->SetTitleSize(0.048);
	 rapporto_accettanze->DrawNormalized();
        RatOverall->DrawNormalized("SAME");
        legend->Draw();
        cratio->SetLogx();
      //  cratio->SaveAs("confronto_star.pdf");

*/
}
