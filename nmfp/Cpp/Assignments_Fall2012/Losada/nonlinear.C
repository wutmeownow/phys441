#include <ostream>
#define _USE_MATH_DEFINES
#include <math.h>
#include <TMatrixD.h>

//**************USER OPTIONS*******************************\\
/***/ const bool errors = true; //true if using error	
/***/ FILE *f = fopen("nonlinear.dat","r");			
//********************************************************\\
//data arrays
Double_t x[10000],y[10000],sx[10000],sy[10000];
int n=0;
//methods
void fill();
void graph();

//MAIN
void nonlinear(){
fill();
TMatrixD beta_old = TMatrixD(2,1);


//guess
beta_old[0][0] = .2; //A
beta_old[1][0] = .4; //B
double diff=1;


for(int r=0;r<10;r++){
//***FIND JACOBIAN***\\
TMatrixD Jacobian = TMatrixD(n,2);
for(int i=0; i<n; i++){
	Jacobian[i][0] =  x[i]/(beta_old[1][0]+x[i]);
	Jacobian[i][1] =  (beta_old[0][0]*x[i])/(pow((beta_old[1][0]+x[i]),2));
}    
//for(int i=0;i<n;i++){cout<<i<<"  J0: "<<Jacobian[i][0]<<"  J1: "<<Jacobian[i][1]<<endl;}

//***FIND TRANSPOSED JACOBIAN***\\
TMatrixD Transpose(TMatrixD::kTransposed, Jacobian);
//***FIND WEIGHTS***\\
TMatrixD W = TMatrixD(n,n);
for(int i=0;i<n;i++){
	W[i][i]=1/pow(sy[i],2);
}

//***FIND DELTA Y***\\
TMatrixD dy = TMatrixD(n,1); 
for(int i=0;i<n;i++){
   dy[i][0]=y[i]-(beta_old[0][0]*x[i])/(beta_old[1][0]+x[i]);
}
//Find delta_beta
TMatrixD TW(Transpose,TMatrixD::kMult,W);
TMatrixD TWJ(TW,TMatrixD::kMult,Jacobian);
TMatrixD TWY(TW,TMatrixD::kMult,dy);
TWJ.InvertFast();
TMatrixD db(TWJ,TMatrixD::kMult,TWY);
cout<<"==================================="<<endl<<"+++++++++++++++++++++++++++++++++++"<<endl;
//***FIND BETA NEW***\\
TMatrixD beta_new = TMatrixD(2,1);
for(int i=0;i<2;i++){
	beta_new[i][0]=beta_old[i][0]+db[i][0];
	cout<<"Beta["<<i<<"] : "<<beta_new[i][0]<<endl;
}
diff = db[0][0]/beta_new[0][0];
cout<<"DIFF:  "<<diff<<endl;

beta_old[0][0]=beta_new[0][0];
beta_old[1][0]=beta_new[1][0];

}
}






















void graph(){
	TCanvas *c1 = new TCanvas("canvas","HW2",40,40,600,600);
	//set options
	gStyle->SetOptStat(0); //turns on(1)/off(0) stat box
	gStyle->SetOptFit(0);  //turns on(1)/off(0) fit box
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
	g->Draw("ADP");
	c1->Update();
}
void fill(){
int i=0;
	while(!feof(f)){
		fscanf(f,"%lf %lf %lf\n",&x[i],&y[i],&sy[i]);
//		printf("%i %f %f %f\n",i,x[i],y[i],sy[i]);
		sx[i]=0.0;
		i++;n++;
	}
}
