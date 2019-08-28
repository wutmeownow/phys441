#include "TF2.h"
#include "TH2.h"
#include "TCutG.h"
#include "TMath.h"
#include "TCanvas.h"
#include "TStyle.h"


//+ Fitting a 2-D histogram (a variant)
// This tutorial illustrates :
//  - how to create a 2-d function
//  - fill a 2-d histogram randomly from this function
//  - fit the histogram
//  - display the fitted function on top of the histogram (lego-plot)
//    using a surface plot in a sub-range of the histogram.
//
// This example can be executed via the interpreter or/and the compiler
//   root > .x fit2a.C
//   root > .x fit2a.C++
//Author: Rene Brun
         
Double_t g2(Double_t *x, Double_t *par) {
   Double_t r1 = Double_t((x[0]-par[1])/par[2]);
   Double_t r2 = Double_t((x[1]-par[3])/par[4]);
   return par[0]*TMath::Exp(-0.5*(r1*r1+r2*r2));
}   


Double_t fun2(Double_t *x, Double_t *par) {
   Double_t *p1 = &par[0];
   Double_t *p2 = &par[5];
   Double_t *p3 = &par[10];
   Double_t result = g2(x,p1) + g2(x,p2) + g2(x,p3);
   return result;
}

void fit2c() {
   gStyle->SetOptStat(kTRUE); 
   gStyle->SetPalette(1); 
   
   const Int_t npar = 15;
   Double_t f2params[npar] = {100,-3,3,-3,3,160,0,0.8,0,0.9,40,4,0.7,4,0.7};
   TF2 *f2 = new TF2("f2",fun2,-10,10,-10,10, npar);
   f2->SetParameters(f2params);

   //Create an histogram and fill it randomly with f2
   TH2F *h2 = new TH2F("h2","Triple Gaussian",40,-10,10,40,-10,10);
   Int_t nentries = 100000;
   h2->FillRandom("f2",nentries);

   const Int_t ncuts=3;
   
   TCanvas *c2 = new TCanvas("c2","c2",10,10,700,500);
   c2->Divide(1,3);
   TCanvas *c1 = new TCanvas("c1","c1",510,510,700,500);

   const Int_t ncuts=3;
   Double_t Pi = 3.14159265;
   const Int_t ng2par = 5;
   Double_t g2params[npar];
   Double_t nx0, x0, sigmax, ny0, y0, sigmay;

   c1->Update();
   c1->cd();
   h2->Draw();
//
   cout << "Drew Histogram ... now defining cut ... " << endl;
   cut0=(TCutG*)gPad->WaitPrimitive("CUTG","CutG");
   cut0->SetName("cut0");
   cut0->Print();
   cout << "Finished defining cut and setting name ... " << endl;
//
   c2->Update();

   c2->cd(1);
   h2->Draw("[cut0]");
   c2->cd(2);
   h2->ProjectionX("a",-1,-1,"[cut0]");
   a->Draw();
   a->Fit("gaus");
   TF1 *fitx0 = a->GetFunction("gaus");
   nx0 = fitx0->GetParameter(0);
   x0 = fitx0->GetParameter(1);
   sigmax = fitx0->GetParameter(2);
   cout << "Fit Parameters = " << nx0 << " " << x0 << " " << sigmax << endl;
   c2->cd(3);
   h2->ProjectionY("b",-1,-1,"[cut0]");
   b->Draw();
   b->Fit("gaus");
   TF1 *fity0 = b->GetFunction("gaus");
   ny0 = fity0->GetParameter(0);
   y0 = fity0->GetParameter(1);
   sigmay = fity0->GetParameter(2);
   cout << "Fit Parameters = " << ny0 << " " << y0 << " " << sigmay << endl;
   cout << "Redraw histogram ... " << endl;

   g2params[0] = (nx0*sigmax+ny0*sigmay)/(2.0*sqrt(2.0*Pi)*sigmax*sigmay);
   g2params[1] = x0;
   g2params[2] = sigmax;
   g2params[3] = y0;
   g2params[4] = sigmay;
   TF2 *g2fit0 = new TF2("g2fit0",g2,-10,10,-10,10, ng2par);
   g2fit0->SetParameters(g2params);
   
   c1->Update();
   c1->cd();
   h2->Draw();
   cut0->SetLineColor(kRed);
   cut0->Draw("same");
//
   cout << "Drew Histogram ... now defining cut ... " << endl;
   cut1=(TCutG*)gPad->WaitPrimitive("CUTG","CutG");
   cut1->SetName("cut1");
   cut1->Print();
   cout << "Finished defining cut and setting name ... " << endl;
//
   c2->Update();

   c2->cd(1);
   h2->Draw("[cut1]");
   c2->cd(2);
   h2->ProjectionX("a",-1,-1,"[cut1]");
   a->Draw();
   a->Fit("gaus");
   TF1 *fitx1 = a->GetFunction("gaus");
   nx0 = fitx1->GetParameter(0);
   x0 = fitx1->GetParameter(1);
   sigmax = fitx1->GetParameter(2);
   cout << "Fit Parameters = " << nx0 << " " << x0 << " " << sigmax << endl;
   c2->cd(3);
   h2->ProjectionY("b",-1,-1,"[cut1]");
   b->Draw();
   b->Fit("gaus");
   TF1 *fity1 = b->GetFunction("gaus");
   ny0 = fity1->GetParameter(0);
   y0 = fity1->GetParameter(1);
   sigmay = fity1->GetParameter(2);
   cout << "Fit Parameters = " << ny0 << " " << y0 << " " << sigmay << endl;
   cout << "Redraw histogram ... " << endl;   
   
   g2params[0] = (nx0*sigmax+ny0*sigmay)/(2.0*sqrt(2.0*Pi)*sigmax*sigmay);
   g2params[1] = x0;
   g2params[2] = sigmax;
   g2params[3] = y0;
   g2params[4] = sigmay;
   TF2 *g2fit1 = new TF2("g2fit1",g2,-10,10,-10,10, ng2par);
   g2fit1->SetParameters(g2params);
   
   c1->Update();
   c1->cd();
   h2->Draw();
   cut1->SetLineColor(kRed);
   cut0->Draw("same");
   cut1->Draw("same");
//
   cout << "Drew Histogram ... now defining cut ... " << endl;
   cut2=(TCutG*)gPad->WaitPrimitive("CUTG","CutG");
   cut2->SetName("cut2");
   cut2->Print();
   cout << "Finished defining cut and setting name ... " << endl;
//
   c2->Update();

   c2->cd(1);
   h2->Draw("[cut2]");
   c2->cd(2);
   h2->ProjectionX("a",-1,-1,"[cut2]");
   a->Draw();
   a->Fit("gaus");
   TF1 *fitx2 = a->GetFunction("gaus");
   nx0 = fitx2->GetParameter(0);
   x0 = fitx2->GetParameter(1);
   sigmax = fitx2->GetParameter(2);
   cout << "Fit Parameters = " << nx0 << " " << x0 << " " << sigmax << endl;
   c2->cd(3);
   h2->ProjectionY("b",-1,-1,"[cut2]");
   b->Draw();
   b->Fit("gaus");
   TF1 *fity2 = b->GetFunction("gaus");
   ny0 = fity2->GetParameter(0);
   y0 = fity2->GetParameter(1);
   sigmay = fity2->GetParameter(2);
   cout << "Fit Parameters = " << ny0 << " " << y0 << " " << sigmay << endl;
   cout << "Redraw histogram ... " << endl; 

   g2params[0] = (nx0*sigmax+ny0*sigmay)/(2.0*sqrt(2.0*Pi)*sigmax*sigmay);
   g2params[1] = x0;
   g2params[2] = sigmax;
   g2params[3] = y0;
   g2params[4] = sigmay;
   TF2 *g2fit2 = new TF2("g2fit2",g2,-10,10,-10,10, ng2par);
   g2fit2->SetParameters(g2params);

   c1->Update();
   c1->cd();
   h2->Draw();
   cut2->SetLineColor(kRed);
   cut0->Draw("same");
   cut1->Draw("same");
   cut2->Draw("same");

   TCanvas *c3 = new TCanvas("c3","c3",1010,1010,700,500);
   c3->cd();
   //h2->Draw("lego2 0");
   h2->Draw();
   h2->SetFillColor(38);
   g2fit0->SetNpx(80);
   g2fit0->SetNpy(80);
   g2fit0->Draw("CONT0 same [cut0]");
   g2fit1->SetNpx(80);
   g2fit1->SetNpy(80);
   g2fit1->Draw("CONT0 same [cut1]");
   g2fit2->SetNpx(80);
   g2fit2->SetNpy(80);
   g2fit2->Draw("CONT0 same [cut2]");


}

   //Fit h2 with original function f2
//   Float_t ratio = 4*nentries/100000;
//   f2params[ 0] *= ratio;
//   f2params[ 5] *= ratio;
//   f2params[10] *= ratio;
//   f2->SetParameters(f2params);
//   h2->Fit("f2","N");
//   TCutG *cutg = new TCutG("cutg",5);
//   cutg->SetPoint(0,-7,-7);
//   cutg->SetPoint(1, 2,-7);
//   cutg->SetPoint(2, 2, 2);
//   cutg->SetPoint(3,-7, 2);
//   cutg->SetPoint(4,-7,-7);
//   h2->Draw("lego2 0");
//   h2->SetFillColor(38);
//   f2->SetNpx(80);
//   f2->SetNpy(80);
//   f2->Draw("surf1 same bb [cutg]");
//   return c;
