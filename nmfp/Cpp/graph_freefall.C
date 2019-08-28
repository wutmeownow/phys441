#include <ostream>

void graph_freefall() {
   //
   //Modified: Edward J. Brash
   //		
  
   //gStyle->SetOptFit(kFALSE);	
   gStyle->SetOptFit(1);	
   TCanvas *c1 = new TCanvas("c1","Freefall",200,10,700,500);
   c1->Divide(2,1);
   FILE *f = fopen("plot.txt","r");
   FILE *g = fopen("NoAir.txt","r");
   FILE *h = fopen("vplot.txt","r");
   FILE *j = fopen("vNoAir.txt","r");

   c1->SetFillColor(42);
   c1->SetGrid();

   const Int_t n = 10000;
   Double_t x[n], y[n], xnoair[n], ynoair[n], xv[n], xvnoair[n], v[n], vnoair[n];
   Int_t i=0;

   while (!feof(f)){
	  fscanf(f,"%lf %lf\n",&x[i],&y[i]);
	  fscanf(g,"%lf %lf\n",&xnoair[i],&ynoair[i]);
	  fscanf(h,"%lf %lf\n",&xv[i],&v[i]);
	  fscanf(j,"%lf %lf\n",&xvnoair[i],&vnoair[i]);
	  i++;
   }

   const Int_t n=i;

   gr = new TGraph(n,x,y);
   grr = new TGraph(n,xnoair,ynoair);
   grv = new TGraph(n,xv,v);
   grrv = new TGraph(n,xvnoair,vnoair);

//   gr->SetLineColor(2);
//   gr->SetLineWidth(4);
   gr->SetMarkerColor(kBlue);
   grr->SetMarkerColor(kRed);
   grv->SetMarkerColor(kBlue);
   grrv->SetMarkerColor(kRed);
   gr->SetMarkerStyle(21);
   grr->SetMarkerStyle(22);
   grv->SetMarkerStyle(21);
   grrv->SetMarkerStyle(22);
   gr->SetTitle("Freefall");
   gr->GetXaxis()->SetTitle("X");
   gr->GetYaxis()->SetTitle("Y");
   grv->SetTitle("Freefall");
   grv->GetXaxis()->SetTitle("X");
   grv->GetYaxis()->SetTitle("Y");
//   TAxis *axis = gr->GetXaxis();
//   axis->SetLimits(-5.,5.);
   gr->GetHistogram()->SetMaximum(40000.0);
   gr->GetHistogram()->SetMinimum(0.0);
   grv->GetHistogram()->SetMaximum(600.0);
   grv->GetHistogram()->SetMinimum(0.0);

   c1->cd(1);
   gr->Draw("AP");
   grr->Draw("P");
   c1->cd(2);
   grv->Draw("AP");
   grrv->Draw("P");

   // draw the legend
//   Char_t message[80];
//   TLegend *legend=new TLegend(0.4,0.15,0.88,0.35);
//   legend->SetTextFont(72);
//   legend->SetTextSize(0.04);
//   legend->AddEntry(gr,"Data","lpe");
//   sprintf(message,"Cubic Fit: #chi^{2}/NDF = %.5f",pfit1chi2ndf);
//   legend->AddEntry(pfit1,message);
//   legend->Draw();

   // TCanvas::Update() draws the frame, after which one can change it
   c1->Update();
   c1->GetFrame()->SetFillColor(21);
   c1->GetFrame()->SetBorderSize(12);
   c1->Modified();
}
