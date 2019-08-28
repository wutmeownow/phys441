#include <ostream>

void graph_fft() {
   //
   //Modified: Edward J. Brash
   //		
  
   //gStyle->SetOptFit(kFALSE);	
   gStyle->SetOptFit(1);	
   TCanvas *c1 = new TCanvas("c1","Fourier Transform Data",200,10,700,500);
   c1->Divide(3,1);
   FILE *f = fopen("y.txt","r");
   FILE *g = fopen("ytReal.txt","r");
   FILE *h = fopen("ytImag.txt","r");
   FILE *d = fopen("powSpec.txt","r");

   c1->SetFillColor(42);
   c1->SetGrid();

   const Int_t n = 10000;
   Double_t t[n], y[n];
   Double_t fa[n], ytr[n];
   Double_t fb[n], yti[n];
   Double_t fc[n], p[n];
   Int_t i=0;

   while (!feof(f)){
	  fscanf(f,"%lf %lf\n",&t[i],&y[i]);
	  fscanf(g,"%lf %lf\n",&fa[i],&ytr[i]);
	  fscanf(h,"%lf %lf\n",&fb[i],&yti[i]);
	  fscanf(d,"%lf %lf\n",&fc[i],&p[i]);
	  i++;
   }

   const Int_t n=i;

   gra = new TGraph(n,t,y);
   grb = new TGraph(n,fa,ytr);
   grc = new TGraph(n,fb,yti);
   grd = new TGraph(n,fc,p);

//   gr->SetLineColor(2);
//   gr->SetLineWidth(4);
   gra->SetMarkerColor(kBlue);
   grb->SetMarkerColor(kRed);
   grc->SetMarkerColor(kGreen);
   grc->SetMarkerColor(kRed);
   gra->SetLineColor(kBlue);
   grb->SetLineColor(kRed);
   grc->SetLineColor(kBlue);
   grd->SetLineColor(kRed);
   //
   gra->SetMarkerStyle(22);
   grb->SetMarkerStyle(22);
   grc->SetMarkerStyle(22);
   gra->SetTitle("Fourier Motion");
   gra->GetXaxis()->SetTitle("Time");
   gra->GetYaxis()->SetTitle("Amplitude");
   grb->SetTitle("Fourier Motion");
   grb->GetXaxis()->SetTitle("Frequency");
   grb->GetYaxis()->SetTitle("Amplitude");
   grc->SetTitle("Fourier Motion");
   grc->GetXaxis()->SetTitle("Frequency");
   grc->GetYaxis()->SetTitle("Amplitude");
   grc->SetTitle("Fourier Motion");
   grc->GetXaxis()->SetTitle("Frequency");
   grc->GetYaxis()->SetTitle("Amplitude");
//   TAxis *axis = gr->GetXaxis();
//   axis->SetLimits(-5.,5.);
   gra->GetHistogram()->SetMaximum(1.0);
   gra->GetHistogram()->SetMinimum(-1.0);
   grb->GetHistogram()->SetMaximum(30.0);
   grb->GetHistogram()->SetMinimum(-30.0);
   grc->GetHistogram()->SetMaximum(30.0);
   grc->GetHistogram()->SetMinimum(-30.0);
   grd->GetHistogram()->SetMaximum(800.0);
   grc->GetHistogram()->SetMinimum(-10.0);

   c1->cd(1);
   gra->Draw("AL");
   c1->cd(2);
   grc->Draw("AL");
   grb->Draw("L");
   c1->cd(3);
   grd->Draw("AL");

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
