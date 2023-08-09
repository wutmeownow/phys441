#include <TMath.h>
#include <TCanvas.h>
#include <TGraph.h>
#include <TPad.h>
using namespace std;

void derivativeestimation()
{

	double derivative;
	double x=1;
	const int numPoints=21;
	double h[numPoints];
	derivative = 2;
	double limitH=10;
	double deltaH[numPoints];
	//double xplush=0;
	//double step2=0;
	//double step3=0;
	
	const int numSteps=7;
	double step[numSteps];
	//int j=0;
	//double h2[numpoints];
	//double h3[numpoints];
	double deltaH2[numPoints];
	double deltaH3[numPoints];

	for(int i=0;i<numPoints;i++)
	{
	    limitH=1/(TMath::Power(10,i+1));
	    //cout << pow(10,i)<<endl;
	    //cout << limitH<<endl;
	    h[i]=limitH;
	    step[0]=(x+limitH)*(x+limitH);
	   // j++;
	    //cout<<xplush<<endl;
	    step[1]=step[0]-(x*x);
	    step[3]=step[0]-((x-limitH)*(x-limitH));
	    step[5]=(8*step[3])+((x-(2*limitH))*(x-(2*limitH)))-((x+(2*limitH))*(x+(2*limitH)));
	    //j++
	    //cout<<estep2<<endl;
	    step[2]=step[1]/limitH;
	    step[4]=step[3]/(2*limitH);
	    step[6]=step[5]/(12*limitH);
	    //cout<<step3<<endl;
	    //cout<<derivative<<endl;
	    deltaH[i]=TMath::Abs(step[2]-derivative);
	    deltaH2[i]=TMath::Abs(step[4]-derivative);
	    deltaH3[i]=TMath::Abs(step[6]-derivative);
	    cout<<"i= "<<i<<" deltaH = "<<deltaH[i]<<" deltaH2 = "<<deltaH2[i]<<" deltaH3 = "<<deltaH3[i]<<endl;
	    //memset(step,0,7);
	 }

	TCanvas *c1 = new TCanvas("c1","H v DeltaH", 200, 10, 1000, 1000);
	c1->Divide(3,1);
	c1->SetFillColor(42);
	c1->SetGrid();
	//c1->SetLogx();
	//c1->SetLogy();
	
	TPad *p1=(TPad*)(c1->cd(1));
	p1->SetLogx(1);
	p1->SetLogy(1);
        TGraph *gr = new TGraph(numPoints,h,deltaH);
	gr->SetTitle("Forward Difference Method");
	gr->SetMarkerStyle(21);
	gr->Draw("ALP");

	TPad *p2=(TPad*)(c1->cd(2));
	p2->SetLogx(1);
	p2->SetLogy(1);
	TGraph *gr2=new TGraph(numPoints,h,deltaH2);
	gr2->SetTitle("Centered Difference Method");
	gr2->SetMarkerStyle(21);
	gr2->Draw("ALP");

	TPad *p3=(TPad*)(c1->cd(3));
	p3->SetLogx(1);
	p3->SetLogy(1);
	TGraph *gr3=new TGraph(numPoints,h,deltaH3);
	gr3->SetTitle("Improved Centered Difference Method");
	gr3->SetMarkerStyle(21);
	gr3->Draw("ALP");
	
	c1->Update();
   	c1->Modified();
}

