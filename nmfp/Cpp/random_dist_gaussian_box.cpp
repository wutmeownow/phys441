// Program to generate a data file containing a uniform distribution of random numbers 
// Uses the linear congruential algorithm
//
// Author:  Edward J. Brash
//

#include <iostream>
#include <fstream>
#include "math.h"

double rand_ejb( long& seed );

using namespace std;

int main() {

  //* Initialize the polynomial
  
  int npoints, i;
  double Pi=3.14159265;
  double u,r,rho,theta,x;
  double mu=1.0,sigma=0.3;
  long seed = 1;

  ofstream myfile;
  myfile.open ("random_dist.dat");

  cout << "Enter the number of data points to generate:" << endl;
  cin >> npoints;

  const int n = npoints;

  for (i=0;i<npoints; i++){

	  r = rand_ejb(seed);
	  u = -log(1-r);
	  r = rand_ejb(seed);
	  rho=pow((2.0*sigma*sigma*u),0.5);
	  theta=2.0*Pi*r;
	  x = rho*cos(theta)+mu;
	  cout << "Random number: " << i << " = " << seed << " = " << x << endl;
	  myfile << x << endl;
	  x=0.0;
  }

  myfile.close();
  return 0;
	  
}
