#include <math.h>
#include <TMatrixD.h>
#include <iostream>

void HwThree() {

	const int n = 7;
	const int m = 2;
	const double Aguess = 0.4;
	const double Bguess = 0.6;
	Int_t contr = 1;
	Int_t conv = 0;
	Double_t x[n];
	Double_t y[n];
	Double_t ex[n];
	Double_t ey[n];
	Double_t det;
	TMatrixD BetaOld(m,1);
	TMatrixD BetaNew(m,1);
	TMatrixD DeltaY(n,1);
	TMatrixD J(n,m);
	TMatrixD W(n,n);
	TMatrixD Unc(m,1);
	BetaOld(0,0) = Aguess;
	BetaOld(1,0) = Bguess;

	x[0] = 0.038;
	x[1] = 0.194;
	x[2] = 0.425;
	x[3] = 0.626;
	x[4] = 1.253;
	x[5] = 2.500;
	x[6] = 3.740;

	y[0] = 0.050;
	y[1] = 0.127;
	y[2] = 0.094;
	y[3] = 0.2122;
	y[4] = 0.2729;
	y[5] = 0.2665;
	y[6] = 0.3317;

	ex[0] = 0;
	ex[1] = 0;
	ex[2] = 0;
	ex[3] = 0;
	ex[4] = 0;
	ex[5] = 0;
	ex[6] = 0;

	ey[0] = 0.010;
	ey[1] = 0.010;
	ey[2] = 0.030;
	ey[3] = 0.030;
	ey[4] = 0.030;
	ey[5] = 0.020;
	ey[6] = 0.010;

	while (conv == 0) {

		// Calculate DeltaY

		for (int i = 0; i < n ; i++) {
			DeltaY(i,0) = (y[i] - ((BetaOld(0,0) * x[i])/(BetaOld(1,0) + x[i])));
		}

		// Calculate J

		for (int j = 0; j < m; j++) {
			if (j == 0) {
				for (int i = 0; i < n; i++) {
				J(i,0) = (x[i]/(BetaOld(1,0)+x[i]));
				}
			}
			else {
				for (int i = 0; i < n; i++) {
				J(i,1) = (((-1)*BetaOld(0,0)*x[i])/(pow((BetaOld(1,0) + x[i]),2)));
				}
			}
		}

		// Calculate W
	
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (i == j) {
				W(i,j) = pow(ey[i],2);
				}
				else {
					W(i,j) = 0;
				}
			}
		}		

		// Calculate Jtrans

		TMatrixD Jtrans(TMatrixD::kTransposed,J);

		// Calculate WJ
	
		TMatrixD WJ(W,TMatrixD::kMult,J);

		// Calculate JtransWJ and Uncertainties

		TMatrixD JtransWJ(Jtrans,TMatrixD::kMult,WJ);
		//std::cout<<"JtransWJ = "<<JtransWJ(0,0)<<std::endl;
		//std::cout<<"JtransWJ = "<<JtransWJ(1,1)<<std::endl;
		for (int i = 0; i < m; i++) {
			Unc(i,0) = sqrt(JtransWJ(i,i));
		}

		// Calculate invJtransWJ

		TMatrixD invJtransWJ = JtransWJ.InvertFast(&det);

		// Calculate WDeltaY

		TMatrixD WDeltaY(W,TMatrixD::kMult,DeltaY);

		// Calculate JtransWDeltaY

		TMatrixD JtransWDeltaY(Jtrans,TMatrixD::kMult,WDeltaY);

		// Calculate DeltaBeta

		TMatrixD DeltaBeta(invJtransWJ,TMatrixD::kMult,JtransWDeltaY);
		//std::cout<<"DeltaBeta1 = "<<DeltaBeta(0,0)<<std::endl;
		//std::cout<<"DeltaBeta2 = "<<DeltaBeta(1,0)<<std::endl;

		// Calculate BetaNew

		BetaNew = (BetaOld +DeltaBeta);
		BetaOld = BetaNew;

		// Checks for convergence
		
		Int_t check = 0;
		for (int i = 0; i < m; i++) {
			if (DeltaBeta(i,0)/BetaOld(i,0) < 0.001 && DeltaBeta(i,0)/BetaOld(i,0) > -0.001){
				check++;
			}
		}	
		if (check == m) {
			conv = 1;
		}
	}
	
	std::cout<<"A = "<<BetaOld(0,0)<<" +/- "<<Unc(0,0)<<std::endl;
	std::cout<<"B = "<<BetaOld(1,0)<<" +/- "<<Unc(1,0)<<std::endl;


	TCanvas *c1 = new TCanvas("c1","HwThree",200,10,700,500);
	c1->SetFillColor(42);
	c1->SetGrid();
	gStyle->SetOptStat(1);
	gStyle->SetOptFit(1);
	gr = new TGraphErrors(7,x,y,ex,ey);
	//gr->Fit("fitfunction", "V");
	gr->SetMarkerColor(4);
	gr->SetMarkerStyle(21);
	gr->SetTitle("HwThree");
	gr->GetXaxis()->SetTitle("X title");
	gr->GetYaxis()->SetTitle("Y title");
	gr->Draw("AP");
	c1->Update();
}
