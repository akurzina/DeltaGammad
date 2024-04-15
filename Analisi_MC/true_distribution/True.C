void LoadingTrue (){

    TChain *datatree_kstar = new TChain("Bd2JpsiKstzMC/MCDecayTree;11");
    datatree_kstar->Add("/home/akurzina/Analisi_MC/Selezione_jpsikshort/Bd2JpsiKshort_MC_final.root");

    TChain *datatree_kshort = new TChain("Bd2JpsiKstzMC/MCDecayTree;1");
    datatree_kshort->Add("/home/akurzina/Analisi_MC/Selezione_jpsikstar/B02JpsiKstar_2016_magDown_MC.root");

    datatree_kshort->SetBranchStatus("*",0);
    datatree_kshort->SetBranchStatus("B0_TRUETAU", 1);

    datatree_kstar->SetBranchStatus("*",0);
    datatree_kstar->SetBranchStatus("B0_TRUETAU", 1);
    
    double tkshort, tkstar;

    datatree_kstar->SetBranchAddress("B0_TRUETAU", &tkstar);
    datatree_kshort->SetBranchAddress("B0_TRUETAU", &tkshort);
    
    const int nbins=9;
    Double_t xbins[nbins]={0.0005*1000,0.0007*1000,0.0010*1000,0.0013*1000,0.0016*1000,0.002*1000,0.0025*1000,0.0035*1000,0.014*1000};
   
    TH1F *res_histo_star = new TH1F("res_histo_star", "res_histo_star",nbins-1, xbins);
    TH1F *res_histo_short = new TH1F("res_histo_short", "res_histo_short",nbins-1, xbins);
    
	for (int i=0; i<datatree_kstar->GetEntries(); i++) {
	  datatree_kstar->GetEntry(i);
          tkstar = tkstar * 1000;
          res_histo_star->Fill(tkstar);
        }    

	for (int i=0; i<datatree_kshort->GetEntries(); i++) {
	  datatree_kshort->GetEntry(i);
          tkshort = tkshort * 1000;
          res_histo_short->Fill(tkshort);
        } 

        TFile* file1= new TFile("res_histo_star.root", "RECREATE");
        res_histo_star->Write();
        file1->Close();
        
        TFile* file2= new TFile("res_histo_short.root", "RECREATE");
        res_histo_short->Write();
        file2->Close();   


}
