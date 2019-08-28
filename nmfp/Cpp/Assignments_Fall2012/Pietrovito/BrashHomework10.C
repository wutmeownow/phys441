#include <math.h>
#include <TMatrixD.h>
#include <iostream.h>

const int n = 1000000;
double x[n];
void drawHisto();
double rand();

void BrashHomework10() {
	int a = pow(7, 5);
	int M = pow(2, 31) - 1;
	int C = 0;
	int I = 1;			 // seed can't be 0 
	int choice;
	cout<<"Choose distribution: 1=Uniform 2=Triangle 3=Gaussian 4=Exponential 5=Box-Muller ... "; cin>>choice;
	
	rand(x, a, M, C, I, choice);
	drawHisto(x, choice);
	
	
}

void rand(double r[], int a, int M, int C, int I, int choice) {
	int Inext; double InextD; double MD;
	for(int i=0;i<n;i++){
		Inext = (a*I+C)%M;
		InextD = Inext;
		MD = M;
		r[i] = InextD/MD;
		if(choice!=3) {
			r[i] = sqrt(r[i]*r[i]);
		}
		I=Inext;
	}	
}

void drawHisto(double q[], int choice) {
	TCanvas *c1 = new TCanvas("canvas","Random number generator",40,40,600,600);
	gStyle->SetOptStat(1);		// turns on stat box
	gStyle->SetOptFit(0);		// turns off fit box
	c1->ToggleEventStatus();	// turns on event status bar
	if(choice==1) { // uniform distribution
		TH1D *h1 = new TH1D("h1", "x distribution",500,-0.2,1.2);
		for(int i=0;i<n;i++){
			h1->Fill(q[i]);
		}
		h1->Draw();
	}
	if(choice==2) { // triangle distribution
		TH1D *h1 = new TH1D("h1", "x distribution",500,-0.2,2.2);
		for(int i=0;i<(n/2);i++){
			h1->Fill(q[i]+q[n-i]);
		}
		h1->Draw();
	}
	if(choice==3) { // gaussian distribution
		TH1D *h1 = new TH1D("h1", "x distribution",500,-4,4);
		for(int i=0; i<(n/2); i++) {
			double S = pow(q[i],2)+pow(q[n-i],2);
			if(S<1) {
				h1->Fill(q[i]*sqrt(-2*log(S)/S));
				h1->Fill(q[n-i]*sqrt(-2*log(S)/S));
			}
		}
		h1->Draw();
	}
	if(choice==4) { // triangle distribution
		TH1D *h1 = new TH1D("h1", "x distribution",500,-0.2,4.2);
		for(int i=0;i<n;i++){
			h1->Fill(-log(1-q[i]));
		}
		h1->Draw();
	}
}