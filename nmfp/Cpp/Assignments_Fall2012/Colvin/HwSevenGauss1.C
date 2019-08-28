#include <iostream>
#include <math.h>
void HwSevenGauss1() {
	TCanvas *c1 = new TCanvas("c1","Hw Seven Gauss One",200,10,700,500);
        gStyle->SetOptStat(1);
	TH1D *h1 = new TH1D("h1", "x distribution", 100, -4.2, 4.2);

	int Ip = 1;
	int Ip2 = 1000;
	int In = 0;
	int a = pow(7,5);
	int C = 0;
	int M = (pow(2,31)-1);
	int L = 1;
	const int num = 100000;
	Double_t S = 0;
	Double_t R[num] = 0;
	Double_t R0[num] = 0;
	Double_t R1[num] = 0;
	Double_t R2[num] = 0;
	
	for (int i = 0; i < num; i++) {
		In = (a*Ip)%M;
		double SquirrelBait = In;
		double SquirrelTrap = M;
		R1[i] = SquirrelBait/SquirrelTrap;
		Ip = In;
		R1[i] = (-1)+(1-(-1))*R1[i];
	}
	for (int i = 0; i < num; i++) {
		In = (a*Ip2)%M;
		double SquirrelBait = In;
		double SquirrelTrap = M;
		R2[i] = SquirrelBait/SquirrelTrap;
		Ip2 = In;
		R2[i] = (-1)+(1-(-1))*R2[i];
	}
	int j = 0;
	for (int i = 0; i < num; i++) {
		S = pow(R1[i],2) + pow(R2[i],2);
		if (S < 1) {
			if (j >= num) {
				break;
			}
			R[j] = R1[i]*sqrt(((-2*log(S[i]))/S[i]));
			j++;
			if (j >= num) {
				break;
			}
			R[j] = R2[i]*sqrt(((-2*log(S[i]))/S[i]));
			j++;

		}
	}
	for (int i = 0; i < num; i++) {
		h1->Fill(R[i]);
	}
	h1->Draw();
}
