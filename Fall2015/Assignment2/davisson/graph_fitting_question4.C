#include <ostream>
#include "TMatrixD.h"
#include "TRandom.h"
#include "time.h"

//Double_t x_coordinates

using namespace::std;

Double_t generating_function(Double_t x)
{
	Double_t par[4];
//	par[0]=0.4321;
//	par[1]=1.6789;
//	par[2]=0.0000;
//	par[3]=0.0000;

//	par[0]=1.80;
//	par[1]=-4.05;
//	par[2]=0.40;
//	par[3]=1.0000;

	Double_t f = par[0]+par[1]*x+par[2]*x*x+par[3]*x*x*x;

	return f;
}

void graph_fitting_question4() {
   //
   //Modified: Edward J. Brash
   //		
  
   //gStyle->SetOptFit(kFALSE);
   const Int_t n = 15;

   Double_t x[n]={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
   Double_t y[n]={1.6711,2.00994,2.26241,2.18851,2.33006,2.42660,2.48424,2.63729,2.77163,2.89610,2.89083,3.08081,3.05305,3.24079,3.36212};

   int uncertainties;
   TRandom r;
   cout<<"Equal uncertainties(1) or unequal uncertainties(2)? "<<endl;
   cin>>uncertainties;
   Double_t xError[n];
   Double_t yError[n]={0.05,0.08,0.2,0.11,0.13,0.5,0.01,0.16,0.1,0.3,0.15,0.07,0.04,0.03,0.2};

   if(uncertainties==1)
     {      
       for(int i=0;i<n;i++)
	 {
	   xError[i]=0;
	   yError[i]=0.1;
	 }
     }
   srand(time(NULL));
   if(uncertainties==2)
     {
       /*double randomNumber;
       double large=.2;
       double small=.01;
       double range = large-small;
       //double rand=0.0;*/
       for(int i=0;i<n;i++)
	 {
	   xError[i]=0;
	   //yError[i]=rand;
	 }
       
     }
   /*  for(int i=0;i<15;i++)
    {
      cout<<y[i]<<endl;
      }*/

   gStyle->SetOptFit(1);	
   TCanvas *c1 = new TCanvas("c1","Cubic Data",200,10,700,500);

   // Set the order of the fitting polynomial here.
   Int_t m = 1;

   c1->SetFillColor(42);
   c1->SetGrid();

   // Double_t x[n], y[n],rnd;
   Int_t i;

   TRandom r;

   /* for (i=0;i<n;i++){
	   //x[i]=i+1;
	   x[i]=-4.0+8.0*i/n;
	   y[i]=generating_function(x[i]);
	   rnd = r.Gaus(0.0,1.5);
	   y[i]=y[i]+rnd;
   }
*/
   const Int_t m_params = m+1;
   Int_t k = 0;
   Int_t j =0;

   TMatrixD a(m_params,m_params);
   //TMatrixD aError(m_params,m_params);
   TMatrixD aold(m_params,m_params);
   TMatrixD v(m_params,1);
   Double_t det;

   for (k=0;k<=m;k++){
	   v[k][0]=0;
	   for (i=0; i<n; i++){
	     v[k][0]=v[k][0]+y[i]*pow(x[i],k)/pow(yError[i],2);
	   }
	   cout << "v[" << k << "] =" << v[k][0] << endl;
	   for (j=0; j<=m; j++){
		   a[k][j]=0;
		   //aError[k][j]=0;
	   	   for (i=0; i<n; i++){
		     //aError[k][j]+=pow(x[i],k+j)/pow(yError[i],2);
		     a[k][j]+=pow(x[i],k+j)/pow(yError[i],2);
	   	   }		
		   cout << "a[" << k << "][" << j << "] = " << a[k][j] << endl;
	   }

   }

   aold = a;

   a.InvertFast(&det);
   //aError.InvertFast();
   TMatrixD U1(a,TMatrixD::kMult,aold);
   TMatrixDDiag diag1(U1); diag1=0.0;
   const Double_t U1_max_offdiag = (U1.Abs()).Max();
   cout << " Maximum off-diagonal = " << U1_max_offdiag << endl;
   cout << " Determinant          = " << det << endl;

   TMatrixD coeff(a,TMatrixD::kMult,v);
   for (k=0;k<=m;k++){
     cout << " c[" << k << "] = " << coeff[k][0] << endl;
   }	
 
   double fitUncertainty=0.0;
   double chiSquared=0.0;
   for(int i=0;i<n;i++)
     {
       for(int j=0;j<=m;j++)
	 {
	   fitUncertainty+=coeff[j][0]*pow(x[i],j);
	 }
       chiSquared+=pow((y[i]-fitUncertainty)/(yError[i]),2);
       fitUncertainty=0;
     }

    cout<<"Chi squared per degree of freedom: "<<chiSquared<<"/"<<(n-m-1)<<endl;
   Double_t chiSquaredReduced=chiSquared/(n-m-1);
   Double_t error[m_params];
   Double_t errorWithBars[m_params];
   for(int t=0;t<m_params;t++)
     {
       //error[t]=sqrt(a[t][t]*chiSquaredReduced);
       errorWithBars[t]=sqrt(a[t][t]);
     }

   for(int p=0;p<m_params;p++)
     {
       cout<<"Error in p["<<p<<"] is: "<<errorWithBars[p]<<endl;
     }
   //  gr2=new TGraphErrors(n,x,y,0,0.1);
   gr = new TGraphErrors(n,x,y,xError,yError);
   // ostringstream stream;
   //stream<<m;
   //string poly = "pol"+stream.str();
   
   TF1 *pfit1 = new TF1("pfit1","pol1");
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
