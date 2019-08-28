Double_t myfunction(Double_t x)
{
        Double_t xx = x;

        Double_t par[5];
        par[0]=847.192;
        par[1]=-2064.25;
        par[2]=1927.42;
        par[3]=-812.332;
	par[4]=129.88;
        
	Double_t f = par[1]+2.0*par[2]*xx+3.0*par[3]*xx*xx+4.0*par[4]*xx*xx*xx;

	return f;
}

Double_t myfinalfunction(Double_t x, Double_t ymin)
{
        Double_t xx = x;
	Double_t yymin = ymin;

        Double_t par[5];
        par[0]=847.192;
        par[1]=-2064.25;
        par[2]=1927.42;
        par[3]=-812.332;
	par[4]=129.88;
        
	Double_t f = par[0]+par[1]*xx+par[2]*xx*xx+par[3]*xx*xx*xx+par[4]*xx*xx*xx*xx-yymin-1;
        
	return f;
}

Double_t myorigfunction(Double_t x)
{
        Double_t xx = x;

        Double_t par[5];
        par[0]=847.192;
        par[1]=-2064.25;
        par[2]=1927.42;
        par[3]=-812.332;
	par[4]=129.88;
        
	Double_t f = par[0]+par[1]*xx+par[2]*xx*xx+par[3]*xx*xx*xx+par[4]*xx*xx*xx*xx;
        
	return f;
}
        
void graph_root_find_complete_function() {
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
   //c1->SetLogy();

   
  //* Initialize the polynomial

   double f, xmid, fa, fb, fc;

   double xlow = 1.1;
   double xhigh = 2.0;
   const int npoints = 10007;
   double dx = (xhigh-xlow)/npoints;
  
   double xval[npoints];
   double yval[npoints];
   double yval2[npoints];
   double yval3[npoints];

   for (int i = 0; i<npoints;i++){
	xval[i]=xlow+i*dx;
	yval[i]=myfunction(xval[i]);
	yval2[i]=myorigfunction(xval[i]);
   }	

  //* Search the arrays for sign changes
  
   double xmin;

   int niter = npoints;
   double ycomp=0;
   int nroots_found=0;

   for (int i=1; i<niter; i++){
	double y=yval[i];
	if (y == 0.0) {
		cout << "Found root at x = " << xval[i] << endl;
		xmin = xval[i];
		nroots_found++;
	}
	if (y*ycomp < 0.0){
		//* Found a root in this interval
		xlow = xval[(i-1)];
		xhigh = xval[i];
  		double epsilon = 1.0E-4;
  		double diff = 1.0E12;
		while (diff > epsilon){
			fa = myfunction(xmid);
			fb = myfunction(xhigh);
			xmid = (xhigh + xlow)/2.0;
			fc = myfunction(xmid);
			double product = fa*fc;
			if (product < 0) {
				xhigh = xmid;
				fb = fc;
			} else {
				xlow = xmid;
				fa = fc;
			}

			diff = fabs(fc);
		} 
		cout << "Found root at x = " << xmid << endl;
		xmin = xmid;
		nroots_found++;
		ycomp=y;
	}
	else{
		ycomp=y;
	}
   }


   double ymin = myorigfunction(xmin);
   cout << "ymin = " << ymin << endl;

   TGraph *gr = new TGraph(npoints,xval,yval2);
   c1->cd();
   gr->Draw();
  
   xlow=1.1;
   for (int i = 0; i<npoints;i++){
	xval[i]=xlow+i*dx;
	yval3[i]=myfinalfunction(xval[i],ymin);
	//cout << "x = " << xval[i] << " y = " << yval3[i] << endl;
   }

   ycomp=0;
   nroots_found=0;
   for (int i=1; i<niter; i++){
         double y=yval3[i];
          if (y == 0.0) { 
                  cout << "Found root at x = " << xval[i] << endl;
                  xmin = xval[i];
                  nroots_found++;
         }
         if (y*ycomp < 0.0){
                 //* Found a root in this interval
                 xlow = xval[(i-1)];
                 xhigh = xval[i]; 
                 double epsilon = 1.0E-4;
                 double diff = 1.0E12;
                 while (diff > epsilon){
                         fa = myfinalfunction(xmid,ymin);
                         fb = myfinalfunction(xhigh,ymin);
                         xmid = (xhigh + xlow)/2.0;
                         fc = myfinalfunction(xmid,ymin);
                         double product = fa*fc;
                         if (product < 0) {
                                 xhigh = xmid;
                                 fb = fc;
                         } else {
                                 xlow = xmid;
                              fa = fc;
                         }
                         
                      diff = fabs(fc);
                 } 
                 cout << "Found root at x = " << xmid << endl;
                 xmin = xmid;
                 nroots_found++;
                 ycomp=y;
         }
         else{   
                 ycomp=y;
         }
    }
   

   // TCanvas::Update() draws the frame, after which one can change it
   c1->Update();
   c1->GetFrame()->SetFillColor(21);
   c1->GetFrame()->SetBorderSize(12);
   c1->Modified();
}

