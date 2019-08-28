#include <stdio.h>
#include <math.h>
Double_t pi=3.14159265358979323846;
Double_t DC=(.0043*1*1.2);				//Drag Coefficient

void Proj_Motion(){
	Double_t iy; Double_t iv, itheta;
	printf("Initial Height:  "); scanf("%lf",&iy);
	printf("Initial Velocity:  "); scanf("%lf",&iv);
	printf("Initial Angle:  "); scanf("%lf",&itheta);
	itheta=(itheta/180)*pi;
	Double_t vy=iv*sin(itheta);
	Double_t vx=iv*cos(itheta);
	
	///////////////////Air Resistance////////////////////
	
	Int_t rows=0;
	TMatrixD posar(1,2);
	posar(0,1)=iy;
	Double_t t=0; 
	Double_t ox=0; Double_t nx; Double_t oy=iy; Double_t ny;		//old and new pos
	Double_t ovx=vx; Double_t nvx; Double_t ovy=vy; Double_t nvy;	//old and new velocity
	Double_t ov=sqrt(pow(ovx,2)*pow(ovy,2));						// velocity magnitude
	Double_t oax=-ovx*ov*DC;			//
	Double_t oay=-ovy*ov*DC;			// Accelerations
	Double_t nax; Double_t nay;			//
	
	while (ny>=0){
		nax=-DC*ov*ovx;
		nay=-9.8-(DC*ov*ovy);
		nvx=ovx+(oax*t);
		nvy=ovy+(oay*t);
		nx=ox+(ovx*t);
		ny=oy+(ovy*t);

		if (ny>=0) {
			rows++;
			posar.ResizeTo(rows+1,2);
			posar(rows,0)=nx;
			posar(rows,1)=ny;
			
			ox=nx; ovx=nvx; oax=nax;
			oy=ny; ovy=nvy; oay=nay;
			ov=sqrt(pow(ovx,2)*pow(ovy,2));
			t+=.001;
		}
		else {
			rows++;
			posar.ResizeTo(rows+1,2);
			posar(rows,0)=nx;
			posar(rows,1)=ny;
		}
	}
	const Int_t row=rows;
	Double_t xar[row],yar[row];
	for (Int_t i=0; i<row; i++) {
		xar[i]=posar(i,0);
		yar[i]=posar(i,1);
	}
	
	
	////////////////////No Air Resistance////////////////////
	
	rows=0; t=0;
	TMatrixD pos(1,2);
	pos(0,1)=iy;
	ox=0; oy=iy;
	ovy=vy; oy=iy; ny=1; 

	while (ny>=0){
		nvy=ovy+(-9.8*t);
		nx=ox+vx*t;
		ny=oy+(ovy*t);
		
		if (ny>=0) {
			rows++;
			pos.ResizeTo(rows+1,2);
			pos(rows,0)=nx;
			pos(rows,1)=ny;
			oy=ny;
			ox=nx;
			ovy=nvy;
			t+=.001;
		}
		else {
			rows++;
			pos.ResizeTo(rows+1,2);
			pos(rows,0)=nx;
			pos(rows,1)=ny;
		}
	}
	const Int_t rownar=rows;
	Double_t xnar[rownar],ynar[rownar];
	for (Int_t i=0; i<rownar; i++) {
		xnar[i]=pos(i,0);
		ynar[i]=pos(i,1);
	}
	
	
	gStyle->SetOptFit();
	TCanvas *c1 = new TCanvas("c1","Projectile Motion",700,500);
	c1->SetGrid();
	TMultiGraph *mg=new TMultiGraph();
	TGraph *AR=new TGraph(row,xar,yar);
	AR->SetLineColor(2);
	AR->SetLineWidth(4);
	AR->SetMarkerColor(4);
	AR->SetMarkerStyle(21);
	TGraph *NAR = new TGraph(rownar,xnar,ynar);
	NAR->SetLineColor(4);
	NAR->SetLineWidth(2);
	NAR->SetMarkerColor(2);
	NAR->SetMarkerStyle(21);
	mg->SetTitle("Projectile Motion; X Pos; Y Pos");
	mg->Add(AR);
	mg->Add(NAR);
	
	mg->Draw("ap");
	
}
