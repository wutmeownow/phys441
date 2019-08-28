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
  double r1,r2;
  long seed = 1;

  ofstream myfile;
  myfile.open ("random_dist.dat");

  cout << "Enter the number of data points to generate:" << endl;
  cin >> npoints;

  const int n = npoints;

  for (i=0;i<npoints; i++){

	  r1 = rand_ejb(seed);
	  r2 = rand_ejb(seed);
	  cout << "Random number: " << i << " = " << seed << " = " << r1+r2 << endl;
	  myfile << r1+r2 << endl;
  }

  myfile.close();
  return 0;
	  
}
