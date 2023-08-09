#include <iostream>
#include <TMath.h>
using namespace std;

void for_deriv_diff()
{
	gStyle->SetOptFit(kFALSE);
	TCanvas *c1 = new TCanvas("c1","Derivative Difference",200,10,700,500);
   
	c1->SetFillColor(42);
	c1->SetLogx();
	c1->SetLogy();
	
	
	const double npoints = 22;
	
	double hdel[npoints];
	double h[npoints];
	
	int x = 1;

	for(int i=0; i<=npoints; i++)
	{
		h[i] = pow(10, (-i));
		//cout << "h = " << h[i] << endl;

		hdel[i] = fabs(2*x-(((x+h[i])*(x+h[i])-x*x)/h[i]));
		//cout << "hdel = " << hdel[i] << endl;
	}


	gr = new TGraph(npoints,h,hdel);
	gr->SetMarkerStyle(5);
	gr->SetMarkerColor(7);
	gr->SetTitle("Derivative Difference (forward)");
	gr->GetXaxis()->SetTitle("h");
	gr->GetYaxis()->SetTitle("del h");
	gr->Draw("PAL");

	// TCanvas::Update() draws the frame, after which one can change it
	c1->Update();
	c1->GetFrame()->SetFillColor(21);
	c1->GetFrame()->SetBorderSize(12);
	c1->Modified();
}
