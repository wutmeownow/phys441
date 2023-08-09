#include <ostream>
#include "TMatrixD.h"
#include "TRandom.h"
#include <stdlib>


void graph_linear_fitting() {
   //
   //Modified: Edward J. Brash
   //Modified: Samuel J. Porter
   //		
  
   //gStyle->SetOptFit(kFALSE);	
   gStyle->SetOptFit(1);	
   TCanvas *c1 = new TCanvas("c1","Data",200,10,700,500);

   // Set the order of the fitting polynomial here.
   Int_t m;
   cout << "What order fit would you like?" << endl;
   cin >> m;

   c1->SetFillColor(42);
   c1->SetGrid();

   const Int_t n = 15;
   Double_t x[n], y[n], rnd;
   Int_t i;

   TRandom r;

   x[0]=1;
   x[1]=2;
   x[2]=3;
   x[3]=4;
   x[4]=5;
   x[5]=6;
   x[6]=7;
   x[7]=8;
   x[8]=9;
   x[9]=10;
   x[10]=11;
   x[11]=12;
   x[12]=13;
   x[13]=14;
   x[14]=15;

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



   const Int_t m_params = m+1;
   Int_t k = 0;
   Int_t j =0;

   TMatrixD a(m_params,m_params);
   TMatrixD aold(m_params,m_params);
   TMatrixD v(m_params,1);
   Double_t det;

   Double_t dely[n];
	for(i=0;i<n;i++){
		dely[i] = 0.000001;
		rnd = r.Gaus(0.0,0.05);
		//dely[i] = rnd;
	}

   for (k=0;k<=m;k++){
	   v[k][0]=0;
	   for (i=0; i<n; i++){
			   v[k][0]=v[k][0]+y[i]*pow(x[i],k)/pow(dely[i],2);
	   }
	   cout << "v[" << k << "] =" << v[k][0] << endl;
	   for (j=0; j<=m; j++){
		   a[k][j]=0;
	   	   for (i=0; i<n; i++){
			   a[k][j]=a[k][j]+pow(x[i],k+j)/pow(dely[i],2);
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


	Double_t yfit[n];

	for(i=0;i<n;i++){
		yfit[i] = 0;
		for(j=0;j<=m;j++){
			yfit[i] += coeff[j][0]*pow(x[i],j);
		}
	}

	Double_t chi2 = 0;
	Double_t NDF = n-(m_params);
	for(i=0;i<n;i++){
		chi2 += pow((y[i]-yfit[i]),2);
	}

	Double_t uncer[m_params];
	for(i=0;i<=m;i++){
		uncer[i] = sqrt(a[i][i]);
	}
	
	for(i=0;i<=m;i++){
		cout << "uncertainty in c[" << i << "] = " << uncer[i] << endl;
	}





   gr = new TGraph(n,x,y);
   gr2 = new TGraph(n,x,yfit);
   TF1 *pfit1 = new TF1("pfit1","pol1");
   gr2->SetLineColor(10);
   gr2->SetLineWidth(2);
   gr2->SetMarkerColor(4);
   gr->SetMarkerStyle(21);
   gr->SetTitle("Linear Fit");
   gr->GetXaxis()->SetTitle("X");
   gr->GetYaxis()->SetTitle("Y");
//   TAxis *axis = gr->GetXaxis();
//   axis->SetLimits(-5.,5.);
//   gr->GetHistogram()->SetMaximum(10.0);
//   gr->GetHistogram()->SetMinimum(0.0);


   pfit1->SetLineColor(2);
//   gr->Fit("pfit1","q");
   Double_t pfit1chi2 = chi2;
   Double_t pfit1ndf = NDF;
   Double_t pfit1chi2ndf = pfit1chi2/pfit1ndf;
   printf("Fit 1: %f %f \n",pfit1chi2,pfit1ndf);
   gr->Draw("AP");
   gr2->Draw("l");

   // draw the legend
   Char_t message[80];
   TLegend *legend=new TLegend(0.4,0.15,0.88,0.35);
   legend->SetTextFont(72);
   legend->SetTextSize(0.04);
   legend->AddEntry(gr,"Data","lpe");
   sprintf(message,"Fit: #chi^{2}/NDF = %.5f",pfit1chi2ndf);
   legend->AddEntry(pfit1,message);
   //legend->Draw();

   // TCanvas::Update() draws the frame, after which one can change it
   c1->Update();
   c1->GetFrame()->SetFillColor(21);
   c1->GetFrame()->SetBorderSize(12);
   c1->Modified();
}
