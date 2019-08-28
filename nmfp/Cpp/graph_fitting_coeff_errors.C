#include <ostream>
#include "TMatrixD.h"
#include "TRandom3.h"
#include "TMath.h"

Double_t generating_function(Double_t x)
{
	Double_t par[4];
//	par[0]=0.0;
//	par[1]=0.0;
//	par[2]=0.0;
//	par[3]=1.0000;

	par[0]=1.80;
	par[1]=-4.05;
	par[2]=0.40;
	par[3]=1.0000;

	Double_t f = par[0]+par[1]*x+par[2]*x*x+par[3]*x*x*x;

	//Double_t f = 1.0/(1.0+x*x);

	return f;
}

void graph_fitting_coeff_errors() {
   //
   //Modified: Edward J. Brash
   //		
  
   //gStyle->SetOptFit(kFALSE);	
   gStyle->SetOptFit(1);	
   TCanvas *c1 = new TCanvas("c1","Cubic Fits",700,260,1000,800);


   // Set the order of the fitting polynomial here.
   //Int_t polynomial_order = 4;

   c1->SetFillColor(42);
   c1->SetGrid();
   c1->Divide(2,2);
   
   const Int_t n = 9;
   const Int_t order_max = 3;
   Double_t x[n], y[n],rnd;
   Int_t i;
   Double_t order[order_max],chi2[order_max];
   Double_t forder[order_max],ftest[order_max], chi2_old, order_old;
   Double_t fdist_integral[order_max];

   TRandom r;

   for (i=0;i<n;i++){
	   //x[i]=i+1;
	   x[i]=-4.0+8.0*i/(n-1.0);;
	   //x[i]=-5.0+10.0*i/(n-1.0);
	   y[i]=generating_function(x[i]);
	   rnd = r.Gaus(0.0,1.000);
	   //rnd=0.0;
	   y[i]=y[i]+rnd;
	   cout << x[i] << "  " << y[i] << endl;
   }

   for (Int_t polynomial_order=0; polynomial_order<=order_max;polynomial_order++){

   	const Int_t m = polynomial_order+1;
   	order[polynomial_order]=polynomial_order;
   	forder[polynomial_order]=polynomial_order+1;

   	Int_t k = 0;
   	Int_t j =0;

   	TMatrixD a(m,m);
   	TMatrixD aold(m,m);
   	TMatrixD v(m,1);
   	Double_t det;

   	for (k=0;k<m;k++){
	   v[k][0]=0;
	   for (j=0; j<n; j++){
			   v[k][0]=v[k][0]+y[j]*pow(x[j],k);
	   }
	   //cout << "v[" << k << "] =" << v[k][0] << endl;
	   for (i=0; i<m; i++){
		   a[k][i]=0;
	   	   for (j=0; j<n; j++){
			   a[k][i]=a[k][i]+pow(x[j],k+i);
	   	   }		
		   //cout << "a[" << k << "][" << i << "] = " << a[k][i] << endl;
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
     		for (k=0;k<m;k++){
               		yfit=yfit+coeff[k][0]*pow(x[j],k);
     		}
     		cout << " i y fit = " << j << " " << y[j] << " " << yfit << endl;
     		error_sum = error_sum + pow((yfit-y[j]),2);
     		yfit = 0;
   	}
   
   	chi2[polynomial_order]=error_sum/(n-m);
   
   	if (polynomial_order>0) {
		ftest[polynomial_order-1]=chi2_old/chi2[polynomial_order];
 		fdist_integral[polynomial_order-1] = TMath::FDistI(ftest[polynomial_order-1],n-m,order_old);
		cout << "F Test Probability " << ftest[polynomial_order-1] << " Integral = " << fdist_integral[polynomial_order-1] << endl;
		if (fdist_integral[polynomial_order-1] > 0.95) {
			chi2_old = chi2[polynomial_order];
			order_old = n-m;
		} 
   	} else {
		chi2_old = chi2[polynomial_order];
		order_old = n-m;
   	}

   	cout << endl;
   	cout << " chi^2          = " << chi2[polynomial_order]*(n-m) << endl;
   	cout << " NDf            = " << (n-m) << endl;
   	cout << endl;

   	TMatrixD error(m,m);

   	for (k=0;k<m;k++){
          	cout << "p" << k;
          	for (i=0;i<m;i++){
                 	cout << "    " << a[k][i];
          	}
          	cout << endl;
          	error[k][k]=pow(a[k][k]*chi2[polynomial_order],0.5);
   	}

   	cout << endl;
   	for (k=0;k<m;k++){
         	cout << " c[" << k << "] = " << coeff[k][0] << " +/- " << error[k][k] << endl;
   	}

   } //loop over polynomial order

   cout << "Best Fit Order = " << n-order_old-1 << endl;
   for (i=0;i<n;i++){
   	cout << x[i] << " " << y[i] << endl;
   }

   TGraph *gr = new TGraph(n,x,y);
   TGraph *gr2= new TGraph(order_max+1,order,chi2);
   TGraph *gr3= new TGraph(order_max,forder,ftest);
   TGraph *gr4= new TGraph(order_max,forder,fdist_integral);

   TF1 *pfit1 = new TF1("pfit1","pol3");
//   gr->SetLineColor(2);
//   gr->SetLineWidth(4);
//   gr->SetMarkerColor(4);
   gr->SetMarkerStyle(21);
   gr->SetTitle("Fitting - No Uncertainties");
   gr->GetXaxis()->SetTitle("X");
   gr->GetYaxis()->SetTitle("Y");
   gr2->SetMarkerStyle(21);
   gr2->SetTitle("Chi^2 - No Uncertainties");
   gr2->GetXaxis()->SetTitle("Order");
   gr2->GetYaxis()->SetTitle("Chi2");
   gr3->SetMarkerStyle(21);
   gr3->SetTitle("F Test - No Uncertainties");
   gr3->GetXaxis()->SetTitle("Order");
   gr3->GetYaxis()->SetTitle("F");
   gr4->SetMarkerStyle(21);
   gr4->SetTitle("F Test - No Uncertainties");
   gr4->GetXaxis()->SetTitle("Order");
   gr4->GetYaxis()->SetTitle("Confidence");

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
   c1->cd(1);
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

   c1->cd(2);
   c1->SetLogy();
   gr2->Draw("APL");
   c1->cd(3);
   gr3->Draw("APL");
   c1->cd(4);
   gr4->Draw("APL");

   // TCanvas::Update() draws the frame, after which one can change it
   c1->Update();
   c1->GetFrame()->SetFillColor(21);
   c1->GetFrame()->SetBorderSize(12);
   c1->Modified();
}
