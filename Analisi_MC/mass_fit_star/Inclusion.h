        //Inclusions to make a Root script executable
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <fstream>
#include "TROOT.h"
#include "TRootCanvas.h"
#include "TRootEmbeddedCanvas.h"
#include "TCanvas.h"
//#include "/opt/root/hist/inc/TH1.h"
#include <TH1.h>
#include "TH2.h"
#include "TH3.h"
#include "TH2F.h"
#include "TH1F.h"
#include "TFile.h"
#include "TVectorD.h"
//#include "/opt/root/matrix/inc/TMatrixT.h"
#include <TMatrixT.h>
#include "TTime.h"
#include "TTimeStamp.h"
#include "TTree.h"
#include "TF1.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TGraphAsymmErrors.h"
#include "TMultiGraph.h"
#include "TApplication.h"
#include "TChain.h"
#include "TLorentzVector.h"
#include "TPaveLabel.h"
#include "TPaveText.h"
#include "TMath.h"

#include "TError.h"

#include<algorithm>
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <vector>
#include <map>
#include <string>
#include "TRandom3.h"
#include "TRandom.h"

#include "TVector3.h"
#include "TLorentzRotation.h"
#include "TCut.h"
#include "TFormula.h"
#include "TString.h"
#include "Riostream.h"
#include "TDecompChol.h"
#include "TDecompSVD.h"
#include "TTime.h"
#include "TTimeStamp.h"
#include "TObjectTable.h"
#include "TAxis.h"
#include "TLatex.h"
#include "TLegend.h"
#include "Riostream.h"

#include "TLine.h"
#include "TStyle.h"
using namespace std;

// #ifndef __CINT__
// #include "RooGlobalFunc.h"
// #endif
#include "RooRealVar.h"
#include "RooStats/SPlot.h"
#include "RooDataSet.h"
#include "RooDataHist.h"
#include "RooGaussian.h"
#include "RooExponential.h"
#include "RooChebychev.h"
#include "RooCrystalBall.h"
#include "RooCBShape.h"
#include "RooAddPdf.h"
#include "RooExtendPdf.h"
#include "RooPlot.h"
#include "RooProdPdf.h"
#include "RooAddition.h"
#include "RooProduct.h"
#include "RooFit.h"
#include "RooDecay.h"
#include "Riostream.h"
#include "RooBifurGauss.h"
#include "RooAbsReal.h"
#include "RooMath.h"
#include "TCanvas.h"
#include "RooPolynomial.h"
#include "TAxis.h"
#include "RooAbsPdf.h"
#include "RooFitResult.h"
#include "RooWorkspace.h"
#include "RooConstVar.h"
#include "RooTreeDataStore.h"
#include "RooGenericPdf.h"
#include "RooGaussModel.h"
#include "RooEffProd.h"
#include "RooFormulaVar.h"
#include "RooHypatia2.h"

using namespace RooFit;
using namespace RooStats;
