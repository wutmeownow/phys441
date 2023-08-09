#include <iostream>
#include <TMath.h>

int first_deriv()
{
//Instantiating variables and arrays
double h_exp_min = 20;
const int n = 10000;
double h [n];
double del_h [n];
double del_h_cent [n];
double del_h_cent_imp [n];
double dh = h_exp_min/n;

//Filling in the arrays with data
for (int i=0; i<n; i++){
	h[i] = pow(10,-i*dh);
	del_h[i] = fabs(2 - ((1 + h[i])*(1 + h[i]) - 1)/h[i]);
	if(del_h[i] == 0.0) del_h[i]=1.0e-18;
	del_h_cent[i] = fabs(2 - ((1 + h[i])*(1 + h[i]) - (1 - h[i])*(1 - h[i]))/(2*h[i]));
	if(del_h_cent[i] == 0.0) del_h_cent[i]=1.0e-18;
	del_h_cent_imp[i] = fabs(2 - (pow(1-2*h[i],2.0) - 8*pow(1-h[i],2.0) + 8*pow(1+h[i],2.0) - pow(1+2*h[i],2.0))/(12*h[i]));
	if(del_h_cent_imp[i] == 0.0) del_h_cent_imp[i]=1.0e-18;
}

//Making the canvas
TCanvas *c1 = new TCanvas("c1","First Derivative Check",200,10,1400,650);
c1->Divide(3,1);
TMultiGraph *mg = new TMultiGraph();
c1->SetFillColor(42);
c1->SetTitle("First Derivative Check");
c1->cd(1)->SetGrid();
c1->cd(1)->SetLogx();
c1->cd(1)->SetLogy();
c1->cd(2)->SetGrid();
c1->cd(2)->SetLogx();
c1->cd(2)->SetLogy();
c1->cd(3)->SetGrid();
c1->cd(3)->SetLogx();
c1->cd(3)->SetLogy();

//Making the graphs
gr = new TGraph(n,h,del_h);
gr2 = new TGraph(n,h,del_h_cent);
gr3 = new TGraph(n,h,del_h_cent_imp);
gr->SetLineColor(2);
gr2->SetLineColor(2);
gr3->SetLineColor(2);
gr->SetLineWidth(2);
gr2->SetLineWidth(2);
gr3->SetLineWidth(3);
gr->SetMarkerColor(4);
gr2->SetMarkerColor(3);
gr3->SetMarkerColor(2);
gr->SetMarkerStyle(6);
gr2->SetMarkerStyle(6);
gr3->SetMarkerStyle(6);
gr->SetTitle("Forward method");
gr2->SetTitle("Centered method");
gr3->SetTitle("Improved Centered method");
gr->GetXaxis()->SetTitle("H size");
gr2->GetXaxis()->SetTitle("H size");
gr3->GetXaxis()->SetTitle("H size");
gr->GetYaxis()->SetTitle("Delta H");
gr2->GetYaxis()->SetTitle("Delta H");
gr3->GetYaxis()->SetTitle("Delta H");

//Filling the canvas
c1->cd(1); gr->Draw("AP");
c1->cd(2); gr2->Draw("AP");
c1->cd(3); gr3->Draw("AP");
c1->Update();
c1->GetFrame()->SetFillColor(21);
c1->GetFrame()->SetBorderSize(12);
c1->Modified();
}	
