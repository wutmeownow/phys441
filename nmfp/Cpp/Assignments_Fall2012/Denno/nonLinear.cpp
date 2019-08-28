#include "TMatrixD.h"

using namespace std;

void main(){
	const Int_t n=7;
	Int_t i,j,k;
	Double_t x[7]={.038,.194,.425,.626,1.253,2.5,3.74};
	Double_t y[7]={.05,.127,.094,.2122,.2729,.2665,.3317};
	Double_t err[7]={.01,.01,.03,.03,.03,.02,.01};
	Double_t b_old[2]={.2,.4}; 
	Double_t b_new[2];
	Double_t ChiSq;
	Double_t dy[7];
	Double_t WTdy[7]; 
	Double_t db[2];
	TMatrixD J(7,2);
	TMatrixD W(n,n); 
	TMatrixD JT(2,n); 
	TMatrixD WT(n,n);
	TMatrixD WTJ(2,n);
	for(i=0;i<5;i++){
		for(j=0;j<n;j++){
			J[j][0]=x[j]/(b_old[0]+x[j]);
			J[j][1]=(b_old[0]*x[j])/(pow((b_old[1]+x[j]),2));
		}
		JT=JT.Transpose(J);
		for(j=0;j<n;j++){
			for(k=0;k<n;k++){
				if(j == k){
					W[j][k]=1.0/pow(err[j],2);
				}else{
					W[j][k]=0.0;
				}
			}
		}
		for(j=0;j<n;j++){
			dy[j]=y[j]-(b_old[0]*x[j])/(b_old[1]+x[j]);
		}
		WTJ=JT*W; 
		cout << "Got to here - 4!" << endl;
		for(j=0;j<7;j++){
			WTdy[j]=0;
			for(k=0;k<7;k++){WTdy+=WT[j][k]*dy[k];}
		}
		for(j=0;j<2;j++){
			for(Int_t k=0;k<7;k++){db[k]+=WTJ[k][j]*WTdy[j];}
		}
		for(j=0;j<2;j++){
			b_new[j]=b_old[j]+db[j];
		}
		b_old[0]=b_new[0];
		b_old[1]=b_new[1];
	}
	Double_t yf[7];
	for(i=0;i<n;i++){
		yf[j]=(b_o[0]*x[j])/(beta_old[1]+x[j]);
	}
	TCanvas *c1=new TCanvas("c1","Non-Linear Fit",600,600);
	TGraph *gr=new TGraph(7,x,y);
	gr->Draw("A*");
	TGraph *gr1=new TGraph(7,x,yf);
	gr1->Draw("C");
}
