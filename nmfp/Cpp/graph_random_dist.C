// random_dist - Program to compute and plot a uniform distribution of 
//               random numbers on the interval [0,1]

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
//  a, m, b are from Apple CarbonLib algorithm
//
  const double a = 16807.0;
  const double m = 2147483647.0; //2^31 -1
  const double b = 0.0;
  
  double temp = a*seed + b;
  seed = (long)(fmod(temp,m));
  double rand = seed/m;
  return(rand);
}

void graph_random_dist() {
//
//Author : Edward J. Brash
//	       

int npoints, i;
double r;
long seed = 1;
    
cout << "Enter the number of data points to generate:" << endl;
cin >> npoints;

const int nbins=1000;

//TH1F *h1 = new TH1F("h1","Random Number Distribution",nbins+20,-0.1,1.1);
TH1F *h1 = new TH1F("h1","Random Number Distribution",nbins,0.0,1.0);

for (i=0;i<npoints; i++){
	r = rand_ejb(seed);
	//cout << "Random number: " << i << " = " << seed << " = " << r << endl;
	h1->Fill(r,1.0*nbins/npoints);
}

// Plotting stuff below this point ...

   const Int_t n = npoints;

   TCanvas *c1 = new TCanvas("c1","Cubic Data",200,10,700,500);
   c1->SetFillColor(42);
   c1->SetGrid();
   //gStyle->SetOptFit(kFALSE);	
   gStyle->SetOptFit(1);	
   
   c1->cd();
   h1->Draw();

   // TCanvas::Update() draws the frame, after which one can change it
   c1->Update();
   c1->GetFrame()->SetFillColor(21);
   c1->GetFrame()->SetBorderSize(12);
   c1->Modified();
}
