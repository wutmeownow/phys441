#include <ostream>

Double_t fitfunction(Double_t *x, Double_t *par)
{
	Double_t f = par[0]*exp(par[1]*x[0]+par[2]*pow(x[0],1.5));
	//Double_t f = par[0]*exp(par[1]*x[0]*x[0]);
	return f;
}

void graph_basic() {
   //
   //Modified: Edward J. Brash
   //		
  
   //gStyle->SetOptFit(kFALSE);	
   gStyle->SetOptFit(1);	
   TCanvas *c1 = new TCanvas("c1","Freefall",200,10,700,500);
   FILE *f = fopen("density.txt","r");

   c1->SetFillColor(42);
   c1->SetGrid();
   c1->SetLogy();

   const Int_t n = 10000;
   Double_t h[n], t[n], g[n], p[n], rho[n], mu[n];
   Int_t i=0;

   while (!feof(f)){
	  fscanf(f,"%lf %lf %lf %lf %lf %lf\n",&h[i],&t[i],&g[i],&p[i],&rho[i],&mu[i]);
	  i++;
   }

   const Int_t n=i;

   gr = new TGraph(n,h,rho);
   TF1 *pfit1 = new TF1("fitfunction",fitfunction,6000.0,85000.0,3);
   pfit1->SetParameters(12.0,-0.0001,-0.0000000001);
   pfit1->SetParNames("rho_0","linear","quadratic");
   //pfit1->SetParameters(12.0,-0.000000001);
   //pfit1->SetParNames("rho_0","linear");

//   gr->SetLineColor(2);
//   gr->SetLineWidth(4);
   gr->SetMarkerColor(kBlue);
   gr->SetMarkerStyle(21);
   gr->SetTitle("Freefall");
   gr->GetXaxis()->SetTitle("X");
   gr->GetYaxis()->SetTitle("Y");
//   TAxis *axis = gr->GetXaxis();
//   axis->SetLimits(-5.,5.);
//   gr->GetHistogram()->SetMaximum(40000.0);
//   gr->GetHistogram()->SetMinimum(0.0);
   gr->Fit("fitfunction","V");
   gr->Draw("AP");

   // TCanvas::Update() draws the frame, after which one can change it
   c1->Update();
   c1->GetFrame()->SetFillColor(21);
   c1->GetFrame()->SetBorderSize(12);
   c1->Modified();
}
