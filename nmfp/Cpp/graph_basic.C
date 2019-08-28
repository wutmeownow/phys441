//
// Fit to U.S. Standard Atmosphere Data
// From http://www.engineeringtoolbox.com/standard-atmosphere-d_604.html
//

#include <ostream>

Double_t fitfunction(Double_t *x, Double_t *par)
{
	//Double_t f = par[0]*exp(par[1]*x[0]+par[2]*x[0]*x[0]+par[3]*x[0]*x[0]*x[0]);
	//Double_t f = par[0]*exp(par[1]*x[0]+par[4]*x[0]*x[0]) + par[2]*exp(par[3]*x[0]+par[5]*x[0]*x[0]);
	Double_t f = par[0]*exp(par[1]*x[0]) + par[2]*exp(par[3]*x[0]);
	return f;
}

void graph_basic(Bool_t ylog = 0, Bool_t xlog = 0, Bool_t ifit = 0) {

   gStyle->SetOptFit(1);	
   TCanvas *c1 = new TCanvas("c1","Density of Air vs. Altitude",200,10,1000,750);
   FILE *f = fopen("density.txt","r");

   c1->SetFillColor(42);
   c1->SetGrid();
   if (xlog) {c1->SetLogx();}
   if (ylog) {c1->SetLogy();}

   const Int_t n = 10000;
   Double_t altitude[n], temp[n], gravity[n], pressure[n], density[n], viscosity[n];
   Int_t i=0;

   while (!feof(f)){
	  fscanf(f,"%lf %lf %lf %lf %lf %lf\n",&altitude[i],&temp[i],&gravity[i],&pressure[i],&density[i],&viscosity[i]);
	  density[i]=density[i]*0.1;
          i++;
   }

   const Int_t np=i;

   TGraph *gr = new TGraph(np,altitude,density);
   TF1 *pfit1 = new TF1("fitfunction",fitfunction,0.0,80000.0,4);
   //pfit1->SetParameters(1.2,-1.0E-6,1.0E-2,-1.0E-7,1.0E-12,1.0E-12);
   //pfit1->SetParNames("rho_0","linear_0","rho_1","linear_1","quadratic_0","quadratic_1");
   pfit1->SetParameters(1.2,-1.0E-6,1.0E-2,-1.0E-7);
   pfit1->SetParNames("rho_0","linear_0","rho_1","linear_1");

   gr->SetMarkerColor(kBlue);
   gr->SetMarkerStyle(21);
   gr->SetTitle("Density");
   gr->GetXaxis()->SetTitle("Altitude (m)");
   gr->GetYaxis()->SetTitle("Density (kg/m^3)");

//   TAxis *axis = gr->GetXaxis();
//   axis->SetLimits(-5.,5.);
//   gr->GetHistogram()->SetMaximum(40000.0);
//   gr->GetHistogram()->SetMinimum(0.0);

   if (ifit) gr->Fit("fitfunction","V");
   gr->Draw("AP");

   // TCanvas::Update() draws the frame, after which one can change it
   c1->Update();
   c1->GetFrame()->SetFillColor(21);
   c1->GetFrame()->SetBorderSize(12);
   c1->Modified();
}

