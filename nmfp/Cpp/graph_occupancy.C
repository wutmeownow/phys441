#include <ostream>
#include <TMath.h>

Double_t woods_saxon(Double_t *x, Double_t *par)
{
	//Double_t f = (par[0]-x[0])/(4.0*par[1]/sqrt(2.0))+0.5;
	Double_t f = 1.0/(1.0+exp(sqrt(2.0)*(x[0]-par[0])/(par[1])));
	//Double_t f = 0.5*ROOT::Math::erfc((x[0]-par[0])/(sqrt(2.0)*par[1]));
	return f;
}

void graph_occupancy() {
   //
   //Modified: Edward J. Brash
   //		
  
   //gStyle->SetOptFit(kFALSE);	
   gStyle->SetOptFit(1);	
   TCanvas *c1 = new TCanvas("c1","Freefall",600,600,1300,1200);
   FILE *f = fopen("occupancy.dat","r");

   c1->SetFillColor(42);
   c1->SetGrid();

   const Int_t n = 10000;
   Double_t occ[n],dac[n],gfit[n],wsfit[n];
   Int_t i=0;

   Int_t thr_of_half_max = 0;
   Double_t occ_min = 0.20;
   Double_t occ_max = 0.80;
   Double_t min_difference = 1.0;

   Double_t sumx = 0.0;
   Double_t sumy = 0.0;
   Double_t sumxy = 0.0;
   Double_t sumxx = 0.0;
   Int_t sumn = 0;

   while (!feof(f)){
	  fscanf(f,"%lf %lf\n",&dac[i],&occ[i]);
	  if (fabs(0.5-occ[i]) < min_difference){
		  thr_of_half_max = dac[i];
		  min_difference = fabs(0.5-occ[i]);
	  }
	  if (fabs(occ[i])<occ_max && fabs(occ[i])>occ_min){
		 sumn++;
		 sumx=sumx+dac[i];
		 sumy=sumy+occ[i];
		 sumxy=sumxy+dac[i]*occ[i];
		 sumxx=sumxx+dac[i]*dac[i];
	  } 
	  i++;
   }
   
   const Int_t n=i;

   Double_t xbar=sumx/sumn;
   Double_t ybar=sumy/sumn;
   Double_t beta = (sumxy - 1.0/sumn*sumx*sumy)/(sumxx - 1.0/sumn*sumx*sumx);
   Double_t alpha = ybar - beta*xbar;

   cout << "beta = " << beta << endl;
   cout << "alpha = " << alpha << endl;

   Double_t a=-1.0*sqrt(2.0)/(4.0*beta);
   Double_t x0=(alpha-0.5)*(4.0*a)/sqrt(2.0);

   Double_t a_corrected = a * 0.857065;
   //Double_t a_corrected = a * 0.857;
   //Double_t a_corrected = a * 1.00;
   
   Double_t xvalue[1];
   Double_t par[2];
   par[0]=x0;
   par[1]=a_corrected;

   Double_t chi2=0.0;

   for (i=0;i<n;i++){
	   xvalue[0]=dac[i];
	   wsfit[i]=woods_saxon(xvalue,par);
	   chi2=chi2+(wsfit[i]-occ[i])*(wsfit[i]-occ[i]);
	   //cout << "Fit = " << wsfit[i] << " i = " << i << endl;
	   gfit[i]=0.5*exp(-0.5*(dac[i]-x0)*(dac[i]-x0)/(a*a));
   }

   cout << "Chi2 / dof " << chi2 << " / " << n-2 << endl;
   cout << "MS_error = " << sqrt(chi2/(n-2)) << endl;

// Loop to estimate errors in parameters.
   
   Double_t x0_inc = 0.0001;
   Double_t a_inc = 0.0001;

   Double_t fit_increment=0.0;
   while (fit_increment < 1.0){
	   par[0]=par[0]+x0_inc;
	   Double_t chi2_inc=0.0;
	   for(i=0;i<n;i++){
	   	xvalue[0]=dac[i];
	   	wsfit[i]=woods_saxon(xvalue,par);
	   	chi2_inc=chi2_inc+(wsfit[i]-occ[i])*(wsfit[i]-occ[i]);
	   }
	   fit_increment=(n-2)*(chi2_inc/chi2-1.0);
   }

   Double_t dxplus=par[0]-x0;
   par[0]=x0;
   
   Double_t fit_increment=0.0;
   while (fit_increment < 1.0){
	   par[0]=par[0]-x0_inc;
	   Double_t chi2_inc=0.0;
	   for(i=0;i<n;i++){
	   	xvalue[0]=dac[i];
	   	wsfit[i]=woods_saxon(xvalue,par);
	   	chi2_inc=chi2_inc+(wsfit[i]-occ[i])*(wsfit[i]-occ[i]);
	   }
	   fit_increment=(n-2)*(chi2_inc/chi2-1.0);
   }

   Double_t dxminus=par[0]-x0;
   Double_t dx0=(dxplus-dxminus)/2.0;
  
   par[0]=x0; 
   Double_t fit_increment=0.0;
   while (fit_increment < 1.0){
	   par[1]=par[1]+a_inc;
	   Double_t chi2_inc=0.0;
	   for(i=0;i<n;i++){
	   	xvalue[0]=dac[i];
	   	wsfit[i]=woods_saxon(xvalue,par);
	   	chi2_inc=chi2_inc+(wsfit[i]-occ[i])*(wsfit[i]-occ[i]);
	   }
	   fit_increment=(n-2)*(chi2_inc/chi2-1.0);
   }

   Double_t daplus=par[1]-a_corrected;
   par[1]=a_corrected;
   
   Double_t fit_increment=0.0;
   while (fit_increment < 1.0){
	   par[1]=par[1]-a_inc;
	   Double_t chi2_inc=0.0;
	   for(i=0;i<n;i++){
	   	xvalue[0]=dac[i];
	   	wsfit[i]=woods_saxon(xvalue,par);
	   	chi2_inc=chi2_inc+(wsfit[i]-occ[i])*(wsfit[i]-occ[i]);
	   }
	   fit_increment=(n-2)*(chi2_inc/chi2-1.0);
   }

   Double_t daminus=par[1]-a_corrected;
   Double_t da=(daplus-daminus)/2.0;

   cout << "a_corrected = " << a_corrected << " +/- " << da <<endl;
   cout << "x0 = " << x0 << " +/- " << dx0 << endl;

//////////

   TF1 *pfit1 = new TF1("woods_saxon",woods_saxon,93.0,102.0,2);
   pfit1->SetParameters(thr_of_half_max,5.0);
   pfit1->SetParNames("Threshold","Sigma");

   gr = new TGraph(n,dac,occ);
   gr->SetMarkerColor(kBlue);
   gr->SetMarkerStyle(21);
   gr->SetTitle("Occupancy");
   gr->GetXaxis()->SetTitle("DAC");
   gr->GetYaxis()->SetTitle("Occupancy");
   gr->Fit(pfit1);
   gr->Draw("AP");

   gr2 = new TGraph(n,dac,gfit);
   gr2->SetLineColor(kGreen);
   gr2->SetLineWidth(3);
   gr2->Draw("L");
   
   gr3 = new TGraph(n,dac,wsfit);
   gr3->SetLineColor(kRed);
   gr3->SetLineWidth(3);
   gr3->Draw("L");

   // TCanvas::Update() draws the frame, after which one can change it
   c1->Update();
   c1->GetFrame()->SetFillColor(21);
   c1->GetFrame()->SetBorderSize(12);
   c1->Modified();
}
