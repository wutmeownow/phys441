#include <math.h>
#include <TMatrixD.h>
#include <iostream.h>

Double_t fit(Double_t *x, Double_t *par)
{
	Double_t Pi=3.14159265;
	Double_t a=0.5*pow(Pi/2.0,0.5)*par[1];
	Float_t xx = x[0];
	Double_t f = 1000.0/200.0*par[0]*pow(2.0/Pi,0.5)/pow(a,3)*xx*xx*exp(-1.0*xx*xx/(2.0*a*a));
	return f;
}

void BrashFinalProject() {

	ifstream f("C:/root/macros/vmagF.txt");
	Int_t i=0;
	const Int_t n = 10000;
	Double_t x[n];
	while(i<n) {
		f>>x[i];
		i++;
	}
	TCanvas *c1 = new TCanvas("canvas","Velocity Distribution",40,40,600,600);
	gStyle->SetOptStat(1);		// turns on stat box
	gStyle->SetOptFit(0);		// turns off fit box
	c1->ToggleEventStatus();	// turns on event status bar
	TH1D *h1 = new TH1D("h1", "Velocity Distribution", 300, 0, 1000);
	for(int i=0;i<n;i++){
			h1->Fill(x[i]);
		}
	
	TF1 *pfit1 = new TF1("fit",fit,0.0,1000.0,2);
	pfit1->SetParameters(12000.0,400.0);
	pfit1->SetParNames("N","Mean");
	pfit1->SetLineColor(2);
	h1->Fit("fit","V");

	Double_t yy[15]; Double_t xx[15];
	// Mean Velocity Data From Temp: 20k to 300k collected from repeated trials
	xx[0]=20; xx[1]=40; xx[2]=60; xx[3]=80; xx[4]=100; xx[5]=120; xx[6]=140; xx[7]=160; xx[8]=180; xx[9]=200; xx[10]=220; 
	xx[11]=240; xx[12]=260; xx[13]=280; xx[14]=300;
	yy[0]=103.1; yy[1]=145.8; yy[2]=178.5; yy[3]=206.1; yy[4]=230.5; yy[5]=252.5; yy[6]=272.7; yy[7]=291.5; yy[8]=309.2;
	yy[9]=325.9; yy[10]=341.8; yy[11]=356.8; yy[12]=371.4; yy[13]=385.2; yy[14]=398.3;

	TCanvas *c2 = new TCanvas("canvas2","Mean VS Temperature",40,40,600,600);
	gr1 = new TGraph(15, xx, yy);
	gr1->SetMarkerStyle(4);
	gr1->Draw("ADP");

}