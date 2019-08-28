#include <math.h>
#include <TMatrixD.h>
#include <iostream.h>

void BrashHomework6() {
	
	// Data Points
	Double_t x[7], y[7];
	x[0]=0.038;	x[1]=0.194;	x[2]=0.425;	x[3]=0.626;	x[4]=1.253;	x[5]=2.5;	x[6]=3.740;
	y[0]=0.05;	y[1]=0.127;	y[2]=0.094;	y[3]=0.2122;y[4]=0.2729;y[5]=0.2665;y[6]=0.3317;
	// Uncertainty
	Double_t deltaY[7];
	deltaY[0]=0.01;	deltaY[1]=0.01;	deltaY[2]=0.03;	deltaY[3]=0.03;	deltaY[4]=0.03;	deltaY[5]=0.02;	deltaY[6]=0.01;

	TMatrixD beta = TMatrixD(2,1);
	// Guess
	beta(0, 0) = 0.2; // A
	beta(1, 0) = 0.3; // B
	Double_t diff = 1;

	//for(int q=0; q<10; q++) {
		// Jacobian
		TMatrixD J = TMatrixD(7,2);
		for(int i=0; i<7; i++) {
			J(i, 0) = x[i]/(beta(1, 0) + x[i]);
			J(i, 1) = (beta(0, 0)*x[i])/pow((beta(1, 0)+x[i]),2);
		}

		// Jacobian Transpose
		TMatrixD JTranspose(TMatrixD::kTransposed, J);

		// Weights
		TMatrixD weight = TMatrixD(7,7);
		for(int i=0; i<7; i++) {
			weight(i, i) = 1/pow(deltaY[i],2);
		}

		// Calculate Y
		TMatrixD Y = TMatrixD(7,1);
		for(int i=0; i<7; i++) {
			Y(i, 0) = y[i] - (beta(0, 0)*x[i])/(beta(1, 0)+x[i]);
		}

		// Find delta beta
		TMatrixD TW(JTranspose, TMatrixD::kMult, weight);
		TMatrixD TWJ(TW, TMatrixD::kMult, J);
		TMatrixD TWJY(TW, TMatrixD::kMult, Y);
		TWJ.InvertFast();
		TMatrixD deltaBeta(TWJ, TMatrixD::kMult, TWJY);

		// Find beta new
		TMatrixD bNew = TMatrixD(2,1);
		for(int i=0; i<2; i++) {
			bNew(i, 0) = beta(i, 0) + deltaBeta(i, 0);
			cout<<"beta["<<i<<"]: "<<bNew(i, 0)<<endl;
		}

		diff = deltaBeta(0, 0)/bNew(0, 0);
		cout<<"Diff: "<<diff<<endl;

		beta(0, 0) = bNew(0, 0);
		beta(1, 0) = bNew(1, 0);

		
	//}
}