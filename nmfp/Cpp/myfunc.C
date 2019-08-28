#include <TMath.h>

Double_t myfunction(Double_t *x, Double_t *par)
{
   Float_t xx =x[0];
//   Double_t f = par[0]+par[1]*xx+par[2]*xx*xx;
   Double_t f = 0.12*par[0]/sqrt(2.0*3.14159265*pow(par[2],2))*pow(2.718281828,-0.5*pow((xx-par[1]),2)/pow(par[2],2));
   return f;
}

void myfunc()
{
   TF1 *f1 = new TF1("myfunc",myfunction,-6.0,6.0,3);
   f1->SetParameters(20000.0,0.0,1.0);
   f1->SetParNames("N","mean","sigma");
   f1->Draw();
}

void myfit()
{
   TH1F *h1=new TH1F("h1","test",100,-6,6);
   h1->FillRandom("myfunc",20000);
   TF1 *f1=gROOT->GetFunction("myfunc");
   f1->SetParameters(19999.0,0.1,1.5);
   h1->Fit("myfunc");
}
