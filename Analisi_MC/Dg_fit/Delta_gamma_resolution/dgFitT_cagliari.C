

TH1F* makeHisto16(std::string name = "res_histo_star.root", std::string name2 = "res_histo_short.root"){

  //std::cout << "MakeHisto 16 Opening " << name <<  " " << name2 << std::endl;

std::vector<float> hbins8 = {0.50f, 700.0f/1000.0f, 1000.0f/1000.0f, 1.30f, 1.60f, 2.00f, 2.50f, 3.50f, 14.00f};
TH1F* h8Kstar = new TH1F("h8Kstar","Yields", hbins8.size()-1, &hbins8[0]); h8Kstar->Sumw2();
TH1F* h8Ks = new TH1F("h8Ks","Yields", hbins8.size()-1, &hbins8[0]); h8Ks->Sumw2();
TH1F* div = (TH1F*)h8Kstar->Clone("div");

 TFile* file = new TFile(name.c_str());
 TH1F* res_histo = (TH1F*)file->Get("res_histo_star");

 TFile* file2 = new TFile(name2.c_str());
 TH1F* res_histo2 = (TH1F*)file2->Get("res_histo_short");

 for (int i = 1; i <= res_histo->GetNbinsX(); ++i){
   h8Kstar->SetBinContent(i,res_histo->GetBinContent(i));
   h8Kstar->SetBinError(i,res_histo->GetBinError(i));


   h8Ks->SetBinContent(i,res_histo2->GetBinContent(i));
   h8Ks->SetBinError(i,res_histo2->GetBinError(i));
 }

 
 // Define the Canvas
 TCanvas *c = new TCanvas("c", "canvas", 850,600);

 /*
         for(int i=1; i<h8Kstar->GetEntries(); i++){
          res_histo->SetBinContent(i,segnale[i-1]);
          h8Kstar->SetBinError(i,sqrt(segnale[i-1]));
        }
 */
 

 
 // h1 settings
  h8Kstar->SetLineColor(kBlue+1);
  h8Kstar->SetLineWidth(2);
  h8Kstar->SetMinimum(10000);  // Define Y ..
  h8Kstar->SetMaximum(60000); // .. range
  h8Kstar->SetStats(0);          // No statistics on upper plot
  h8Kstar->GetXaxis()->SetTitle("time [ps]");
  h8Kstar->GetYaxis()->SetTitleSize(0.048);
  h8Kstar->GetXaxis()->SetTitleSize(0.048);
  h8Kstar->GetYaxis()->SetTitle("Events");
  
  h8Kstar->Draw("PEL");               // Draw h1
  h8Ks->SetLineColor(kRed);
  h8Ks->SetLineWidth(2);
  h8Ks->GetXaxis()->SetTitle("time [ps]");
 //h8Ks->GetYaxis()->SetTitleSize(0.048);
  //h8Ks->GetXaxis()->SetTitleSize(0.048);
  h8Ks->GetYaxis()->SetTitle("Events");
 
 h8Ks->Draw("PELSAME");         // Draw h2 on top of h1


  
  TLegend* legend = new TLegend(0.15, 0.75, 0.45, 0.88);
  legend->SetFillColor(kWhite);
  legend->SetLineColor(kWhite);
  TLegendEntry* entry1= legend->AddEntry("Star", "Numero di eventi B_{d} #rightarrow J/#psi K*", "L");
  entry1->SetLineColor(kBlue);
  TLegendEntry* entry2= legend->AddEntry("Star", "Numero di eventi B_{d} #rightarrow J/#psi K_{s}", "L");
  entry2->SetLineColor(kRed);
  legend->Draw();      
  
  
   TCanvas *c2 = new TCanvas("c2", "canvas", 850,600);
  // Define the ratio plot
  //TH1F* div = (TH1F*)h8Kstar->Clone("div");
  div->Divide(h8Kstar,h8Ks);
  div->SetLineColor(kBlack);
  //div->SetMinimum(0.1);  // Define Y ..
  //div->SetMaximum(3.5); // .. range
  //div->Sumw2();
  div->SetStats(0);      // No statistics on lower plot
  //div->Divide(h8Ks);
  //div->SetMarkerStyle(21);
  // Ratio plot (div) settings
 // div->SetTitle("Ratio"); // Remove the ratio title
  
    div->GetXaxis()->SetTitle("time [ps]");
 div->GetYaxis()->SetTitleSize(0.048);
 div->GetXaxis()->SetTitleSize(0.048);
  div->GetYaxis()->SetTitle("Ratio");
  //div->Draw("ep");       // Draw the ratio plot
  div->Draw("PE");
  c->Draw();

 //div->Divide(h8Ks);
 ////div->Divide(h8Kstar,h8Ks);
 //div->Draw();
 file->Close();
 file2->Close();
 return div;
}

/*
double evaluate(double g, double dg, double t1, double t2){

  // std::cout << g << " " << dg << " " << t1 << " " << t2 << std::endl;
  double v1 = g-0.5*dg;
  double v2 = g+0.5*dg;
  double fact = v1/v2;

  double top = exp(-v2*t2) - exp(-v2*t1);
  double bottom = exp(-v1*t2) - exp(-v1*t1);
  return top/bottom;
}
*/

double kstar_conv(double g, double dg, double t1, double t2){  
  double s = 3.88e-2; //effective sigma   
  double m = -3.3e-4; //mean of gauss 
  double za = (g - dg/2)*(s/sqrt(2)); 
  double zb=  (g + dg/2)*(s/sqrt(2));
  double x1  = (t1 - m) / (sqrt(2) * s); 
  double x2  = (t2 - m) / (sqrt(2) * s);

  double fadd_a1 = exp(pow(za-x1,2))*RooMath::erfc(za-x1);
  double fadd_b1 = exp(pow(zb-x1,2))*RooMath::erfc(zb-x1);
  double term1 = ((s / (4 * sqrt(2) * za)) * (RooMath::erf(x1) -  exp(-pow(x1,2)) * fadd_a1)) + ((s / (4 * sqrt(2) * zb)) * (RooMath::erf(x1) -  exp(-pow(x1,2)) * fadd_b1));
  
  double fadd_a2 = exp(pow(za-x2,2))*RooMath::erfc(za-x2);
  double fadd_b2 = exp(pow(zb-x2,2))*RooMath::erfc(zb-x2);
  double term2 = ((s / (4 * sqrt(2) * za)) * (RooMath::erf(x2) -  exp(-pow(x2,2)) * fadd_a2)) + ((s / (4 * sqrt(2) * zb)) * (RooMath::erf(x2) -  exp(-pow(x2,2)) * fadd_b2));

  double result = term2 - term1;
  return result;
}

double kshort_conv(double g, double dg, double t1, double t2){
  double cosbeta=0.7151;
  double s = 4.43e-2; //effective sigma   
  double m = -1.1e-4; //mean of gauss //-3.0e-4
  
  double za = (g - dg/2)*(s/sqrt(2)); 
  double zb=  (g+ dg/2)*(s/sqrt(2));
  double x1  = (t1 - m) / (sqrt(2) * s); 
  double x2  = (t2 - m) / (sqrt(2) * s);

  double fadd_a1 = exp(pow(za-x1,2))*RooMath::erfc(za-x1);
  double fadd_b1 = exp(pow(zb-x1,2))*RooMath::erfc(zb-x1);
  double term1 = ((1 + cosbeta) * s / (4 * sqrt(2) * za) * (RooMath::erf(x1) -  exp(-pow(x1,2)) * fadd_a1)) + ((1 - cosbeta) * s / (4 * sqrt(2) * zb) * (RooMath::erf(x1) -  exp(-pow(x1,2)) * fadd_b1));
  
  double fadd_a2 = exp(pow(za-x2,2))*RooMath::erfc(za-x2);
  double fadd_b2 = exp(pow(zb-x2,2))*RooMath::erfc(zb-x2);
  double term2 = ((1 + cosbeta) * s / (4 * sqrt(2) * za) * (RooMath::erf(x2) -  exp(-pow(x2,2)) * fadd_a2)) + ((1 - cosbeta) * s / (4 * sqrt(2) * zb) * (RooMath::erf(x2) -  exp(-pow(x2,2)) * fadd_b2));

  double result = term2 - term1;
  
  return result;
}

double evaluate(double g, double dg, double t1, double t2){

  // std::cout << g << " " << dg << " " << t1 << " " << t2 << std::endl;
  double cosbeta=0.7151;
  double coff=(2.*g+dg);

/*
  if (t2>1.30f){
    double top = (1./g)*(exp(-g*t1) - exp(-g*t2));
    double bottom = (1./g)* (exp(-g*t1) - exp(-g*t2))+(cosbeta*dg)/(2*g*g)*(exp(-g*t1) * (1+g * t1)-exp(-g*t2) *(1+g*t2));
    return top/bottom;
  }
*/


  if (t2>1.30f){
    double top = (1. / (dg - 2*g)) * exp((-g+dg/2) * t2) - (1./ (2*g + dg) * exp((-g - dg/2)*t2))-(1. / (dg - 2*g)) * exp((-g+dg/2) * t1) + (1./ (2*g + dg)*exp((-g -dg/2)*t1));
    double bottom = (1+cosbeta)/ (dg - 2*g) * exp((-g+dg/2) * t2) - (1-cosbeta)/ (2*g + dg) * exp((-g - dg/2)*t2)- ((1+cosbeta) / (dg - 2*g) * exp((-g+dg/2) * t1)) + (1-cosbeta)/ (2*g + dg) * exp((-g - (dg/2))*t1);
    return top/bottom;
   }

 
 else{
    double top = kstar_conv(g,dg,t1,t2);
    double bottom = kshort_conv(g,dg,t1,t2);
    return top/bottom;
  }
}

TH1F* g_histo;

double myfcn(const double* x) {

  double chi2=0;
  for (int i =1; i<= g_histo->GetNbinsX(); ++i){
    double val =  g_histo->GetBinContent(i);
    double s2 = g_histo->GetBinError(i)*g_histo->GetBinError(i);
    double expected = x[2]*evaluate(x[0],x[1],g_histo->GetBinLowEdge(i),g_histo->GetBinLowEdge(i) + g_histo->GetBinWidth(i));
    chi2 += std::pow(expected-val,2)/s2;

   std::cout << "chi2 " << chi2 << " x[0] "<< x[0] << " " << " x[1] " << x[1] << " x[2] " << x[2] << " expected " << expected << " value " << val << std::endl;
 }
  return chi2;
}

TH1F* histoResult(double g, double dg, double N){

  TH1F* reshisto = (TH1F*)g_histo->Clone("res_histo");
  for (int i =1; i<= reshisto->GetNbinsX(); ++i){
    double expected = N*evaluate(g,dg, reshisto->GetBinLowEdge(i),reshisto->GetBinLowEdge(i) + reshisto->GetBinWidth(i));
    reshisto->SetLineWidth(2);
    reshisto->SetBinContent(i,expected);
  }
  return reshisto;
}

typedef struct{
double value;
double error;

} ValueWithError;

typedef struct {
  ValueWithError N;
  ValueWithError dg;

} Result;

Result dgFitT(TH1F* hacc,TH1F* h, bool mplot,std::string canname, double gammaval =  0.6583){

  ROOT::Math::Minimizer* min = new ROOT::Minuit2::Minuit2Minimizer();
  min->SetMaxFunctionCalls(1000000);
  min->SetTolerance(0.0000001);
  min->SetPrintLevel(1);

  ROOT::Math::Functor f(&myfcn,3);
  //perchè abbiamo un 2?
  double variable[3] = {gammaval,0.001, 2.};
  double step[3] = {0.01,0.00001,0.0001};
  min->SetFunction(f);

  //actual division for the acceptance
  TH1F* temp = (TH1F*)h->Clone("temp");
  if (hacc) temp->Divide(hacc);
  g_histo = temp;

  min->SetVariable(0,"fit_g",variable[0], step[0]);
  min->SetLimitedVariable(1,"fit_dg",variable[1], step[1], -0.15, 0.35);
  min->SetLimitedVariable(2,"N",variable[2], step[2], -0.2, 2.5);
  min->FixVariable(0);

  min->Minimize();
  min->Hesse();

  Result res;
  res.dg.value =  min->X()[1];
  res.dg.error = min->Errors()[1];
  res.N.value =  min->X()[2];
  res.N.error = min->Errors()[2];

  if (mplot){

    TLatex lat;
    lat.SetTextSize(0.06);
    lat.SetTextAlign(13);

      TH1F* rh = histoResult( min->X()[0],  min->X()[1],  min->X()[2] );
      TCanvas* can = new TCanvas("can","can", 850,600);
      rh->SetLineColor(2);
      //double themax = TMath::Max(g_histo->GetMaximum(),rh->GetMaximum());
      //g_histo->SetMaximum(themax);
      g_histo->SetMinimum(0.7);
     // g_histo->GetYaxis()->SetTitleFont(132);
      //g_histo->GetYaxis()->SetLabelOffset(1.06);
      g_histo->GetYaxis()->SetTitle("Arbitary Units");
      g_histo->GetXaxis()->SetTitle("t [ps]");
    
      g_histo->Draw("PE");
      rh->Draw("HISTOSAME");
      lat.DrawLatex(10,0.75,"LHCb MC");
      //g_histo->Draw("PSAME");
      //LEGEND
      /*
      TLegend* legend2 = new TLegend(0.15, 0.75, 0.45, 0.88);
      legend2->SetFillColor(kWhite);
      legend2->SetLineColor(kWhite);
      TLegendEntry* entry12= legend2->AddEntry("mc", "MC", "PL");
      TLegendEntry* entry22= legend2->AddEntry("fit", "Fit", "L");
      entry22->SetLineColor(kRed);
      legend2->Draw();      
      */
      
      
      can->Print(canname.c_str());
      min->PrintResults();

      //
      if (hacc){
	TCanvas* cana = new TCanvas("cana","Acceptance", 800,600);
        gROOT->SetBatch(kFALSE);
        gROOT->Reset();
        gROOT->Clear();
        cout.precision(8);

        TH1::SetDefaultSumw2();
	
	hacc->SetMinimum(2.8);
	//hacc->GetYaxis()->SetTitleFont(132);
        hacc->GetYaxis()->SetTitleOffset(1.2);
        hacc->GetYaxis()->SetTitle("Acceptance Ratio [a.u.]");
        hacc->GetXaxis()->SetTitle("time [ps]");
        hacc->SetTitle(" ");
	hacc->DrawNormalized("HISTO");
	std::string aname = "bacc_"+canname;
	cana->Print(aname.c_str());
      }
   }

  delete min;
  if (!mplot )delete temp;
  return res;
}

Result runFits(std::string Kstarname,std::string Ksname, std::string name = "2016-linear.root",std::string dset= "2016", bool mplot = false , std::string hname = "h8_bc",double gammaval =  0.6583){


  std::string canname =  name.substr(0,name.size() - 5) + ".pdf";

  //gROOT -> ProcessLine( ".x lhcbStyle.C" );
  //gStyle -> SetErrorX(0.);

  //std::cout << "runFits: "  << Kstarname << " and: " << Ksname << " Dataset: " << dset << std::endl;

  TH1F* h;
  if (dset == "2016") h= makeHisto16(Kstarname,Ksname);

  std::cout << "runFits after makeHisto16 "  << std::endl;

  //std::cout << "h " << h<< std::endl;
  //TCanvas *cratio = new TCanvas("cratio", "canvas ratio", 1000,400);
  //h->Draw();
  //cratio->Draw();
  //Result res3;
  //return res3;


  // std::string haccname = "hdiv";
  TH1F* hacc = 0;
  if (name != "NONE") {
     TFile* fileAcc = new TFile(name.c_str());
     hacc = (TH1F*)fileAcc->Get(hname.c_str());
     /*
     TCanvas *cacc = new TCanvas("cacc", "canvas ratio", 1000,400);
     hacc->Draw();
     cacc->Draw();
     */
  }

  //std::cout << "Call dgFit. Canname:   " << canname  << std::endl;

  Result res = dgFitT(hacc,h,1,canname,gammaval);
  std::cout << res.dg.value << " "<< res.dg.error << std::endl;
  return res;
}
  /*
  TH1F* histo = new TH1F("histo","histo",100, 0, 0.15); histo->Sumw2();

  for (auto i = 0; i < 500; ++i){
    std::string haccname = "s"+std::to_string(i)+"_"+hname;
    TH1F* hacc = (TH1F*)fileAcc->Get(haccname.c_str());
    Result res = dgFitT(hacc,h,mplot);
    histo->Fill(res.dg.value);
  }

  histo->Draw();
}
*/


ValueWithError weightedAvg(std::vector<ValueWithError>& vals){

  double sumWeight = 0; double avg = 0;
  for (auto& m : vals){
    double w2 = 1/(m.error*m.error);
    avg += m.value*w2;
    sumWeight += w2;
  }

  ValueWithError theResult = {avg/sumWeight, sqrt(1/sumWeight)};

  std::cout << "weightedAvg: "  << avg/sumWeight << " Error: " << sqrt(1/sumWeight) <<  std::endl;

  // calc chi2
  double chi2 = 0;
  for (auto& m : vals){
    chi2+= pow(m.value-theResult.value,2.)/(m.error*m.error);
  }
  std::cout << "chi2 " <<  chi2 << " Prob chi2 " << TMath::Prob(chi2,vals.size()-1) << std::endl;
  return theResult;
}

  //std::cout <<  "I am here" <<  std::endl;

  std::vector<std::string> accslinear = {"rapporto_accettanze.root"};
  std::vector<std::string> accsquad = {"new_2016-quad.root"};
  std::vector<std::string> accsparab = {"new_2016-parab.root"};
  std::vector<std::string> accsNONE = {"NONE"};

   /// J[si Kshort /////
  std::vector<std::string> Ksdefaults = {"res_histo_short.root"};

   /// J[si Kstar /////
  std::vector<std::string> defaultFiles = {"res_histo_star.root"};


void run4(std::vector<std::string> files = defaultFiles, std::vector<std::string> Ksfiles = Ksdefaults,std::string accform = "NONE", std::string hname = "h8_bc",double gammaval =  0.6583){

  std::vector<std::string> datasets ={"2016"};
  std::vector<std::string> accs;
  if (accform == "quad"){
    accs = accsquad;
  }
  else if (accform == "parab"){
    accs = accsparab;
  }
  else if (accform == "NONE"){
    accs = accsNONE;
  }
  else {
    accs = accslinear;
  }

  //std::cout << "run4: "  << files[1] << " and " << Ksfiles[1] << " Acceptance: " << accs[1] <<  std::endl;

  std::vector<ValueWithError> vals;
  for (int i = 0; i<datasets.size(); ++i){
    std::cout << "run4 cycle: "  << i << std::endl;
    Result res = runFits(files[i],Ksfiles[i],accs[i],datasets[i], true, hname,gammaval);
    vals.push_back(res.dg);
  }

  ValueWithError wavg =  weightedAvg(vals);
  std::cout << wavg.value << " " << wavg.error<<std::endl;

}


void altfits(){

   //file Jpsi Kstar
   std::vector<std::string> files = {"res_histo_star.root"};
   //file Jpsi Kshort
   std::vector<std::string> Ksdefaults = {"res_histo_short.root"};

   //std::cout << "Altfits: "  << files[1] << " and " << Ksdefaults[1] << std::endl;

// run4(files, Ksdefaults, " ", "hdiv", 0.6583);  // for binned approach //
 //run4(files, Ksdefaults, "NONE", "h8_bc", 0.6583); // no acceptance h8_bc= name acceptance
  run4(files, Ksdefaults, "linear", "Rapporto_accettanze", 0.6583);
// run4(files, Ksdefaults, "parab", "h8_bc", 0.6583);
// run4(files, Ks defaults, "quad", "h8_bc", 0.6583);

}
