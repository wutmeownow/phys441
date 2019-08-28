// root_find - Program to find the roots of a polynomial of degree
// three using Newton's Method.
//
// Author:  Edward J. Brash
//

#include <iostream>
#include <math.h>

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

  double f, fp, x0, xnew;
  double epsilon = 1.0E-8;
  double diff = 1.0E12;

  cout << "Enter the starting value:" << endl;
  cin >> x0;

  while (diff > epsilon) {
	  f = a0 + a1*x0 + a2*x0*x0 + a3*x0*x0*x0;
 	  fp = a1 + 2.0*a2*x0 + 3.0*a3*x0*x0; 

  	  xnew = x0 - f/fp; 

  	  diff = xnew - x0;
	  cout << "New x-value: " << xnew << " Diff: " << diff << endl; 
	  x0 = xnew;
	  diff = fabs(diff);
  }	  

  cout << "Root = " << xnew << endl;
  return 0;
	  
}
