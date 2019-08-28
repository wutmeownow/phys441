
using namespace std;

Int_t m=15;
Double_t x[15]={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
Double_t y[15]={1.6711,2.00994,2.26241,2.18851,2.33006,2.42660,2.48424,2.63729,2.77163,2.89610,2.89083,3.08081,3.05305,3.24079,3.36212};
Double_t Err[15];
Double_t YFit[15];
Double_t ChiSqr;
Int_t n;

void main(){
	TCanvas *c1=new TCanvas("c1","Linear Fit",900,900);
	c1->Divide(2,2,.01,.01);
	c1->cd(1);
	TGraph *gr=new TGraph(15,x,y);
	gr->Draw("A*");
	NoErr();
	TGraph *gr1=new TGraph(15,x,YFit);
	gr1->SetLineWidth(3);
	gr1->Draw("C");

	c1->cd(2);
	gr->Draw("A*");
	SErr();
	TGraph *gr2=new TGraphErrors(15,x,YFit,0,Err);
	gr2->SetLineWidth(3);
	gr2->Draw("C");

	c1->cd(3);
	gr->Draw("A*");
	DErr();
	TGraph *gr3=new TGraph(15,x,YFit);
	gr3->SetLineWidth(3);
	gr3->Draw("C");

	c1->cd(4);
	gr->Draw("A*");
	polyFit();
	TGraph *gr4=new TGraph(15,x,YFit);
	gr4->SetLineWidth(3);
	gr4->Draw("C");
}

void NoErr(){		//No Error
	n=2;
	Int_t i=0; Int_t j=0; Int_t k=0;
	TMatrixD X(m,n); TMatrixD XT(n,m); Double_t A[2];
	for(i=0;i<m;i++){
		for(j=0;j<n;j++){
			X[i][j]=pow(x[i],j);
		}
	}
	XT=XT.Transpose(X);
	TMatrixD XTX(n,n); XTX=XT*X; XTX.InvertFast();
	for(i=0;i<n;i++){
		A[i]=0;
		for(j=0;j<n;j++){
			for(k=0;k<m;k++){
				A[i]+=XTX[i][j]*XT[j][k]*y[k];
			}
		}
	}
	for(i=0;i<m;i++){
		for(j=0;j<n;j++){
			YFit[i]+=X[i][j]*A[j];
		}
	}
	for(i=0;i<m;i++){
		ChiSqr+=pow((y[i]-YFit[i]),2);
	}
	cout<<ChiSqr<<"\n";
}

void SErr(){			//Same Error
	for(int i=0;i<15;i++){Err[i]=.01;}
	Fit();
}

void DErr(){			//Different Error
	for(int i=0;i<15;i++){Err[i]=.01;if(i>10 || i==1){Err[i]+=.04;}}
	Fit();
}

void polyFit(){
	Int_t i,j,k;Int_t N=15;Int_t M=3;
	for(i=0;i<15;i++){Err[i]=1;}
	Double_t b[15]; TMatrixD A(N,M); 
	TMatrixD AT(M,N);
	for(i=0;i<N;i++){
		b[i]=y[i]/Err[i];
		for(j=0; j<M; j++){A[i][j]= pow(x[i],j)/Err[i];}  
		}
	AT=AT.Transpose(A); 
	TMatrixD C(M,M); TMatrixD Cinv(M,M);
	C=AT*A; C.InvertFast();
	Double_t a_fit[3];
	for(k=0;k<M;k++){
		a_fit[k]=0.0;
		for(j=0;j<M;j++){
			for(i=0;i<N;i++){a_fit[k]+=C[k][j]*A[i][j]*b[i];}
		}
	}

	Double_t da[3];
	for(j=0;j<M;j++){da[j]=pow(C[j][j],.5);}                 

	ChiSqr=0;
	for(i=0;i<N;i++){
		YFit[i]=0;
		for(j=0;j<M;j++){YFit[i]+=a_fit[j]*pow(x[i],j);}  
		double delta=(y[i]-YFit[i]);
		ChiSqr+=delta*delta;
		}
	cout<<ChiSqr<<"\n";
}

void Fit(){
	Int_t i,j,k;Int_t N=15;Int_t M=2;
	Double_t b[15]; TMatrixD A(N,M); 
	TMatrixD AT(M,N);
	for( i=0;i<N;i++) {
		b[i]=y[i]/Err[i];
		for(j=0; j<M; j++){A[i][j]= pow(x[i],j)/Err[i];}  
	}
	AT=AT.Transpose(A); 
	TMatrixD C(M,M); TMatrixD Cinv(M,M);
	C=AT*A; C.InvertFast();
	Double_t a_fit[2];
	for(k=0;k<M;k++){
		a_fit[k]=0.0;
		for(j=0;j<M;j++){
			for(i=0;i<N;i++ ){a_fit[k]+=C[k][j]*A[i][j]*b[i];}
		}
	}

	Double_t sig_a[2];
	for(j=0;j<M;j++){sig_a[j] = pow(C[j][j],.5);}                 

	ChiSqr=0;
	for(i=0;i<N;i++) {
		YFit[i]=0;
		for(j=0;j<M;j++){YFit[i]+=a_fit[j]*pow(x[i],j);}  
		double delta=(y[i]-YFit[i])*Err[i];
		ChiSqr+=delta*delta;
		}
	cout<<ChiSqr<<"\n";
}