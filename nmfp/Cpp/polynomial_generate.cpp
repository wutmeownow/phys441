// Program to generate a data file containing x and y values
// of the given polynomial between user-specified limits.
//
// Author:  Edward J. Brash
//

#include <iostream>
#include <fstream>
#include "math.h"
#include <TRandom.h>

using namespace std;

int main() {

  //* Initialize the polynomial

//  double pi = 3.14159265;
//  double a0 = -pi*pi*pi;
//  double a1 = 3*pi*pi;
//  double a2 = -3*pi;
//  double a3 = 1.0;

  double a0 = -6;
  double a1 = 11;
  double a2 = -6;
  double a3 = 1;

  double xlow,xhigh;
  int npoints, i;

  ofstream myfile;
  myfile.open ("poly.dat");
  ofstream dfile;
  dfile.open ("deriv.dat");

  cout << "Enter the number of data points:" << endl;
  cin >> npoints;
  cout << "Enter the lower range:" << endl;
  cin >> xlow;
  cout << "Enter the upper range:" << endl;
  cin >> xhigh;

  const int n = npoints;
  TRandom r;

  float x0[n],d[n],f[n],ef[n];

  double step = (xhigh - xlow)/npoints;
  double rand = 0;

  for (i=0; i<npoints; i++) {
	  x0[i] = xlow + i*step;
	  f[i] = a0 + a1*x0[i] + a2*x0[i]*x0[i] + a3*x0[i]*x0[i]*x0[i];
	  ef[i]=pow(fabs(f[i]),0.5);
	  rand = ef[i];
	  f[i]=f[i]+r.Gaus(0.0,rand);
	  cout << "X-value: " << x0[i] << " F(x): " << f[i] << endl; 
	  myfile << x0[i] << " " << f[i] << " " << ef[i] << endl;
  }	  

  for (i=1;i<npoints-1; i++){
	  d[i]=(f[i+1]-f[i-1])/(2.0*step);
	  cout << "X-value: " << x0[i] << " F'(x): " << d[i] << endl; 
	  dfile << x0[i] << " " << d[i] << endl;
  }

  myfile.close();
  dfile.close();
  return 0;
	  
}
