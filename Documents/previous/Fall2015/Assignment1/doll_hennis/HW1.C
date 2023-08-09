#include <TRandom.h>

HW1() {
   //Draw a simple graph
   // To see the output of this macro, click begin_html <a href="gif/graph.gif">here</a>. end_html
   //Author: Rene Brun
   //
   //Modified: Edward J. Brash, to find roots of a cubic polynomial, using bisection method
   //Modified: Austin Doll-Hennis to determine chunk size vs step size
  
   gStyle->SetOptFit(kFALSE);	
   TCanvas *c1 = new TCanvas("c1","Root Finding Example",200,10,700,500);
   
   c1->SetFillColor(42);
   c1->SetGrid();
   c1->Divide(1,2);
   //c1->SetLogy();

//* Initialize the polynomial

  double a0;
  cout << "a0: ";
  cin >> a0;
  double a1;
  cout << "a1: ";
  cin >> a1;
  double a2;
  cout << "a2: ";
  cin >> a2;
  double a3;
  cout << "a3: ";
  cin >> a3;

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
  //arrays to keep track of step and chunk size
  double stepSize[npoints];
  double chunkSize[npoints];
  //* step size in x
  double dx = (xhigh-xlow)/npoints;

  for (int i = 0; i<npoints;i++){
	xval[i]=xlow+i*dx;
	yval[i]=a0+a1*xval[i]+a2*xval[i]*xval[i]+a3*xval[i]*xval[i]*xval[i];
  }	

  //chunk size from 1 to 10000
  
  for(int nsearch=1;nsearch<=5000;nsearch++){
  chunkSize[nsearch-1]=nsearch;
  int niter = npoints/nsearch;
  double ycomp=yval[0];
  int nsteps=0;
  int nroots_found=0;
  double zeroroot = 0.0;
  //* Main iteration loop

  for (int i=1; i<niter; i++){
	double y=yval[nsearch*i];
        //* check to see if the endpoint of the chunk is a root
	if (y == 0.0) {
		zeroroot=xval[nsearch*i];
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

  stepSize[nsearch-1]=nsteps;

}
  while(nroots_found>0){
	cout << "Found root at x = "<< xmid <<" and " << zeroroot << endl;	
	nroots_found--;
}
   
   c1->cd(1);
   gr = new TGraph(npoints,chunkSize, stepSize);
   gr->SetMarkerStyle(21);
   gr->SetMaximum(2000.0);
   gr->SetMinimum(1.0);
   gr->GetXaxis()->SetLimits(1.0,5000.0);
   gr->SetTitle("Chunk Size v Number of Steps");
   gr->GetXaxis()->SetTitle("Chunk Size");
   gr->GetYaxis()->SetTitle("Number of Steps");
   gr->Draw("AL");

   c1->cd(2);
   gr2 = new TGraph(npoints,xval,yval);
   gr2->SetMaximum(20.0);
   gr2->SetMinimum(-20.0);
   gr2->GetXaxis()->SetLimits(-5.0,5.0);
   gr2->SetTitle("Bisection Method");
   gr2->GetXaxis()->SetTitle("X");
   gr2->GetYaxis()->SetTitle("Y");
   gr2->Draw("AL");

   c1->Update();
   c1->GetFrame()->SetFillColor(21);
   c1->GetFrame()->SetBorderSize(12);
   c1->Modified();
}
