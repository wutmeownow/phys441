#include <TMath.h>

Double_t myfunction(Double_t x)
{
        Double_t xx = x;

	Double_t f = 3.0/2.0*(1.0 - xx*xx);

	return f;
}

void graph_integration_multiple(Int_t max_order = 5, Int_t nbins = 20, Int_t min_order = 2) {
  
   gStyle->SetOptFit(kFALSE);	
   TCanvas *c1 = new TCanvas("c1","Integration Example",200,200,1000,1000);
   c1->SetFillColor(41);
   c1->SetGrid();
   c1->Divide(1,2); 
   
   TRandom3 *rnum = new TRandom3(0);

   const Int_t norders = max_order - min_order + 1;
   const Int_t nbin = nbins;
   Double_t sum[norders][nbin];
   Double_t np[norders];
   Double_t enp[norders];
   Double_t sum2[norders];
   Double_t esum2[norders];
   Double_t esum3[norders];
   Double_t np2[norders];
   Double_t np3[norders];
   
   for (int j = min_order; j<=max_order; j++){
	Int_t npoints = pow(10,j);
	np[j-min_order] = npoints;
	np2[j-min_order] = 1/sqrt(npoints);;
	np3[j-min_order] = log(1.0*npoints);;
	enp[j-min_order]=0;
	sum2[j-min_order]=0;
	esum2[j-min_order]=0;
	esum3[j-min_order]=0;
	for (int k = 0; k<nbin; k++){


  //* Initialize the polynomial

	   double f, xmid;

	   double xlow = 0.0;
	   double xhigh = 1.0;
	   double dx = (xhigh-xlow)/npoints;
	   
	   sum[j-min_order][k] = 0.0;
   	   double xval, yval;
	   for (int i = 0; i<npoints;i++){
		   xval = rnum->Uniform(xlow,xhigh);
		   yval=myfunction(xval);
		   sum[j-min_order][k]+= dx*yval;
	   }	

	}

	for (int k = 0; k<nbin; k++){
		sum2[j-min_order]+=sum[j-min_order][k]/nbin;
	}

	for (int k = 0; k<nbin; k++){
		esum2[j-min_order]+= pow((sum[j-min_order][k]-sum2[j-min_order]),2)/nbin;
	}
	esum2[j-min_order]=sqrt(esum2[j-min_order]);


   	cout << "Integral = " << sum2[j-min_order] << " +/- " << esum2[j-min_order] << " for npoints = " << npoints << endl;
   	cout << "Error = " << abs(1.0 - sum2[j-min_order]) << endl;
	esum3[j-min_order]=log(esum2[j-min_order]);

   }

   TGraphErrors *gr = new TGraphErrors(norders,np,sum2,enp,esum2);
   TGraph *gr2 = new TGraph(norders,np3,esum3);

   gr->SetLineColor(2);
   gr->SetLineWidth(4);
   gr->SetMarkerColor(4);
   gr->SetMarkerStyle(21);
   gr->SetTitle("MC integration 1");
   gr->GetXaxis()->SetTitle("N points");
   gr->GetYaxis()->SetTitle("Integral");
   gr2->SetLineColor(2);
   gr2->SetLineWidth(4);
   gr2->SetMarkerColor(4);
   gr2->SetMarkerStyle(21);
   gr2->SetTitle("MC integration 2");
   gr2->GetXaxis()->SetTitle("log(Npoints)");
   gr2->GetYaxis()->SetTitle("log(Error in Integral)");

   c1->cd(1);
   gPad->SetLogx();
   gr->Draw();
   c1->cd(2);
   gr2->Draw();
   gr2->Fit("pol1");

   // TCanvas::Update() draws the frame, after which one can change it
   c1->Update();
   c1->GetFrame()->SetFillColor(21);
   c1->GetFrame()->SetBorderSize(12);
   c1->Modified();
}

