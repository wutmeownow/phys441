#include "TMath.h"
#include "TGraph.h"
#include "TPad.h"
#include "TCanvas.h"

Double_t func(Double_t x){
	return TMath::Power(x,2.0);
}
Double_t deriv(Double_t x){
	return 2.0*x;
}

Double_t forwardDifference(Double_t x, Double_t h){
	Double_t f1 = func(x+h);
	Double_t f0 = func(x);
	return TMath::Abs(deriv(x)-((f1-f0)/(h)));
}
Double_t centeredDifference(Double_t x, Double_t h){
	Double_t f1 = func(x+h);
	Double_t fneg1 = func(x-h);
	return TMath::Abs(deriv(x)-((f1-fneg1)/(2.0*h)));
}
Double_t improvedCenteredDiff(Double_t x, Double_t h){
	Double_t f2 = func(x+2.0*h);
	Double_t fneg2 = func(x-2.0*h);
	Double_t f1 = func(x+h);
	Double_t fneg1 = func(x-h);
	return TMath::Abs(deriv(x)-((fneg2-(8.0*fneg1)+(8.0*f1)-f2)/(12*h)));
}

void first_der_compare(){

	Double_t h[21];
	Double_t forwVal[21];
	Double_t centVal[21];
	Double_t imprVal[21];
	
	for (int i=0;i<21;i++){
		h[i] = TMath::Power(10.0,-i-1);
		forwVal[i] = forwardDifference(1.0,h[i]);
		centVal[i] = centeredDifference(1.0,h[i]);
		imprVal[i] = improvedCenteredDiff(1.0,h[i]);
	}

	gStyle->SetOptFit(kFALSE);
    TCanvas *c1 = new TCanvas("c1","First Derivative Calculation",200,10,700,500);
    c1->SetFillColor(42);
    c1->SetGrid();
	c1->Divide(1,3);

	TPad *p1 = (TPad*) (c1->cd(1));
    p1->SetLogx(1);
    p1->SetLogy(1);
	TGraph *forGraph = new TGraph(21,h,forwVal);
    forGraph->SetMarkerStyle(21);
    forGraph->SetTitle("Forward Difference");
    forGraph->GetXaxis()->SetTitle("h");
    forGraph->GetYaxis()->SetTitle("Delta h");
    forGraph->Draw("ALP");

	TPad *p2 = (TPad*) (c1->cd(2));
    p2->SetLogx(1);
    p2->SetLogy(1);
	TGraph *centGraph = new TGraph(21,h,centVal);
    centGraph->SetMarkerStyle(21);
    centGraph->SetTitle("Centered Difference");
    centGraph->GetXaxis()->SetTitle("h");
    centGraph->GetYaxis()->SetTitle("Delta h");
    centGraph->Draw("ALP");

	TPad *p3 = (TPad*) (c1->cd(3));
    p3->SetLogx(1);
    p3->SetLogy(1);
	TGraph *imprGraph = new TGraph(21,h,centVal);
    imprGraph->SetMarkerStyle(21);
    imprGraph->SetTitle("Improved Centered Difference");
   	imprGraph->GetXaxis()->SetTitle("h");
    imprGraph->GetYaxis()->SetTitle("Delta h");
    imprGraph->Draw("ALP");

   // TCanvas::Update() draws the frame, after which one can change it
   c1->Update();
   c1->GetFrame()->SetFillColor(21);
   c1->GetFrame()->SetBorderSize(12);
   c1->Modified();
}











