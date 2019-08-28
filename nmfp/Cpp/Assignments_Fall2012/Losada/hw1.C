#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>


double hpoints[20],dhpoints[20];

void hw1(){	
	for(int i=0; i>=-20; i--){
		double h = pow(10,i);	
		hpoints[i*-1]=h;
//		std::cout<<"h=  "<<h<<std::endl;
		double x =1;
		double dh = abs((2*x)-((pow((x+h),2)-pow(x,2))/h));
		dhpoints[i*-1]=dh;
//		std::cout<<dh<<std::endl;
	}
/**	for(int i=0;i<=20;i++){
		std::cout<<hpoints[i]<<"  =   "<<dhpoints[i]<<std::endl;
	}
	system("PAUSE");
*/
TCanvas *c1 = new TCanvas("canvas","HW1",40,40,800,800);
//set options
  gStyle->SetOptStat(0); //turns on stat box
  gStyle->SetOptFit(1);  //turns on fit box
  c1->ToggleEventStatus(); //turns on event status bar
  
g = new TGraph(20,hpoints,dhpoints);
  // g->SetLineColor(2);
  // g->SetLineWidth(4);
  // g->SetMarkerColor(4);
   g->SetMarkerStyle(21);
   g->SetTitle("HW1");
   g->GetXaxis()->SetTitle("H");
   g->GetYaxis()->SetTitle("dH");
   c1->SetLogx();
g->Draw("ADP");

c1->Update();

}
