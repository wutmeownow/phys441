#include <ostream>
#include "TMatrixD.h"
#include "TRandom.h"

void graph_vaccines(TString fittype = "pol0") {
   //
   //Modified: Edward J. Brash
   //		
  
   //gStyle->SetOptFit(kFALSE);	
   gStyle->SetOptFit(1);
   TCanvas *c1 = new TCanvas("c1","Cubic Data",200,10,700,500);

   // Set the order of the fitting polynomial here.
   
   c1->SetFillColor(42);
   c1->SetGrid();

   const Int_t n = 2;
   Double_t x[n], y[n], ex[n],ey[n];
   Int_t i;

   x[0] = 0;
   x[1] = 1;
   ex[0] = 0;
   ex[1] = 0;

   y[0] = 51;
   y[1] = 74;
   ey[0] = 14;
   ey[1] = 17;
   
   TGraphErrors *gr = new TGraphErrors(n,x,y,ex,ey);
   gr->SetMarkerStyle(21);
   TAxis *axis = gr->GetXaxis();
   axis->SetLimits(-1.0,2.0);
   gr->GetHistogram()->SetMaximum(100.0);
   gr->GetHistogram()->SetMinimum(0.0);
   gr->GetXaxis()->SetTitle("X");
   gr->GetYaxis()->SetTitle("Y");

   gr->Fit(fittype);
   gr->Draw("AP");

   c1->GetFrame()->SetFillColor(21);
   c1->GetFrame()->SetBorderSize(12);
   c1->Modified();
   c1->Update();
   c1->WaitPrimitive();
}
