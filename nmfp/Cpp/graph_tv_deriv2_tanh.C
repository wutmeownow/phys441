#include <iostream>

Double_t fitfunction(Double_t *x, Double_t *par)
{
	Double_t xx = x[0];
	Double_t f = par[0]/2.0*(1.0+tanh((xx-par[2])/par[1]));
        return f;
}

void graph_tv_deriv2_tanh() {
   //
   //Modified: Edward J. Brash
   //		
  
   //gStyle->SetOptFit(kFALSE);	
   gStyle->SetOptFit(1);	
   TCanvas *c1 = new TCanvas("c1","Cubic Data",200,10,700,500);
   c1->SetFillColor(42);
   c1->SetGrid();
   
   FILE *f = fopen("tv_rate.dat","r");

   const Int_t n = 10000;
   Double_t x[n], y[n];
   Int_t i=0;

   while (!feof(f)){
	  fscanf(f,"%lf %lf\n",&x[i],&y[i]);
	  i++;
   }
   
   const Int_t n = i;
   gr = new TGraphErrors(n,x,y);
//   gr->SetLineColor(2);
//   gr->SetLineWidth(4);
//   gr->SetMarkerColor(4);
   gr->SetMarkerStyle(21);
   gr->SetTitle("TV Ownership Rate");
   gr->GetXaxis()->SetTitle("Year");
   gr->GetYaxis()->SetTitle("Rate");
//

   TF1 *pfit1 = new TF1("fitfunction",fitfunction,1949,2013,3);
   pfit1->SetParameters(98.0,0.2,1954.0);
   pfit1->SetParNames("Amplitude","Decay Rate","Start Year");
   //gr->Fit("fitfunction","V");
   gr->Fit("fitfunction");

   Double_t yp2[n+100],xp2[n+100];
   Double_t parameter_matrix[3];
   parameter_matrix[0]=pfit1->GetParameter(0);
   parameter_matrix[1]=pfit1->GetParameter(1);
   parameter_matrix[2]=pfit1->GetParameter(2);
   Double_t xvalue[1];

   for(i=0;i<80;i++){
	   Double_t yp,yc,ym;
	   xvalue[0]=1940+i;
	   xp2[i]=xvalue[0];
	   yc=fitfunction(xvalue,parameter_matrix);
	   xvalue[0]=1940+i+1;
	   yp=fitfunction(xvalue,parameter_matrix);
	   xvalue[0]=1940+i-1;
	   ym=fitfunction(xvalue,parameter_matrix);
	   yp2[i]=-1.0*(yp-2*yc+ym);
   }


   gr2 = new TGraphErrors(80,xp2,yp2);
//   gr2->SetLineColor(2);
//   gr2->SetLineWidth(4);
//   gr2->SetMarkerColor(4);
   gr2->SetMarkerStyle(21);
   gr2->SetTitle("Negative Second Derivative of TV Ownership Rate");
   gr2->GetXaxis()->SetTitle("Year");
   gr2->GetYaxis()->SetTitle("Negative Second Derivative");
//
   TAxis *axis = gr2->GetXaxis();
   axis->SetLimits(1940,2020);
   //gr2->GetHistogram()->SetMaximum(4.25);
   //gr2->GetHistogram()->SetMinimum(-1.5);

   gr2->Draw("AP");

   // TCanvas::Update() draws the frame, after which one can change it
   c1->Update();
   c1->GetFrame()->SetFillColor(21);
   c1->GetFrame()->SetBorderSize(12);
   c1->Modified();
}
