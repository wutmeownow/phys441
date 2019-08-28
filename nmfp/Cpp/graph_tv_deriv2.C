#include <iostream>

Double_t fitfunction(Double_t *x, Double_t *par)
{
	Float_t xx = x[0];
	Double_t f = par[0]*(1.0-exp(-par[1]*xx));
        return f;
}

void graph_tv_deriv2() {
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
   Double_t x[n], y[n], xp[n], yp[n];
   Int_t i=0;

   while (!feof(f)){
	  fscanf(f,"%lf %lf\n",&x[i],&y[i]);
	  i++;
   }
   
   const Int_t n = i;

   for(i=1;i<n-1;i++){
	   xp[i-1]=x[i];
	   yp[i-1]=-1.0*(y[i+1]-2*y[i]+y[i-1]);
   }

   gr = new TGraphErrors(n-2,xp,yp);
//   gr->SetLineColor(2);
//   gr->SetLineWidth(4);
//   gr->SetMarkerColor(4);
   gr->SetMarkerStyle(21);
   gr->SetTitle("Second Derivative of TV Ownership Rate");
   gr->GetXaxis()->SetTitle("Year");
   gr->GetYaxis()->SetTitle("Second Derivative of Rate");
//   TAxis *axis = gr->GetXaxis();
//   axis->SetLimits(-5.,5.);
//   gr->GetHistogram()->SetMaximum(10.0);
//   gr->GetHistogram()->SetMinimum(0.0);

   gr->Draw("AP");

   // TCanvas::Update() draws the frame, after which one can change it
   c1->Update();
   c1->GetFrame()->SetFillColor(21);
   c1->GetFrame()->SetBorderSize(12);
   c1->Modified();
}
