//
// Chaos Theory Example - basic growth function
//

#include <ostream>

Double_t growthfunction(Double_t *x, Double_t *par)
{
	Double_t f = par[0]*x[0]*(1.0-x[0]);
	return f;
}

void graph_chaos_xstart(Double_t lambda_start = 2.3, Int_t npoints = 20, Double_t xstart1 = 0.5, Double_t xstart2 = 0.51) {
   //
   //Modified: Edward J. Brash
   //		
  
   //gStyle->SetOptFit(kFALSE);	
   gStyle->SetOptFit(1);	
   TCanvas *c1 = new TCanvas("c1","Population vs. Time",200,10,800,1000);
   TCanvas *c2 = new TCanvas("c2","Population vs. Time",220,30,800,1000);
   //c1->SetFillColor(42);
   //c1->SetGrid();
   //c2->SetFillColor(42);
   //c2->SetGrid();
   //c1->SetLogy();
   //c1->SetLogx();

   const Int_t n = npoints;
   Double_t population1[n],population2[n],year[n];
   Double_t lambda[1];
   Double_t xvalue[1];

   year[0]=0;
   population1[0]=xstart1;
   population2[0]=xstart2;
   lambda[0]=lambda_start;

   for (Int_t i=1; i<n; i++){
        year[i]=i;
        xvalue[0]=population1[i-1];
        population1[i]=growthfunction(xvalue,lambda);
        xvalue[0]=population2[i-1];
        population2[i]=growthfunction(xvalue,lambda);
   }

   TGraph *gr1 = new TGraph(n,year,population1);
   TGraph *gr2 = new TGraph(n,year,population2);
   TGraph *gr3 = new TGraph(n,population1,population2);

//   gr->SetLineColor(2);
//   gr->SetLineWidth(4);
   c1->cd();
   gr1->SetMarkerColor(kBlue);
   gr1->SetMarkerStyle(20);
   gr1->SetMarkerSize(0.5);
   gr1->SetTitle("Growth Function: lambda*x*(1-x)");
   gr1->GetXaxis()->SetTitle("Year");
   gr1->GetYaxis()->SetTitle("Population");
   gr1->Draw("AP");
   gr2->SetMarkerColor(kRed);
   gr2->SetMarkerStyle(20);
   gr2->SetMarkerSize(0.5);
   gr2->Draw("P");
   c2->cd();
   gr3->SetMarkerColor(kBlue);
   gr3->SetMarkerStyle(20);
   gr3->SetMarkerSize(1.0);
   gr3->SetTitle("Growth Function: lambda*x*(1-x)");
   gr3->GetXaxis()->SetTitle("Population1");
   gr3->GetYaxis()->SetTitle("Population2");
   gr3->Draw("AP");


   // TCanvas::Update() draws the frame, after which one can change it
   c1->Update();
   c1->GetFrame()->SetFillColor(21);
   c1->GetFrame()->SetBorderSize(12);
   c1->Modified();
}
