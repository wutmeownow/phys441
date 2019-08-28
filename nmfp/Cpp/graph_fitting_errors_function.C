#include <ostream>
#include "TMatrixD.h"
#include "TRandom.h"

Double_t generating_function(Double_t x)
{
        Double_t par[4];
        par[0]=50.0000;
        par[1]=5.0000;
        par[2]=0.5000;
        par[3]=0.0500;

        Double_t f = par[0]+par[1]*x+par[2]*x*x+par[3]*x*x*x;

        return f;
}

Double_t fitfunction(Double_t *x, Double_t *par)
{
        Double_t xx=x[0];
	//Double_t f = par[0]+par[1]*xx+par[2]*xx*xx+par[3]*xx*xx*xx;
	Double_t f = par[0]+par[1]*xx*xx*xx;
	//Double_t f = par[0]+par[1]*xx+par[2]*xx*xx*xx;
        return f;
}

void graph_fitting_errors_function() {
   //
   //Modified: Edward J. Brash
   //		
  
   //gStyle->SetOptFit(kFALSE);	
   gStyle->SetOptFit(1);	
   TCanvas *c1 = new TCanvas("c1","Cubic Data",200,10,700,500);

   // Set the order of the fitting polynomial here.
   
   Double_t chi2;
   polynomial_order = 3;

   TString s = "pol";
   s += polynomial_order;

   c1->SetFillColor(42);
   c1->SetGrid();

   const Int_t n = 15;
   Double_t x[n], y[n], ex[n],ey[n];
   Int_t i;

   TRandom r;
   TRandom re;

   for (i=0;i<n;i++){
           x[i]=i+1;
           y[i]=generating_function(x[i]);
           y[i]=y[i]+1.0*r.Gaus(0.0,sqrt(y[i]));
           //y[i]=y[i]+r.Gaus(0.0,1.0);
	   ex[i]=0.0;
	   ey[i]=1.0*sqrt(fabs(y[i]));
	   //ey[i]=re.Gaus(0.0,5.0);
	   //ey[i]=1.0*(i+1)/16.0;
	   //ey[i]=0.0;
   }
   
   const Int_t m = polynomial_order+1;
   Int_t k = 0;
   Int_t j =0;

   TMatrixD xkj(m,m);
   TMatrixD xkjold(m,m);
   TMatrixD v(m,1);
   Double_t det;

   for (k=0;k<m;k++){
	   v[k][0]=0;
	   for (i=0; i<n; i++){
			   v[k][0]=v[k][0]+y[i]*pow(x[i],k)/pow(ey[i],2);
	   }
	   //cout << "v[" << k << "] =" << v[k][0] << endl;
	   for (j=0; j<m; j++){
		   xkj[k][j]=0;
	   	   for (i=0; i<n; i++){
			   xkj[k][j]=xkj[k][j]+pow(x[i],k+j)/pow(ey[i],2);
	   	   }		
		   //cout << "xjk[" << k << "][" << j << "] = " << xkj[k][j] << endl;
	   }
   }

   xkjold = xkj;

   xkj.InvertFast(&det);
   TMatrixD U1(xkj,TMatrixD::kMult,xkjold);
   TMatrixDDiag diag1(U1); diag1=0.0;
   const Double_t U1_max_offdiag = (U1.Abs()).Max();
   //cout << " Maximum off-diagonal = " << U1_max_offdiag << endl;
   //cout << " Determinant          = " << det << endl;

   TMatrixD coeff(xkj,TMatrixD::kMult,v);

   Double_t error_sum=0;
   Double_t yfit=0;
   for (i=0; i<n; i++){
	   for (k=0;k<m;k++){
		   yfit=yfit+coeff[k][0]*pow(x[i],k);
	   }
           //cout << " i y fit = " << i << " " << y[i] << " " << yfit << endl; 
	   error_sum = error_sum + pow(((yfit-y[i])/ey[i]),2);
	   yfit = 0;
   }
   chi2=error_sum/(n-m);

   //cout << endl;
   //cout << " chi^2          = " << chi2*(n-m) << endl;
   //cout << " NDf            = " << (n-m) << endl;
   //cout << endl;

   TMatrixD error(m,m);
   
   for (k=0;k<m;k++){
	   cout << "p" << k;
	   for (j=0;j<m;j++){
   	                cout << "    " << xkj[k][j];
	   }
	   cout << endl;
           error[k][k]=pow(xkj[k][k],0.5);
   }
   
   cout << endl;
   for (k=0;k<m;k++){
   	cout << " c[" << k << "] = " << coeff[k][0] << " +/- " << error[k][k] << endl;
   }

   cout << endl;
 
   for (k=0;k<m;k++){
	for (j=0;j<m;j++){
		if (j > k) cout << " rho[" << k << "," << j << "] = " << xkj[k][j]/sqrt(xkj[k][k]*xkj[j][j]) << "  ";
   	}
	cout << endl;
   }

   	
   	

   gr = new TGraphErrors(n,x,y,ex,ey);
//   TF1 *pfit1 = new TF1("pfit1",s);
   TF1 *pfit1 = new TF1("pfit1",fitfunction,0.0,15.0,2);

//   gr->SetLineColor(2);
//   gr->SetLineWidth(4);
//   gr->SetMarkerColor(4);
   gr->SetMarkerStyle(21);
   gr->SetTitle("Linear Fit");
   gr->GetXaxis()->SetTitle("X");
   gr->GetYaxis()->SetTitle("Y");
//   TAxis *axis = gr->GetXaxis();
//   axis->SetLimits(-5.,5.);
//   gr->GetHistogram()->SetMaximum(10.0);
//   gr->GetHistogram()->SetMinimum(0.0);


   pfit1->SetLineColor(polynomial_order-1);
   //gr->Fit("pfit1","V");
   gr->Fit("pfit1","");
   Double_t pfit1chi2 = pfit1->GetChisquare();
   Double_t pfit1ndf = pfit1->GetNDF();
   Double_t pfit1chi2ndf = pfit1chi2/pfit1ndf;
   printf("Fit 1: %f %f \n",pfit1chi2,pfit1ndf);
   gr->Draw("AP");

   cout << "Fit Order = " << polynomial_order << " Chi2/dof = " << chi2 << endl;

   // draw the legend
   Char_t message[80];
   TLegend *legend=new TLegend(0.4,0.15,0.88,0.35);
   legend->SetTextFont(72);
   legend->SetTextSize(0.04);
   legend->AddEntry(gr,"Data","lpe");
   sprintf(message,"Cubic Fit: #chi^{2}/NDF = %.5f",pfit1chi2ndf);
   legend->AddEntry(pfit1,message);
//   legend->Draw();

   // TCanvas::Update() draws the frame, after which one can change it
   c1->Update();
   c1->GetFrame()->SetFillColor(21);
   c1->GetFrame()->SetBorderSize(12);
   c1->Modified();
}
