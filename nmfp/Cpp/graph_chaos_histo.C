//
// Chaos Theory Example - basic growth function
//

#include <ostream>

Double_t growthfunction(Double_t *x, Double_t *par)
{
	Double_t f = par[0]*x[0]*(1.0-x[0]);
	return f;
}

void graph_chaos_histo(Double_t lambda_start = 2.3, Int_t npoints = 20, Double_t xstart = 0.5, Int_t iflag = 1) {
   //
   //Modified: Edward J. Brash
   //		
  
   //gStyle->SetOptFit(kFALSE);	
   gStyle->SetOptFit(1);	
   TCanvas *c2 = new TCanvas("c2","Frequency Histogram",300,100,800,1000);

   c2->SetFillColor(42);
   c2->SetGrid();
   if (iflag == 1) c2->SetLogy();
   //c2->SetLogx();

   TH1D *h1 = new TH1D("h1","Frequency Histogram",1000,0.0,1.0); 

   const Int_t n = npoints;
   Double_t population,year;
   Double_t lambda[1];
   Double_t xvalue[1];

   year=0;
   population=xstart;
   lambda[0]=lambda_start;

   for (Int_t i=1; i<n; i++){
        year=i;
        xvalue[0]=population;
        population=growthfunction(xvalue,lambda);
        h1->Fill(population);
   }

   c2->cd();
   h1->Draw();

   // TCanvas::Update() draws the frame, after which one can change it
   c2->Update();
   c2->GetFrame()->SetFillColor(21);
   c2->GetFrame()->SetBorderSize(12);
   c2->Modified();
}
