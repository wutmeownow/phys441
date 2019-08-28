#include <ostream>
#include "TMatrixD.h"

Double_t fitfunction(Double_t *x, Double_t *par)
{
	Float_t xx = x[0];
	Double_t f = par[0]*TMath::Poisson(xx,par[1]);
	return f;	
}

void graph_poisson() {
  
   //gStyle->SetOptFit(kFALSE);	
   gStyle->SetOptFit(1);	
   TCanvas *c1 = new TCanvas("c1","Physics 201 Data",200,10,700,500);
   FILE *f = fopen("data_poisson.txt","r");

   c1->SetFillColor(42);
   c1->SetGrid();

   const Int_t n = 10000;
   Double_t x[n], y[n];
   Int_t i=0;

   while (!feof(f)){
	  fscanf(f,"%lf %lf\n",&x[i],&y[i]);
          printf("%i %f %f\n",i,x[i],y[i]);
	  i++;
   }

   	
   gr = new TGraph(n,x,y);
   TF1 *pfit1 = new TF1("fitfunction",fitfunction,0.0,40.0,2);
   pfit1->SetParameters(5.0,25.0);
   pfit1->SetParNames("Amplitude","Mean");
   
   gr->SetMarkerStyle(21);
   gr->SetTitle("Physics 201 Data");
   gr->GetXaxis()->SetTitle("Score");
   gr->GetYaxis()->SetTitle("N");
//   TAxis *axis = gr->GetXaxis();
//   axis->SetLimits(-5.,5.);
//   gr->GetHistogram()->SetMaximum(0.45);
//   gr->GetHistogram()->SetMinimum(0.0);


   pfit1->SetLineColor(2);
   gr->Fit("fitfunction","V");
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
