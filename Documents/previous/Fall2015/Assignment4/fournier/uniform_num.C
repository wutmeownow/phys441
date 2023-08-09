#include <iostream>
#include <ctime>
#include <cmath>
#include <limits>
#include <cstdlib>
using namespace std;


void uniform_num() {
	
	const int num;
	cout << "Enter amount of numbers: ";
 	cin >> num;
	double nums [num];
	double count [num];
	double x;

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
	nums[i]=((double) rand() / (RAND_MAX+1)) ;
	
	for (int j = 0; j<num; j++)
  	{
		x = num[j];
		if(x - nums[i] <= 0.01)
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
