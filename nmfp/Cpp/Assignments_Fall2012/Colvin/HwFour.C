#include <iostream>
#include <math.h>
void HwFour() {
	// Variables for no air resistance
	Int_t choose;
	Double_t H0;
	Double_t D0 = 0;
	Double_t H1;
	Double_t D1;
	bool air = false;
	bool noair = false;
	cout << "Enter '1' to assume no air resistance or '0' to assume air resistance: ";
	cin >> choose;
	cout << "Enter the initial height above the ground: ";
	cin >> H0;
	// Variables for air resistance
	Double_t Y0 = H0;
	Double_t X0 = 0;
	Double_t Y1;
	Double_t X1;
	Double_t D = (1.225*0.5*0.001487)/2; // Air resistance constant for a baseball D = pCA/2
	Double_t V;
	Double_t Vy;
	Double_t Vx;
	Double_t A = 9.81;
	Double_t Th;
	Double_t Pi = 3.1459;
	Double_t ts;      // Time step
	const double nts; // # of steps
	cout << "Enter the initial velocity: ";
	cin >> V;
	cout << "Enter the initial launch angle: ";
	cin >> Th;
	cout << "Enter the time step value: ";
	cin >> ts;
	cout << "Enter the number of time steps: ";
	cin >> nts;
	Double_t d[nts];
	Double_t h[nts];
	Double_t x[nts];
	Double_t y[nts];
	Double_t Theta = (Th*Pi)/180;
	Vy = V*sin(Theta);
	Vx = V*cos(Theta);
	// Motion without air resistance
	if (choose == 1) {
		for (int i = 0; i < nts; i++) {
			d[i] = D0;
			h[i] = H0;
			H1 = H0;
			D1 = D0;
			H0 = H0 + Vy*ts;
			D0 = D0 + Vx*ts;
			Vy = (Vy - ts*A);
			if (Vy <= 0 && noair == false) {
				cout << "Y max with no air resistance: " << H0 << endl;
				noair = true; 
			}
			if (H0 <= 0) {
				cout << "X max with no air resistance: " << D0 << endl;
				break;
			}
		}
	}
	// Motion without air resistance
	else {
		//Vy = V*sin(Theta);
		//Vx = V*cos(Theta);
		for (int i = 0; i < nts; i++) {
			x[i] = X0;
			y[i] = Y0;
			Y1 = Y0;
			X1 = X0;
			Y0 = Y0 + Vy*ts;
			X0 = X0 + Vx*ts;
			Vy = ((Vy - ts*A) - D*Vy);
			Vx = (Vx - D*Vx);
			if (Vy <= 0 && air == false) {
				cout << "Y max with air resistance: " << Y0 << endl;
				air = true; 
			}
			if (Y0 <= 0){
				cout << "X max with air resistance: " << X0 << endl;
				break;
			}
		}
	}
	TCanvas *c1 = new TCanvas("c1","Hw four",200,10,700,500);
	c1->SetFillColor(42);
	c1->SetGrid();
        gStyle->SetOptStat(1);
	gStyle->SetOptFit(1);
	if (choose == 1) {
		gr = new TGraph(nts,d,h);
		gr->SetMarkerColor(4);
		gr->SetMarkerStyle(21);
		gr->SetTitle("Hw four with no air resistance");
		gr->GetXaxis()->SetTitle("X");
		gr->GetYaxis()->SetTitle("Y");
		gr->Draw("AP");
	}
	else {
		gr = new TGraph(nts,x,y);
		gr->SetMarkerColor(4);
		gr->SetMarkerStyle(21);
		gr->SetTitle("Hw four with air resistance");
		gr->GetXaxis()->SetTitle("X");
		gr->GetYaxis()->SetTitle("Y");
		gr->Draw("AP");
	}
	c1->Update(); 
}
