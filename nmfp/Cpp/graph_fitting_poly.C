#include <ostream>
#include "TMatrixD.h"

Double_t fitfunction(Double_t *x, Double_t *par)
{
	Float_t xx = x[0];
	//Double_t f = par[0]*xx*xx*xx + par[1]*xx*xx + par[2]*xx + par[3];
	Double_t f = par[0]*xx*xx*xx*xx + par[1]*xx*xx*xx + par[2]*xx*xx + par[3]*xx+par[4];
	return f;	
}

void graph_fitting_poly() {
  
   //gStyle->SetOptFit(kFALSE);	
   gStyle->SetOptFit(1);	
   TCanvas *c1 = new TCanvas("c1","Cubic Data",200,10,700,500);
   FILE *f = fopen("poly5.dat","r");

   c1->SetFillColor(42);
   c1->SetGrid();

   const Int_t n = 10000;
   Double_t x[n], y[n], ex[n],ey[n];
   Int_t i=0;

   while (!feof(f)){
	  fscanf(f,"%lf %lf\n",&x[i],&y[i]);
          printf("%i %f %f\n",i,x[i],y[i]);
	  ex[i]=0.0;
	  i++;
   }

   	
   gr = new TGraph(n,x,y);
   TF1 *pfit1 = new TF1("fitfunction",fitfunction,0.0,10.0,5);
   pfit1->SetParameters(1.0,1.0,1.0,1.0,1.0);
   pfit1->SetParNames("A","B","C","D","E");
   
   gr->SetMarkerStyle(21);
   gr->SetTitle("Polynomial Fit");
   gr->GetXaxis()->SetTitle("x");
   gr->GetYaxis()->SetTitle("f(x)");
//   TAxis *axis = gr->GetXaxis();
//   axis->SetLimits(-5.,5.);
   gr->GetHistogram()->SetMaximum(70.0);
   gr->GetHistogram()->SetMinimum(-10.0);


   pfit1->SetLineColor(2);
   gr->Fit("pol4");
   Double_t pfit1chi2 = pfit1->GetChisquare();
   Double_t pfit1ndf = pfit1->GetNDF();
   Double_t pfit1chi2ndf = pfit1chi2/pfit1ndf;
//   printf("Fit 1: %f %f \n",pfit1chi2,pfit1ndf);
   gr->Draw("AP");

   // TCanvas::Update() draws the frame, after which one can change it
   c1->Update();
   c1->GetFrame()->SetFillColor(21);
   c1->GetFrame()->SetBorderSize(12);
   c1->Modified();
}
