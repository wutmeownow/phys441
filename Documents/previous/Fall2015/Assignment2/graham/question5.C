#include <ostream>
#include <vector>
#include <sstream>
#include <string>
#include <algorithm>
#include "TMatrixD.h"
#include "TRandom.h"

//X Values for the Function
Double_t* xfunction(){
	Double_t val[15] ={1.0,2.0,3.0,4.0,5.0,6.0,7.0,8.0,
		  9.0,10.0,11.0,12.0,13.0,14.0,15.0};
	Double_t *par = new Double_t[15];
	std::copy(val, val+15, &par[0]);
	return par;
}

//Y Values for the Function
Double_t* yfunction(){
	Double_t val[15] = {1.6711,2.00944,2.26241,2.18851,2.33006,
		  2.42660,2.48424,2.63729,2.77163,2.89610,
		  2.89083,3.08081,3.05305,3.24079,3.36212};
	Double_t *par = new Double_t[15];
	std::copy(val, val+15, &par[0]);
	return par;
}

//Error on the Data Points
Double_t* sigmaFunction(Double_t* y){
	Double_t *par = new Double_t[15];
	for(int i=0;i<15;i=i+2){
		par[i] = 0.378;
	}
	for(int i=1;i<15;i=i+2){
		par[i] = 0.1;
	}
	return par;
}

void question5() {
	const Int_t n = 15;
	//vector is populated with chisquare values for all values of m
	std::vector<Double_t> chis;
	for(int attempt=0; attempt < n-1;attempt++){
		// Order of polynomial change to change plotting
		Int_t m = attempt;
		Double_t *x = xfunction();
		Double_t *y = yfunction();
		Double_t *sigma = sigmaFunction(y);
		const Int_t m_params = m+1;

		TMatrixD a(m_params,m_params);
		TMatrixD aold(m_params,m_params);
		TMatrixD v(m_params,1);
		Double_t det;
		Double_t edet;

		for (Int_t k=0;k<=m;k++){
			v[k][0]=0;
			for (Int_t i=0; i<n; i++){
					v[k][0]+=(y[i]*pow(x[i],k))/pow(sigma[i],2.0);
			}
			for (Int_t j=0; j<=m; j++){
				a[k][j]=0;
				   for (Int_t i=0; i<n; i++){
						a[k][j]+=pow(x[i],k+j)/pow(sigma[i],2.0);
				   }
			}
		}

		aold = a;
		a.InvertFast(&det);

		TMatrixD coeff(a,TMatrixD::kMult,v);
		Double_t chisquare=0.0;
		for(Int_t i=0; i<n; i++){
			Double_t yfit = 0.0;
			for(Int_t j=0; j<=m; j++){
				yfit+=coeff[j][0]*pow(x[i],j);
			}
			chisquare+=pow((y[i]-yfit)/sigma[i],2.0);
		}
		Double_t ndf = n-m-1.0;
		chis.push_back(chisquare/ndf);
		TMatrixD error(m_params,1);
		for(Int_t l=0;l<=m;l++){
			error[l][0] = pow(a[l][l],0.5);
		}
	}
	Double_t bestOrder = 0;
	Double_t min = fabs(chis[0]-1.0);
	for (int i=1;i<n-1;i++){
		Double_t newMin = fabs(chis[i]-1.0);
		if(newMin < min){
			min = newMin;
			bestOrder = i;
		}
	}
	cout<<"The Best Order Polynomial is: "<<bestOrder<<endl;
	cout<<"The CHI^2/NDF is: "<<chis[bestOrder]<<endl;
}
