#include <TMath.h>

void rounding_error(Int_t ichoice=1) {
   //
   //Author: Edward J. Brash, look at rounding errors
   //			 	by comparing derivative to calculation
  
   TCanvas *c1 = new TCanvas("c1","Absolute Error",1200,520,700,500);

   c1->SetFillColor(41);
   c1->SetGrid();
   c1->SetLogx();
   c1->SetLogy();

   const Int_t n = 21;
   Double_t h, hpower;
   Double_t dfunc[n], dfunch[n], dfunchh[n],xfunc[n], xfunchp[n], xfunchm[n];
   Double_t xfunchpp[n],xfunchmm[n];
   Double_t x[n],diff[n],difftwo[n];
   Double_t xval = 1.0;
   
   if (ichoice == 1) {
	cout << "Using forward derivative ... " << endl;
   }else if (ichoice==2) {
	cout << "Using centered derivative ... " << endl;
   }else {
	cout << "Using both methods ... " << endl;
   }

   for (Int_t i=0;i<n;i++) {

     hpower=i-n+1;
     x[i] = pow(10.0,hpower);
     dfunc[i]=3.0e+00*xval*xval;
     xfunc[i]=xval*xval*xval;
     xfunchp[i]=(xval+x[i])*(xval+x[i])*(xval+x[i]);
     xfunchm[i]=(xval-x[i])*(xval-x[i])*(xval-x[i]);
     xfunchpp[i]=(xval+x[i]+x[i])*(xval+x[i]+x[i])*(xval+x[i]+x[i]);
     xfunchmm[i]=(xval-x[i]-x[i])*(xval-x[i]-x[i])*(xval-x[i]-x[i]);

     if (ichoice == 1) {
	dfunch[i]=(xfunchp[i]-xfunc[i])/(x[i]);
     }else if (ichoice ==2 ) {
	dfunch[i]=(xfunchp[i]-xfunchm[i])/(2.0e+00*x[i]);
     } else {
	dfunchh[i]=(xfunchp[i]-xfunc[i])/(x[i]);
	dfunch[i]=(xfunchp[i]-xfunchm[i])/(2.0e+00*x[i]);
     }	
     
     diff[i]=fabs(dfunc[i]-dfunch[i]);
     difftwo[i]=fabs(dfunc[i]-dfunchh[i]);

     printf(" i %i %f %f %f %f %f %f %f\n",i,x[i],xfunc[i],xfunchp[i],xfunchm[i],dfunc[i],dfunch[i],diff[i]);

   }



   TGraph *gr = new TGraph(n,x,diff);
   TGraph *grtwo = new TGraph(n,x,difftwo);
   gr->SetMarkerStyle(21);
   if (ichoice > 2) { 
	grtwo->SetMarkerStyle(20);
	grtwo->SetMarkerColor(2);
	grtwo->SetLineColor(2);
   }
   gr->SetTitle("Round Error Calculation");
   gr->GetXaxis()->SetTitle("h");
   gr->GetYaxis()->SetTitle("Absolute Error");
   gr->Draw("ALP");
   if (ichoice > 2) grtwo->Draw("LP");

   // TCanvas::Update() draws the frame, after which one can change it
   c1->Update();
   c1->GetFrame()->SetFillColor(21);
   c1->GetFrame()->SetBorderSize(12);
   c1->Modified();
}
