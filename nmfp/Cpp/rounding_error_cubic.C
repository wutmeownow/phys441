#include <TRandom.h>
#include <TMath.h>

void rounding_error_cubic() {
   //
   //Author: Edward J. Brash, look at rounding errors
   //			 	by comparing derivative to calculation
  
   TCanvas *c1 = new TCanvas("c1","Absolute Error",200,10,700,500);

   c1->SetFillColor(42);
   c1->SetGrid();
   c1->SetLogx();
   c1->SetLogy();

   const Int_t n = 21;
   Double_t x[n], h, hpower;
   Double_t dfunc[n], dfunch[n], xfunc[n], xfunch[n];
   Double_t diff[n];
   Double_t xval = 1.0;

   for (Int_t i=0;i<n;i++) {
     hpower=i-n+1;
     x[i] = pow(10.0,hpower);
     dfunc[i]=3.0e+00*xval*xval;
     xfunc[i]=xval*xval*xval;
     xfunch[i]=(xval+x[i])*(xval+x[i])*(xval+x[i]);
     dfunch[i]=(xfunch[i]-xfunc[i])/x[i];
     diff[i]=fabs(dfunc[i]-dfunch[i]);

     printf(" i %i %f %f %f %f %f %f\n",i,x[i],xfunc[i],xfunch[i],dfunc[i],dfunch[i],diff[i]);
   }
   TGraph *gr = new TGraph(n,x,diff);
//   gr->SetLineColor(2);
//   gr->SetLineWidth(4);
//   gr->SetMarkerColor(4);
   gr->SetMarkerStyle(21);
   gr->SetMinimum(0.000000001);
   gr->SetMaximum(10.0);
   gr->SetTitle("Round Error Calculation");
   gr->GetXaxis()->SetTitle("h");
   gr->GetYaxis()->SetTitle("Absolute Error");
   gr->Draw("AP");

   // TCanvas::Update() draws the frame, after which one can change it
   c1->Update();
   c1->GetFrame()->SetFillColor(21);
   c1->GetFrame()->SetBorderSize(12);
   c1->Modified();
}
