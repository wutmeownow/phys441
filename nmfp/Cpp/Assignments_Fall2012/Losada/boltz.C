#include <ostream>
#define _USE_MATH_DEFINES
#include <math.h>
#include <TMatrixD.h>
using namespace std;

//**************USER OPTIONS******************************\\
/***/ FILE *f = fopen("vmagF_200.txt","r");			
//********************************************************\\
//data arrays
Double_t vf[10000];
int n=0;
//methods
void fill();
void graph();

//MAIN
void boltz(){
	fill();
	//v=sqrt((3kT)/m)  	derive with resect to...???
	
	TF1 *myfit = new TF1("myfit",, 0, 1000,2);
	
	
	
	
	graph();
}

Double_t fit(double *x, double *par){
	double pi = 3.14159265;
	double a = .5*sqrt(pi/2.0)*par[1];
	Float_t xx = x[0];
	double f = 1000.0/200.0*par[0]*sqrt(2/pi)/xx*xx*exp(-1*xx*xx/(2*a*a));
return f;
}


void graph(){
	TCanvas *c1 = new TCanvas("canvas","HW2",40,40,600,600);
	//set options
	c1->ToggleEventStatus(); 
	TH1D *h1 = new TH1D("h1","Max",200,-0.2,1000);
	for(int j=0;j<10000;j++){
		h1->Fill(vf[j]);
	}
	double mean = h1->GetMean(1);
	h1->Draw();
	
cout<<mean<<endl;
}
void fill(){
int i=0;
	while(!feof(f)){
		fscanf(f,"%lf\n",&vf[i]);
//		printf("%i %f %f %f\n",i,x[i],y[i],sy[i]);
		i++;n++;
	}
}
