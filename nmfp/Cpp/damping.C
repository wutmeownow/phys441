#include <iostream>
#include <TMath.h>

Double_t critical_damping(Double_t *x, Double_t *par)
{
	Double_t omega0=par[0];
	Double_t x0=par[1];
	Double_t v0=par[2];
	Double_t dbeta=par[3];
	Double_t beta=(1.0+dbeta)*omega0;
	Float_t xx = x[0];
	Double_t c1=x0;
	Double_t c2=v0+beta*c1;
	Double_t f = exp(-1.0*beta*xx)*(c1+c2*xx);
	return f;
}

Double_t under_damping(Double_t *x, Double_t *par)
{
	Double_t omega0=par[0];
	Double_t x0=par[1];
	Double_t v0=par[2];
	Double_t dbeta=par[3];
	Double_t beta=(1.0+dbeta)*omega0;
	Double_t omega1=sqrt(omega0*omega0-beta*beta);
	Float_t xx = x[0];
	Double_t a=x0;
	Double_t b=(v0+x0*beta)/omega1;
	Double_t f = exp(-1.0*beta*xx)*(a*cos(omega1*xx)+b*sin(omega1*xx));
	return f;
}

Double_t over_damping(Double_t *x, Double_t *par)
{
	Double_t omega0=par[0];
	Double_t x0=par[1];
	Double_t v0=par[2];
	Double_t dbeta=par[3];
	Double_t beta=(1.0+dbeta)*omega0;
	Double_t r1=-(beta-sqrt(beta*beta-omega0*omega0));
	Double_t r2=-(beta+sqrt(beta*beta-omega0*omega0));
	Double_t c2=(x0*r1-v0)/(r1-r2);
	Double_t c1=x0-c2;
	Float_t xx = x[0];
	Double_t f = c1*exp(r1*xx)+c2*exp(r2*xx);
	return f;
}

void damping() {

	TCanvas *c1 = new TCanvas("c1","Damping",450,450,1474,1218);
	c1->SetFillColor(42);
	c1->SetGrid();
	//c1->SetLogy();
	
	const Int_t n = 1000;
	Double_t x[n],yc[n],yu[n],yo[n];
	Double_t par[4];
	Double_t xvalue[1];

	Double_t g=9.80524;
	Double_t dx=0.5000;
	Double_t x0=0.0000;
	Double_t v0=2.0000;
	Double_t dbeta=0.90;
	Double_t omega0=sqrt(g/dx);
	par[0]=omega0;
	par[1]=x0;
	par[2]=v0;

	for(Int_t i=0; i<n; ++i){
		x[i]=i*3.0/n;
		xvalue[0]=x[i];
		par[3]=0.0;
		yc[i]=critical_damping(xvalue,par);
		par[3]=-dbeta;
		yu[i]=under_damping(xvalue,par);
		par[3]=+dbeta;
		yo[i]=over_damping(xvalue,par);
	}

	gr = new TGraph(n,x,yu);
	gr->SetMarkerColor(kBlue);
	//gr->SetMarkerStyle(21);
	gr->SetTitle("Damping");
	gr->GetXaxis()->SetTitle("time");
	gr->GetYaxis()->SetTitle("position");

	gr->Draw("AP");

	gr2 = new TGraph(n,x,yc);
	gr2->SetMarkerColor(kRed);
	//gr2->SetMarkerStyle(21);
	gr2->SetTitle("Damping");
	gr2->GetXaxis()->SetTitle("time");
	gr2->GetYaxis()->SetTitle("position");

	gr2->Draw("P");

	gr3 = new TGraph(n,x,yo);
	gr3->SetMarkerColor(kBlack);
	//gr3->SetMarkerStyle(21);
	gr3->SetTitle("Damping");
	gr3->GetXaxis()->SetTitle("time");
	gr3->GetYaxis()->SetTitle("position");

	gr3->Draw("P");

	c1->Update();
	c1->GetFrame()->SetFillColor(21);
	c1->GetFrame()->SetBorderSize(12);
	c1->Modified();

}
