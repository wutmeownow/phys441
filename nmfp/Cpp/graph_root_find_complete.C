void graph_root_find_complete() {
   //Draw a simple graph
   // To see the output of this macro, click begin_html <a href="gif/graph.gif">here</a>. end_html
   //Author: Rene Brun
   //
   //Modified: Edward J. Brash, to change to simple linear plot
   //				with random fluctuations
  
   gStyle->SetOptFit(kFALSE);	
   TCanvas *c1 = new TCanvas("c1","Root Finding Example",1200,520,700,500);
   
   c1->SetFillColor(41);
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
  const int npoints = 10007;
  double xval[npoints];
  double yval[npoints];
  double xstep[npoints];
  double ystep[npoints];
  double dx = (xhigh-xlow)/npoints;

  for (int i = 0; i<npoints;i++){
	xval[i]=xlow+i*dx;
	yval[i]=a0+a1*xval[i]+a2*xval[i]*xval[i]+a3*xval[i]*xval[i]*xval[i];
	// cout << "x: " << xval[i] << "  y: " << yval[i] << endl;
  }	

  //* Search the arrays for sign changes
  
  int nsearch;

  for (nsearch=1; nsearch<npoints; nsearch++){

  cout << "Nsearch = " << nsearch << endl;

  int niter = npoints/nsearch;
  double ycomp=yval[0];
  int nsteps=0;
  int nroots_found=0;

  for (int i=1; i<niter; i++){
	double y=yval[nsearch*i];
	if (y == 0.0) {
		if(nsearch == 1) cout << "Found root at x = " << xval[nsearch*i] << endl;
		nsteps=nsteps+1;
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
		if (nsearch ==1 ) cout << "Found root at x = " << xmid << endl;
		nroots_found++;
		ycomp=y;
		nsteps++;
	}
	else{
		ycomp=y;
		nsteps++;
	}
  }

  xstep[nsearch]=nsearch;
  if (nroots_found == 3) {
	ystep[nsearch]=nsteps;
  }else{
	ystep[nsearch]=10000.0;	
  }

  }

   gr = new TGraph(npoints,xstep,ystep);
//   gr->SetLineColor(2);
//   gr->SetLineWidth(4);
//   gr->SetMarkerColor(4);
   gr->SetMarkerStyle(21);
   gr->SetMaximum(10000.0);
   gr->SetMinimum(400.0);
   gr->GetXaxis()->SetLimits(1.0,1200.0);
   gr->SetTitle("Root Finding Example");
   gr->GetXaxis()->SetTitle("Division Size");
   gr->GetYaxis()->SetTitle("NSteps");
   gr->Draw("AL");

   // TCanvas::Update() draws the frame, after which one can change it
   c1->Update();
   c1->GetFrame()->SetFillColor(21);
   c1->GetFrame()->SetBorderSize(12);
   c1->Modified();
}

