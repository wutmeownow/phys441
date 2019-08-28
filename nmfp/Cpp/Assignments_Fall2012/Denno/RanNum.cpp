#include <math.h>

using namespace std;
Double_t m=pow(2,31)-1;
Double_t a=16807;
Double_t pi=3.141592653589793238462;

Double_t Rand(Double_t seed){
	Double_t rand=fmod((a*seed),m);
	return rand;
}

int main(){
	TCanvas *c1=new TCanvas("c1","Random Number Generator",1200,800);
	c1->Divide(3,2,.01,.01);
	Random(1);
	Triangle(1,100);
	Exp(1);
	Gauss1(1,100);
	Gauss2(1,100);
	return 1;
}

void Random(Double_t seed){
	Double_t rand;
	TH1D *h1=new TH1D("Uniform Dist","Uniform Dist",500,-.2,1.2);
	for(Int_t i=0; i<1000000; i++){
        rand=(Rand(seed)/m);
        h1->Fill(rand);
		seed=Rand(seed);
	}
	c1->cd(1);
	h1->Draw();
}

void Triangle(Double_t s1,Double_t s2){
	Double_t rand;
	TH1D *Tri=new TH1D("Triangle Dist","Triangle Dist",500,-.2,2.2);
	for(Int_t i=0; i<1000000; i++){
        rand=(Rand(s1)/m)+(Rand(s2)/m);
        Tri->Fill(rand);
		s1=Rand(s1); s2=Rand(s2);
	}
	c1->cd(2);
    Tri->Draw();
}

void Exp(Double_t seed){
	Double_t rand;
	TH1D *exp=new TH1D("Exponential Dist","Exponential Dist",500,-.2,4);
	for(Int_t i=0; i<1000000; i++){
        rand=-log(1-(Rand(seed)/m));
        exp->Fill(rand);
		seed=Rand(seed);
	}
	c1->cd(3);
    exp->Draw();
}

void Gauss1(Double_t s1,Double_t s2){
    Double_t rand;
	Double_t x1,x2,z1,z2;
    TH1D *gss1=new TH1D("Gaussian 1","Gaussian 1",500,-4,4);
	for(Int_t i=0;i<500000;i++){
		x1=Rand(s1)/m; x2=Rand(s2)/m;
		z1=pow(-2*log(x1),.5)*cos(2*pi*x2);
		z2=pow(-2*log(x1),.5)*sin(2*pi*x2);
		gss1->Fill(z1); gss1->Fill(z2);
		s1=Rand(s1); s2=Rand(s2);
	}
	c1->cd(4);
    gss1->Draw();
}

void Gauss2(Double_t s1,Double_t s2){
    Double_t rand;
	Double_t x1,x2,z1,z2;
    TH1D *gss2=new TH1D("Gaussian 2","Gaussian 2",500,-4,4);
	for(Int_t i=0;i<500000;i++){
		x1=Rand(s1)/m; x2=Rand(s2)/m;
		z1=pow(-2*log(x1),.5)*.3*cos(2*pi*x2)+1;
		z2=pow(-2*log(x1),.5)*.3*sin(2*pi*x2)+1;
		gss2->Fill(z1); gss2->Fill(z2);
		s1=Rand(s1); s2=Rand(s2);
	}
    c1->cd(5);
	gss2->Draw();
}

