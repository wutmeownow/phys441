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
  
  int npoints, i,j;
  double r,x=0.0;
  int m = 48;
  long seed = 1;

  ofstream myfile;
  myfile.open ("random_dist.dat");

  cout << "Enter the number of data points to generate:" << endl;
  cin >> npoints;

  const int n = npoints;

  for (i=0;i<npoints; i++){
	  for(j=0;j<m;j++){

	  r = rand_ejb(seed);
	  x = x+pow((12.0/m),0.5)*(r-0.5);
	  }
	  cout << "Random number: " << i << " = " << seed << " = " << x << endl;
	  myfile << x << endl;
	  x=0.0;
  }

  myfile.close();
  return 0;
	  
}
