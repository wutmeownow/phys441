#include <string>
//#include <ostream>
#include <sstream>
#define _USE_MATH_DEFINES
#include <math.h>
#include <TMatrixD.h>
#include <TVectorD.h>

//**************USER OPTIONS*******************************\\
/***/ const int m=1;    //ORDER of fit			
/***/ Option_t* opt = "pol1"; //replace # with value of m
/***/ const bool errors = false; //true if using error	
/***/ FILE *f = fopen("means.txt","r");			
//********************************************************\\
//data arrays
Double_t x[1000],y[1000];
int n=0;
//methods
void fill();
void graph();

//MAIN
void meanplot(){
	fill();
//Construct A
	TMatrixD a =  TMatrixD(m+1,m+1);
// Construct V	
	TVectorD v = TVector(m+1);
//fill a
	for(int i =0; i<m+1;i++){
		for(int j=0; j<m+1; j++){
			for(int k=0;k<n;k++){
				
					a[i][j]=a[i][j]+pow(x[k],(i+j));
				
			if(j==0){
				
					v[i]=v[i]+(y[k]*pow(x[k],(i)));
				
			}	
			}	
		}
	}
	
//Invert A
	Double_t det1;
	a.InvertFast();
//******FIND C******\\
TVectorD c = a*v;
for(int i=0; i<m+1;i++){cout<<"c: "<<c[i]<<endl;}
graph();
}


void graph(){
	TCanvas *c1 = new TCanvas("canvas","HW2",40,40,600,600);
	//set options
	gStyle->SetOptStat(0); //turns on(1)/off(0) stat box
	gStyle->SetOptFit(0);  //turns on(1)/off(0) fit box
	c1->ToggleEventStatus(); //turns on event status bar
	g = new TGraph(n,x,y);
	 g->SetLineColor(2);
	 g->SetLineWidth(4);
	 g->SetMarkerColor(4);
	g->SetMarkerStyle(21);
	g->SetTitle("HW2");
	g->GetXaxis()->SetTitle("X");
	g->GetXaxis()->SetLimits(0,300);
	g->GetYaxis()->SetTitle("Y");
g->GetYaxis()->SetLimits(0,400);
	g->Fit(opt);
	g->Draw("ACP");
	c1->Update();
}

void fill(){
	int i=0;
	while(i<15){
		fscanf(f,"%lf %lf\n",&x[i],&y[i]);
		cout<<x[i]<<"   "<<y[i]<<endl;
		i++;n++;
	}
}
