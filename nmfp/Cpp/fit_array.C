#include "TF2.h"
#include "TH2.h"
#include "TCutG.h"
#include "TMath.h"
#include "TCanvas.h"
#include "TStyle.h"

// Function for 2D Gaussian
//
Double_t g2(Double_t *x, Double_t *par) {
   Double_t r1 = Double_t((x[0]-par[1])/par[2]);
   Double_t r2 = Double_t((x[1]-par[3])/par[4]);
   return par[0]*TMath::Exp(-0.5*(r1*r1+r2*r2));
}   

// Function for creating three 2D Gaussians histogram
//
Double_t fun2(Double_t *x, Double_t *par) {
   Double_t *p1 = &par[0];
   Double_t *p2 = &par[5];
   Double_t *p3 = &par[10];
   Double_t *p4 = &par[15];
   Double_t result = g2(x,p1) + g2(x,p2) + g2(x,p3) + g2(x,p4);
   return result;
}

void fit_array() {
   gStyle->SetOptStat(kTRUE); 
   gStyle->SetPalette(1); 
   
   // assign positions and normalizations of three 2D Gaussians
   const Int_t npar = 20;
   Double_t f2params[npar] = {100,-3,1.5,-3,1.5,160,-3,1.1,3,1.1,40,3,1,-3,1,250,3,0.7,3,0.7};
   TF2 *f2 = new TF2("f2",fun2,-10,10,-10,10, npar);
   f2->SetParameters(f2params);

   //Create an histogram and fill it randomly with f2
   TH2F *h2 = new TH2F("h2","Triple Gaussian",40,-10,10,40,-10,10);
   Int_t nentries = 100000;
   h2->FillRandom("f2",nentries);

   const Int_t ncuts=4;
   
   TCanvas *c2 = new TCanvas("c2","c2",10,10,700,500);
   c2->Divide(3,ncuts);
   TCanvas *c1 = new TCanvas("c1","c1",510,510,700,500);

   Double_t Pi = 3.14159265;
   const Int_t ng2par = 5;
   Double_t g2params[ncuts][npar];
   Double_t nx0, x0, sigmax, ny0, y0, sigmay;
   TString buffer;

   TCutG* cut[ncuts];  // array of pointers to various 2D cuts
   TF1* fitx[ncuts]; // array of pointers to X-projection Guassian fits
   TF1* fity[ncuts]; // array of pointers to Y-projection Gaussian fits
   TF2* g2fit[ncuts]; // array of pointers to 2D Gaussian fits (created from 1D Gaussian projection fits) 

   for (Int_t i=0; i<ncuts; i++){

   	c1->Update();
   	c1->cd();
   	h2->Draw();
	// plot previous cuts already chosen by user
	for (Int_t j=0; j<i; j++){
		cut[j]->SetLineColor(kRed);
		cut[j]->Draw("same");
	}

   	// Get new 2D cut from user
	cout << "Drew Histogram ... now defining cut ... " << endl;
   	cut[i]=(TCutG*)gPad->WaitPrimitive("CUTG","CutG");
	buffer.Form("cut%d",i);
	cout << "cut name = " << buffer << endl;
   	cut[i]->SetName(buffer);
   	cut[i]->Print();
   	cout << "Finished defining cut and setting name = " << buffer << endl;

   	// create X and Y projections, fit each with a 1D Gaussian, and store fit results
	c2->Update();
	TString mycut = "["+buffer+"]";
	c2->cd(3*i+1);
   	h2->Draw(mycut);
   	c2->cd(3*i+2);
   	h2->ProjectionX("a",-1,-1,mycut);
   	a->Draw();
   	a->Fit("gaus");
   	fitx[i] = a->GetFunction("gaus");
   	nx0 = fitx[i]->GetParameter(0);
   	x0 = fitx[i]->GetParameter(1);
   	sigmax = fitx[i]->GetParameter(2);
   	cout << "Fit Parameters = " << nx0 << " " << x0 << " " << sigmax << endl;
   	c2->cd(3*i+3);
   	h2->ProjectionY("b",-1,-1,mycut);
   	b->Draw();
   	b->Fit("gaus");
   	fity[i] = b->GetFunction("gaus");
   	ny0 = fity[i]->GetParameter(0);
   	y0 = fity[i]->GetParameter(1);
   	sigmay = fity[i]->GetParameter(2);
   	cout << "Fit Parameters = " << ny0 << " " << y0 << " " << sigmay << endl;
   	cout << "Redraw histogram ... " << endl;

   	// Combine X and Y Gaussian fits into 2D Gaussian fit
	g2params[i][0] = (nx0*sigmax+ny0*sigmay)/(2.0*sqrt(2.0*Pi)*sigmax*sigmay);
   	g2params[i][1] = x0;
   	g2params[i][2] = sigmax;
   	g2params[i][3] = y0;
   	g2params[i][4] = sigmay;
   	g2fit[i] = new TF2("g2fit0",g2,-10,10,-10,10, ng2par);
   	g2fit[i]->SetParameters(g2params[i]);

   }

   // Replot last cut defined above
   c1->cd();
   cut[ncuts-1]->SetLineColor(kRed);
   cut[ncuts-1]->Draw("same");
   
   // Replot all data and cut fits in new Canvas
   TCanvas *c3 = new TCanvas("c3","c3",1010,1010,700,500);
   c3->cd();
   h2->Draw();
   h2->SetFillColor(38);
   // Plot 2D Gaussian fits to all 2D cut regions defined above
   for (Int_t k=0; k<ncuts; k++){
   	g2fit[k]->SetNpx(80);
   	g2fit[k]->SetNpy(80);
	buffer.Form("cut%d",k);
	TString myhistspec="CONT0 same ["+buffer+"]";
   	g2fit[k]->Draw(myhistspec);
	cout << "2D Cut Number "<<k<<": X = "<<g2params[k][1]<<" +/- "<<g2params[k][2]/sqrt(g2params[k][0])<<" Y = "<<g2params[k][3]<<" +/- "<<g2params[k][4]/sqrt(g2params[k][0])<<endl;
   }

}
