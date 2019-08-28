#include <ostream>
#include "TMatrixD.h"
#include "TRandom.h"

Double_t generating_function(Double_t x)
{
// Simple cubic function - specify parameters locally.

	Double_t par[4];

	par[0]=1.80;
	par[1]=-4.05;
	par[2]=0.40;
	par[3]=1.0000;

	Double_t f = par[0]+par[1]*x+par[2]*x*x+par[3]*x*x*x;

	return f;
}

void graph_fitting() {
   //
   //Modified: Edward J. Brash
   //		
  
   //gStyle->SetOptFit(kFALSE);	
   gStyle->SetOptFit(1);	
   TCanvas *c1 = new TCanvas("c1","Cubic Data",200,10,700,500);

   // Set the order of the fitting polynomial here.
   Int_t m = 3;

   c1->SetFillColor(42);
   c1->SetGrid();

   const Int_t n = 15; //number of data points
   Double_t walk[n] = {-1,1,-.5,.5,0,-1,1,-.5,.5,0,-1,1,-.5,.5,0};
   Double_t x[n], y[n], rnd;  //arrays to hold xy values, and fluctuations
   Int_t i;

   TRandom r;  //Use one of ROOT's built-in random number generator

   for (i=0;i<n;i++){
	   x[i]=-4.0+8.0*i/n;  // choose x betwen -4 and 4
	   y[i]=generating_function(x[i]); // call generating function
	   //rnd = r.Gaus(0.0,1.5);
           rnd = 0.5*walk[i];
	   y[i]=y[i]+rnd; // add some random "noise" to data
   }

//
// Use ROOT's linear algebra package to calculate fix parameters "by hand"
//

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

   for (j=0;j<m_params;j++){
       for (i=0;i<m_params;i++){
           cout << "ainv[" << j << "][" << i << "] = " << a[j][i] << endl;
        }
    }


   TMatrixD U1(a,TMatrixD::kMult,aold);
   TMatrixDDiag diag1(U1); diag1=0.0;
   const Double_t U1_max_offdiag = (U1.Abs()).Max();
   cout << " Maximum off-diagonal = " << U1_max_offdiag << endl;
   cout << " Determinant          = " << det << endl;

   TMatrixD coeff(a,TMatrixD::kMult,v);
   for (k=0;k<=m;k++){
   	cout << " c[" << k << "] = " << coeff[k][0] << endl;
   }	

//
// Fill TGraph object with generated data, and fit with ROOT's 
// built-in polynomial fitting function - p3 = 3rd order polynomial
//

   TGraph *gr = new TGraph(n,x,y);
   TF1 *pfit1 = new TF1("pfit1","pol3");
   gr->SetMarkerStyle(21);
   gr->SetTitle("Cubic Fit");
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
//   legend->Draw();

   // TCanvas::Update() draws the frame, after which one can change it
   c1->Update();
   c1->GetFrame()->SetFillColor(21);
   c1->GetFrame()->SetBorderSize(12);
   c1->Modified();
}
