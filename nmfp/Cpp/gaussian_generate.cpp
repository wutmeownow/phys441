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
  
  int npoints;
  double mu,sigma;

  ofstream myfile;
  myfile.open ("gaussian_errors.dat");

  cout << "Enter the number of samples:" << endl;
  cin >> npoints;
  cout << "Enter the centroid:" << endl;
  cin >> mu;
  cout << "Enter the standard deviation" << endl;
  cin >> sigma;

  const int n = npoints;
  const int nbins = 100;
  const int nsigma = 4;
  TRandom r;

  float x0[nbins],f[nbins],ef[nbins];

  double step = 2.0*nsigma*sigma/nbins;
  double rand = 0.0;
  int ibin, i;
  double xvalue;
  double xlow=mu-nsigma*sigma;
  double xhigh=mu+nsigma*sigma;

  for (i=0;i<nbins;i++){
	  x0[i]=0;
	  f[i]=0;
	  ef[i]=0;
  }

  for (i=0; i<npoints; i++) {
	  xvalue=r.Gaus(mu,sigma);
	  ibin = (xvalue-xlow)/step;
	  if (ibin<0) {
		  ibin=0;
	  }
	  if (ibin>=nbins) {
		  ibin=nbins-1;
	  }
	  f[ibin]++;
//	  cout << " x i f = " << xvalue << " " << ibin <<  " "  << f[ibin] << endl;
  }	  

  for (i=0;i<nbins; i++){
	  x0[i]=xlow+i*step;
	  if(f[i]==0){
		  ef[i]=1.0;
	  }else{
	  	ef[i]=pow(f[i],0.5);
	  }
	  cout << x0[i] << " " << f[i] << " " << ef[i] << endl;
	  myfile << x0[i] << " " << f[i] << " " << ef[i] << endl;
  }

  myfile.close();
  return 0;
	  
}
