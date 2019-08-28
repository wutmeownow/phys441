#include <ostream>
#include "TGraph.h"
#include "TCanvas.h"
#include "TStyle.h"
#include "TGraphPolar.h"
#include "TH1F.h"
#include "TAxis.h"
#include "TFrame.h"

void graph_orbit() {
   //
   //Modified: Edward J. Brash
   //		
  
   //gStyle->SetOptFit(kFALSE);	
   gStyle->SetOptFit(1);	
   TCanvas *c1 = new TCanvas("c1","Cubic Data",200,10,700,500);
   c1->Divide(3,1);
   FILE *f = fopen("rplot.txt","r");
   FILE *g = fopen("tplot.txt","r");
   FILE *d = fopen("total.txt","r");
   FILE *h = fopen("kinetic.txt","r");
   FILE *e = fopen("potential.txt","r");

   c1->SetFillColor(42);
   c1->SetGrid();

   const Int_t n = 1000;
   Double_t xr[n], yr[n];
   Double_t xt[n], yt[n];
   Double_t xe[n], ye[n];
   Double_t xk[n], yk[n];
   Double_t xp[n], yp[n];
   Int_t i=0;

   while (!feof(f)){
	  fscanf(f,"%lf %lf\n",&xr[i],&yr[i]);
	  fscanf(g,"%lf %lf\n",&xt[i],&yt[i]);
	  fscanf(d,"%lf %lf\n",&xe[i],&ye[i]);
	  fscanf(h,"%lf %lf\n",&xk[i],&yk[i]);
	  fscanf(e,"%lf %lf\n",&xp[i],&yp[i]);
	  i++;
   }

   const Int_t n2=i;

   TGraphPolar * grr = new TGraphPolar(n2,xr,yr);
   TGraph *grt = new TGraph(n2,xt,yt);
   TGraph *gre = new TGraph(n2,xe,ye);
   TGraph *grk = new TGraph(n2,xk,yk);
   TGraph *grp = new TGraph(n2,xp,yp);

//   gr->SetLineColor(2);
//   gr->SetLineWidth(4);
   grr->SetMarkerColor(kBlue);
   grt->SetMarkerColor(kBlue);
   gre->SetMarkerColor(kRed);
   grk->SetMarkerColor(kGreen);
   grp->SetMarkerColor(kBlue);
   //
   grr->SetMarkerStyle(22);
   grt->SetMarkerStyle(22);
   gre->SetMarkerStyle(22);
   grk->SetMarkerStyle(22);
   grp->SetMarkerStyle(22);
   gre->SetTitle("Keplerian Motion");
   gre->GetXaxis()->SetTitle("Time");
   gre->GetYaxis()->SetTitle("Energy");
   grr->SetTitle("Keplerian Motion");
   grr->GetXaxis()->SetTitle("Theta");
   grr->GetYaxis()->SetTitle("Radius");
   grt->SetTitle("Keplerian Motion");
   grt->GetXaxis()->SetTitle("Time");
   grt->GetYaxis()->SetTitle("Radius");
//   TAxis *axis = gr->GetXaxis();
//   axis->SetLimits(-5.,5.);
   gre->GetHistogram()->SetMaximum(30.0);
   gre->GetHistogram()->SetMinimum(-45.0);
   grt->GetHistogram()->SetMaximum(2.5);
   grt->GetHistogram()->SetMinimum(0.5);

   c1->cd(1);
   grr->Draw("AP");
   c1->Update();
   grr->SetMaxRadial(1.1);
   grr->SetMinRadial(0.9);
   c1->cd(2);
   grt->Draw("AP");
   c1->cd(3);
   gre->Draw("AP");
   grk->Draw("P");
   grp->Draw("P");

   // draw the legend
//   Char_t message[80];
//   TLegend *legend=new TLegend(0.4,0.15,0.88,0.35);
//   legend->SetTextFont(72);
//   legend->SetTextSize(0.04);
//   legend->AddEntry(gr,"Data","lpe");
//   sprintf(message,"Cubic Fit: #chi^{2}/NDF = %.5f",pfit1chi2ndf);
//   legend->AddEntry(pfit1,message);
//   legend->Draw();

   // TCanvas::Update() draws the frame, after which one can change it
   c1->Update();
   c1->GetFrame()->SetFillColor(21);
   c1->GetFrame()->SetBorderSize(12);
   c1->Modified();
}
