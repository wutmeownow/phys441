#include <iostream>
#include <ctime>
#include <cmath>
#include <limits>
#include <cstdlib>
using namespace std;


void triangular_num() {
	
	const int num;
	double tip;
	cout << "Enter amount of numbers: ";
	cin >> num;
	cout << "Enter tip of triangle: ";
	cin >> tip;
	double xmin = 0;
	double xmax = 2;
	double nums [num];
	int count [num];
	double x;
	double U;
	double F = (tip - xmin) / (xmax - xmin);

gStyle->SetOptFit(kFALSE);	
   TCanvas *c1 = new TCanvas("c1","Uniform Distribution",200,10,700,500);
   
   c1->SetFillColor(42);
   c1->SetGrid();
   c1->Divide(1,2);

for (int i = 0; i<num; i++)
  {
	count[i] = 0;
  }

for (int i = 0; i<num; i++)
  {
	double U = ((double)rand()) / RAND_MAX;
	if (U <= F)
	{
		nums[i] = xmin + sqrt(U * (xmax - xmin) * (tip - xmin));
	}
	else
	{
		nums[i] = xmax - sqrt((1 - U) * (xmax - xmin) * (xmax - tip));
	}
	
	for (int j = 0; j<num; j++)
  	{
		x = num[j];
		if(x == nums[i])
		{ 
			count[i] = count[i] + 1;
		}	
	}
  }	

gr = new TGraph(21,nums,count);
	gr->SetMarkerStyle(21);
   	gr->SetTitle("Uniform Distribution");
   	gr->GetXaxis()->SetTitle("x");
  	gr->GetYaxis()->SetTitle("y");
   	gr->Draw("ALP");
}
