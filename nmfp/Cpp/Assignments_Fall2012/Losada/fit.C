#include <string>
//#include <ostream>
#include <sstream>
#define _USE_MATH_DEFINES
#include <math.h>
#include <TMatrixD.h>
#include <TVectorD.h>

//**************USER OPTIONS*******************************\\
/***/ const int m=2;    //ORDER of fit			
/***/ Option_t* opt = "pol2"; //replace # with value of m
/***/ const bool errors = true; //true if using error	
/***/ FILE *f = fopen("linear.dat","r");			
//********************************************************\\
//data arrays
Double_t x[10000],y[10000],sx[10000],sy[10000];
int n=0;
//methods
void fill();
void graph();

//MAIN
void fit(){
	fill();
//Construct A
	TMatrixD a =  TMatrixD(m+1,m+1);
// Construct V	
	TVectorD v = TVector(m+1);
//fill a
	for(int i =0; i<m+1;i++){
		for(int j=0; j<m+1; j++){
			for(int k=0;k<n;k++){
				if(errors){
					a[i][j]=a[i][j]+(pow(x[k],(i+j))/pow(sy[k],2));
				}
				else{
					a[i][j]=a[i][j]+pow(x[k],(i+j));
				}
			if(j==0){
				if(errors){
					v[i]=v[i]+((y[k]*pow(x[k],(i)))/pow(sy[k],2));
				}
				else{
					v[i]=v[i]+(y[k]*pow(x[k],(i)));
				}
			}	
			}	
		}
	}
	for(int i =0; i<m+1;i++){for(int j=0; j<m+1; j++){cout<<"A["<<i<<"]["<<j<<"] "<<a[i][j]<<"  "<<endl;}}
	for(int i=0; i<m+1;i++){cout<<"v: "<<v[i]<<endl;}

//Invert A
	Double_t det1;
	a.InvertFast();
//	for(int i =0; i<m+1;i++){for(int j=0; j<m+1; j++){cout<<"A-1["<<i<<"]["<<j<<"] "<<a[i][j]<<" "<<endl;}}
//******FIND C******\\
TVectorD c = a*v;
for(int i=0; i<m+1;i++){cout<<"c: "<<c[i]<<endl;}
graph();
}


void graph(){
	TCanvas *c1 = new TCanvas("canvas","HW2",40,40,600,600);
	//set options
	gStyle->SetOptStat(1); //turns on(1)/off(0) stat box
	gStyle->SetOptFit(1);  //turns on(1)/off(0) fit box
	c1->ToggleEventStatus(); //turns on event status bar
	if(errors){g = new TGraphErrors(n,x,y,sx,sy);}
	else{g = new TGraph(n,x,y);}
	// g->SetLineColor(2);
	// g->SetLineWidth(4);
	// g->SetMarkerColor(4);
	g->SetMarkerStyle(21);
	g->SetTitle("HW2");
	g->GetXaxis()->SetTitle("X");
	g->GetYaxis()->SetTitle("Y");
	//   c1->SetLogx();
	g->Fit(opt);
	g->Draw("ADP");
	c1->Update();
}
//took fill method from Dr. Brash
void fill(){
	int i=0;
	while(!feof(f)){
		fscanf(f,"%lf %lf %lf\n",&x[i],&y[i],&sy[i]);
		printf("%i %f %f %f\n",i,x[i],y[i],sy[i]);
		sx[i]=0.0;
		i++;n++;
	}
}
