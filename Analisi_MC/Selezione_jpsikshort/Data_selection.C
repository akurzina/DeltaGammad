//////////////////////////////////////////////////////////////////////////
// to use it:
// make Data_selection
// ./Data_selection
/////////////////////////////////////////////////////////////////////////


#include "Inclusion.h" //oppure #include "/path/to/file/Inclusion.h"
//Seleziona i dati B0->JpsiKshort
//


void Data_selection() {

  //Importazione tree originale
	TChain *datatree = new TChain("Bd2JpsiKstz/DecayTree;8");
	datatree->Add("Bd2JpsiKshort_MC_final.root");

  //Variabili Trigger
 	bool Bd_L0Global_TOS, Bd_Hlt1DiMuonHighMassDecision_TOS, Bd_Hlt2DiMuonDetachedJPsiDecision_TOS, Bd_Hlt2DiMuonJPsiDecision_TOS;
  //Variabili Stripping
        double muminus_PT, muminus_PIDmu, muplus_PT, muplus_PIDmu, piminus_PIDK, piplus_PIDK;
        double Jpsi_ENDVERTEX_CHI2, Jpsi_M, Jpsi_FDCHI2_OWNPV;
        int  Jpsi_ENDVERTEX_NDOF;
       
        double piplus_PT, piminus_PT, piplus_P, piminus_P;
	double muminus_TRACK_CHI2NDOF, muplus_TRACK_CHI2NDOF, piminus_TRACK_CHI2NDOF, piplus_TRACK_CHI2NDOF;
	double Ks_PT, Ks_ENDVERTEX_CHI2, Ks_FDCHI2_OWNPV;
	int Ks_ENDVERTEX_NDOF;
	double Ks_M;
	double Bd_LOKI_MASS_JpsiConstr, Bd_IPCHI2_OWNPV, Bd_MINIPCHI2NEXTBEST;
        double muplus_LOKI_ETA, muminus_LOKI_ETA, piplus_LOKI_ETA, piminus_LOKI_ETA;
        float Bd_PVConst_PV_Chi2[10], Bd_PVConst_ctau[10],  Bd_PVConst_PV_Ndof[10] ;

	double c = 2.99792458E11; //velocita luce
  	double ps = pow(10, -12); //picosecondi

	datatree->SetBranchStatus("*",0);
	datatree->SetBranchStatus("Bd_L0Global_TOS", 1);
        datatree->SetBranchStatus("Bd_Hlt1DiMuonHighMassDecision_TOS", 1);
        datatree->SetBranchStatus("Bd_Hlt2DiMuonDetachedJPsiDecision_TOS",1);
	datatree->SetBranchStatus("Bd_Hlt2DiMuonJPsiDecision_TOS",1);
	datatree->SetBranchStatus("muminus_PT", 1);
	datatree->SetBranchStatus("muplus_PT", 1);
	datatree->SetBranchStatus("muminus_PIDmu", 1);
	datatree->SetBranchStatus("muplus_PIDmu", 1);
	datatree->SetBranchStatus("piminus_PIDK", 1);
	datatree->SetBranchStatus("piplus_PIDK", 1);
	
	datatree->SetBranchStatus("Jpsi_ENDVERTEX_CHI2", 1);
	datatree->SetBranchStatus("Jpsi_ENDVERTEX_NDOF", 1);
	datatree->SetBranchStatus("Jpsi_M", 1);
	datatree->SetBranchStatus("Jpsi_FDCHI2_OWNPV", 1);
	datatree->SetBranchStatus("piplus_PT", 1);
	datatree->SetBranchStatus("piminus_PT", 1);
	datatree->SetBranchStatus("piplus_P", 1);
	datatree->SetBranchStatus("piminus_P", 1);
	datatree->SetBranchStatus("muminus_TRACK_CHI2NDOF", 1);
	datatree->SetBranchStatus("muplus_TRACK_CHI2NDOF", 1);
	datatree->SetBranchStatus("piminus_TRACK_CHI2NDOF", 1);
	datatree->SetBranchStatus("piplus_TRACK_CHI2NDOF", 1);
        datatree->SetBranchStatus("Ks_PT", 1);
        datatree->SetBranchStatus("Ks_ENDVERTEX_CHI2", 1);
        datatree->SetBranchStatus("Ks_ENDVERTEX_NDOF", 1);
        datatree->SetBranchStatus("Ks_FDCHI2_OWNPV", 1);
        datatree->SetBranchStatus("Ks_M", 1);
        datatree->SetBranchStatus("Bd_LOKI_MASS_JpsiConstr", 1);
	datatree->SetBranchStatus("Bd_IPCHI2_OWNPV", 1);
	datatree->SetBranchStatus("Bd_MINIPCHI2NEXTBEST", 1);
	datatree->SetBranchStatus("Bd_PVConst_PV_Chi2", 1);
	datatree->SetBranchStatus("Bd_PVConst_PV_Ndof", 1);
	datatree->SetBranchStatus("Bd_PVConst_ctau", 1);
        datatree->SetBranchStatus("Bd_TRUETAU", 1);
	
	datatree->SetBranchStatus("muplus_LOKI_ETA", 1);
	datatree->SetBranchStatus("muminus_LOKI_ETA", 1);
	datatree->SetBranchStatus("piplus_LOKI_ETA", 1);
	datatree->SetBranchStatus("piminus_LOKI_ETA", 1);

	
	
	
	
	datatree->SetBranchAddress("Bd_L0Global_TOS", &Bd_L0Global_TOS);
 	datatree->SetBranchAddress("Bd_Hlt1DiMuonHighMassDecision_TOS", &Bd_Hlt1DiMuonHighMassDecision_TOS);
        datatree->SetBranchAddress("Bd_Hlt2DiMuonDetachedJPsiDecision_TOS", &Bd_Hlt2DiMuonDetachedJPsiDecision_TOS);
	datatree->SetBranchAddress("Bd_Hlt2DiMuonJPsiDecision_TOS", &Bd_Hlt2DiMuonJPsiDecision_TOS);
        datatree->SetBranchAddress("muminus_PT", &muminus_PT);
        datatree->SetBranchAddress("muplus_PT", &muplus_PT);
	datatree->SetBranchAddress("muminus_PIDmu", &muminus_PIDmu);
 	datatree->SetBranchAddress("muplus_PIDmu", &muplus_PIDmu);
 	
 	datatree->SetBranchAddress("piminus_PIDK", &piminus_PIDK);
 	datatree->SetBranchAddress("piplus_PIDK", &piplus_PIDK);
 	
 	datatree->SetBranchAddress("Jpsi_ENDVERTEX_CHI2", &Jpsi_ENDVERTEX_CHI2);
 	datatree->SetBranchAddress("Jpsi_ENDVERTEX_NDOF", &Jpsi_ENDVERTEX_NDOF);
 	datatree->SetBranchAddress("Jpsi_M", &Jpsi_M);
 	datatree->SetBranchAddress("Jpsi_FDCHI2_OWNPV", &Jpsi_FDCHI2_OWNPV);
 	datatree->SetBranchAddress("piplus_PT", &piplus_PT);
 	datatree->SetBranchAddress("piminus_PT", &piminus_PT);
 	datatree->SetBranchAddress("piplus_P", &piplus_P);
 	datatree->SetBranchAddress("piminus_P", &piminus_P);
 	datatree->SetBranchAddress("muminus_TRACK_CHI2NDOF", &muminus_TRACK_CHI2NDOF);
   	datatree->SetBranchAddress("muplus_TRACK_CHI2NDOF", &muplus_TRACK_CHI2NDOF);
   	datatree->SetBranchAddress("piminus_TRACK_CHI2NDOF", &piminus_TRACK_CHI2NDOF);
 	datatree->SetBranchAddress("piplus_TRACK_CHI2NDOF", &piplus_TRACK_CHI2NDOF);
 	datatree->SetBranchAddress("Ks_PT", &Ks_PT);
 	datatree->SetBranchAddress("Ks_ENDVERTEX_CHI2", &Ks_ENDVERTEX_CHI2);
 	datatree->SetBranchAddress("Ks_ENDVERTEX_NDOF", &Ks_ENDVERTEX_NDOF);
 	datatree->SetBranchAddress("Ks_FDCHI2_OWNPV", &Ks_FDCHI2_OWNPV);
       	datatree->SetBranchAddress("Ks_M", &Ks_M);
 	datatree->SetBranchAddress("Bd_LOKI_MASS_JpsiConstr", &Bd_LOKI_MASS_JpsiConstr);
 	datatree->SetBranchAddress("Bd_IPCHI2_OWNPV", &Bd_IPCHI2_OWNPV);
 	datatree->SetBranchAddress("Bd_MINIPCHI2NEXTBEST", &Bd_MINIPCHI2NEXTBEST);
 	datatree->SetBranchAddress("Bd_PVConst_PV_Chi2", &Bd_PVConst_PV_Chi2);
 	datatree->SetBranchAddress("Bd_PVConst_PV_Ndof", &Bd_PVConst_PV_Ndof);
	datatree->SetBranchAddress("Bd_PVConst_ctau", &Bd_PVConst_ctau);
 	
 	datatree->SetBranchAddress("muplus_LOKI_ETA", &muplus_LOKI_ETA);
	datatree->SetBranchAddress("muminus_LOKI_ETA", &muminus_LOKI_ETA);
	datatree->SetBranchAddress("piplus_LOKI_ETA", &piplus_LOKI_ETA);
	datatree->SetBranchAddress("piminus_LOKI_ETA", &piminus_LOKI_ETA);
    
 	
	//Creo nuovo tree
 	TFile newfile("Bd2JpsiKshort_MC_selected.root", "recreate");
 	auto newtree = datatree->CloneTree(0);
	float time;
	newtree->Branch("time", &time, "time/F");

//datatree->GetEntries()

	for(int i=0; i<datatree->GetEntries(); i++){

 		datatree->GetEntry(i);

		time = Bd_PVConst_ctau[0]/c/ps;
 		//Controllo Trigger
 		//
 
        if(Bd_L0Global_TOS != 1 || Bd_Hlt1DiMuonHighMassDecision_TOS != 1 || (Bd_Hlt2DiMuonDetachedJPsiDecision_TOS != 1 && Bd_Hlt2DiMuonJPsiDecision_TOS != 1) ){ continue;}

 		//Stripping

 		if(muminus_PIDmu <= 0 ||  muplus_PIDmu <= 0 ){continue;	}

 		if(muminus_PT <= 500 ||  muplus_PT <= 500 ){continue;	}
 		
 		if((Jpsi_ENDVERTEX_CHI2/Jpsi_ENDVERTEX_NDOF) >= 16){continue;	}

 		if(Jpsi_M < 3030 ||  Jpsi_M > 3150){continue;	}

 		//if(Jpsi_FDCHI2_OWNPV < 3){continue;	}

                if(muplus_TRACK_CHI2NDOF > 4 || muminus_TRACK_CHI2NDOF > 4){continue;	}
 		
 		if(piplus_TRACK_CHI2NDOF > 4 || piminus_TRACK_CHI2NDOF > 4){continue;	}

                if (piminus_PIDK > 0 || piplus_PIDK > 0 ){continue;	}
                
                if(piminus_PT < 250 || piplus_PT < 250){continue;	}

                if(piminus_P < 2000 || piplus_P < 2000){continue;	}

 		if(Ks_PT < 1000){continue;	}
 		
 		if(Ks_ENDVERTEX_CHI2 / Ks_ENDVERTEX_NDOF > 25){continue;	}
 		
 		// if(Ks_FDCHI2_OWNPV < 3){continue;	}
 		
 		if(Ks_M > 512 || Ks_M < 482  ){continue;	}

		if(Bd_LOKI_MASS_JpsiConstr < 5150 || Bd_LOKI_MASS_JpsiConstr > 5340){continue;	}

 		if(Bd_IPCHI2_OWNPV > 25){continue;	}

 		if(Bd_MINIPCHI2NEXTBEST < 50 && Bd_MINIPCHI2NEXTBEST != (-1)){continue;	}

 		if((Bd_PVConst_PV_Chi2[0] / Bd_PVConst_PV_Ndof[0])  > 5){continue;	}

 		if((Bd_PVConst_ctau[0]/c/ps ) < (0.45) || (Bd_PVConst_ctau[0]/c/ps) > (14) ){continue;	}

		if((muplus_LOKI_ETA < 2 || muplus_LOKI_ETA > 5) || (muminus_LOKI_ETA < 2 || muminus_LOKI_ETA > 5) ||
		   (piplus_LOKI_ETA < 2 || piplus_LOKI_ETA > 5) || (piminus_LOKI_ETA < 2 || piminus_LOKI_ETA > 5)){continue;	}
		
		
		//newtree->CopyEntries(datatree);
 		newtree->Fill();
    	}

 	newtree->Print();
 	newfile.Write("", TObject::kOverwrite);

}


int main( int argv, const char * argc[] )
{
    Data_selection();
		cout << "The end" << endl;
    return 0;
}


