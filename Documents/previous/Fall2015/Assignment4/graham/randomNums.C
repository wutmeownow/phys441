#include "TRandom.h"

void randomNums(){
	int n = 300000;
	int bins = 100;
	TH1D *h1 = new TH1D("h1", "Uniform 0-1", bins, -0.1, 1.1);
	TH1D *h2 = new TH1D("h2", "Triangular 0-2", bins, -0.1, 2.1);
	TH1D *h3 = new TH1D("h3", "Exponential 0-3", bins, -0.1, 3.1);
	TH1D *h4 = new TH1D("h4", "Gaussian -3-3", bins, -3.1, 3.1);
	TH1D *h5 = new TH1D("h5", "Gaussian 0-2", bins, -0.1, 2.1);
	TRandom3 rand;
	for (int i = 0; i<n; i++){
		h1->Fill(rand.Uniform());
		Double_t r1;
		while (true){
			r1 = rand.Rndm()*2;
			Double_t p = -fabs(r1-1)+1;
			if (rand.Rndm()*2 < p) break;
		} 
		h2->Fill(r1);
		h3->Fill(rand.Exp(1));
		h4->Fill(rand.Gaus());
		h5->Fill(rand.Gaus(1,0.3));
	}
  
	//gStyle->SetOptFit(kFALSE);	
	gStyle->SetOptFit(1);	
	TCanvas *c1 = new TCanvas("c1","Random Number Plots",200,10,700,500);
	c1->Divide(2,3);
	c1->SetFillColor(42);
	c1->SetGrid();
	c1->cd(1);
	h1->Draw();
	c1->cd(2);
	h2->Draw();
	c1->cd(3);
	h3->Draw();
	c1->cd(4);
	h4->Draw();
	c1->cd(5);
	h5->Draw();
	c1->Update();
	c1->GetFrame()->SetFillColor(21);
	c1->GetFrame()->SetBorderSize(12);
	c1->Modified();
}
