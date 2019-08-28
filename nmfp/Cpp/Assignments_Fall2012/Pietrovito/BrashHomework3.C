#include <math.h>
#include <TMatrixD.h>
#include <iostream.h>

void BrashHomework3() {

	const Int_t m = 1;		// m is the order of fit
	const Int_t n = 15;		// n is the number of data points
	const Int_t nrows = m+1;
	const Int_t ncols = m+1;

	// data for a higher order fit
	Double_t x[n], y[n];
	x[0]=1; x[1]=2; x[2]=3; x[3]=4; x[4]=5; x[5]=6; x[6]=7; x[7]=8; x[8]=9; x[9]=10; x[10]=11; x[11]=12; x[12]=13; x[13]=14; x[14]=15;
	y[0]=1.6711; y[1]=2.00994; y[2]=2.26241; y[3]=2.18851; y[4]=2.33006; y[5]=2.42660; y[6]=2.48424; y[7]=2.63729; y[8]=2.77163; y[9]=2.89610;
	y[10]=2.89083; y[11]=3.08081; y[12]=3.05305; y[13]=3.24079; y[14]=3.36212;

	TMatrixD A(nrows, ncols);
	TMatrixD V(nrows, 1);
	Double_t sigmaY[n];
	bool uncertainty = true;

	// Assign uncertainties
	for(Int_t k=0; k<n; k++) {
		sigmaY[k] = 0.1;	
	}

	// Calculating matrix A
	for(Int_t k=0; k<(m+1); k++) {
		for(Int_t i=0; i<(m+1); i++) {
			for(Int_t j=0; j<(n); j++)
				if(uncertainty == true) {
					A(k, i) = A(k, i) + pow(x[j], (i+k))/pow(sigmaY[j],2);
				}
				else {
					A(k, i) = A(k, i) + pow(x[j], (i+k));
				}
			}
		}


	// Calculating matrix V
	for(Int_t k=0; k<(m+1); k++) {
		for(Int_t j=0; j<n; j++) {
			if(uncertainty == true) {
					V(k, 0) = V(k, 0) + y[j]*pow(x[j], k)/pow(sigmaY[j],2);
				}
				else {
					V(k, 0) = V(k, 0) + y[j]*pow(x[j], k);
				}
		}
	}

	// Calculating matrix C
	TMatrixD AInverse(nrows, ncols);
	AInverse = A.Invert();
	TMatrixD C(AInverse,TMatrixD::kMult,V);

	for(int i=0; i<(m+1); i++) {
		std::cout << "C" << i << ": " << (C[i][0]) << std::endl;
	}

	//chi Square
	Double_t chi = 0;
	Double_t observed = 0;
	Double_t expected = 0;
	for(int i=0; i<n; i++) {
		observed = y[i];
		expected = C[0][0]+x[i]*C[1][0];
		chi += (pow((observed - expected),2))/expected;
	}
	std::cout<< "Chi Squared= " << chi << std::endl;

	TCanvas *c1 = new TCanvas("c1","Curve Fitting Part I",200,10,700,500);
	
	c1->ToggleEventStatus();
	c1->SetFillColor(0);
	gStyle->SetOptFit(1);

	for (Int_t i=0;i<n;i++) {
		printf(" i %i  %f %f \n",i,x[i],y[i]);
	}
	gr1 = new TGraph(n,x,y);
	gr1->SetLineColor(2);
	gr1->SetLineWidth(4);
	gr1->SetMarkerColor(4);
	gr1->SetMarkerStyle(21);

	Double_t xx[2]; Double_t yy[2];
	xx[0]=0; yy[0]=C[0][0]; xx[1]=16; yy[1]=C[0][0]+(16*C[1][0]);
	gr2 = new TGraph(2,xx,yy);
	gr2->SetLineColor(2);
	gr2->SetLineWidth(4);
	gr2->SetMarkerColor(0);
	gr2->SetMarkerStyle(21);

	TMultiGraph *mg = new TMultiGraph();
    mg->Add(gr1,"DP");
    mg->Add(gr2,"CP");
    mg->Draw("A");

	// TCanvas::Update() draws the frame, after which one can change it
	c1->Update();
	c1->GetFrame()->SetFillColor(0);
	c1->GetFrame()->SetBorderSize(12);
	c1->Modified();
}