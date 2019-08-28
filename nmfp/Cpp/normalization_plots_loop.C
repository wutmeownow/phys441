#include <ostream>
#include "TMatrixD.h"

Double_t fitfunction(Double_t *x, Double_t *par)
{
	Float_t xx = x[0];
    	Float_t binsize = x[1];
	Double_t f = binsize*par[0]/sqrt(2.0*3.14159265*pow(par[2],2))*pow(2.718281828,-0.5*pow((xx-par[1]),2)/pow(par[2],2));
//	cout << "function: " << xx << " " << f << endl;
	return f;	
}

Double_t myfitfunction(Double_t *x, Double_t *par)
{
	Float_t xx = x[0];
	Double_t f = 0.40*par[0]/sqrt(2.0*3.14159265*pow(par[2],2))*pow(2.718281828,-0.5*pow((xx-par[1]),2)/pow(par[2],2));
    //	cout << "function: " << xx << " " << f << endl;
	return f;
}

void normalization_plots_loop(const Int_t nloop = 1000) {
  

  Int_t npoints;
  Double_t mu,sigma;
  cout << "Enter the number of samples:" << endl;
  cin >> npoints;
  cout << "Enter the centroid:" << endl;
  cin >> mu;
  cout << "Enter the standard deviation" << endl;
  cin >> sigma;

  const Int_t nbins = 50;
  const Int_t nsigma = 5;
  const Int_t np = npoints;
  Double_t zval[nloop], ybar[nloop];
  Double_t xlow=mu-nsigma*sigma;
  Double_t xhigh=mu+nsigma*sigma;

  TRandom3 r;
  
  TCanvas *c1 = new TCanvas("c1","Normalization_Plots",200,10,700,500);
  c1->SetFillColor(42);
  c1->SetGrid();
  c1->Divide(3,3);
  c1->cd(1);

  Int_t padcount = 1;

  for (Int_t jj = 0; jj<nloop; jj++){

  	Double_t x[nbins],y[nbins],ex[nbins],ey[nbins];

  	Double_t step = 2.0*nsigma*sigma/nbins;
  	Double_t ymax = 6.0*npoints/nbins;
  	Double_t rand = 0.0;
  	Int_t ibin, i;
  	Double_t xval[np];

  	for (i=0;i<nbins;i++){
	  x[i]=0;
	  y[i]=0;
	  ex[i]=0;
	  ey[i]=0;
  	}

  	for (i=0; i<npoints; i++) {
	  //xval[i]=mu-2.0*sigma+4.0*sigma*r.Rndm();
	  xval[i]=r.Gaus(mu,sigma);
	  //xval[i]=r.Landau(mu,sigma);
	  ibin = (xval[i]-xlow)/step;
	  if (ibin<0) {
		  ibin=0;
	  }
	  if (ibin>=nbins) {
		  ibin=nbins-1;
	  }
          y[ibin]++;
  	}

  	for (i=0;i<nbins; i++){
	  x[i]=xlow+i*step;
	  if(y[i]==0){
	  	ey[i]=1.0;
	  }else{
	        ey[i]=pow(y[i],0.5);
	  }
  	}

   	//gStyle->SetOptFit(kFALSE);	
   	//gStyle->SetOptFit(1);	
   	//gr = new TGraphErrors(m,x,y,ex,ey);
   	//gr = new TGraph(m,x,y);
   	TH1F *h1 = new TH1F("h1","Gaussian Fit",nbins,xlow,xhigh);
   	for(i=0;i<npoints;i++){h1->Fill(xval[i]);}

	if (jj%111 == 0){
		cout << "Pad = " << padcount << endl;
		h1->Draw();
        	c1->cd(padcount+1);
        	padcount++;
	}

	Double_t mean = h1->GetMean();
	zval[jj] = (mean - mu)/(sigma/sqrt(npoints));
	ybar[jj] = mean;

   	//TF1 *pfit1 = new TF1("fitfunction",myfitfunction,xlow,xhigh,3);
   	//pfit1->SetParameters(npoints,mu,sigma);
   	//pfit1->SetParNames("Amplitude","Mu","Sigma");
   
   	//pfit1->SetLineColor(2);
   	//h1->Fit("fitfunction","V");
   	//Double_t pfit1chi2 = pfit1->GetChisquare();
   	//Double_t pfit1ndf = pfit1->GetNDF();
   	//Double_t pfit1chi2ndf = pfit1chi2/pfit1ndf;

  }
  
  c1->Update();
  c1->GetFrame()->SetFillColor(21);
  c1->GetFrame()->SetBorderSize(12);
  c1->Modified();

  TCanvas *c2 = new TCanvas("c2","Normalization_Plots",220,30,700,500);
  c2->SetFillColor(42);
  c2->SetGrid();
  c2->Divide(1,2);
   
  TH1F *h2 = new TH1F("h2","Z-distribution",100,-4,4);
  TH1F *h3 = new TH1F("h3","Ybar distribution",1000,xlow,xhigh);
  for (Int_t jj = 0; jj < nloop; jj++){
	h2->Fill(zval[jj]);
	h3->Fill(ybar[jj]);
  }
  c2->cd(1);
  h2->Draw();
  c2->cd(2);
  h3->Draw();

}
