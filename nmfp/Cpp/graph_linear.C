#include <TRandom.h>

void graph_linear() {
   //Draw a simple graph
   // To see the output of this macro, click begin_html <a href="gif/graph.gif">here</a>. end_html
   //Author: Rene Brun
   //
   //Modified: Edward J. Brash, to change to simple linear plot
   //				with random fluctuations
  
   gStyle->SetOptFit(1);	
   TCanvas *c1 = new TCanvas("c1","Linear Example",200,10,700,500);

   c1->SetFillColor(42);
   c1->SetGrid();

   const Int_t n = 20;
   Double_t x[n], y[n];
   Double_t ey[n],ex[n];
   Double_t rnd;

   TRandom r;

   for (Int_t i=0;i<n;i++) {
     x[i] = i*0.5;
     //y[i] = 1.078*x[i]+0.5684-0.0456*x[i]*x[i];
     y[i] = 1.078*x[i]+0.5684;
     rnd = r.Gaus(0.0,0.0);
     y[i]=y[i]+rnd;
     ex[i]=0.0;
     ey[i]=0.3;

     printf(" i %i %f %f %f \n",i,x[i],y[i],ey[i]);
   }
   //gr = new TGraphErrors(n,x,y,ex,ey);
   gr = new TGraph(n,x,y);
   TF1 *pfit1 = new TF1("pfit1","pol1");
   TF1 *pfit2 = new TF1("pfit2","pol2");
//   gr->SetLineColor(2);
//   gr->SetLineWidth(4);
//   gr->SetMarkerColor(4);
   gr->SetMarkerStyle(21);
   gr->SetTitle("a simple graph");
   gr->GetXaxis()->SetTitle("X title");
   gr->GetYaxis()->SetTitle("Y title");
   pfit1->SetLineColor(2);
   pfit2->SetLineColor(3);
   gr->Fit("pfit1","q");
   Double_t pfit1chi2 = pfit1->GetChisquare();
   Double_t pfit1ndf = pfit1->GetNDF();
   printf("Fit 1: %f %f \n",pfit1chi2,pfit1ndf);
   Double_t pfit1chi2ndf = pfit1chi2/pfit1ndf;
   //gr->Fit("pfit2","q+");
   //Double_t pfit2chi2 = pfit2->GetChisquare();
   //Double_t pfit2ndf = pfit2->GetNDF();
   //printf("Fit 2: %f %f \n",pfit2chi2,pfit2ndf);
   //Double_t pfit2chi2ndf = pfit2chi2/pfit2ndf;
   gr->Draw("AP");

   // draw the legend
   Char_t message[80];
   TLegend *legend=new TLegend(0.4,0.15,0.88,0.35);
   legend->SetTextFont(72);
   legend->SetTextSize(0.04);
   legend->AddEntry(gr,"Data","lpe");
   sprintf(message,"Linear Fit: #chi^{2}/NDF = %.2f",pfit1chi2ndf);
   legend->AddEntry(pfit1,message);
   //sprintf(message,"Quadratic Fit: #chi^{2}/NDF = %.2f",pfit2chi2ndf);
   //legend->AddEntry(pfit2,message);
   legend->Draw();

   // TCanvas::Update() draws the frame, after which one can change it
   c1->Update();
   c1->GetFrame()->SetFillColor(21);
   c1->GetFrame()->SetBorderSize(12);
   c1->Modified();
}
