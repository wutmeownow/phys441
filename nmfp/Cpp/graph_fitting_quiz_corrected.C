#include <ostream>
#include "TMatrixD.h"
#include "TRandom.h"

Double_t fitfunction(Double_t *x, Double_t *par)
{
        Double_t xx=x[0];
	//Double_t f = par[0]*TMath::Binomial(12,int(xx))*pow(par[1],int(xx))*pow((1.0-par[1]),12-int(xx));
	Double_t f = par[0]*TMath::Poisson(xx,par[1]);
	//Double_t f = par[0]*TMath::Gaus(xx,par[1],par[2],kFALSE);
        return f;
}

void graph_fitting_quiz_corrected() {
   //
   //Modified: Edward J. Brash
   //		
  
   //gStyle->SetOptFit(kFALSE);	
   gStyle->SetOptFit(1);	
   TCanvas *c1 = new TCanvas("c1","Quiz Data",200,10,700,500);

   // Set the order of the fitting polynomial here.
   
   c1->SetFillColor(42);
   c1->SetGrid();

   const unsigned int n = 12;
   const unsigned int m=4;
   Double_t x[n], y[n], ex[n],ey[n];
   Int_t i;

   y[0]=0.01;
   y[1]=0.02;
   y[2]=0.03;
   y[3]=0.06;
   y[4]=0.07;
   y[5]=0.09;
   y[6]=0.12;
   y[7]=0.12;
   y[8]=0.15;
   y[9]=0.15;
   y[10]=0.12;
   y[11]=0.06;

   Int_t Npeople=3278;

   for (i=0;i<n;i++){
           x[i]=i+1;
	   x[i]=x[i]-(n-x[i])/(m-1);
	   ex[i]=0.0;
	   ey[i]=1.96*sqrt(y[i]*(1.0-y[i])/Npeople);
   }

   gr = new TGraphErrors(n,x,y,ex,ey);
//   TF1 *pfit1 = new TF1("pfit1",s);
   //TF1 *pfit1 = new TF1("pfit1",fitfunction,-3.0,13.0,3);
   TF1 *pfit1 = new TF1("pfit1",fitfunction,-3.0,13.0,2);
   //pfit1->SetParameters(0.5,0.80);
   pfit1->SetParameters(1.0,9.0);
   //pfit1->SetParameters(1.0,7.0,2.0);

//   gr->SetLineColor(2);
//   gr->SetLineWidth(4);
//   gr->SetMarkerColor(4);
   gr->SetMarkerStyle(21);
   gr->SetTitle("Poisson Fit");
   gr->GetXaxis()->SetTitle("X");
   gr->GetYaxis()->SetTitle("Y");
   TAxis *axis = gr->GetXaxis();
   axis->SetLimits(-3.0,13.0);
//   gr->GetHistogram()->SetMaximum(10.0);
//   gr->GetHistogram()->SetMinimum(0.0);


   //pfit1->SetLineColor(polynomial_order-1);
   //gr->Fit("pfit1","V");
   gr->Fit("pfit1","");
   Double_t pfit1chi2 = pfit1->GetChisquare();
   Double_t pfit1ndf = pfit1->GetNDF();
   Double_t pfit1chi2ndf = pfit1chi2/pfit1ndf;
   printf("Fit 1: %f %f \n",pfit1chi2,pfit1ndf);
   gr->Draw("AP");

   //cout << "Fit Order = " << polynomial_order << " Chi2/dof = " << chi2 << endl;

   // draw the legend
   Char_t message[80];
   TLegend *legend=new TLegend(0.4,0.15,0.88,0.35);
   legend->SetTextFont(72);
   legend->SetTextSize(0.04);
   legend->AddEntry(gr,"Data","lpe");
   sprintf(message,"Cubic Fit: #chi^{2}/NDF = %.5f",pfit1chi2ndf);
   legend->AddEntry(pfit1,message);
//   legend->Draw();

   // TCanvas::Update() draws the frame, after which one can change it
   c1->Update();
   c1->GetFrame()->SetFillColor(21);
   c1->GetFrame()->SetBorderSize(12);
   c1->Modified();
}
