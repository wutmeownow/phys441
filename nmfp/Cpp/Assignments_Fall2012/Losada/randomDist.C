#include <iostream>
#include <math.h>
/**uniform distribution**/
const int n = 1000000;
const int m = 6;
double x[n];
double y[n];
double c[m][n];
double rand();
//Main
void randomDist(){
TCanvas *c1 = new TCanvas("canvas","Random number generator",40,40,1200,600);
//set options
	gStyle->SetOptStat(1); //turns on(1)/off(0) stat box
	gStyle->SetOptFit(0);  //turns on(1)/off(0) fit box
	c1->ToggleEventStatus(); //turns on event status bar
c1->Divide(3,2);

	int a = pow(7,5);
	int M = pow(2,31)-1;
	int C = 0;
	int I = 1;   //seed DO NOT USE 0 


//Uniform	
	TH1D *h1 = new TH1D("h1", "uniform distribution",500,-0.2,1.2);
	rand(x,a,M,C,I);
	for(int i=0;i<n;i++){
		h1->Fill(x[i]);
	} 
	c1->cd(1);h1->Draw();c1->Update();

	
//Triangular	
	TH1D *h2 = new TH1D("h2", "triangular distribution",500,-0.2,2.2);
	I+=100;
	rand(y,a,M,C,I);
	double R=0;
	for(int i=0;i<n;i++){
		R=x[i]+y[i];
		h2->Fill(R);
	} 
	c1->cd(2);h2->Draw();c1->Update();

//Exponential
	TH1D *h3 = new TH1D("h3", "exponential distribution",500,-0.2,2.2);
	double L = 1;
	for(int i=0;i<n;i++){
		double u = -L*log(1-x[i]);
		h3->Fill(u);
	} 
	c1->cd(3);h3->Draw();c1->Update();


//Gaussian
	TH1D *h4 = new TH1D("h4", "gaussian distribution",100,-4,4);
	I=1;
	rand(x,a,M,C,I);
	I=1000;
	rand(y,a,M,C,I);
	for(int i=0;i<n;i++){
		x[i]=-1+2*x[i];
		y[i]=-1+2*y[i];
		
	}
	double sigma = 1;
	double mew = 0;
	double W[n];
	int ii = 0;
	for(int i=0;i<n;i++){
		double S=x[i]*x[i]+y[i]*y[i];
		if(S<1){
			W[ii]=x[i]*sqrt((-2*log(S))/S);
			ii++;
			W[ii]=y[i]*sqrt((-2*log(S))/S);
			ii++;
		}
		if(ii==n-1||ii==n-2){
			break;
		}
	}
	for(int i=0;i<n;i++){
		h4->Fill(W[i]);
	}
	c1->cd(4);h4->Draw();c1->Update();

//GAUSSIAN 2
	TH1D *h5 = new TH1D("h5", "gaussian distribution",100,-4,4);
	sigma = .3;
	mew = 1;
	for(int i=0;i<n;i++){
		W[i] = W[i]*sigma+mew;
		h5->Fill(W[i]);
	}
	c1->cd(5);h5->Draw();c1->Update();
}
void rand(double r[],int a, int M, int C, int I){
	for(int i=0;i<n;i++){
		int Inext = (a*I+C)%M;
		r[i]=Inext;
		double InextD = Inext;
		double MD = M;
		r[i]=InextD/MD;
//		cout<<x[i]<<endl;
		I=Inext;
	}	
}

