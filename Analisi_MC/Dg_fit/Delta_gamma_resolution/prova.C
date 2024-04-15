#include "Inclusion.h"
double kstar_conv(){
  double g = 0.6583;  
  double dg = -1.2e-3;
  double t1 = 1.0;  
  double t2 = 1.3;
        
  double s = 3.88e-2; //effective sigma   
  double m = -3.3e-4; //mean of gauss 
 
  double za = (g - dg/2)*(s/sqrt(2)); 
  double zb=  (g + dg/2)*(s/sqrt(2));
  double x1  = (t1 - m) / (sqrt(2) * s); 
  double x2  = (t2 - m) / (sqrt(2) * s);

  double fadd_a1 = exp(pow(za-x1,2))*RooMath::erfc(za-x1);
  double fadd_b1 = exp(pow(zb-x1,2))*RooMath::erfc(zb-x1);
  double term1 = ( (s / (4 * sqrt(2) * za)) * (RooMath::erf(x1) -  exp(-pow(x1,2)) * fadd_a1)) + ((s / (4 * sqrt(2) * zb)) * (RooMath::erf(x1) -  exp(-pow(x1,2)) * fadd_b1));
  
  double fadd_a2 = exp(pow(za-x2,2))*RooMath::erfc(za-x2);
  double fadd_b2 = exp(pow(zb-x2,2))*RooMath::erfc(zb-x2);
  double term2 = ( (s / (4 * sqrt(2) * za)) * (RooMath::erf(x2) -  exp(-pow(x2,2)) * fadd_a2)) + ((s / (4 * sqrt(2) * zb)) * (RooMath::erf(x2) -  exp(-pow(x2,2)) * fadd_b2));

  double result = term2 - term1;
  
  return result;
}

double kshort_conv(){
  double g = 0.6583;  
  double dg = -1.2e-3;
  double cosbeta=0.7151;
  double t1 = 1.3;  
  double t2 = 1.6; 
   
  double s = 4.43e-2; //effective sigma   
  double m = -1.1e-4; //mean of gauss //-3.0e-4
  
  double za = (g - dg/2)*(s/sqrt(2)); 
  double zb  =  (g + dg/2)*(s/sqrt(2));
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


/*
void prova_kstar2() {
  //mesaured in ps
   
  double g = 0.6583;  
  double t1 = 0.5;  
  double t2 = 0.7;
        
  double s = 0.0443; //effective sigma   
  double m = 0.00011; //mean of gauss  
 
  double z = g * s / sqrt(2); 
  double x1  = (t1 - m) / (sqrt(2) * s); 
  double x2  = (t2 - m) / (sqrt(2) * s);  
  

  double fadd2 = exp(pow(z-x2,2))*RooMath::erfc(z-x2);
  double term2 = (s / sqrt(2)) * (1./(2*z)) * (RooMath::erf(x2) -  exp(-pow(x2,2)) * fadd2);
     
  cout<<"(s / sqrt(2)) * (1./(2*z))"<<(s / sqrt(2)) * (1./(2*z))<<"\n \n";
  cout<<"x2 "<<x2<<"\n \n";
  cout<<"erf2 "<<RooMath::erf(t2/(sqrt(2)*s))<<"\n \n";
  cout<<"exp2 "<<exp(-pow(x2,2))<<"\n \n";
  cout<<"fadd1 "<<fadd2<<"\n \n";

  double fadd1 = exp(pow(z-x1,2))*RooMath::erfc(z-x1);
  double term1 = (s / sqrt(2)) * (1./(2*z)) * (RooMath::erf(x1) -  exp(-pow(x1,2)) * fadd1);
 
  cout<<"(s / sqrt(2)) * (1./(2*z))"<<(s / sqrt(2)) * (1./(2*z))<<"\n \n";
  cout<<"erf1 "<<RooMath::erf(x1)<<"\n \n";
  cout<<"x1 "<<x1<<"\n \n";
  cout<<"exp1 "<<exp(-pow(x1,2))<<"\n \n";
  cout<<"fadd1 "<<fadd1<<"\n \n";
 
 
 cout<<"term1 "<<term1<<" term2 "<<term2<<"\n";
 double result = term2-term1;

}

void prova_kshort2(){
  //mesaured in ps
  double g = 0.6583;  
  double cosbeta=0.7151;
  double dg = -1.2e-3; 
  double t1 = 0.5;  
  double t2 = 0.7;
  double pi = TMath::Pi();  
    
  double s = 0.0388; //effective sigma   
  double m = 0.00033; //mean of gauss  
 
  double z = g * s / sqrt(2); 
  double x1  = (t1 - m) / (sqrt(2) * s); 
  double x2  = (t2 - m) / (sqrt(2) * s);
  
  double a0 = 1;
  double a1 = dg * cosbeta / 2;
  
  double fadd1 = exp(pow(z-x1,2))*RooMath::erfc(z-x1);
  double fadd2 = exp(pow(z-x2,2))*RooMath::erfc(z-x2);
  
  double M0 = (RooMath::erf(x2) - exp(-pow(x2,2)) * fadd2) - (RooMath::erf(x1) - exp(-pow(x1,2)) * fadd1) ;
  double M1 = (2 * exp(-pow(x2,2)) * (-sqrt(1./pi)-x2*fadd2)) - (2 * exp(-pow(x1,2)) * (-sqrt(1./pi)-x1*fadd1));
  
  double k0 = (1./(2.*z));
  double k1 = (1./(2*pow(z,2)));
 
 
  double result = a0 * k0 * M0 + a1/2 * k1 * M1 + a1/2 * k0 * M1; 
 
  cout<<"result "<<result;
  }

*/ 
 
