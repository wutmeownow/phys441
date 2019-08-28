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

void fit2b() {
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
   TCanvas *c1 = new TCanvas("c1","c1",10,510,700,1000);

   char cutname[20];

   for (Int_t i=0; i<ncuts; i++){
   	c1->Update();
   	c1->cd();
   	h2->Draw();
//
   	cout << "Drew Histogram ... now defining cut ... " << endl;
	sprintf(cutname,"cut%d",convert(i));
   	TCutG* cut[i]=(TCutG*)gPad->WaitPrimitive("CUTG","CutG");
	cout << "cut name = " << cutname << endl;
   	cut[i]->SetName(cutname);
	cut[i]->Print();
   	cout << "Finished defining cut and setting name ... " << endl;
//
   //const Int_t npfit = 5;
   //Double_t fitparams[npfit] = {40,4.0,1.0,4.0,1.0};
   //TF2 *ffit = new TF2("g2","xygaus",-10,10,-10,10);
   //ffit->SetParameters(fitparams);
   //h2->Fit("g2","[cut1]");
//
   	c2->Update();

   	c2->cd(1);
   	h2->Draw("AP",cutname);
   	c2->cd(2);
   	h2->ProjectionX("a",-1,-1,cutname);
   	a->Draw();
   	a->Fit("gaus");
   	c2->cd(3);
   	h2->ProjectionY("b",-1,-1,cutname);
   	b->Draw();
   	b->Fit("gaus");
   	cout << "Redraw histogram ... " << endl;
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
}
