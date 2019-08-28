#include <math.h>
void HwOneFirstDerivative(){
	
	TCanvas *c1 = new TCanvas("c1","First Derivative Comparisons",200,10,700,500);
	c1->SetFillColor(42);
	c1->SetGrid();
	c1->SetLogx();

	Int_t z = 1;
	Int_t f = z*z;
	Int_t fprime = 2*z;
	Double_t deltah = 0;
	const Int_t a = 21;
	Double_t x[a], y[a];
	Double_t h = 0;
	Int_t hold = 0;
	for (Int_t n=-20;n<1;n++) {
		h = pow(10,n);
		Double_t fxplush = (z+h)*(z+h);
		deltah = (fprime-((fxplush-f)/h));
		if (deltah < 0) {
			deltah = deltah*-1;
		}
		x[hold] = h;
		y[hold] = deltah;
		hold++;	
	}
	for(int i =0; i < 21; i++) {
		std::cout<<x[i]<<"   "<<y[i]<<std::endl;
	}
	gr = new TGraph(21,x,y);
	gr->GetYaxis()->SetRangeUser(0.,2.);
	gr->SetLineColor(2);
	gr->SetLineWidth(4);
	gr->SetMarkerColor(4);
	gr->SetMarkerStyle(21);
	gr->SetTitle("First Derivative Comparisons");
	gr->GetXaxis()->SetTitle("X title");
	gr->GetYaxis()->SetTitle("Y title");
	gr->Draw("ACP");
	c1->Update();
} 
