#include <iostream>
#include <TMath.h>

void zdist() {
   // Calculate a Gaussian probability distribution with mu=0 and sigma=1, and then return integral between limits
   //
   // Author: Edward J. Brash
  
//   gStyle->SetOptFit(kFALSE);	
   TCanvas *c1 = new TCanvas("c1","Linear Example",800,800);

   c1->SetFillColor(42);
   c1->SetGrid();

   double z;
   cout << "Enter the z-value: " << endl;
   cin >> z; 

   TF1 *f1 = new TF1("f1","1.0/sqrt(2.0*3.14159265)*pow(2.718281828,-pow(x,2.0)/2.0)",-6,6);
   double prob = f1->Integral(-6.0,z);
   f1->Draw();
   cout << "returned integral is " << prob << endl;

//   gr = new TGraphErrors(n,x,y,ex,ey);
//   TF1 *pfit1 = new TF1("pfit1","pol1");
//   TF1 *pfit2 = new TF1("pfit2","pol2");
//   gr->SetLineColor(2);
//   gr->SetLineWidth(4);
//   gr->SetMarkerColor(4);
//   gr->SetMarkerStyle(21);
//   gr->SetTitle("a simple graph");
//   gr->GetXaxis()->SetTitle("X title");
//   gr->GetYaxis()->SetTitle("Y title");
//   pfit1->SetLineColor(2);
//   pfit2->SetLineColor(3);
//   gr->Fit("pfit1","q");
//   Double_t pfit1chi2 = pfit1->GetChisquare();
//   Double_t pfit1ndf = pfit1->GetNDF();
//   printf("Fit 1: %f %f \n",pfit1chi2,pfit1ndf);
//   Double_t pfit1chi2ndf = pfit1chi2/pfit1ndf;
//   gr->Fit("pfit2","q+");
//   Double_t pfit2chi2 = pfit2->GetChisquare();
//   Double_t pfit2ndf = pfit2->GetNDF();
//   printf("Fit 2: %f %f \n",pfit2chi2,pfit2ndf);
//   Double_t pfit2chi2ndf = pfit2chi2/pfit2ndf;
//   gr->Draw("AP");

   // draw the legend
//   Char_t message[80];
//   TLegend *legend=new TLegend(0.4,0.15,0.88,0.35);
//   legend->SetTextFont(72);
//   legend->SetTextSize(0.04);
 //  legend->AddEntry(gr,"Data","lpe");
//   sprintf(message,"Linear Fit: #chi^{2}/NDF = %.2f",pfit1chi2ndf);
//   legend->AddEntry(pfit1,message);
//   sprintf(message,"Quadratic Fit: #chi^{2}/NDF = %.2f",pfit2chi2ndf);
//   legend->AddEntry(pfit2,message);
//   legend->Draw();

   // TCanvas::Update() draws the frame, after which one can change it
   c1->Update();
   c1->GetFrame()->SetFillColor(21);
   c1->GetFrame()->SetBorderSize(12);
   c1->Modified();
}
