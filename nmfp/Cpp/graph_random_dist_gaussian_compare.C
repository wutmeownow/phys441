// random_dist - Program to compute and plot a gaussian distribution of 
//               random numbers on the interval [-6*sigma,6*sigma]
#include <iostream>
#include <ctime> 
#include "math.h"
#include "TStopwatch.h"
#include "TRandom.h"

// function to return specific bits of a seed, for LCG algorithms that only use
// a certain bit range
unsigned long long bitExtracted( unsigned long long number, unsigned long long k, int p) {
	
	unsigned long long result;

	//cout << "Input: " << number << " " << k << " " << p << endl;

	//cout << "Right shift by (p - 1) = " << (number >> (p - 1)) << endl;

	//cout << "Other part = " << ((1 << k) - 1) << endl;

	result = (((1ULL << k) - 1ULL) & (number >> (p - 1)));
       	//cout << "Seed = " << number << " result = " << result << endl;
	return result;	
}       

// Random number generator; Uniform dist. in [0,1]
double rand_ejb( unsigned long long& seed ) {
//                                                                          
// Input:                                                                           
//   	seed    Integer seed (DO NOT USE A SEED OF ZERO)
// Output:
//   	rand    Random number uniformly distributed in [0,1)
//
// Numerical Recipes
//  const unsigned long long a = 1664525;
//  const unsigned long long m = 2147483648*2;
//  const unsigned long long c = 1013904223;
//  const int choice = 0;
//  const int k = 1;
//  const int p = 1;
//  const unsigned long long divisor = 1; // 2^k
// Borland Delphi, Virtual Pascal
//  const unsigned long long a = 134775813;
//  const unsigned long long m = 2147483648*2;
//  const unsigned long long c = 1;
//  const int choice = 1;
//  const int k = 31;
//  const int p = 1;
//  const unsigned long long divisor = 2147483648; // 2^k
// Borland C++
//  const unsigned long long a = 22695477;
//  const unsigned long long m = 2147483648*2;
//  const unsigned long long c = 1;
//  const int choice = 1;
//  const int k = 31;
//  const int p = 1;
//  const unsigned long long divisor = 2147483648; // 2^k
// glibc
//  const unsigned long long a = 1103515245;
//  const unsigned long long m = 2147483648;
//  const unsigned long long c = 12345;
//  const int choice = 1;
//  const int k = 31;
//  const int p = 1;
//  const unsigned long long divisor = 2147483648; // 2^k
// Apple CarbonLib 
//  const unsigned long long a = 16807;
//  const unsigned long long m = 2147483647;
//  const unsigned long long c = 0;
//  const int choice = 0;
//  const int k = 1;
//  const int p = 1;
//  const unsigned long long divisor = 1; // 2^k
// POSIX1 
//  const unsigned long long a = 25214903917;
//  const unsigned long long m = 281474976710656; // 2^48
//  const unsigned long long c = 11;
//  const int choice = 1;
//  const unsigned long long k = 33;
//  const int p = 16;
//  const unsigned long long divisor = 8589934592; // 2^k
// POSIX2 
  const unsigned long long a = 25214903917;
  const unsigned long long m = 281474976710656; // 2^48
  const unsigned long long c = 11;
  const int choice = 1;
  const unsigned long long k = 48;
  const int p = 1;
  const unsigned long long divisor = 281474976710656; // 2^k


  unsigned long long temp = a * seed + c;
  seed = (unsigned long long)(temp % m);
  double rand;

  if (choice == 0){
  	rand = 1.0*seed/m;
  } else {
	rand = 1.0*bitExtracted(seed, k, p)/divisor; 
  }

  return(rand);
}

void graph_random_dist_gaussian_compare() {
//
//Author : Edward J. Brash
//	       

int npoints, i;
double r1,r2,x,x0,pgauss,sigma;

//unsigned long long second = time(0);
//unsigned long long seed = (second << 32);
//cout << "Seeds:  " << second << " " << (second << 32) << " " << seed << endl;

unsigned long long seed = 1;

cout << "Enter the number of data points to generate:" << endl;
cin >> npoints;

cout << "Enter the centroid of the gaussian:" << endl;
cin >> x0;

cout << "Enter the sigma of the gaussian:" << endl;
cin >> sigma;

const int nbins=1000;
double width = 12*sigma;
double dx = width/nbins;
int n_randoms=0;

TH1F *h1 = new TH1F("h1","Random Number Distribution (EJB)",nbins,x0-width/2.0,x0+width/2.0);
TH1F *h2 = new TH1F("h2","Random Number Distribution (ROOT)",nbins,x0-width/2.0,x0+width/2.0);

TStopwatch timer;
TStopwatch timer3;
timer.Start();

for (i=0;i<npoints; i++){
	bool check=true;
	while(check){
		//cout << "Random number: " << seed << endl;
		r1 = rand_ejb(seed);
		//cout << "Random number: " << seed << endl;
		n_randoms++;
		x=(x0-width/2.0+width*r1);
		pgauss=exp(-1.0*(x-x0)*(x-x0)/(2.0*sigma*sigma));
		r2 = rand_ejb(seed);
		//cout << "Random number: " << seed << endl;
		n_randoms++;
		//cout << "Random number: " << i << " = " << seed << " = " << r1 << " = " << pgauss << " = " << r2 << endl;
		if (r2<pgauss) check=false;
	}	
	h1->Fill( x , 1.0/width/sqrt(2.0*3.14159265*sigma*sigma) );
	//h1->Fill(x,1.0);
}
   
timer.Stop();
TRandom3 *rnum = new TRandom3();
timer3.Start();

for (i=0;i<npoints; i++){
	x=rnum->Gaus(x0,sigma);
	h2->Fill( x , 1.0/width/sqrt(2.0*3.14159265*sigma*sigma) );
	//h1->Fill(x,1.0);
}
timer3.Stop();

TH1F *h3 = (TH1F*)h1->Clone("h3");
h3->Divide(h2);

// Plotting stuff below this point ...

   const Int_t n = npoints;
   cout << "Total number of randoms generated = " << n_randoms << endl;
   cout << endl;
   cout << "EJB Random Generation" << endl;
   cout << "Total real time = " << timer.RealTime() << endl;
   cout << "Total CPU time = " << timer.CpuTime() << endl;
   cout << "Real time / random = " << timer.RealTime()/npoints << endl;
   cout << "CPU time /random = " << timer.CpuTime()/npoints << endl;
   cout << endl;
   cout << "ROOT Random Generation" << endl;
   cout << "Total real time = " << timer3.RealTime() << endl;
   cout << "Total CPU time = " << timer3.CpuTime() << endl;
   cout << "Real time / random = " << timer3.RealTime()/npoints << endl;
   cout << "CPU time /random = " << timer3.CpuTime()/npoints << endl;
   cout << endl;

   TCanvas *c2 = new TCanvas("c2","Cubic Data",200,10,700,800);
   TCanvas *c1 = new TCanvas("c1","Cubic Data",200,10,700,800);
   c1->Divide(1,2);
   c1->SetFillColor(42);
   c1->SetGrid();
   c2->SetFillColor(42);
   c2->SetGrid();
   //gStyle->SetOptFit(kFALSE);	
   gStyle->SetOptFit(1);	
   
   c2->cd();
   h3->Draw();
   c1->cd(1);
   h1->Fit("gaus");
   h1->Draw();
   c1->cd(2);
   h2->Fit("gaus");
   h2->Draw();
   
   // TCanvas::Update() draws the frame, after which one can change it
   c2->Update();
   c2->GetFrame()->SetFillColor(21);
   c2->GetFrame()->SetBorderSize(12);
   c2->Modified();
   c1->Update();
   c1->GetFrame()->SetFillColor(21);
   c1->GetFrame()->SetBorderSize(12);
   c1->Modified();
}
