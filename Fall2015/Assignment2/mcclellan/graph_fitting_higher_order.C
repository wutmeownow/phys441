#include <iostream>
#include "TMatrixD.h"
#include "TRandom.h"
#include <string>
#include <sstream>

Double_t generating_function(Double_t x)
{
	Double_t par[4];
//	par[0]=0.4321;
//	par[1]=1.6789;
//	par[2]=0.0000;
//	par[3]=0.0000;

	par[0]=3.80;
	par[1]=-4.05;
	par[2]=5.40;
	par[3]=1.0000;

	Double_t f = par[0]+par[1]*x+par[2]*x*x+par[3]*x*x*x;

	return f;
}

void graph_fitting_higher_order() {
   //
   //Modified: Edward J. Brash
   //		
  
   //gStyle->SetOptFit(kFALSE);	
   gStyle->SetOptFit(1);	
   TCanvas *c1 = new TCanvas("c1","Linear Fit with Uncertainties",200,10,700,500);
   int m_chosen;
   // Set the order of the fitting polynomial here.
   cout << "What order polynomial?";
   cin >> m_chosen;
   const Int_t m = m_chosen;

   c1->SetFillColor(42);
   c1->SetGrid();

   const Int_t n = 15;
   Double_t x[n], y[n],rnd, delta_y[n];
   Int_t i;
   
   for (i=0;i<n;i++){
	x[i]=i+1;
   }

   y[0]=1.6711;
   y[1]=2.00994;
   y[2]=2.26241;
   y[3]=2.18851;
   y[4]=2.33006;
   y[5]=2.42660;
   y[6]=2.48424;
   y[7]=2.63729;
   y[8]=2.77163;
   y[9]=2.89610;
   y[10]=2.89083;
   y[11]=3.08081;
   y[12]=3.05305;
   y[13]=3.24079;
   y[14]=3.36212;

   //const Double_t delta_y = 0.1;

   TRandom r;

   /*for (i=0;i<n;i++){
	   //x[i]=i+1;
	   x[i]=-4.0+8.0*i/n;
	   y[i]=generating_function(x[i]);
	   rnd = r.Gaus(0.0,1.5);
	   y[i]=y[i]+rnd;
   }*/

   for (i=0;i<n;i++){
	   rnd = r.Gaus(0.05,0.15);
	   delta_y[i]=rnd;
	   //delta_y[i] = 1.0;
	   //delta_y[i] = sqrt(y[i]);
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
			   v[k][0]=v[k][0]+y[i]*pow(x[i],k)/pow(delta_y[i],2);
	   }
	   cout << "v[" << k << "] =" << v[k][0] << endl;
	   for (j=0; j<=m; j++){
		   a[k][j]=0;
	   	   for (i=0; i<n; i++){
			   a[k][j]=a[k][j]+pow(x[i],k+j)/pow(delta_y[i],2);
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

   const Double_t numsteps = 1000;
   Double_t x_fit[n*numsteps];
   Double_t y_fit[n];
   Double_t y_fit_graph[n*numsteps];

   for (i=0; i<n; i++){
	y_fit[i] = 0;
	for (j=0; j<=m; j++){
		y_fit[i] += coeff[j][0]*pow(x[i],j);
	}
   }

   for (i=0; i<=numsteps; i++){
        x_fit[i] = (n/numsteps)*i;
	y_fit_graph[i] = 0;
	for (j=0; j<=m; j++){
		y_fit_graph[i] += coeff[j][0]*pow(x_fit[i],j);
	}
   }

   Double_t CHI_2 = 0;
   Double_t NDF = n - m - 1;

   for (i=0; i<n; i++) {
	CHI_2 += pow(y[i] - y_fit[i],2);
   }

   Double_t uncertain[m+1];

   for (i=0; i<=m; i++) {
	uncertain[i] = sqrt(a[i][i]*CHI_2/NDF);
   }

   cout << " chi squared = " << CHI_2 << endl;
   cout << " NDF = " << NDF << endl;
   for (i=0; i<=m; i++) {
	cout << " Uncertainty in coeff " << i << " = " << uncertain[i] << endl;
   }	
   
   gr = new TGraphErrors(n,x,y,0,delta_y);
   //TF1 *pfit1 = new TF1("pfit1",polM);
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


   /*pfit1->SetLineColor(2);
   gr->Fit("pfit1","q");
   Double_t pfit1chi2 = pfit1->GetChisquare();
   Double_t pfit1ndf = pfit1->GetNDF();
   Double_t pfit1chi2ndf = pfit1chi2/pfit1ndf;
   printf("Fit 1: %f %f \n",pfit1chi2,pfit1ndf);*/
   //gr->Draw("AP");

   gr2 = new TGraph(numsteps,x_fit,y_fit_graph);
   gr2->SetMarkerStyle(6);
   gr2->SetMarkerColor(4);
   gr2->SetLineColor(4);
   //gr2->Draw("AL");
   mg = new TMultiGraph();
   mg->Add(gr,"P");
   mg->Add(gr2,"P");
   mg->Draw("A");

   // draw the legend
   /*Char_t message[80];
   TLegend *legend=new TLegend(0.4,0.15,0.88,0.35);
   legend->SetTextFont(72);
   legend->SetTextSize(0.04);
   legend->AddEntry(gr,"Data","lpe");
   sprintf(message,"Fit: #chi^{2}/NDF = %.5f",pfit1chi2ndf);
   legend->AddEntry(pfit1,message);*/
//   legend->Draw();

   // TCanvas::Update() draws the frame, after which one can change it
   c1->Update();
   c1->GetFrame()->SetFillColor(21);
   c1->GetFrame()->SetBorderSize(12);
   c1->Modified();
}
