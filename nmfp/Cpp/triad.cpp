// Program to generate a time waveform for a specified musical triad
//  - initial version is for a C-major triad (C - E - G)
//
// Author:  Edward J. Brash
//

#include <iostream>
#include <fstream>
#include "math.h"

using namespace std;

int main() {

  //* Initialize values for an equal tempered scale based on A-440
  
  double f0 = 440.0;
  double a = pow(2.0,1.0/12.0);
  double fn[12], time, Pi=3.14159265;
  int i;

  for (i=0; i<12; i++){
	  fn[i]=f0*pow(a,i);
	  cout << " fn[" << i << "] = " << fn[i] << endl;
  }

  ofstream myfile;
  myfile.open ("triad.dat");

  double froot = fn[3]/2.0;
  double fthree = fn[7]/2.0;
  double ffive = fn[10]/2.0;
  double fextra = fn[3]/2.0;

  cout << "froot = " << froot << "; fthree = " << fthree << "; ffive = " << ffive << endl;

  double aroot = 1.0;
  double athree = 1.0;
  double afive = 1.0;
  double aextra = 1.0;

  double period = 1.0 / froot;
  double tmax = 300.0*period;
  double timestep = period/100.0;
  int nsteps = tmax/timestep;

  const int n = nsteps;
  float tseries[n];

  for (i=0;i<nsteps;i++){
	  tseries[i]=0;
  }

  for (i=0;i<nsteps; i++){
	  time = i*timestep;
	  tseries[i] = aroot*sin(2.0*Pi*froot*time)+athree*sin(2.0*Pi*fthree*time)+afive*sin(2.0*Pi*ffive*time)+aextra*sin(2.0*Pi*fextra*time);
	  //tseries[i] = aroot*sin(2.0*Pi*froot*time);
	 // tseries[i] = athree*sin(2.0*Pi*fthree*time);
	 // tseries[i] = afive*sin(2.0*Pi*ffive*time);
	//  cout << time  << " " << tseries[i] << endl;
	  myfile << time  << " " << tseries[i] << endl;
  }

  myfile.close();
  return 0;
	  
}
