#include <math.h>
#include <TGraph>

void ICDMroot(){
	
   TCanvas *c1 = new TCanvas("c1","Delta H v H",200,10,700,500);
   c1->SetFillColor(42);
   c1->SetGrid();

double x = 1.0;
double fx = pow(x,2);
double dfx = 2.0 * x;
double h2 = 1.0;
double dh2 = 1.0;
double dhArray2[21];
double hArray2[21];
int r = 0;

for(int j = 0; j <= 20; j++){
	h2 = 1/(pow(10,j+1));
	dh2 = fabs(dfx - (pow((x-2*h2),2)-(8*pow((x-h2),2))+(8*pow((x+h2),2))-(pow((x+2*h2),2))) / (12*h2));
	dhArray2[r] = dh2;
	hArray2[r] = h2;	
	r++;
    }

   c1->SetLogx();
   c1->SetLogy();
   gr2 = new TGraph(21,hArray2,dhArray2);
   gr2->SetMarkerStyle(21);
   gr2->SetTitle("Delta H vs H (ICDM)");
   gr2->GetXaxis()->SetTitle("H");
   gr2->GetYaxis()->SetTitle("Delta H");
   gr2->Draw("ALP");
   c1->Update();
   c1->Modified();

}
