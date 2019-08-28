#include <math.h>
#include <TMatrixD.h>
#include <iostream>

void HwTwo(){

	const int n = 5;
	const int m = 2;
	Int_t contr = 1;
	Double_t x[n];
	Double_t y[n];
	Double_t YLine = 0;
	TMatrixD V(m+1,1);
	TMatrixD A(m+1,m+1);
	TMatrixD C(m+1,1);
	TMatrixD Ainv(m+1,m+1);

	x[0] = -2;
	x[1] = -1;
	x[2] = 0;
	x[3] = 1;
	x[4] = 2;

	y[0] = 5.94824;
	y[1] = 3.13729;
	y[2] = 2.17163;
	y[3] = 2.89610;
	y[4] = 6.08081;

	for (int k = 0; k < (m+1); k++) {
		V(k,0)=0.0;
		for (int i = 0; i < (m+1); i++){
			A(k,i)=0.0;
			for (int j = 0; j < n; j++) {
				A(k,i) = A(k,i) + (pow(x[j],(i+k)));
				V(k,0) = V(k,0) + (y[j]*pow(x[j],k));
				//std::cout<<"V = "<<V(k,0)<<std::endl;
				//std::cout<<"A = "<<A(k,i)<<std::endl;
			}
		}
	}

	Ainv = A.Invert();

	for (int k = 0; k < (m+1); k++) {
		C(k,0)=0.0;
		for (int i = 0; i < (m+1); i++) {
			C(k,0) = C(k,0) + (Ainv(k,i)*V(i,0));
		}
	}

	//for (int i = 0; i < (m+1); i++) {
	//	YLine = YLine + (C(i,0)*pow(x,i));
	//}

	std::cout<< C(0,0) << " " << C(1,0) << " " << C(2,0) << std::endl;

	//for(int i =0; i <5; i++) {
	//	std::cout<<x[i]<<"   "<<y[i]<<std::endl;
	//}
	
	TCanvas *c1 = new TCanvas("c1","HwTwo",200,10,700,500);
	c1->SetFillColor(42);
	c1->SetGrid();
	gStyle->SetOptStat(1);
	gStyle->SetOptFit(1);
	gr = new TGraph(5,x,y);
	gr->Fit("pol2");
//	gr->plot(Yline);
	gr->SetMarkerColor(4);
	gr->SetMarkerStyle(21);
	gr->SetTitle("HwTwo");
	gr->GetXaxis()->SetTitle("X title");
	gr->GetYaxis()->SetTitle("Y title");
	gr->Draw("ADP");
	c1->Update();
}
