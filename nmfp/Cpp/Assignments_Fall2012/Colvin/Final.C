#include <iostream>
#include <math.h>
void Final() {
	TH1D *h1 = new TH1D("h1", "x distribution", 300, 0, 1000);
	Int_t i = 0;
	Double_t x[10000] = 0;
	FILE *f = fopen("vmagF.txt","r");
	while (!feof(f)) {
		fscanf(f,"%lf\n",&x[i]);
		h1->Fill(x[i]);
		i++;
	}
	TCanvas *c1 = new TCanvas("c1","Final",200,10,700,500);
	gStyle->SetOptStat(1);
	gStyle->SetOptFit(1);
	h1->Draw();
	c1->Update(); 
// The mean and RMS width match what i would expect from a Max-Boltz distribution.
}
