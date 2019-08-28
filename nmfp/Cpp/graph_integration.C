Double_t myfunction(Double_t x)
{
        Double_t xx = x;

	Double_t f = 3.0/2.0*(1.0 - xx*xx);

	return f;
}

void graph_integration(Int_t npoints = 10000) {
  
   gStyle->SetOptFit(kFALSE);	
   //TCanvas *c1 = new TCanvas("c1","Integration Example",1200,520,700,500);
   
   //c1->SetFillColor(41);
   //c1->SetGrid();
   //c1->SetLogy();
   
   TRandom3 *rnum = new TRandom3(0);
   
  //* Initialize the polynomial

   double f, xmid;

   double xlow = 0.0;
   double xhigh = 1.0;
   double dx = (xhigh-xlow)/npoints;
  
   double sum = 0.0;
   double xval, yval;

   for (int i = 0; i<npoints;i++){
	xval = rnum->Uniform(xlow,xhigh);
	yval=myfunction(xval);
	sum+= dx*yval;
   }	

   cout << "Integral = " << sum << endl;
   cout << "Error = " << abs(1.0 - sum) << endl;

   // TCanvas::Update() draws the frame, after which one can change it
   //c1->Update();
   //c1->GetFrame()->SetFillColor(21);
   //c1->GetFrame()->SetBorderSize(12);
   //c1->Modified();
}

