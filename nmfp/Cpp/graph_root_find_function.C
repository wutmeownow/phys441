Double_t myfunction(Double_t x)
{
	Double_t xx = x;

	Double_t par[4];
	par[0]=1.80;
	par[1]=-4.05;
	par[2]=0.40;
	par[3]=1.00;

	Double_t L = 10.0;
	Double_t v0 = 200.0;

	Double_t f = par[0]+par[1]*xx+par[2]*xx*xx+par[3]*xx*xx*xx;
	//Double_t f = sin(x);
	//Double_t f = cos(x);
	//Double_t f = xx*xx-.001;
	
	//Double_t f = tan(pow(xx,0.5)*L/2.0)-pow((v0/xx-1.0),0.5);

	return f;
}

void graph_root_find_function() {
  
   gStyle->SetOptFit(kFALSE);	
   TCanvas *c1 = new TCanvas("c1","Root Finding Example",200,10,700,500);
   
   c1->SetFillColor(42);
   c1->SetGrid();
   //c1->SetLogy();

  Double_t f, xmid, fa, fb, fc;

  // User changes the following:  xmin, xmax, and the number of points
  
  const Double_t xmin = -4.0;
  const Double_t xmax = 4.0;
  const Int_t npoints = 10007;
  const Double_t epsilon = 1.0E-10;
  
  ////////////////////////////////////////////////////////////////////

  Double_t xlow;
  Double_t xhigh;
  Double_t xstep[npoints];
  Double_t ystep[npoints];
  Double_t xval[npoints],yval[npoints];
  Double_t dx = (xmax-xmin)/npoints;

  Int_t nsearch;

  for (nsearch=1; nsearch<npoints; nsearch++){

  Int_t niter = npoints/nsearch;
  Double_t ycomp;
  Int_t nsteps=0;
  Int_t nroots_found=0;
  Int_t nroots_expected;

  ycomp = myfunction(xmin);

  for (Int_t i=1; i<niter; i++){
        Double_t x=xmin+(nsearch*i)*dx;
	Double_t y=myfunction(x);
	xval[i]=x;
	yval[i]=y;
	// if (nsearch == 2) cout << "i = " << i << " e = " << x << " f = " << y << endl;
	if (y == 0.0) {
		if(nsearch == 1) cout << " A Found root at x = " << x << endl;
		nsteps=nsteps+1;
		nroots_found++;
	}
	nsteps++;
	// if (nsearch == 2) cout << "i = " << i << " y = " << y << " ycomp = " << ycomp << endl;
	if (y*ycomp < 0.0 && fabs(y) < 1.0){
		//* Found a root in this interval
		xlow = xmin+(nsearch*(i-1))*dx;
		xhigh = xmin+(nsearch*(i))*dx;
		nsteps=nsteps+2;
  		Double_t diff = 1.0E12;
		while (diff > epsilon){
			//if (i< 20) cout << "i = " << i << " diff = " << diff << endl;
			fa = myfunction(xlow);
			fb = myfunction(xhigh);
			xmid = (xhigh + xlow)/2.0;
			fc = myfunction(xmid);
			nsteps=nsteps+4;
			Double_t product = fa*fc;
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
	        if (nsearch == 1) cout << "nsearch = " << nsearch << " Found root at x = " << xmid << endl;
		nroots_found++;
		ycomp=y;
		nsteps++;
	}
	else{
		ycomp=y;
		nsteps++;
	}
  }

  if (nsearch == 1) nroots_expected = nroots_found;

  xstep[nsearch]=nsearch;
  if (nroots_found == nroots_expected) {
	ystep[nsearch]=nsteps;
  }else{
	ystep[nsearch]=0.0;	
  }

  }

   gr = new TGraph(npoints,xval,yval);
//   gr->SetLineColor(2);
//   gr->SetLineWidth(4);
//   gr->SetMarkerColor(4);
   gr->SetMarkerStyle(21);
   gr->SetMaximum(10.0);
   gr->SetMinimum(-10.0);
   //Double_t upper_limit = npoints/5.;
   //gr->GetXaxis()->SetLimits(1.0,upper_limit);
   //gr->SetTitle("Root Finding Example");
   //gr->GetXaxis()->SetTitle("Division Size");
   //gr->GetYaxis()->SetTitle("NSteps");
   gr->Draw("AP");

   // TCanvas::Update() draws the frame, after which one can change it
   c1->Update();
   c1->GetFrame()->SetFillColor(21);
   c1->GetFrame()->SetBorderSize(12);
   c1->Modified();
}

