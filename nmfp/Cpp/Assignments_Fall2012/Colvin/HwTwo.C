#include <math.h>
#include <TMatrixD.h>
#include <iostream>

void HwTwo(){

	const int n = 5;
	const int m = 2;
	int z = 0;
	Int_t contr = 1;
	Double_t x[n];
	Double_t y[n];
	Double_t ex[n];
	Double_t ey[n];
	TMatrixD V(m+1,1);
	TMatrixD A(m+1,m+1);
	TMatrixD C(m+1,1);
	TMatrixD Ainv(m+1,m+1);
	TMatrixD Cunc(m+1,1);

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

	ex[0] = 0;
	ex[1] = 0;
	ex[2] = 0;
	ex[3] = 0;
	ex[4] = 0;

	ey[0] = 0.1855;
	ey[1] = 0.1855;
	ey[2] = 0.1855;
	ey[3] = 0.1855;
	ey[4] = 0.1855;

	// Calculate V

	for (int k = 0; k < (m+1); k++) {
		for (int j = 0; j < n; j++) {
			V(k,0) = V(k,0) + (y[j]*pow(x[j],k))/(pow(ey[j],2));
			//std::cout<<"V = "<<V(k,0)<<std::endl;
		}
	}

	// Calculate A

	for (int k = 0; k < (m+1); k++) {
		for (int i = 0; i < (m+1); i++){
			for (int j = 0; j < n; j++) {
				A(k,i) = A(k,i) + ((pow(x[j],(i+k)))/(pow(ey[j],2)));
				//std::cout<<"A = "<<A(k,i)<<std::endl;
			}
		}
	}

	// Invert A

	Ainv = A.Invert();

	// Calculates the C values

	for (int k = 0; k < (m+1); k++) {
		for (int i = 0; i < (m+1); i++) {
			C(k,0) = C(k,0) + (Ainv(k,i)*V(i,0));
			//std::cout<<"C("<<k<<",0) = "<<C(k,0)<<std::endl;
		}
	}

	// Calculate C uncertainties
		
	for (int i = 0; i < (m+1); i++) {
		Cunc(z,0) = pow(Ainv(z,i),.5);
		z++;
	}

	// Prints out Coefficients with uncertainties	

	for (int i = 0; i < (m+1); i++) {
		std::cout<<"C"<<i<<" = "<<C(i,0)<<" +/- "<<Cunc(i,0)<<std::endl;
	}
	
	TCanvas *c1 = new TCanvas("c1","HwTwo",200,10,700,500);
	c1->SetFillColor(42);
	c1->SetGrid();
	gStyle->SetOptStat(1);
	gStyle->SetOptFit(1);
	gr = new TGraphErrors(5,x,y,ex,ey);
	gr->Fit("pol2");
	gr->SetMarkerColor(4);
	gr->SetMarkerStyle(21);
	gr->SetTitle("HwTwo");
	gr->GetXaxis()->SetTitle("X title");
	gr->GetYaxis()->SetTitle("Y title");
	gr->Draw("ADP");
	c1->Update();
}
