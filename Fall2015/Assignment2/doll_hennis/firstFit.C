#include <ostream>
#include "TMatrixD.h"
#include "TRandom.h"
//Edited by Austin Doll-Hennis to answer questions 3 and 4

void firstFit() {

   //gStyle->SetOptFit(kFALSE);	
   gStyle->SetOptFit(1);	
   TCanvas *c1 = new TCanvas("c1","First Fit",200,10,700,500);

   // Set the order of the fitting polynomial here.
   Int_t m = 3;

   c1->SetFillColor(42);
   c1->SetGrid();

   const Int_t n = 15;
   Double_t x[n] = {1.0,2.0,3.0,4.0,5.0,6.0,7.0,8.0,9.0,10.0,11.0,12.0,13.0,14.0,15.0};
   Double_t y[n] = {1.6711,2.00994,2.26241,2.18851,2.33006,2.42660,2.48424,2.63729,2.77163,2.89610,2.89083,3.08081,3.05305,3.24079,3.36212};
   Double_t dx[n];
   Double_t dy[n];
   Double_t rnd;
   Int_t i;

   TRandom r;

   for(i=0; i<n; i++){
	dx[i] = 0;
	rnd = r.Gaus(0.0,.1127);
	dy[i] = rnd;
   }


   const Int_t m_params = m+1;
   Int_t k = 0;
   Int_t j =0;

   TMatrixD a(m_params,m_params);
   TMatrixD aold(m_params,m_params);
   TMatrixD v(m_params,1);
   Double_t det;

   for (k=0;k<=m;k++){
	   v[k][0]=0;
	   for (i=0; i<n; i++){
			   v[k][0]=v[k][0]+y[i]*pow(x[i],k);
	   }
	   cout << "v[" << k << "] =" << v[k][0] << endl;
	   for (j=0; j<=m; j++){
		   a[k][j]=0;
	   	   for (i=0; i<n; i++){
			   a[k][j]=a[k][j]+pow(x[i],k+j);
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
   for (k=0;k<=m;k++){
   	cout << " c[" << k << "] = " << coeff[k][0] << endl;
   }	

   gr = new TGraphErrors(n,x,y,dx,dy);
   TF1 *pfit1 = new TF1("pfit1","pol3");
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
   legend->Draw();

   // TCanvas::Update() draws the frame, after which one can change it
   c1->Update();
   c1->GetFrame()->SetFillColor(21);
   c1->GetFrame()->SetBorderSize(12);
   c1->Modified();
}
