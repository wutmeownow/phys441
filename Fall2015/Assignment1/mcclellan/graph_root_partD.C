#include <TRandom.h>

void graph_root_partD() {
   //Draw a simple graph
   // To see the output of this macro, click begin_html <a href="gif/graph.gif">here</a>. end_html
   //Author: Rene Brun
   //
   //Modified: Edward J. Brash, to find roots of a cubic polynomial, using bisection method
  
   gStyle->SetOptFit(kFALSE);	
   TCanvas *c1 = new TCanvas("c1","Efficiency of Root Finding vs Chunk Size",200,10,1000,700);
   c1->Divide(2,1);
   c1->SetFillColor(42);
   c1->cd(1)->SetGrid();
   c1->cd(1)->SetLogy();
   c1->cd(2)->SetGrid();

//* Initialize the polynomial
  int nroots_known = 3;
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
  int nroots_found_MAX = 0;

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
if (nroots_found > nroots_found_MAX) {nroots_found_MAX = nroots_found;}
if (nroots_found == nroots_known) {nsteps_array[j]=nsteps;}

//Debugging: making sure it's actually processing and not broken
if (j%100 == 0) {cout << j << endl;}
}
  //cout << "Number of roots found = " << nroots_found << endl;
  //cout << "Number of instructions ~ " << nsteps << endl;

   gr = new TGraph(npoints,xval,yval);
   gr2 = new TGraph(nroots_found_MAX,xroots,yroots);
   gr->SetLineColor(2);
   gr->SetLineWidth(4);
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

	gr3 = new TGraph(npoints,nsearch_array,nsteps_array);
	gr3->SetLineColor(2);
	gr3->SetLineWidth(4);
	gr3->SetMarkerColor(4);
	gr3->SetMarkerStyle(6);
	gr3->GetXaxis()->SetLimits(0,npoints);
	gr3->SetTitle("Efficiency of Root Finding");
	gr3->GetXaxis()->SetTitle("Chunk size");
	gr3->GetYaxis()->SetTitle("Steps taken");
	//gr->SetMaximum(1000);
	c1->cd(1); gr3->Draw("AP");

   // TCanvas::Update() draws the frame, after which one can change it
   c1->Update();
   c1->GetFrame()->SetFillColor(21);
   c1->GetFrame()->SetBorderSize(12);
   c1->Modified();
}
