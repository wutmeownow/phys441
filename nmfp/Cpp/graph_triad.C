#include <TRandom.h>

void graph_triad() {
   //
   //Modified: Edward J. Brash
   //		
  
   //gStyle->SetOptFit(kFALSE);	
   gStyle->SetOptFit(1);	
   TCanvas *c1 = new TCanvas("c1","Cubic Data",200,10,700,500);
   FILE *f = fopen("triad.dat","r");

   c1->SetFillColor(42);
   c1->SetGrid();

   const Int_t n = 40000;
   Double_t x[n], y[n];
   Int_t i=0;

   while (!feof(f)){
	  fscanf(f,"%lf %lf\n",&x[i],&y[i]);
	  i++;
   }

   gr = new TGraph(i,x,y);
   gr->SetMarkerStyle(1);
   gr->SetMarkerColor(kBlue);
   gr->SetTitle("Triad Time Series");
   gr->GetXaxis()->SetTitle("Time");
   gr->GetYaxis()->SetTitle("Amplitude");
   TAxis *axis = gr->GetXaxis();
   axis->SetLimits(0.0,1.2);
   gr->Draw("AC");

   // TCanvas::Update() draws the frame, after which one can change it
   c1->Update();
   c1->GetFrame()->SetFillColor(21);
   c1->GetFrame()->SetBorderSize(12);
   c1->Modified();
}
