#include <iostream>

Double_t fitfunction(Double_t *x, Double_t *par)
{
	Double_t xx = x[0];
	Double_t f = par[0]/2.0*(1.0+tanh((xx-par[2])/par[1]));
        return f;
}

void graph_tv_tanh() {
   //
   //Modified: Edward J. Brash
   //		
  
   //gStyle->SetOptFit(kFALSE);	
   gStyle->SetOptFit(1);	
   TCanvas *c1 = new TCanvas("c1","Cubic Data",200,10,700,500);
   c1->SetFillColor(42);
   c1->SetGrid();
   
   FILE *f = fopen("tv_rate.dat","r");

   const Int_t n = 10000;
   Double_t x[n], y[n];
   Int_t i=0;

   while (!feof(f)){
	  fscanf(f,"%lf %lf\n",&x[i],&y[i]);
	  i++;
   }
   
   const Int_t n2 = i;
   TGraph *gr = new TGraphErrors(n2,x,y);
//   gr->SetLineColor(2);
//   gr->SetLineWidth(4);
//   gr->SetMarkerColor(4);
   gr->SetMarkerStyle(21);
   gr->SetTitle("TV Ownership Rate");
   gr->GetXaxis()->SetTitle("Year");
   gr->GetYaxis()->SetTitle("Rate");
//

   TF1 *pfit1 = new TF1("fitfunction",fitfunction,1949,2013,3);
   pfit1->SetParameters(98.0,0.2,1954.0);
   pfit1->SetParNames("Amplitude","Decay Rate","Start Year");
   //gr->Fit("fitfunction","V");
   gr->Fit("fitfunction");

//   TAxis *axis = gr->GetXaxis();
//   axis->SetLimits(-5.,5.);
   gr->GetHistogram()->SetMaximum(140.0);
//   gr->GetHistogram()->SetMinimum(0.0);

   gr->Draw("AP");

   // TCanvas::Update() draws the frame, after which one can change it
   c1->Update();
   c1->GetFrame()->SetFillColor(21);
   c1->GetFrame()->SetBorderSize(12);
   c1->Modified();
}
