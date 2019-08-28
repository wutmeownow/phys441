/*#include <TRandom.h>
#include <TMath.h>
#include <TCanvas.h>
#include <TGraph.h>*/
#include <iostream>
#include <math.h>

using namespace std;

int main() {
 
  
  //gStyle->SetOptFit(kFALSE);	
  // TCanvas *c1 = new TCanvas("c1","Root Finding Example",200,10,700,500);
   
  // c1->SetFillColor(42);
  // c1->SetGrid();
   //c1->SetLogy();

//* Initialize the polynomial

  double a0 = 1.80;
  double a1 = -4.05;
  double a2 = 0.40;
  double a3 = 1.00;

  double f, xmid, fa, fb, fc;

  double xlow = -4.0;
  double xhigh = 4.0;
  const int npoints = 10000;
  //* arrays to store the function
  double xval[npoints];
  double yval[npoints];
  //* arrays to store the positions of the roots
  double xroots[npoints];
  double yroots[npoints];
  //* step size in x
  double dx = (xhigh-xlow)/npoints;

  for (int i = 0; i<npoints;i++){
	xval[i]=xlow+i*dx;
	yval[i]=a0+a1*xval[i]+a2*xval[i]*xval[i]+a3*xval[i]*xval[i]*xval[i];
  }	

  //* Get the chunk size from the user, and determine the number of iterations for the searc
  
  int nsearch;
  cout << "Enter the chunk size for the search: ";
  cin >> nsearch;

  int niter = npoints/nsearch;
  double ycomp=yval[0];
  int nsteps=0;
  int nroots_found=0;

  //* Main iteration loop

  for (int i=1; i<niter; i++){
	double y=yval[nsearch*i];
        //* check to see if the endpoint of the chunk is a root
	if (y == 0.0) {
		cout << "Found root at x = " << xval[nsearch*i] << endl;
		nsteps=nsteps+1;
		//* store the position of the found root
		xroots[nroots_found]=xval[nsearch*i];
		yroots[nroots_found]=0.0;
		nroots_found++;
	}
	nsteps++;
	if (y*ycomp < 0.0){
		//* Found a root in this interval
		xlow = xval[nsearch*(i-1)];
		xhigh = xval[nsearch*i];
		nsteps=nsteps+2;
  		double epsilon = 1.0E-10;
  		double diff = 1.0E12;
		while (diff > epsilon){
			fa = a0 + a1*xlow + a2*xlow*xlow + a3*xlow*xlow*xlow;
			fb = a0 + a1*xhigh + a2*xhigh*xhigh + a3*xhigh*xhigh*xhigh;
			xmid = (xhigh + xlow)/2.0;
			fc = a0 + a1*xmid + a2*xmid*xmid + a3*xmid*xmid*xmid;
			nsteps=nsteps+4;
			double product = fa*fc;
			if (product < 0) {
				xhigh = xmid;
				fb = fc;
				nsteps=nsteps+2;
			} else {
				xlow = xmid;
				fa = fc;
				nsteps=nsteps+2;
			}

			diff = fabs(fc);
			nsteps++;
		}
		//* store the position of the found root 
		cout << "Found root at x = " << xmid << endl;
		xroots[nroots_found]=xmid;
		yroots[nroots_found]=0.0;
		nroots_found++;
		ycomp=y;
		nsteps++;
	}
	else{
		ycomp=y;
		nsteps++;
	}
  }

  cout << "Number of roots found = " << nroots_found << endl;
  cout << "Number of instructions ~ " << nsteps << endl;

  /*TGraph *gr = new TGraph(npoints,xval,yval);
  TGraph *gr2 = new TGraph(nroots_found,xroots,yroots);
//   gr->SetLineColor(2);
//   gr->SetLineWidth(4);
   gr2->SetMarkerColor(4);
   gr->SetMarkerStyle(21);
   gr2->SetMarkerStyle(21);
   gr->SetMaximum(20.0);
   gr->SetMinimum(-20.0);
   gr->GetXaxis()->SetLimits(-5.0,5.0);
   gr->SetTitle("Bisection Method");
   gr->GetXaxis()->SetTitle("X");
   gr->GetYaxis()->SetTitle("Y");
   gr->Draw("AL");
   gr2->Draw("P");

   // TCanvas::Update() draws the frame, after which one can change it
   c1->Update();
   //c1->GetFrame()->SetFillColor(21);
   //c1->GetFrame()->SetBorderSize(12);
   c1->Modified();*/
}
