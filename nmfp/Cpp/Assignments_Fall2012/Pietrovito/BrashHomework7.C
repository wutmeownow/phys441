#include <math.h>
#include <TMatrixD.h>
#include <iostream.h>

void BrashHomework7() {

	Double_t height; Double_t speed; Double_t Angle; Int_t airResistance;
	Double_t g = -9.8;		//gravity
	cout<<"Initial height: "; cin>>height;
	cout<<"Initial speed: "; cin>>speed;
	cout<<"Initial angle in degrees: "; cin>>Angle;
	cout<<"Air resistance? type 1 for yes 0 for no: "; cin>>airResistance;

	//	h = Vy*t + 0.5gt + h0
	Double_t h = 0.01;
	Double_t x = 0;
	Double_t y = height;
	Double_t Vx = speed*cos((Angle*3.14159265359)/180);
	Double_t Vy = speed*sin((Angle*3.14159265359)/180);
	Double_t X[1000000];	Double_t Y[1000000];
	Double_t Xr[1000000];	Double_t Yr[1000000];
	int i = 0; int j = 0; Double_t yf; Double_t xf;
	TCanvas *c1 = new TCanvas("c1","Projectile Motion",200,10,700,500);


	// Calculate the projectory without resistance
	while(y>0 || Vy>0) {
		yf = y + Vy*h + 0.5*g*pow(h,2);
		xf = x + Vx*h;
		Vy = (yf - y)/h;
		Vx = (xf - x)/h;
		X[i] = xf; Y[i] = yf;
		x = xf;	y = yf;
		i++;
	}	

	if(airResistance==1) { //Air resistance for a baseball drag values found online
		Double_t drag = 1-(0.00045539375);
		x = 0;	y = height;	Vx = speed*cos((Angle*3.14159265359)/180);	Vy = speed*sin((Angle*3.14159265359)/180);
		while(y>0 || Vy>0) {
			yf = y + drag*Vy*h + 0.5*g*pow(h,2);
			xf = x + drag*Vx*h;
			Vy = (yf - y)/h;
			Vx = (xf - x)/h;
			Xr[j] = xf; Yr[j] = yf;
			x = xf;	y = yf;
			j++;
		}
		gr2 = new TGraph(j, Xr, Yr);
		gr2->SetMarkerColor(2);
		gr2->SetMarkerStyle(3);
	}

	gr1 = new TGraph(i, X, Y);
	gr1->SetMarkerStyle(4);
	
	if(airResistance != 1) {
		gr1->Draw("ADP");
	}
	else {
		TMultiGraph *mg = new TMultiGraph();
		mg->Add(gr1,"DP");
		mg->Add(gr2,"DP");
		mg->Draw("A");
	}


}