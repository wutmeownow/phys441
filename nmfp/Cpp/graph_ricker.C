//
// Chaos Theory Example - basic growth function
//

#include <ostream>

Double_t growthfunction(Double_t *x, Double_t *par)
{
	Double_t f = x[0]*exp(par[0]*(1.0-x[0]));
	return f;
}

void graph_ricker(Double_t lambda_start = 2.3, Int_t npoints = 20, Double_t xstart = 0.5) {
   //
   //Modified: Edward J. Brash
   //		
  
   //gStyle->SetOptFit(kFALSE);	
   gStyle->SetOptFit(1);	
   TCanvas *c1 = new TCanvas("c1","Population vs. Time",200,10,800,1000);

   c1->SetFillColor(42);
   c1->SetGrid();
   //c1->SetLogy();
   //c1->SetLogx();

   const Int_t n = npoints;
   Double_t population[n],year[n];
   Double_t lambda[1];
   Double_t xvalue[1];

   year[0]=0;
   population[0]=xstart;
   lambda[0]=lambda_start;

   for (Int_t i=1; i<n; i++){
        year[i]=i;
        xvalue[0]=population[i-1];
        population[i]=growthfunction(xvalue,lambda);
   }

   TGraph *gr = new TGraph(n,year,population);

//   gr->SetLineColor(2);
//   gr->SetLineWidth(4);
   gr->SetMarkerColor(kBlue);
   gr->SetMarkerStyle(20);
   gr->SetMarkerSize(0.5);
   gr->SetTitle("Growth Function: x*exp(lambda*(1-x))");
   gr->GetXaxis()->SetTitle("Year");
   gr->GetYaxis()->SetTitle("Population");
   gr->Draw();

   // TCanvas::Update() draws the frame, after which one can change it
   c1->Update();
   c1->GetFrame()->SetFillColor(21);
   c1->GetFrame()->SetBorderSize(12);
   c1->Modified();
}
