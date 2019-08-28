// Program to generate a data file containing x and y values
// of the given polynomial between user-specified limits.
//
// Author:  Edward J. Brash
//

#include <iostream>
#include <fstream>

using namespace std;

int main() {

  double xlow,xhigh;
  int npoints, i;

  ofstream myfile;
  myfile.open ("runge.dat");

  cout << "Enter the number of data points:" << endl;
  cin >> npoints;
  cout << "Enter the lower range:" << endl;
  cin >> xlow;
  cout << "Enter the upper range:" << endl;
  cin >> xhigh;

  const int n = npoints;

  double x0[n],d[n],f[n];

  double step = (xhigh - xlow)/(npoints-1);

  for (i=0; i<npoints; i++) {
	  x0[i] = xlow + i*step;
	  f[i] = 1.0/(1+x0[i]*x0[i]);
	  cout << "X-value: " << x0[i] << " F(x): " << f[i] << endl; 
	  myfile << x0[i] << " " << f[i] << endl;
  }	  

  myfile.close();
  return 0;
	  
}
