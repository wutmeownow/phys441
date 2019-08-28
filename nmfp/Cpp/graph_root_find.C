#include <TRandom.h>

void graph_root_find() {
   //Draw a simple graph
   // To see the output of this macro, click begin_html <a href="gif/graph.gif">here</a>. end_html
   //Author: Rene Brun
   //
   //Modified: Edward J. Brash, to change to simple linear plot
   //				with random fluctuations
  
   gStyle->SetOptFit(kFALSE);	
   TCanvas *c1 = new TCanvas("c1","Root Finding Example",200,10,700,500);
   FILE *f =  fopen("root_find_bisection_loop.dat","r");
   
   c1->SetFillColor(42);
   c1->SetGrid();
   c1->SetLogy();

   const Int_t n=1000000;
   Int_t i;
   double x[n],y[n];

   while (!feof(f)){
	  fscanf(f,"%lf %lf\n",&x[i],&y[i]);
	  printf("%i %f %f\n",i,x[i],y[i]);
	  i++;
   }

   gr = new TGraph(n,x,y);
//   gr->SetLineColor(2);
//   gr->SetLineWidth(4);
//   gr->SetMarkerColor(4);
   gr->SetMarkerStyle(21);
   gr->SetMaximum(10000.0);
   gr->SetMinimum(50.0);
   gr->GetXaxis()->SetLimits(1.0,2000.0);
   gr->SetTitle("Root Finding Example");
   gr->GetXaxis()->SetTitle("Division Size");
   gr->GetYaxis()->SetTitle("NSteps");
   gr->Draw("AP");

   // TCanvas::Update() draws the frame, after which one can change it
   c1->Update();
   c1->GetFrame()->SetFillColor(21);
   c1->GetFrame()->SetBorderSize(12);
   c1->Modified();
}
