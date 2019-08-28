// Program to generate a data file containing a uniform distribution of random numbers 
// Uses the linear congruential algorithm
//
// Author:  Edward J. Brash
//

#include <iostream>
#include <fstream>
#include "math.h"

double rand_ejb( long& seed );

double pgaus(double x, double mu, double sigma){
	double p;
	double Pi=3.14159265;

	p = 1.0/(pow(2.0*Pi,0.5)*sigma)*exp(-(x-mu)*(x-mu)/(2.0*sigma*sigma));

	return p;
}

using namespace std;

int main() {

  //* Initialize the polynomial
  
  int npoints, i;
  double ntries;
  double Pi=3.14159265;
  double r,ratio,pratio,xtry,ptry;
  double mu=1.0,sigma=0.3;
  double xlow = mu - 6.0*sigma;
  double xhigh = mu + 6.0*sigma;
  long seed = 1;

  ofstream myfile;
  myfile.open ("random_dist.dat");

  cout << "Enter the number of data points to generate:" << endl;
  cin >> npoints;

  const int n = npoints;

  double pmax;

  pmax = pgaus(mu,mu,sigma);

  for (i=0;i<npoints; i++){

	  ratio = 1.0;
	  pratio = 0.0;

	  while (pratio < ratio){
		ntries++;
	  	r = rand_ejb(seed);	
	  	xtry=xlow+(xhigh-xlow)*r;
	  	ptry=pgaus(xtry,mu,sigma);
	  	ratio = rand_ejb(seed);
		pratio = ptry/pmax;
	  }

	  cout << "Random number: " << i << " = " << seed << " = " << xtry << endl;
	  myfile << xtry << endl;

  }

  double pointratio=ntries/npoints*1.0;
  cout << "Total number of tries: " << ntries << " Tries per point: " << pointratio << endl;

  myfile.close();
  return 0;
	  
}
