// fsw - Program to compute the solutions to a finite square well potential
// using the Verlet method
#include <iostream>
#include "math.h"

void graph_fsw(int inodes) {
   //
   //Modified: Edward J. Brash
   //		

  //* Set initial conditions
  double v0 = 2.0;
  double L = 5.0;
  const int vtype = 0;
  // 
  const int npoints = 1000;
  double estep_initial = 1.0E-3;
  double estep_final = 1.0E-6;
  double x_max = 2.0*L;
  double dx = x_max/npoints;
  int irev=0;

  f = new double [npoints]; x = new double [npoints];
  v = new double [npoints];
  double energy=v0*estep_final;
  bool check = true;
  bool really = true;
  int i;
  double f_old=0.0;
  double emin, emax;

  while (check){
  	irev=0;
  	
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

    		//* Test if the wavefunction has passed through 0;
    		//    if yes, remember that a node has been seen.
		if( f[i]*f[i-1] < 0 && x[i] < L ) { // Test position for sign change
      			//cout << "Turning point at x = " << x[i] << endl;
      			irev++;       // Increment the number of reversals
    		}

  	}

	if(f[npoints-1]*f_old < 0.0 && irev == inodes){
		check=false;
		emin = energy-v0*estep_initial;
		emax = energy;
	}
	energy+=v0*estep_initial;
	f_old=f[npoints-1];
	if(energy > v0 && vtype==1){
		check = false;
		really = false;
	}
  }

  if (!really){
	  cout << "No bound states exist for " << inodes << " nodes." << endl;
  }else{
	  cout << "Found solution between " << emin << " and " << emax << endl;
	  energy = emin;
	  check = true;
	  f_old=0.0;
	  while (check){
		  irev = 0;
        	  for (i=0;i<npoints;i++){
			  f[i]=0.0;
			  v[i]=0.0;
			  x[i]=0.0;
		  }
		  
		  f[0]=v0/2.0;
		  f[1]=v0/2.0;
	          x[0]=0.0;
		  x[1]=dx;
		  if(vtype==1){
			  v[0]=0.0;
			  v[1]=0.0;
		  }else{
			  v[0]=0.0;
			  v[1]=v0/(4.0*L*L)*dx*dx;
		  }

	          for( i=2; i<npoints; i++ ) {
	      		  x[i] = i*dx;

			  if(vtype==1){
				  if (x[i] < L){
				  	v[i] = 0.0;
				  }else{
				  	v[i] = v0;
				  }
			  }else{
				  v[i]=v0/(4.0*L*L)*x[i]*x[i];
			  }
			  f[i] = (2.0 + dx*dx*(v[i]-energy))*f[i-1] - f[i-2];

			  //* Test if the wavefunction has passed through 0;
			  //    if yes, remember that a node has been seen.
			  if( f[i]*f[i-1] < 0 && x[i] < L ) { // Test position for sign change									 //cout << "Turning point at x = " << x[i] << endl;
				  irev++;       // Increment the number of reversals
			  }
		  }

	       	  //cout << "f[npoints -1] = " << f[npoints-1] << " Energy = " << energy << endl;
  	          if(f[npoints-1]*f_old < 0.0 && irev == inodes){
	  		cout << "Found it!!" << endl;
	  		check=false;
		  }
  		  energy+=v0*estep_final;
		  f_old=f[npoints-1];
  	  }
  	  // Normalize wavefunction
  	  double wfsum=0.0;
  	  for (i=0; i<(npoints-100); i++){
		wfsum+=f[i]*f[i]*dx;
 	  }
  	  for (i=0; i<npoints; i++){
		//f[i]=f[i]/sqrt(wfsum);
 	  }
	  energy-=v0*estep_final;
	  cout << "Energy =  " << energy << endl;
          cout << "Nodes = " << irev << endl;
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
