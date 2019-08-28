#include <iostream>

Double_t fitfunction(Double_t *x, Double_t *par)
{
	Double_t Pi=3.14159265;
	Double_t a=0.5*pow(Pi/2.0,0.5)*par[1];
	Float_t xx = x[0];
	Double_t f = 1000.0/200.0*par[0]*pow(2.0/Pi,0.5)/pow(a,3)*xx*xx*exp(-1.0*xx*xx/(2.0*a*a));
        return f;
}

void graph_tv_deriv() {
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
   
   const Int_t n2 = i;

   for(i=1;i<n2-1;i++){
	   xp[i-1]=x[i];
	   yp[i-1]=(y[i+1]-y[i-1])/2.0;
   }

   TGraphErrors *gr = new TGraphErrors(n2-2,xp,yp);
//   gr->SetLineColor(2);
//   gr->SetLineWidth(4);
//   gr->SetMarkerColor(4);
   gr->SetMarkerStyle(21);
   gr->SetTitle("First Derivative of TV Ownership Rate");
   gr->GetXaxis()->SetTitle("Year");
   gr->GetYaxis()->SetTitle("First Derivative of Rate");
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
