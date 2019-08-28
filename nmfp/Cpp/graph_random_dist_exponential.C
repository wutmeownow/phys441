// random_dist - Program to compute and plot a exponential distribution of 
//               random numbers - input is decay constant, lambda
#include <iostream>
#include "math.h"

// Random number generator; Uniform dist. in [0,1]
double rand_ejb( long& seed ) {
//                                                                          
// Input:                                                                           
//   	seed    Integer seed (DO NOT USE A SEED OF ZERO)
// Output:
//   	rand    Random number uniformly distributed in [0,1)
//
  const double a = 16807.0;
  const double m = 2147483647.0;
  double temp = a * seed;
  seed = (long)(fmod(temp,m));
  double rand = seed/m;
  return(rand);
}

void graph_random_dist_exponential() {
//
//Author : Edward J. Brash
//	       

int npoints, i;
double r1,x,lambda;
long seed = 1;
    
cout << "Enter the number of data points to generate:" << endl;
cin >> npoints;

cout << "Enter the decay constant of the exponential:" << endl;
cin >> lambda;

const int nbins=1000;

TH1F *h1 = new TH1F("h1","Random Number Distribution",nbins,0.0,6.0*lambda);

for (i=0;i<npoints; i++){

	r1 = rand_ejb(seed);
	x=-lambda*log(1.0-r1);
	//cout << "Random number: " << i << " = " << seed << " = " << r << endl;
	//h1->Fill(x,1.0*nbins/npoints);
	h1->Fill(x,1.0);
}

// Plotting stuff below this point ...

   const Int_t n = npoints;

   TCanvas *c1 = new TCanvas("c1","Cubic Data",200,10,700,500);
   c1->SetFillColor(42);
   c1->SetGrid();
   //gStyle->SetOptFit(kFALSE);	
   gStyle->SetOptFit(1);	
   
   c1->cd();
   h1->Fit("expo");
   h1->Draw();

   // TCanvas::Update() draws the frame, after which one can change it
   c1->Update();
   c1->GetFrame()->SetFillColor(21);
   c1->GetFrame()->SetBorderSize(12);
   c1->Modified();
}
