#include <iostream>
#include "bisection.h"

void plotMacro(){
	
	int steps[10000];
	
	for(int n = 100; n<=100; n++){
		int j = populateAndSearch(10000,-4,4,n);
		cout << "Called populateAndSearch ... j = " << j << endl; 
        	steps[n-1]=j;
	}
    for(int n = 100; n<101; n++){
        cout << n << " - " << steps[n] << endl;
	}
	/*
	Double_t xAxis[10000];
	for(int i = 1; i<10000; i++){
		xAxis[i] = i;
	}
	
	gStyle->SetOptFit(kFALSE);

	TGraph *gr = new TGraph(10000, xAxis, steps);
	TCanvas *c1 = new TCanvas("c1","steps vs. search size",200,10,600,400);

	c1->SetFillColor(42);
	c1->SetGrid();
	//c1->SetLogx();
	//c1->SetLogy();

	gr->SetMarkerStyle(21);
	gr->SetMarkerColor(37);
	gr->SetTitle("Steps vs. Search Size");
	gr->GetXaxis()->SetTitle("Search Size");
	gr->GetYaxis()->SetTitle("Steps");
	gr->Draw("AP");

	c1->Update();
	c1->GetFrame()->SetFillColor(21);
	c1->GetFrame()->SetBorderSize(12);
	c1->Modified();
     */
	
}
