#include <ostream>
#include <sstream>
#include <string>
#include <algorithm>
#include "TMatrixD.h"
#include "TRandom.h"

//X Values for the Function
Double_t* xfunction(){
	Double_t val[15] ={1.0,2.0,3.0,4.0,5.0,6.0,7.0,8.0,
		  9.0,10.0,11.0,12.0,13.0,14.0,15.0};
	Double_t *par = new Double_t[15];
	std::copy(val, val+15, &par[0]);
	return par;
}

//Y Values for the Function
Double_t* yfunction(){
	Double_t val[15] = {1.6711,2.00944,2.26241,2.18851,2.33006,
		  2.42660,2.48424,2.63729,2.77163,2.89610,
		  2.89083,3.08081,3.05305,3.24079,3.36212};
	Double_t *par = new Double_t[15];
	std::copy(val, val+15, &par[0]);
	return par;
}

//Error on the Data Points
Double_t* sigmaFunction(Double_t* y){
	Double_t *par = new Double_t[15];
	for(int i=0;i<15;i=i+2){
		par[i] = 0.378;
	}
	for(int i=1;i<15;i=i+2){
		par[i] = 0.1;
	}
	return par;
}

void part4(int order) {
   // Order of polynomial change to change plotting
   Int_t m = order;

   const Int_t n = 15;
   Double_t *x = xfunction();
   Double_t *y = yfunction();
	Double_t *sigma = sigmaFunction(y);
   const Int_t m_params = m+1;

   TMatrixD a(m_params,m_params);
   TMatrixD aold(m_params,m_params);
   TMatrixD v(m_params,1);
   Double_t det;
	Double_t edet;

   for (Int_t k=0;k<=m;k++){
	   v[k][0]=0;
	   for (Int_t i=0; i<n; i++){
			   v[k][0]+=(y[i]*pow(x[i],k))/pow(sigma[i],2.0);
	   }
	   cout << "v[" << k << "] =" << v[k][0] << endl;
	   for (Int_t j=0; j<=m; j++){
		   a[k][j]=0;
	   	   for (Int_t i=0; i<n; i++){
					a[k][j]+=pow(x[i],k+j)/pow(sigma[i],2.0);
	   	   }		
		   cout << "a[" << k << "][" << j << "] = " << a[k][j] << endl;
	   }
   }

   aold = a;
   a.InvertFast(&det);
   TMatrixD U1(a,TMatrixD::kMult,aold);
   TMatrixDDiag diag1(U1); diag1=0.0;
   const Double_t U1_max_offdiag = (U1.Abs()).Max();
   cout << " Maximum off-diagonal = " << U1_max_offdiag << endl;
   cout << " Determinant          = " << det << endl;

   TMatrixD coeff(a,TMatrixD::kMult,v);
	Double_t chisquare=0.0;
	for(Int_t i=0; i<n; i++){
		Double_t yfit = 0.0;
		for(Int_t j=0; j<=m; j++){
			yfit+=coeff[j][0]*pow(x[i],j);
		}
		chisquare+=pow((y[i]-yfit)/sigma[i],2.0);
	}
	Double_t ndf = n-m-1.0;
	TMatrixD error(m_params,1);
	for(Int_t l=0;l<=m;l++){
		error[l][0] = pow(a[l][l],0.5);
	}
	cout<<endl<<"Fit Parameters: "<<endl;
   for (Int_t k=0;k<=m;k++){
   	cout << " c[" << k << "] = " << coeff[k][0] << " +- " << error[k][0] << endl;
   }

	cout<<"ChiSquare NDF: " << chisquare << " " << ndf << endl << endl;

	//From here down deals with plotting
   //gStyle->SetOptFit(kFALSE);
   gStyle->SetOptFit(1);	
   TCanvas *c1 = new TCanvas("c1","Question 4",200,10,700,500);
   c1->SetFillColor(42);
   c1->SetGrid();

   gr = new TGraphErrors(n,x,y,0,sigma);
	std::ostringstream oss;	
	oss << m;
	std::string pol = "pol"+oss.str();
   TF1 *pfit1 = new TF1("pfit1",pol.c_str());
   gr->SetMarkerStyle(21);
   gr->SetTitle("Linear Fit");
   gr->GetXaxis()->SetTitle("X");
   gr->GetYaxis()->SetTitle("Y");

   pfit1->SetLineColor(2);
   gr->Fit("pfit1","q");
   Double_t pfit1chi2 = pfit1->GetChisquare();
   Double_t pfit1ndf = pfit1->GetNDF();
   Double_t pfit1chi2ndf = pfit1chi2/pfit1ndf;
   printf("Fit 1: %f %f \n",pfit1chi2,pfit1ndf);
   gr->Draw("AP");

   // draw the legend
   Char_t message[80];
   TLegend *legend=new TLegend(0.4,0.15,0.88,0.35);
   legend->SetTextFont(72);
   legend->SetTextSize(0.04);
   legend->AddEntry(gr,"Data","lpe");
   sprintf(message,"Fit: #chi^{2}/NDF = %.5f",pfit1chi2ndf);
   legend->AddEntry(pfit1,message);

   // TCanvas::Update() draws the frame, after which one can change it
   c1->Update();
   c1->GetFrame()->SetFillColor(21);
   c1->GetFrame()->SetBorderSize(12);
   c1->Modified();
}
