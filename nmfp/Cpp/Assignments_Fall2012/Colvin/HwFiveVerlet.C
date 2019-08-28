#include <iostream>
#include <math.h>
void HwFiveVerlet() {
	Double_t Theta_initial;
	Double_t Time_step;
	const double ns; // Number of time steps
	Double_t Omega = 0;
	Double_t Time = 0;
	Double_t Pi = 3.141592653589;
	Int_t Oscillations = 0;
	cout << "Enter the initial angle: ";
	cin >> Theta_initial;
	cout << "Enter the time step value: ";
	cin >> Time_step;
	cout << "Enter the number of time steps: ";
	cin >> ns;
	Double_t Theta = (Theta_initial*Pi)/180;
	Double_t gl = 1; // gl => g/l
	Double_t theta[ns];
	Double_t time[ns];
	Double_t Theta1;
	Double_t Theta2;
	Double_t Alpha = -gl*sin(Theta);
	Theta1 = Theta - Omega*Time_step + 0.5*pow(Time_step,2)*Alpha;
	for (int i = 0; i < ns; i++) {
		theta[i] = (Theta*180)/Pi;
		time[i] = Time;
		Time = Time + Time_step;
		Alpha = -gl*sin(Theta);
		Theta2 = 2*Theta - Theta1 + pow(Time_step,2)*Alpha;
		Theta1 = Theta;
		Theta = Theta2;
		if (Theta*Theta1 < 0) {
			Oscillations++;		
		}
	}
	TCanvas *c1 = new TCanvas("c1","HwFiveVerlet",200,10,700,500);
	c1->SetFillColor(42);
	c1->SetGrid();
	gStyle->SetOptStat(1);
	gStyle->SetOptFit(1);
	gr = new TGraph(ns,time,theta);
	gr->SetMarkerColor(4);
	gr->SetMarkerStyle(21);
	gr->SetTitle("HwFiveVerlet");
	gr->GetXaxis()->SetTitle("Time");
	gr->GetYaxis()->SetTitle("Theta");
	gr->Draw("AP");
	c1->Update(); 
}
