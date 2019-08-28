#include <ostream>
#include "TMatrixD.h"
#include "TRandom.h"

Double_t generating_function(Double_t x)
{
	Double_t par[4];
//	par[0]=0.4321;
//	par[1]=1.6789;
//	par[2]=0.0000;
//	par[3]=0.0000;

	par[0]=1.80;
	par[1]=-4.05;
	par[2]=0.40;
	par[3]=1.0000;

	Double_t f = par[0]+par[1]*x+par[2]*x*x+par[3]*x*x*x;

	//Double_t f = 1.0/(1.0+x*x);

	return f;
}

void graph_fitting_coeff_errors_loop() {
   //
   //Modified: Edward J. Brash
   //		
  
   //gStyle->SetOptFit(kFALSE);	
   gStyle->SetOptFit(1);	
   TCanvas *c1 = new TCanvas("c1","Cubic Data",200,10,700,500);

   // Set the order of the fitting polynomial here.
   Int_t polynomial_order = 6;

   c1->SetFillColor(42);
   c1->SetGrid();

   const Int_t n = 9;
   Double_t x[n], y[n],rnd;
   Int_t i;

   TRandom r;

   for (i=0;i<n;i++){
	   //x[i]=i+1;
	   x[i]=-4.0+8.0*i/n;
	   //x[i]=-5.0+10.0*i/(n-1.0);
	   y[i]=generating_function(x[i]);
	   rnd = r.Gaus(0.0,0.5);
	   //rnd=0.0;
	   y[i]=y[i]+rnd;
   }

   const Int_t m = polynomial_order+1;
   Int_t k = 0;
   Int_t j =0;

   TMatrixD a(m,m);
   TMatrixD aold(m,m);
   TMatrixD v(m,1);
   TMatrixD error(m,m);
   Double_t det;

   for (int m_loop=6; m_loop<=m; m_loop++){

   for (k=0;k<m;k++){
	v[k][0]=0.0;
	for (j=0;j<m;j++){
		a[k][j]=0.0;
		aold[k][j]=0.0;
	}
   }

   for (k=0;k<m_loop;k++){
	   v[k][0]=0;
	   for (j=0; j<n; j++){
			   v[k][0]=v[k][0]+y[j]*pow(x[j],k);
	   }
	   cout << "v[" << k << "] =" << v[k][0] << endl;
	   for (i=0; i<m_loop; i++){
		   a[k][i]=0;
	   	   for (j=0; j<n; j++){
			   a[k][i]=a[k][i]+pow(x[j],k+i);
	   	   }		
		   cout << "a[" << k << "][" << i << "] = " << a[k][i] << endl;
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

   Double_t error_sum=0;
   Double_t yfit=0;
   for (j=0; j<n; j++){
     for (k=0;k<m_loop;k++){
               yfit=yfit+coeff[k][0]*pow(x[j],k);
     }
     cout << " i y fit = " << j << " " << y[j] << " " << yfit << endl;
     error_sum = error_sum + pow((yfit-y[j]),2);
     yfit = 0;
   }
   Double_t chi2=error_sum/(n-m_loop);

   cout << endl;
   cout << " chi^2          = " << chi2*(n-m_loop) << endl;
   cout << " NDf            = " << (n-m_loop) << endl;
   cout << endl;

   for (k=0;k<m_loop;k++){
          cout << "p" << k;
          for (i=0;i<m_loop;i++){
                 cout << "    " << a[k][i];
          }
          cout << endl;
          error[k][k]=pow(a[k][k]*chi2,0.5);
   }

   cout << endl;
   for (k=0;k<m_loop;k++){
         cout << " c[" << k << "] = " << coeff[k][0] << " +/- " << error[k][k] << endl;
   }
  
   }
  
   gr = new TGraph(n,x,y);
   TF1 *pfit1 = new TF1("pfit1","pol6");
//   gr->SetLineColor(2);
//   gr->SetLineWidth(4);
//   gr->SetMarkerColor(4);
   gr->SetMarkerStyle(21);
   gr->SetTitle("Fitting - No Uncertainties");
   gr->GetXaxis()->SetTitle("X");
   gr->GetYaxis()->SetTitle("Y");
//   TAxis *axis = gr->GetXaxis();
//   axis->SetLimits(-5.,5.);
//   gr->GetHistogram()->SetMaximum(10.0);
//   gr->GetHistogram()->SetMinimum(0.0);


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
