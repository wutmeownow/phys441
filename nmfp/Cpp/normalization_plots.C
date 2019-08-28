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

void normalization_plots() {
  

   const Int_t n = 100;

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
  TRandom r;

  Double_t x[nbins],y[nbins],ex[nbins],ey[nbins];

  Double_t step = 2.0*nsigma*sigma/nbins;
  Double_t ymax = 6.0*npoints/nbins;
  Double_t rand = 0.0;
  Int_t ibin, i;
  Double_t xval[np];
  Double_t xlow=mu-nsigma*sigma;
  Double_t xhigh=mu+nsigma*sigma;

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

  Int_t index[np];
  TMath::Sort(np,xval,index,0);

  Double_t zval[np];
  Double_t xval_ordered[np];

  for(i=0;i<npoints;i++){
	  Double_t fraction = (i+1.0)/(npoints+1.0);
	  zval[i]=ROOT::Math::normal_quantile(fraction,1);
	  xval_ordered[i]=xval[index[i]];
	  //cout << index[i] << " " << xval[index[i]] << " " << zval[i] << endl;
  }

  Int_t np_remove = 2;

  const Int_t np_pared = np - np_remove;
  Double_t zvalp[np_pared];
  Double_t xval_orderedp[np_pared];

  for(i=0;i<np_pared;i++){
	  Double_t fraction = (i+1.0)/(np_pared+1.0);
	  zvalp[i]=ROOT::Math::normal_quantile(fraction,1);
	  xval_orderedp[i]=xval[index[i+np_remove/2]];
	  //cout << index[i] << " " << xval[index[i]] << " " << zval[i] << endl;
  }




   const Int_t m = nbins;
   Int_t k = 0;
   Int_t j =0;
   Double_t step_size = (x[m-1]-x[0])/m;
   cout << "Step size = " << step_size << endl;


   //gStyle->SetOptFit(kFALSE);	
   gStyle->SetOptFit(1);	
   TCanvas *c1 = new TCanvas("c1","Normalization_Plots",200,10,700,500);
   c1->SetFillColor(42);
   c1->SetGrid();
   TCanvas *c2 = new TCanvas("c2","Normalization_Plots",200,710,700,500);
   c2->SetFillColor(42);
   c2->SetGrid();
   TCanvas *c3 = new TCanvas("c3","Normalization_Plots",910,10,700,500);
   c3->SetFillColor(42);
   c3->SetGrid();

   TGraph *grnorm = new TGraph(npoints,zval,xval_ordered);

   grnorm->SetMarkerStyle(21);
   grnorm->SetTitle("Normalization Plot");
   grnorm->GetXaxis()->SetTitle("Z");
   grnorm->GetYaxis()->SetTitle("X_ordered");
   grnorm->Fit("pol1");
   grnorm->GetHistogram()->SetMaximum(1.2*xval_ordered[npoints-1]);
   c2->cd();
   //c2->SetLogy();
   //c2->SetLogx();
   grnorm->Draw("AP");


   TGraph *grnorm2 = new TGraph(np_pared,zvalp,xval_orderedp);

   grnorm2->SetMarkerStyle(21);
   grnorm2->SetTitle("Pared Normalization Plot");
   grnorm2->GetXaxis()->SetTitle("Z_p");
   grnorm2->GetYaxis()->SetTitle("X_ordered_p");
   grnorm2->Fit("pol1");
   grnorm2->GetHistogram()->SetMaximum(1.2*xval_ordered[npoints-1]);
   //c3->SetLogy();
   //c3->SetLogx();
   c3->cd();
   grnorm2->Draw("AP");


   c1->cd();
   //gr = new TGraphErrors(m,x,y,ex,ey);
   //gr = new TGraph(m,x,y);
   TH1F *h1 = new TH1F("h1","Gaussian Fit",nbins,xlow,xhigh);
   for(i=0;i<npoints;i++){h1->Fill(xval[i]);}
   TF1 *pfit1 = new TF1("fitfunction",myfitfunction,xlow,xhigh,3);
   pfit1->SetParameters(npoints,mu,sigma);
   pfit1->SetParNames("Amplitude","Mu","Sigma");
   
//   gr->SetMarkerStyle(21);
//   gr->SetTitle("Gaussian Fit");
//   gr->GetXaxis()->SetTitle("X");
//   gr->GetYaxis()->SetTitle("N");
////   TAxis *axis = gr->GetXaxis();
////   axis->SetLimits(-5.,5.);
//   h1->GetHistogram()->SetMaximum(ymax);
//   h1->GetHistogram()->SetMinimum(0.0);


   pfit1->SetLineColor(2);
   h1->Fit("fitfunction","V");
   Double_t pfit1chi2 = pfit1->GetChisquare();
   Double_t pfit1ndf = pfit1->GetNDF();
   Double_t pfit1chi2ndf = pfit1chi2/pfit1ndf;
//   printf("Fit 1: %f %f \n",pfit1chi2,pfit1ndf);
//   h1->Draw("AP");

   // TCanvas::Update() draws the frame, after which one can change it
   c1->Update();
   c1->GetFrame()->SetFillColor(21);
   c1->GetFrame()->SetBorderSize(12);
   c1->Modified();
   c2->Update();
   c2->GetFrame()->SetFillColor(21);
   c2->GetFrame()->SetBorderSize(12);
   c2->Modified();
   c3->Update();
   c3->GetFrame()->SetFillColor(21);
   c3->GetFrame()->SetBorderSize(12);
   c3->Modified();
}
