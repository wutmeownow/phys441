#include <ostream>

void graph_rplot() {
   //
   //Modified: Edward J. Brash
   //		
  
   //gStyle->SetOptFit(kFALSE);	
   gStyle->SetOptFit(1);	
   TCanvas *c1 = new TCanvas("c1","Cubic Data",200,10,700,500);
   FILE *f = fopen("rplot_euler.txt","r");
   FILE *g = fopen("rplot_euler_cromer.txt","r");
   FILE *h = fopen("rplot_runge_kutta.txt","r");

   c1->SetFillColor(42);
   c1->SetGrid();

   const Int_t n = 10000;
   Double_t xe[n], ye[n];
   Double_t xc[n], yc[n];
   Double_t xr[n], yr[n];
   Int_t i=0;

   while (!feof(f)){
	  fscanf(f,"%lf %lf\n",&xe[i],&ye[i]);
	  fscanf(g,"%lf %lf\n",&xc[i],&yc[i]);
	  fscanf(h,"%lf %lf\n",&xr[i],&yr[i]);
	  i++;
   }

   const Int_t n=i;

   gre = new TGraph(n,xe,ye);
   grc = new TGraph(n,xc,yc);
   grr = new TGraph(n,xr,yr);

//   gr->SetLineColor(2);
//   gr->SetLineWidth(4);
   gre->SetMarkerColor(kBlue);
   grc->SetMarkerColor(kRed);
   grr->SetMarkerColor(kGreen);
   //
   gre->SetMarkerStyle(22);
   grc->SetMarkerStyle(22);
   grr->SetMarkerStyle(22);
   gre->SetTitle("Keplerian Motion");
   gre->GetXaxis()->SetTitle("Time");
   gre->GetYaxis()->SetTitle("Radius");
   grc->SetTitle("Keplerian Motion");
   grc->GetXaxis()->SetTitle("Time");
   grc->GetYaxis()->SetTitle("Radius");
   grr->SetTitle("Keplerian Motion");
   grr->GetXaxis()->SetTitle("Time");
   grr->GetYaxis()->SetTitle("Radius");
//   TAxis *axis = gr->GetXaxis();
//   axis->SetLimits(-5.,5.);
   gre->GetHistogram()->SetMaximum(1.02);
   gre->GetHistogram()->SetMinimum(0.98);
   grc->GetHistogram()->SetMaximum(1.02);
   grc->GetHistogram()->SetMinimum(0.98);
   grr->GetHistogram()->SetMaximum(1.02);
   grr->GetHistogram()->SetMinimum(0.98);

   grr->Draw("AP");
   grc->Draw("P");
   gre->Draw("P");

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
