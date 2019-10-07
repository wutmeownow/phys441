#include <TRandom.h>

void graph_runge_random() {
   //
   //Modified: Edward J. Brash
   //		
  
   //gStyle->SetOptFit(kFALSE);	
   gStyle->SetOptFit(1);	
   TCanvas *c1 = new TCanvas("c1","Cubic Data",800,800);

   c1->SetFillColor(42);
   c1->SetGrid();

   TRandom r;

  double xlow,xhigh,rnd;
  int npoints, i;

  cout << "Enter the number of data points:" << endl;
  cin >> npoints;
  cout << "Enter the lower range:" << endl;
  cin >> xlow;
  cout << "Enter the upper range:" << endl;
  cin >> xhigh;

  const int n = npoints;

  double x[n],y[n],d[n],f[n];

  double step = (xhigh - xlow)/(npoints-1);

  for (i=0; i<npoints; i++) {
	   x[i] = xlow + i*step;
	   //y[i] = 1.0/(1+x[i]*x[i]);
	   y[i] = 1.00*pow(x[i],3)+0.40*pow(x[i],2)-4.05*x[i]+1.80;
	   rnd = r.Gaus(0.0,0.0);
	   y[i] = y[i]+rnd;
	   cout << "X-value: " << x[i] << " F(x): " << y[i] << endl;
  }

   TPaveStats *ptstats = new TPaveStats(0.62,0.695,0.98,0.935,"brNDC");
   ptstats->SetName("stats");
   ptstats->SetBorderSize(1);
   ptstats->SetFillColor(0);
   ptstats->SetTextAlign(23);
   ptstats->SetTextColor(2);
   ptstats->SetTextFont(32);
   ptstats->SetTextSize(0.03238342);
   ptstats->SetOptStat(1000000001);
   ptstats->SetOptFit(111);

   TGraph *gr = new TGraph(npoints,x,y);
   TF1 *pfit1 = new TF1("pfit1","pol3");
//   gr->SetLineColor(2);
//   gr->SetLineWidth(4);
//   gr->SetMarkerColor(4);
   gr->SetMarkerStyle(21);
   gr->SetTitle("9th Order Fit");
   gr->GetXaxis()->SetTitle("X");
   gr->GetYaxis()->SetTitle("Y");
   gr->SetMaximum(200.0);
   gr->SetMinimum(-200.0);
   gr->GetXaxis()->SetLimits(-6.0,6.0);
   pfit1->SetLineColor(2);
   gr->Fit("pfit1","q");
   Double_t pfit1chi2 = pfit1->GetChisquare();
   Double_t pfit1ndf = pfit1->GetNDF();
   Double_t pfit1chi2ndf = pfit1chi2/pfit1ndf;
   printf("Fit 1: %f %f \n",pfit1chi2,pfit1ndf);
   ptstats->Draw();
   gr->GetListOfFunctions()->Add(ptstats);
   ptstats->SetParent(gr->GetListOfFunctions());
   gr->Draw("AP");

   // draw the legend
//   Char_t message[80];
//   TLegend *legend=new TLegend(0.4,0.15,0.88,0.35);
//   legend->SetTextFont(72);
//   legend->SetTextSize(0.04);
//   legend->AddEntry(gr,"Data","lpe");
//   sprintf(message,"9th Order Fit: #chi^{2}/NDF = %.5f",pfit1chi2ndf);
//   legend->AddEntry(pfit1,message);
//   legend->Draw();

   // TCanvas::Update() draws the frame, after which one can change it
   c1->Update();
   c1->GetFrame()->SetFillColor(21);
   c1->GetFrame()->SetBorderSize(12);
   c1->Modified();
}
