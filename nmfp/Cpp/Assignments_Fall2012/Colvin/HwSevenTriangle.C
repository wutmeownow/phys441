#include <iostream>
#include <math.h>
void HwSevenTriangle() {
	TCanvas *c1 = new TCanvas("c1","Hw Seven Triangle",200,10,700,500);
        gStyle->SetOptStat(1);
	TH1D *h1 = new TH1D("h1", "x distribution", 500, -0.2, 2.2);

	int Ip = 1;
	int Ip2 = 190;
	int In = 0;
	int a = pow(7,5);
	int C = 0;
	int M = (pow(2,31)-1);
	const int num = 10000000;
	Double_t R[num] = 0;
	Double_t R2[num] = 0;
	Double_t R3[num] = 0;
	
	for (int i = 0; i < num; i++) {
		In = (a*Ip)%M;
		double SquirrelBait = In;
		double SquirrelTrap = M;
		R[i] = SquirrelBait/SquirrelTrap;
		Ip = In;
	}
	for (int i = 0; i < num; i++) {
		In = (a*Ip2)%M;
		double SquirrelBait = In;
		double SquirrelTrap = M;
		R2[i] = SquirrelBait/SquirrelTrap;
		Ip2 = In;
	}
	for (int i = 0; i < num; i++) {
		R3[i] = R[i]+R2[i];
		h1->Fill(R3[i]);
		
	}
	

	h1->Draw();
}
