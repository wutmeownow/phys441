#include <ostream>
#include "TMatrixD.h"

Double_t fitfunction(Double_t *x, Double_t *par)
{
	Double_t Pi = 3.14159265;
	Double_t a = pow(8.0*par[0]/Pi,0.5);
	Float_t xx = x[0];
	Double_t f = a*pow(xx,0.5);
	return f;
}

void graph_fitting_errors_kinetic() {
  
   //gStyle->SetOptFit(kFALSE);	
   gStyle->SetOptFit(1);	
   TCanvas *c1 = new TCanvas("c1","Kinetic Theory of Gases",200,10,700,500);
   FILE *f = fopen("kinetic.dat","r");

   c1->SetFillColor(42);
   c1->SetGrid();

   const Int_t n = 10000;
   Double_t x[n], y[n], ex[n],ey[n];
   Int_t i=0;

   while (!feof(f)){
	  fscanf(f,"%lf %lf %lf\n",&x[i],&y[i],&ey[i]);
          printf("%i %f %f %f\n",i,x[i],y[i],ey[i]);
	  ex[i]=0.0;
	  i++;
   }

   const Int_t m = i;
   	
   gr = new TGraphErrors(m,x,y,ex,ey);
   TF1 *pfit1 = new TF1("fitfunction",fitfunction,1.0,300.0,1);
   pfit1->SetParameter(0,100.0);
   pfit1->SetParNames("slope");
   
   gr->SetMarkerStyle(21);
   gr->SetTitle("Kinetic Theory of Gases");
   gr->GetXaxis()->SetTitle("T");
   gr->GetYaxis()->SetTitle("<V>");
//   TAxis *axis = gr->GetXaxis();
//   axis->SetLimits(-5.,5.);
   gr->GetHistogram()->SetMaximum(500.0);
   gr->GetHistogram()->SetMinimum(0.0);


   pfit1->SetLineColor(2);
   gr->Fit("fitfunction","V");
   Double_t pfit1chi2 = pfit1->GetChisquare();
   Double_t pfit1ndf = pfit1->GetNDF();
   Double_t pfit1chi2ndf = pfit1chi2/pfit1ndf;
   printf("Fit 1: %f %f \n",pfit1chi2,pfit1ndf);
   gr->Draw("AP");

   
   
   // TCanvas::Update() draws the frame, after which one can change it
   c1->Update();
   c1->GetFrame()->SetFillColor(21);
   c1->GetFrame()->SetBorderSize(12);
   c1->Modified();
}
