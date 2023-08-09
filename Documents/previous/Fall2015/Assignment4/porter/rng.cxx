#include <iostream>
#include <TMath.h>
#include <TRandom3.h>

void rng() {

	cout << "What part of the problem?" << endl;
	cout << "1) A, 2) B, 3) C, 4) D, 5) E: ";
	int letter; cin >> letter;


	//cout << "How many random numbers? ";
	const int n = 1000;	//cin >> n;
	

	

	
	TRandom3 r;

	double px[n], x[n];
	double E();
	

	if(letter == 1) {
		int i = 0;
		while(i < n) {		
			double r1 = r.Uniform(0,1);
			x[i] = r1;
			px[i] = 1;
			i++;
		}
	}

	if(letter == 2) {
		int i = 0;
		while(i < n) {		
			double r1 = r.Gaus(1,1);
			
			x[i] = r1;
			px[i] = 1 - fabs(1 - x[i]);
			
			double r2 = r.Uniform(0, 2);
			if(r2 < px[i]){
				i++;
			}
		}
	}



	if(letter == 3) {
		int i = 0;
		while(i < n) {		
			double r1 = r.Gaus(1,1);
			if(r1 > 0) {
				x[i] = r1;
				px[i] = 1 - x[i];

				double r2 = r.Uniform(0, 2);
				if(r2 < px[i]){
					i++;
				}
			}
		}
	}


	if(letter == 4) {
		double mu = 0;
		double sigma = 1;
	}
	if(letter == 5) {
		double mu = 1;
		double sigma = 0.3;
	}
	
	// loops for n random numbers for parts D and E
	if(letter == 4 || letter == 5) {
		int i = 0;
		while(i < n) {
			double r1 = r.Gaus(0,6*sigma);

			x[i] = mu - 3*sigma + r1;
			double z = (-1)*(x[i]-mu)*(x[i]-mu)/(2*sigma*sigma);
			px[i] = pow(E, z);
		
			double r2 = r.Uniform(0, 1);
			if(r2 < px[i]){
				i++;
			}
		}
	}





	//gStyle->SetOptFit(kFALSE);	
	TCanvas *c1 = new TCanvas("c1","RNG",200,10,700,500);
	c1->SetFillColor(42);
	c1->SetGrid();

	gr = new TGraph(n,x,px);

	gr->SetMarkerStyle(21);
	gr->SetTitle("RNG");
	gr->GetXaxis()->SetTitle("X");
	gr->GetYaxis()->SetTitle("Y");
	
	gr->Draw("AP");


	c1->Update();
	c1->GetFrame()->SetFillColor(21);
	c1->GetFrame()->SetBorderSize(12);
	c1->Modified();






}



