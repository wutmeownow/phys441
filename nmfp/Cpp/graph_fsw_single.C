// fsw - Program to compute the solutions to a finite square well potential
// using the Verlet method
#include <iostream>
#include "math.h"

void graph_fsw_single(double energy) {
   //
   //Modified: Edward J. Brash
   //		

  //* Set initial conditions
  double v0 = 2.0;
  double L = 5.0;
  const int vtype = 1;
  // 
  const int npoints = 1000;
  double x_max = 2.0*L;
  double dx = x_max/npoints;
  int irev=0;

  f = new double [npoints]; x = new double [npoints];
  v = new double [npoints];

  int i;
  double f_old=0.0;
  double emin, emax;

	for (i=0;i<npoints;i++){
	  f[i]=0.0;
	  v[i]=0.0;
	  x[i]=0.0;
  	}	

  	f[0]=v0/2.0;
  	f[1]=v0/2.0;
  	x[0]=0.0;
  	x[1]=dx;
	if (vtype == 1){
  		v[0]=0.0;	
  		v[1]=0.0;
	}else{
		v[0]=0.0;
		v[1]=v0/(4.0*L*L)*dx*dx;
	}

  	for( i=2; i<npoints; i++ ) {  

    		x[i] = i*dx;
		if (vtype == 1){
    			if (x[i] < L){
				v[i] = 0.0;
    			}else{
    				v[i] = v0;
    			}
		}else{
			v[i]=v0/(4.0*L*L)*x[i]*x[i];
		}
    		f[i] = (2.0 + dx*dx*(v[i]-energy))*f[i-1] - f[i-2];

  	}

  	  // Normalize wavefunction
  	  double wfsum=0.0;
  	  for (i=0; i<(npoints-100); i++){
		wfsum+=f[i]*f[i]*dx;
 	  }
  	  for (i=0; i<npoints; i++){
		//f[i]=f[i]/sqrt(wfsum);
 	  }

// Plotting stuff below this point ...

   const Int_t n = npoints;

   TCanvas *c1 = new TCanvas("c1","Cubic Data",200,10,700,500);
   c1->SetFillColor(42);
   c1->SetGrid();
   //gStyle->SetOptFit(kFALSE);	
   gStyle->SetOptFit(1);	
   
   gr = new TGraph(npoints,x,f);
   gr2 = new TGraph(npoints,x,v);

   gr->SetMarkerColor(kBlue);
   gr->SetMarkerStyle(21);
   gr->SetTitle("Finite Square Well");
   gr->GetXaxis()->SetTitle("X");
   gr->GetYaxis()->SetTitle("Psi(x)");
   gr2->SetMarkerColor(kRed);
   gr2->SetMarkerStyle(21);
   gr2->SetTitle("Finite Square Well");
   gr2->GetXaxis()->SetTitle("X");
   gr2->GetYaxis()->SetTitle("Psi(x)");
   TAxis *axis = gr->GetXaxis();
   axis->SetLimits(0.0,x_max);
   gr->GetHistogram()->SetMaximum(v0*1.25);
   gr->GetHistogram()->SetMinimum(-v0*1.25);
   c1->cd();
   gr->Draw("AP");
   gr2->Draw("P");

   // TCanvas::Update() draws the frame, after which one can change it
   c1->Update();
   c1->GetFrame()->SetFillColor(21);
   c1->GetFrame()->SetBorderSize(12);
   c1->Modified();
}
