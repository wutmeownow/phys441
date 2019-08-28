// random_dist - Program to compute and plot a gaussian distribution of 
//               random numbers on the interval [-6*sigma,6*sigma]
#include <iostream>
#include "math.h"

void income() {
//
//Author : Edward J. Brash
//	       

int npoints, i;
double x,x0,xu,sigma;
long seed = 1;

TRandom3 *rnum = new TRandom3();
    
cout << "Enter the number of data points to generate:" << endl;
cin >> npoints;

cout << "Enter the centroid of the gaussian:" << endl;
cin >> x0;

cout << "Enter the sigma of the gaussian:" << endl;
cin >> sigma;

const int nbins=100;

TH1F *h1 = new TH1F("h1","Gaussian Savings Distribution",nbins,0.0,100.0);
TH1F *h2 = new TH1F("h2","Gaussian Income Distribution",nbins,0.0,100.0);
TH1F *h3 = new TH1F("h3","Uniform Savings Distribution",nbins,0.0,100.0);
TH1F *h4 = new TH1F("h4","Uniform Income Distribution",nbins,0.0,100.0);

for (i=0;i<npoints; i++){

	x = rnum->Gaus(x0,sigma);
	xu = rnum->Uniform(0.0,100.0);

	int j = x;
	if (j<0){j=0;}
	if (j>nbins){j=nbins;}
	int k = xu;
	if (k<0){k=0;}
	if (k>nbins){k=nbins;}
	//cout << "Random number: " << i << " = " << seed << " = " << r << endl;
	h2->Fill( x , j );
	h1->Fill( x , 1.0 );
	h4->Fill( xu , k );
	h3->Fill( xu , 1.0 );
	//h1->Fill(x,1.0);
}

// Plotting stuff below this point ...

   const Int_t n = npoints;

   TCanvas *c1 = new TCanvas("c1","Cubic Data",200,10,700,500);
   c1->Divide(2,2);
   c1->SetFillColor(42);
   c1->SetGrid();
   //gStyle->SetOptFit(kFALSE);	
   gStyle->SetOptFit(1);	
   
   c1->cd(1);
   h1->Draw();
   c1->cd(2);
   h2->Draw();
   c1->cd(3);
   h3->Draw();
   c1->cd(4);
   h4->Draw();

   // TCanvas::Update() draws the frame, after which one can change it
   //c1_1->Update();
   //c1_1->GetFrame()->SetFillColor(21);
   //c1_1->GetFrame()->SetBorderSize(12);
   //c1_1->Modified();
   //c1_2->Update();
   //c1_2->GetFrame()->SetFillColor(21);
   //c1_2->GetFrame()->SetBorderSize(12);
   //c1_2->Modified();
}
