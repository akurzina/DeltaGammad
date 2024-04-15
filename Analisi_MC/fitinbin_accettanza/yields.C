#include "Inclusion.h"
//Fit in bin e accettanza



int FitPlot(double t1, double t2, int indice, TH1* mass_hist, bool kshort){
        
       //Parametri Ipatia
	RooRealVar BdMass("BdMass", "Bd Mass", 5280,5150, 5340,"MeV/c^{2}");
	RooRealVar lambda("lambda", "lambda", -8.85640e-04, -8.85640e-04, -8.85640e-04);
	RooRealVar zeta("zeta", "zeta", 1.7, 0., 3.);
	RooRealVar beta("beta", "beta", -0.01, -1000, 1000);
	RooRealVar sigma("sigma", "sigma", 8.1, 7.15956e+00, 10.);
	RooRealVar mu("mu", "mu", 5.28011e+03, 5275, 5285);
	RooRealVar a("a", "a",2.27877e+00, 2.27877e+00, 2.27877e+00);
	RooRealVar n("n", "n", 1.70881e+00, 0, 4);
	RooRealVar a2("a2", "a2", 2.26681e+00, 0, 5);
	RooRealVar n2("n2", "n2", 3.20017e+00, 2, 5);
	RooHypatia2 hypatia("hypatia", "Hypatia", BdMass, lambda, zeta, beta, sigma, mu, a, n, a2, n2);     
        
        RooDataHist data1("data", "data", BdMass, mass_hist);	
        
        hypatia.fitTo(data1,Save(kTRUE));
       
       //Plot
	TCanvas *c=new TCanvas("c", "c");
	RooPlot *xframe = BdMass.frame();
	//Plot Residuals
        TLatex lat;
        lat.SetTextSize(0.06);
        lat.SetTextAlign(13);
        double xLat = xframe->GetXaxis()->GetXmin() + 0.80 *(xframe->GetXaxis()->GetXmax()- xframe->GetXaxis()->GetXmin() );
        cout << "xLat: " << xLat << endl;
        double yLat = 0.8*xframe->GetMaximum();
        cout << "yLat: " << yLat << endl;
        gStyle->SetOptTitle(0);
      	c->Divide(2);
        c->GetPad(1)->SetPad(0.0,0.2,1.0,1.0);
        c->GetPad(2)->SetPad(0.0,0.0,1.0,0.2);
        c->GetPad(1)->SetLeftMargin(0.10);
        c->GetPad(2)->SetLeftMargin(0.10);
        c->GetPad(1)->SetRightMargin(0.10);
        c->GetPad(2)->SetRightMargin(0.10);
        c->GetPad(1)->SetBottomMargin(0.01);
        c->GetPad(2)->SetTopMargin(0.01);
        c->GetPad(2)->SetBottomMargin(0.55);
        c->cd(1);
	
	data1.plotOn(xframe);
	hypatia.plotOn(xframe, LineColor(kRed));
	
	xframe->GetYaxis()->SetTitleOffset(1.1);
        xframe->GetXaxis()->SetTitleOffset(1);
        xframe->GetYaxis()->SetTitleSize(0.048);
        xframe->GetXaxis()->SetTitleSize(0.048);
        xframe->SetTitle("");
	xframe->Draw();
	
	 //legend
	TLegend* legend = new TLegend(0.7, 0.7, 0.85, 0.85);
	legend->SetFillColor(kWhite);
	legend->SetLineColor(kWhite);
	TLegendEntry* entry1= legend->AddEntry("hypatia", "Fit", "L");
	entry1->SetLineColor(kRed);
	TLegendEntry* entry2= legend->AddEntry("mc", "MC", "lpe");
	//xframe->Draw();
	legend->Draw();
	
	
	c->cd(2);
        //Plot residuals
        //RooPlot *frameRes = PlotResiduals(xframe, hypatia);
        RooPlot *frameRes = (RooPlot*)xframe->emptyClone("pull");//getPlotVar()->xframe();
        RooHist *resHist = (RooHist*)xframe->pullHist();
        //RooHist *resHist = (RooHist*)xframe->pullHist("datahistogram","hypatia", kTRUE);
        //   for (int i = 0; i < resHist->GetN(); i++)
        //     resHist->SetPointError(i,0.,0.,0.,0.);
        resHist->SetFillColor(kBlue-9); //here
        frameRes->addObject(resHist,"E3") ;
        frameRes->SetMinimum(-6) ;
        frameRes->SetMaximum(+6) ;
        frameRes->SetTitle("");
        frameRes->GetXaxis()->SetTitle(xframe->GetXaxis()->GetTitle());
        
        frameRes->GetYaxis()->SetNdivisions(110);
        frameRes->GetYaxis()->SetLabelSize(0.);
        frameRes->GetYaxis()->SetTitle("Pull");
        frameRes->GetYaxis()->CenterTitle();
          frameRes->GetYaxis()->SetTitleSize(0.22);
          frameRes->GetYaxis()->SetTitleOffset(0.20);
          frameRes->GetXaxis()->SetNdivisions(xframe->GetXaxis()->GetNdivisions() );
          //  frameRes->Draw();
          TGaxis *xup = new TGaxis(-0.05,5.,0.05,5.,-0.05,0.05,510,"-");
          xup->SetLabelSize(0.);
          xup->SetNdivisions(xframe->GetXaxis()->GetNdivisions() );
          //  xup->Draw();
          TGaxis *yright = new TGaxis(0.05,-5.,0.05,5.,-5.,5.,510,"+L");
          yright->SetLabelSize(0.);
          yright->SetNdivisions(110);
            //  yright->Draw();
          TLine *lResup5 = new TLine(frameRes->GetXaxis()->GetXmin(),5.,
                                    frameRes->GetXaxis()->GetXmax(),5.);
	
	lResup5->SetLineColor(kRed+2);
          TLine *lResup = new TLine( frameRes->GetXaxis()->GetXmin(),3.,
                                    frameRes->GetXaxis()->GetXmax(),3.);
          lResup->SetLineColor(kRed+2);
          lResup->SetLineStyle(2);
          //  lResup->Draw();
          TLine *lResdw = new TLine( frameRes->GetXaxis()->GetXmin(), -3.,
                                    frameRes->GetXaxis()->GetXmax(),-3.);
          lResdw->SetLineColor(kRed+2);
          lResdw->SetLineStyle(2);

          TLine *lResdw5 = new TLine( frameRes->GetXaxis()->GetXmin(), -5.,
                                    frameRes->GetXaxis()->GetXmax(),-5.);
          lResdw5->SetLineColor(kRed+2);

          frameRes->addObject(lResup) ;
          frameRes->addObject(lResdw) ;
          frameRes->addObject(lResup5) ;
          frameRes->addObject(lResdw5) ;
        
        
          //TLatex lat;
          lat.SetTextSize(0.16);
          lat.SetTextAlign(32);

          frameRes->GetYaxis()->SetLabelSize(0.15);
          frameRes->GetYaxis()->SetNdivisions(505);
          //  frameRes->SetMinimum(0.85);
          //  frameRes->SetMaximum(1.15);
          frameRes->GetXaxis()->SetTitleOffset(1.1);
          frameRes->GetXaxis()->SetLabelSize(xframe->GetXaxis()->GetLabelSize()*4);
          frameRes->GetXaxis()->SetTitleSize(xframe->GetXaxis()->GetTitleSize()*4);
          frameRes->GetXaxis()->SetTitle(xframe->GetXaxis()->GetTitle());
          frameRes->Draw();
	
	

        
        TString name_plot_file;
        if (kshort == true){
           name_plot_file = Form("mass_fit_short_%d.pdf", indice);
        }

        if (kshort == false) {
           name_plot_file = Form("mass_fit_star_%d.pdf", indice);
        }
        
        
        
        c->SaveAs(name_plot_file);      
        return mass_hist->GetEntries();

}

void PlotEvents(TH1* event_hist, TString nome_canv){
      TCanvas *can_events= new TCanvas("can_events", nome_canv, 1600, 1000);
      event_hist->GetXaxis()->SetTitle("time (ps)");
      event_hist->GetYaxis()->SetTitle("Number of Events");
      event_hist->Draw();
      TString format = ".pdf";
      TString nome_file = nome_canv + format;
      can_events->SaveAs(nome_file);

}


void PlotAcceptance(TH1* acc_hist, TString nome_canv) {
      TCanvas *canacc= new TCanvas("canacc", nome_canv, 1600, 1000);
      acc_hist->GetXaxis()->SetTitle("time (ps)");
      acc_hist->GetYaxis()->SetTitle("Acceptance (a.u)");
      acc_hist->DrawNormalized();
      TString format = ".pdf";
      TString nome_file = nome_canv + format;
      canacc->SaveAs(nome_file);
}




void yields() {
        
        gROOT->SetBatch(kFALSE);
        gROOT->Reset();
        gROOT->Clear();
        cout.precision(8);
        
        TH1::SetDefaultSumw2();
        TLatex latt;

       // Importazione file e tree
        TChain *datatree1 = new TChain("DecayTree");
	datatree1->Add("/home/akurzina/Analisi_MC/Selezione_jpsikstar/B02JpsiKstar_2016_magDown_MC_Selected.root");
	
	TChain *datatree2 = new TChain("Bd2JpsiKstzMC/MCDecayTree;1");
	datatree2->Add("/home/akurzina/Analisi_MC/Selezione_jpsikstar/B02JpsiKstar_2016_magDown_MC.root");
  
	datatree1->SetBranchStatus("*",0);
	datatree1->SetBranchStatus("Bd_TRUETAU", 1);
	datatree1->SetBranchStatus("time", 1);
	datatree1->SetBranchStatus("Bd_LOKI_MASS_JpsiConstr", 1);
	datatree2->SetBranchStatus("*",0);
	datatree2->SetBranchStatus("B0_TRUETAU", 1);
  
  
   	cout<<"Inizio";
   	TChain *datatree1_short = new TChain("DecayTree;1");
	datatree1_short->Add("/home/akurzina/Analisi_MC/Selezione_jpsikshort/Bd2JpsiKshort_MC_selected.root");
	bool kshort = true;
	
	TChain *datatree2_short = new TChain("Bd2JpsiKstzMC/MCDecayTree;11");
	datatree2_short->Add("/home/akurzina/Analisi_MC/Selezione_jpsikshort/Bd2JpsiKshort_MC_final.root");
  
  
        cout<<"\n \n \n Importazione";
	
	datatree1_short->SetBranchStatus("*",0);
	datatree1_short->SetBranchStatus("Bd_TRUETAU", 1);
	datatree1_short->SetBranchStatus("time", 1);
	datatree1_short->SetBranchStatus("Bd_LOKI_MASS_JpsiConstr", 1);
	datatree2_short->SetBranchStatus("*",0);
	datatree2_short->SetBranchStatus("B0_TRUETAU", 1);	
   	   	
   	double Bd_mass;
   	float time;  	
   	datatree1_short->SetBranchAddress("Bd_LOKI_MASS_JpsiConstr", &Bd_mass);
   	datatree1_short->SetBranchAddress("time", &time);
   	
   	//Larghezze bin
        const int nbins=8;
        Double_t   xbins[nbins+1]={0.0005*1000,0.0007*1000,0.0010*1000,0.0013*1000,0.0016*1000,0.002*1000,0.0025*1000,0.0035*1000,0.014*1000};
 
          Double_t segnale_short[nbins];     
          cout<<"\n \n \n Pre for grande";
          //kshort 
          for(int i=0; i<nbins; i++){
                double t1 = xbins[i];
                double t2 = xbins[i+1];
     
                TH1D *mass_hist=new TH1D("mass_hist", "mass_hist", 100,5150,5340);
                
                cout<<"\n \n \n Ho definito l'istogramma";
                for (int iEntry = 0; iEntry < datatree1_short->GetEntries(); iEntry++) {
                      datatree1_short->GetEntry(iEntry);
                      // Applica la selezione temporale
                      if (time > t1 && time < t2) {
                          //cout<<"Riempo "<<iEntry;
                          mass_hist->Fill(Bd_mass);
                      }
                } 
                
                cout<<" \n \n \n prima di fitplot "<<i;
                segnale_short[i] = FitPlot(t1,t2,i,mass_hist, kshort);
                cout<<" \n \n \n dopo  fitplot "<<i;
          }

      //istogramma eventi segnale 
       TH1F *res_histo_short=new TH1F("res_histo_short", "res_histo_short",nbins, xbins);
        
        for(int k=0; k<nbins; k++){
            //Importante che gli indici siano così
            res_histo_short->SetBinContent(k+1,segnale_short[k]);
            res_histo_short->SetBinError(k+1,sqrt(segnale_short[k]));
        }

       //"Numero di eventi B_{d} #rightarrow J/#psi K*"
        TString name_hist_short = Form("Number_of_events_B_{d}_#rightarrow_J/#psi_K_{s}");
        PlotEvents(res_histo_short, name_hist_short);       

/*
        for(int j=0; j<nbins; j++){
          cout<<"\n \n \n Segnale short"<<segnale_short[j]<<" "<<j+1<<"\n \n";
        }
*/
       
        TFile* file2= new TFile("res_histo_short.root", "RECREATE");
        res_histo_short->Write();
        file2->Close();   



       //Accettanza kshort
       
        TH1D *hm1_short=new TH1D("Istogramma1", "h1", nbins, xbins);
 	TH1D *hm_true_short=new TH1D("Bdtruetau", "Bdtruetau", nbins, xbins);
      	
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
          
        TH1D *hm_acceptance_short = (TH1D*)hm1_short->Clone("AccShort");
        hm_acceptance_short->Divide(hm_true_short);
        
        TString name_acc = "Acceptance_kshort"; 
        PlotAcceptance(hm_acceptance_short, name_acc);

//kstar
        kshort = false;

        datatree1->SetBranchStatus("*",0);
	datatree1->SetBranchStatus("Bd_TRUETAU", 1);
	datatree1->SetBranchStatus("time", 1);
	datatree1->SetBranchStatus("Bd_LOKI_MASS_JpsiConstr", 1);
	datatree2->SetBranchStatus("*",0);
	datatree2->SetBranchStatus("B0_TRUETAU", 1);	
   	   	
   	double Bd_massstz;
   	float timestz;  	
   	datatree1->SetBranchAddress("Bd_LOKI_MASS_JpsiConstr", &Bd_massstz);
   	datatree1->SetBranchAddress("time", &timestz);

        double_t segnale_star[nbins];  
        for(int i=0; i<nbins; i++){
                double time1 = xbins[i];
                double time2 = xbins[i+1];
     
                TH1D *mass_hist=new TH1D("mass_hist", "mass_hist", 100,5100,5600);
                
                cout<<"\n \n \n Ho definito l'istogramma";
                for (int iEntry = 0; iEntry < datatree1->GetEntries(); iEntry++) {
                      datatree1->GetEntry(iEntry);
                      // Applica la selezione temporale
                      if (timestz > time1 && timestz < time2) {
                          //cout<<"Riempo "<<iEntry;
                          mass_hist->Fill(Bd_massstz);
                      }
                } 
                
                cout<<" \n \n \n prima di fitplot "<<i;
                segnale_star[i] = FitPlot(time1,time2,i,mass_hist, kshort);
                cout<<" \n \n \n dopo  fitplot "<<i;
          }

        //istogramma eventi segnale 
       TH1F *res_histo_star=new TH1F("res_histo_star", "res_histo_star",nbins, xbins);

       for(int k=0; k<nbins; k++){
            //Importante che gli indici siano così
            res_histo_star->SetBinContent(k+1,segnale_star[k]);
            res_histo_star->SetBinError(k+1,sqrt(segnale_star[k]));
        }

       //"Numero di eventi B_{d} #rightarrow J/#psi K*"
        TString name_hist_star = Form("Number_of_events_B_{d}_#rightarrow_J/#psi_K^{*}");
        PlotEvents(res_histo_star, name_hist_star);  

        TFile* file1= new TFile("res_histo_star.root", "RECREATE");
        res_histo_star->Write();
        file1->Close();  


//accettanza kstar
        TH1D *hm1_star=new TH1D("Istogramma1_star", " ", nbins, xbins);
 	TH1D *hm_true_star=new TH1D("Bd_true_tau_star", "Bd true tau", nbins, xbins);
      	
      	double t_true_selected_star;
	double  t_true_MC_star;
	
	datatree1->SetBranchAddress("Bd_TRUETAU",&t_true_selected_star);
	datatree2->SetBranchAddress("B0_TRUETAU",&t_true_MC_star);
	
        for (int i=0; i<datatree1->GetEntries(); i++) {
	  datatree1->GetEntry(i);
	  hm1_star->Fill(t_true_selected_star * 1000);
          }
         
	for (int i=0; i<datatree2->GetEntries(); i++) {
	  datatree2->GetEntry(i);
          t_true_MC_star = t_true_MC_star * 1000;
          hm_true_star->Fill(t_true_MC_star);
          }
          
        TH1D *hm_acceptance_star = (TH1D*)hm1_star->Clone("AccStar");
        hm_acceptance_star->Divide(hm_true_star);
        
        TString name_acc_star = "Acceptance_kstar"; 
        PlotAcceptance(hm_acceptance_star, name_acc_star);
        
        //rapporto accettanze
        TH1D *rapporto_accettanze = (TH1D*)hm_acceptance_star->Clone("Rapporto_accettanze");
        
        rapporto_accettanze->Divide(hm_acceptance_short);
        rapporto_accettanze->SetTitle("Rapporto Accettanze");
        TCanvas *can_acc=new TCanvas("can_acc", "can_acc");
        rapporto_accettanze->GetXaxis()->SetTitle("time (ps)");
        rapporto_accettanze->SetStats(0);
        rapporto_accettanze->DrawNormalized();
        //rapporto_accettanze->SaveAs("ratio_acc.pdf");
        
        
        //Saving the acceptance ratio in a tree
        TFile* file3= new TFile("rapporto_accettanze.root", "RECREATE");
        rapporto_accettanze->Write();
        file3->Close();  
        
        TFile* file4= new TFile("acc_short.root", "RECREATE");
        hm_acceptance_short->Write();
        file4->Close();   

        TFile* file5= new TFile("acc_star.root", "RECREATE");
        hm_acceptance_star->Write();
        file5->Close();

}




