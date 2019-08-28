//
// Fit to U.S. Standard Atmosphere Data
// From http://www.engineeringtoolbox.com/standard-atmosphere-d_604.html
//

#include <ostream>

Double_t fitfunction(Double_t *x, Double_t *par)
{
	Double_t f = par[0]+par[1]*x[0]+par[2]*pow(x[0],2.0)+par[3]*pow(x[0],3.0);
	//Double_t f = par[0]*exp(par[1]*x[0]+par[2]*pow(x[0],1.5));
	//Double_t f = par[0]*exp(par[1]*x[0]*x[0]);
	return f;
}

void graph_viscosity() {
   //
   //Modified: Edward J. Brash
   //		
  
   //gStyle->SetOptFit(kFALSE);	
   gStyle->SetOptFit(1);	
   TCanvas *c1 = new TCanvas("c1","Viscosity vs. Altitude",200,10,700,500);
   FILE *f = fopen("density2.txt","r");

   c1->SetFillColor(42);
   c1->SetGrid();
   c1->SetLogy();
   //c1->SetLogx();

   const Int_t n = 10000;
   Double_t altitude[n], temp[n], gravity[n], pressure[n], density[n], viscosity[n];
   Double_t ex[n],ey[n];

   Int_t i=0;

   while (!feof(f)){
	  fscanf(f,"%lf %lf %lf %lf %lf %lf\n",&altitude[i],&temp[i],&gravity[i],&pressure[i],&density[i],&viscosity[i]);
	  ex[i]=0.0;
	  ey[i]=0.001;
          i++;
   }

   const Int_t np=i;

   gr = new TGraphErrors(np,altitude,viscosity,ex,ey);
   TF1 *pfit1 = new TF1("fitfunction",fitfunction,0.0,80000.0,4);
   pfit1->SetParameters(10.0,-0.0001,-0.0000001,.00000001);
   pfit1->SetParNames("Amplitude","Linear","Quadratic","Cubic");
   //pfit1->SetParameters(12.0,-0.000000001);
   //pfit1->SetParNames("rho_0","linear");

//   gr->SetLineColor(2);
//   gr->SetLineWidth(4);
   gr->SetMarkerColor(kBlue);
   gr->SetMarkerStyle(21);
   gr->SetTitle("Density");
   gr->GetXaxis()->SetTitle("Altitude (m)");
   gr->GetYaxis()->SetTitle("Density (kg/m^3)");
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
