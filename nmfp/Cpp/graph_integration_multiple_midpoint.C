#include <TMath.h>

Double_t myfunction(Double_t x)
{
        Double_t xx = x;

	Double_t f = 3.0/2.0*(1.0 - xx*xx);

	return f;
}

void graph_integration_multiple_midpoint(Int_t max_order = 5, Int_t nbins = 100, Int_t min_order = 2) {
  
   gStyle->SetOptFit(kFALSE);	
   TCanvas *c1 = new TCanvas("c1","Integration Example",200,200,1000,1000);
   c1->SetFillColor(41);
   c1->SetGrid();
   c1->Divide(2,2); 
   
   TRandom3 *rnum = new TRandom3(0);

   const Int_t norders = max_order - min_order + 1;
   const Int_t nbin = nbins;
   Double_t sum[norders][nbin];
   Double_t np[norders];
   Double_t enp[norders];
   Double_t sum2[norders];
   Double_t esum2[norders];
   Double_t np2[norders];
   Double_t np2mid[norders];

   Double_t summid[norders];
   Double_t esummid[norders];
   
   for (int j = min_order; j<=max_order; j++){
	Int_t npoints = pow(10,j);
	np[j-min_order] = npoints;
	np2[j-min_order] = abs(1/sqrt(npoints));
	np2mid[j-min_order]= abs(1.0/(npoints*npoints));
	enp[j-min_order]=0;
	sum2[j-min_order]=0;
	esum2[j-min_order]=0;

	summid[j-min_order]=0;
	esummid[j-min_order]=0;

	double xlow = 0.0;
	double xhigh = 1.0;
	double dx = (xhigh-xlow)/npoints;
	
	for (int i = 0; i<npoints; i++){
		double xmid = xlow + i*dx + dx/2;
	        double ymid = myfunction(xmid);
	        summid[j-min_order]+=ymid*dx;
	}

	cout << "Midpoint integral = " << summid[j-min_order] << endl;
	esummid[j-min_order]=abs((1.0-summid[j-min_order]));
	cout << "Midpoint Error = " << esummid[j-min_order] << endl;	

	for (int k = 0; k<nbin; k++){


  //* Initialize the polynomial

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
   	cout << "MC integral = " << sum2[j-min_order] << " +/- " << esum2[j-min_order] << " for npoints = " << npoints << endl;
   	cout << "MC Error = " << abs(1.0 - sum2[j-min_order]) << endl;

   }

   for (int i = 0; i<norders; i++){
	   cout << " n: " << np[i] << " " << np2[i] << " " << np2mid[i] << " " << sum2[i] << " +- " << esum2[i] << " " << summid[i] << " +/- " << esummid[i] << endl;
   }

   TGraphErrors *gr = new TGraphErrors(norders,np,sum2,enp,esum2);
   TGraph *gr2 = new TGraph(norders,np2,esum2);
   TGraphErrors *midgr = new TGraphErrors(norders,np,summid,enp,esummid);
   TGraph *midgr2 = new TGraph(norders,np2mid,esummid);

   gr->SetLineColor(2);
   gr->SetLineWidth(4);
   gr->SetMarkerColor(4);
   gr->SetMarkerStyle(21);
   gr->SetTitle("MC integration");
   gr->GetXaxis()->SetTitle("N points");
   gr->GetYaxis()->SetTitle("Integral");
   midgr->SetLineColor(2);
   midgr->SetLineWidth(4);
   midgr->SetMarkerColor(4);
   midgr->SetMarkerStyle(21);
   midgr->SetTitle("Midpoin2 integration");
   midgr->GetXaxis()->SetTitle("N points");
   midgr->GetYaxis()->SetTitle("Integral");
   gr2->SetLineColor(2);
   gr2->SetLineWidth(4);
   gr2->SetMarkerColor(4);
   gr2->SetMarkerStyle(21);
   gr2->SetTitle("MC integration");
   gr2->GetXaxis()->SetTitle("1/sqrt(N");
   gr2->GetYaxis()->SetTitle("Error in Integral");
   midgr2->SetLineColor(2);
   midgr2->SetLineWidth(4);
   midgr2->SetMarkerColor(4);
   midgr2->SetMarkerStyle(21);
   midgr2->SetTitle("Midpoint integration");
   midgr2->GetXaxis()->SetTitle("1/N");
   midgr2->GetYaxis()->SetTitle("Error in Integral");

   c1->cd(1);
   gPad->SetLogx();
   gr->Draw();
   c1->cd(2);
   gPad->SetLogx();
   midgr->Draw();
   c1->cd(3);
   gPad->SetLogx();
   gPad->SetLogy();
   gr2->Draw();
   c1->cd(4);
   gPad->SetLogx();
   gPad->SetLogy();
   midgr2->Draw();

   // TCanvas::Update() draws the frame, after which one can change it
   c1->Update();
   c1->GetFrame()->SetFillColor(21);
   c1->GetFrame()->SetBorderSize(12);
   c1->Modified();
}

