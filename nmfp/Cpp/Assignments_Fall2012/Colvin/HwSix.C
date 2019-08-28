#include <iostream>
#include <math.h>
void HwSix() {
	Double_t Y0;
	cout << "Enter the initial height above the ground: ";
	cin >> Y0;
	Double_t X0 = 0;
	Double_t D = 1.0*(1.225*0.5*0.001487)/2; // Air resistance constant for a baseball D = pCA/2
	Double_t m = 0.145; //Mass of a baseball in kg
	Double_t V0;
	Double_t Vy0;
	Double_t Vx0;
	Double_t Vy1;
	Double_t Vx1;
	Double_t Vy2;
	Double_t Vx2;
	Double_t g = 9.81;
	Double_t Th;
	Double_t Pi = 3.1459265;
	const double nts;
	Double_t ts;
	cout << "Enter the number of time steps: ";
	cin >> nts;
	cout << "Enter the time step: ";
	cin >> ts;
	cout << "Enter the initial velocity: ";
	cin >> V0;
	cout << "Enter the initial launch angle: ";
	cin >> Th;
	Double_t Y1[nts];
	Double_t X1[nts];

	for (int i = 0; i < nts; i++) {
		Y1[i] = 0;
		X1[i] = 0;
	}

	Double_t Theta = (Th*Pi)/180.0;

	Vy0 = V0*sin(Theta);
	Vx0 = V0*cos(Theta);
	// In the loop below you will get an error saying that
	// you are missing 3 closing brakcets. If you comment out
	// everything involving Y in this loop the program runs perfectly.
	// Something is causing the program to crash when trying to use multiple dimensions.
	for (int i = 0; i < nts; i++) {
		Vx1 = (Vx0-((D/m)*pow(Vx0,2))*(ts/2));
		Vx2 = (Vx1-((D/m)*pow(Vx1,2))*(ts));
		X1[i] = (X0+Vx1*ts);
		X0 = X1[i];
		Vx0 = Vx2;
		if (Vy0 < 0) {
			Vy1 = Vy0-(g-D/m*Vy0*Vy0)*ts/2;
			Vy2 = Vy1-(g-D/m*Vy1*Vy1)*ts;
		} else {
			Vy1 = Vy0-(g+D/m*pow(Vy0,2))*ts/2;
			Vy2 = Vy1-(g+D/m*pow(Vy1,2))*ts;
		}
		Y1[i] = (Y0+Vy1*ts);
		Y0 = Y1[i];
		Vy0 = Vy2;
		if (Y1[i] <= 0) {
			break;
		}
	}


	TCanvas *c1 = new TCanvas("c1","Hw Six",200,10,700,500);
	c1->SetFillColor(42);
	c1->SetGrid();
        gStyle->SetOptStat(1);
	gStyle->SetOptFit(1);
	gr = new TGraph(nts,X1,Y1);
	gr->SetMarkerColor(4);
	gr->SetMarkerStyle(21);
	gr->SetTitle("Hw Six");
	gr->GetXaxis()->SetTitle("X");
	gr->GetYaxis()->SetTitle("Y");
	gr->Draw("AP");
	c1->Update(); 
}
