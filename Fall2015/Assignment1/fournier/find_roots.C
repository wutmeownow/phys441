#include <TRandom.h>
#include <math.h>

void find_roots() 
{
	TCanvas *c1 = new TCanvas("c1","Delta h vs h",200,10,700,500);
	c1->SetFillColor(42);
	c1->SetGrid();
	c1->Divide(2,2);
	
	double x = 1.0;
	double f = pow(x,2);
	double df = 2 * x;
	double h = 1.0;
	double dh = 1.0;
	double deltaH [21];
	double H [21];

	double deltaH1 [21];
	double H1 [21];

	double deltaH2 [21];
	double H2 [21];

	for(int i = -20; i <= 0; i++) 
	{
		h = pow(10,i);
	   	dh = fabs(df - (pow((x + h),2) - f)/h);
		deltaH[(i + 20)] = dh;
		H[(i + 20)] = h;
	}

	for(int j = -20; j <= 0; j++) 
	{
		h = pow(10,j);
	   	dh = fabs(df - ((pow((x + h),2)) - (pow((x - h),2)))/(2 * h));
		deltaH1[(j + 20)] = dh;
		H1[(j + 20)] = h;
	}

	for(int i = -20; i <= 0; i++) 
	{
		h = pow(10,i);
	   	dh = fabs(df - (pow((x - 2 * h),2) - (8 * pow((x - h),2)) + (8 * pow((x + h),2)) - (pow((x + 2 * h),2)))/(12 * h));
		deltaH2[(i + 20)] = dh;
		H2[(i + 20)] = h;
	}

	gr = new TGraph(21,H,deltaH);
	gr->SetMarkerStyle(21);
   	gr->SetTitle("Forward Difference");
   	gr->GetXaxis()->SetTitle("h");
  	gr->GetYaxis()->SetTitle("Delta h");
	gr->GetXaxis()->CenterTitle();
	gr->GetYaxis()->CenterTitle();
	c1->cd(1);
	c1->GetPad(1)->SetLogx();
	c1->GetPad(1)->SetLogy();
   	gr->Draw("ALP");

	gr1 = new TGraph(21,H1,deltaH1);
	gr1->SetMarkerStyle(21);
   	gr1->SetTitle("Centered Difference");
   	gr1->GetXaxis()->SetTitle("h");
	gr1->GetXaxis()->CenterTitle();
	gr1->GetYaxis()->CenterTitle();
  	gr1->GetYaxis()->SetTitle("Delta h");
	c1->cd(2);
	c1->GetPad(2)->SetLogx();
	c1->GetPad(2)->SetLogy();
   	gr1->Draw("AP");

	gr2 = new TGraph(21,H2,deltaH2);
	gr2->SetMarkerStyle(21);
   	gr2->SetTitle("Improved Centered Difference");
   	gr2->GetXaxis()->SetTitle("h");
  	gr2->GetYaxis()->SetTitle("Delta h");
	gr2->GetXaxis()->CenterTitle();
	gr2->GetYaxis()->CenterTitle();
	c1->cd(3);
	c1->GetPad(3)->SetLogx();
	c1->GetPad(3)->SetLogy();
   	gr2->Draw("AP");

	
   //TCanvas::Update() draws the frame, after which one can change it
   	c1->Update();
   	c1->GetFrame()->SetFillColor(21);
   	c1->GetFrame()->SetBorderSize(12);
   	c1->Modified(); 
}
