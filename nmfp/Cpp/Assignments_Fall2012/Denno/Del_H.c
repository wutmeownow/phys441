#include <stdio.h>
#include <math.h>
#include <TGraph>

void Del_H () {
	double fxh;
	
	TCanvas *c1 = new TCanvas("c1","Delta H vs h",200,10,700,500);
	
	c1->SetFillColor(42);
	c1->SetGrid();
	
	const Int_t n = 20;
	Double_t h[n], delh[n];
	for (int i=0; i<n; i++) {
		h[i]=pow(10,(i-n));
		delh[i]=abs(2-((pow(1+h[i],2)-1)/h[i]));
	}
	
	
	gr = new TGraph(n,h,delh);
	gr->SetLineWidth(4);
	gr->SetMarkerColor(4);
	gr->SetMarkerStyle(21);
	gr->SetTitle("Delta H vs. h");
	gr->GetXaxis()->SetTitle("H");
	gr->GetYaxis()->SetTitle("Delta H");
	gr->Draw("ACP");
	c1->Update();
	c1->SetLogx();
}
