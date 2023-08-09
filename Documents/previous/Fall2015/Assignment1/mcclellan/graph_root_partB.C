#include <TRandom.h>

void graph_root_partB() {
   //Draw a simple graph
   // To see the output of this macro, click begin_html <a href="gif/graph.gif">here</a>. end_html
   //Author: Rene Brun
   //
   //Modified: Edward J. Brash, to find roots of a cubic polynomial, using bisection method
  
   gStyle->SetOptFit(kFALSE);	
   TCanvas *c1 = new TCanvas("c1","Efficiency of Root Finding vs Chunk Size",200,10,1000,700);
   
   c1->SetFillColor(42);
   c1->SetGrid();
   c1->SetLogy();

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
  
  //int nsearch;
  //cout << "Enter the chunk size for the search: ";
  //cin >> nsearch;
  //int niter = npoints/nsearch;
  
  int nsteps_array [npoints];
  int nsearch_array [npoints];
	
  for (int i=0;i<npoints;i++){
	nsteps_array[i] = 0;
	}

  //* Main iteration loop
for (int j=0; j<npoints; j++){
  int nroots_found=0;
  int nsearch = j+1;
  nsearch_array[j] = j+1;
  int niter = npoints/nsearch;
  int nsteps = 0;
  double ycomp=yval[0];
  /*for (int k=0; k<npoints; k++){
	xroots[k]=0;
	yroots[k]=0;
	}*/

  for (int i=1; i<niter; i++){
	double y=yval[nsearch*i];
        //* check to see if the endpoint of the chunk is a root
	if (y == 0.0) {
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
//cout << i << endl;
  }
if (nroots_found == 3) {nsteps_array[j]=nsteps;}
if (j%100 == 0) {cout << j << endl;}
}
  //cout << "Number of roots found = " << nroots_found << endl;
  //cout << "Number of instructions ~ " << nsteps << endl;

   //gr = new TGraph(npoints,xval,yval);
   //gr2 = new TGraph(nroots_found,xroots,yroots);
//   gr->SetLineColor(2);
//   gr->SetLineWidth(4);
   /*gr2->SetMarkerColor(4);
   gr->SetMarkerStyle(21);
   gr2->SetMarkerStyle(21);
   gr->SetMaximum(20.0);
   gr->SetMinimum(-20.0);
   gr->GetXaxis()->SetLimits(-5.0,5.0);
   gr->SetTitle("Bisection Method");
   gr->GetXaxis()->SetTitle("X");
   gr->GetYaxis()->SetTitle("Y");
   gr->Draw("AL");
   gr2->Draw("P");*/

	gr = new TGraph(npoints,nsearch_array,nsteps_array);
	gr->SetLineColor(2);
	gr->SetLineWidth(4);
	gr->SetMarkerColor(4);
	gr->SetMarkerStyle(6);
	gr->GetXaxis()->SetLimits(0,10000);
	//gr->SetMaximum(1000);
	gr->Draw("AP");

   // TCanvas::Update() draws the frame, after which one can change it
   c1->Update();
   c1->GetFrame()->SetFillColor(21);
   c1->GetFrame()->SetBorderSize(12);
   c1->Modified();
}
