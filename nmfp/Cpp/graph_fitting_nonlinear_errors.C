#include <ostream>
#include "TMatrixD.h"
#include "TRandom.h"

Double_t fitfunction(Double_t *x, Double_t *par)
{
	Double_t f = par[0]*x[0]/(par[1]+x[0]);
	return f;	
}

Double_t jacobian_beta1(Double_t *x, Double_t *par)
{	
	Double_t f = -x[0]/(par[1]+x[0]);
	return f;
}

Double_t jacobian_beta2(Double_t *x, Double_t *par)
{
	Double_t f = par[0]*x[0]/((par[1]+x[0])*(par[1]+x[0]));
	return f;
}

void graph_fitting_nonlinear_errors() {
  
   // Set the order of the fitting polynomial here.
   Int_t beta_order = 2;

   const Int_t m = 7;
   Double_t x[m], y[m], ex[m],ey[m];
   Double_t xvalue[1];
   Double_t par_actual[2];
   par_actual[0]=0.3797;
   par_actual[1]=0.5111;
   Int_t i;

   x[0]=0.038;
   x[1]=0.194;
   x[2]=0.425;
   x[3]=0.626;
   x[4]=1.253;
   x[5]=2.500;
   x[6]=3.740;

   TRandom r;
   
   for(i=0;i<m;i++){
	   xvalue[0]=x[i];
	   Double_t rand=r.Gaus(0.0,0.005);
	   y[i]=fitfunction(xvalue,par_actual)+rand;
	   ex[i]=0.0;
	   ey[i]=0.015;
   }
   
   const Int_t n = beta_order;
   Int_t k = 0;
   Int_t j =0;

   TMatrixD Jacobian(m,n);
   TMatrixD JacobianT(n,m);
   TMatrixD Weights(m,m);
   TMatrixD JTW(n,m);
   TMatrixD residuals(m,1);
   TMatrixD JTWr(n,1);
   TMatrixD WJ(m,n);
   TMatrixD JTWJ(n,n);
   TMatrixD betas(n,1);
   Double_t det;
   Double_t jtwj_array[n][n];

   betas[0][0]=0.90;
   betas[1][0]=0.20;
   Double_t parameter_matrix[n];
   Double_t parameter_matrix_dbeta[n];
   parameter_matrix[0]=betas[0][0];
   parameter_matrix[1]=betas[1][0];
   Double_t jacobian;
   Double_t function_value;
   Double_t dbetamax=10000;
   Double_t dbeta=0;
   Double_t epsilon=0.000001;
   Double_t f0, f1, epsilon_beta=0.005;

   Int_t jacobian_flag = 1;

   while (dbetamax > epsilon){
   	for (i=0;i<m;i++){
	   	xvalue[0]=x[i];
	   	function_value = fitfunction(xvalue,parameter_matrix);
	   	residuals[i][0]=(y[i]-function_value);
		for (k=0;k<m;k++){
			if(i == k){
				Weights[i][k]=1.0/(ey[i]*ey[i]);
			}else{
				Weights[i][k]=0.0;
			}
		}

// Calculate Jacobian from numerical derivative
		if(jacobian_flag == 1){
			for (j=0;j<n;j++){
				for (k=0; k<n;k++){
						if (k==j){
							parameter_matrix_dbeta[k]=parameter_matrix[k]+epsilon_beta;
							}else
							{
							parameter_matrix_dbeta[k]=parameter_matrix[k];
							}
				}
				f0 = fitfunction(xvalue,parameter_matrix);
				f1 = fitfunction(xvalue,parameter_matrix_dbeta);
				jacobian = (f0-f1)/epsilon_beta;
		       		//cout << "Jacobian: " << i << " " << j << " " << jacobian << endl;
				Jacobian[i][j]=jacobian;
			}
		}else{
							
// Calculate Jacobian from pre-programmed function
			for (j=0;j<n;j++){
				if (j==0){	
					jacobian = jacobian_beta1(xvalue,parameter_matrix);
			       		Jacobian[i][j]=jacobian;
				}else
				{	
					jacobian = jacobian_beta2(xvalue,parameter_matrix);
		       			Jacobian[i][j]=jacobian;
				}	
			}
		}
	}


   	TMatrixD JacobianT(TMatrixD::kTransposed,Jacobian);
	TMatrixD JTW(JacobianT,TMatrixD::kMult,Weights);     		
   	TMatrixD JTWr(JTW,TMatrixD::kMult,residuals);

	TMatrixD WJ(Weights,TMatrixD::kMult,Jacobian);
   	TMatrixD JTWJ(JacobianT,TMatrixD::kMult,WJ);

   	JTWJ.InvertFast(&det);
        cout << "Inverse JTJW:" << endl;
        for (i=0;i<n;i++){
            for (j=0;j<n;j++){
                cout << JTWJ[i][j] << "   ";
                jtwj_array[i][j]=JTWJ[i][j];
            }
            cout << endl;
        }

   	TMatrixD Delta(JTWJ,TMatrixD::kMult,JTWr);

	dbetamax = 0;

   	for (j=0;j<n;j++){
	   	parameter_matrix[j]=parameter_matrix[j]-Delta[j][0];
		dbeta = fabs(Delta[j][0]/parameter_matrix[j]);
		if (dbeta > dbetamax){dbetamax = dbeta;}
   	}	
   }


   Double_t error_sum=0;
   Double_t yfit=0;
   Double_t error[m];
   for (j=0; j<m; j++){
	   	xvalue[0]=x[j];
	   	yfit = fitfunction(xvalue,parameter_matrix);
           	cout << " i y yfit error = " << j << " " << y[j] << " " << yfit << " " << (yfit-y[j])/ey[j] << endl; 
	   	error_sum = error_sum + pow(((yfit-y[j])/ey[j]),2);
	   	yfit = 0;
   }
   

   //gStyle->SetOptFit(kFALSE);	
   gStyle->SetOptFit(1);	
   TCanvas *c1 = new TCanvas("c1","NonLinear Errors",200,10,700,500);

   c1->SetFillColor(42);
   c1->SetGrid();
   	
   TGraphErrors *gr = new TGraphErrors(m,x,y,ex,ey);
   TF1 *pfit1 = new TF1("fitfunction",fitfunction,0.0,4.0,2);
   pfit1->SetParameters(0.9,0.2);
   pfit1->SetParNames("Vmax","Km");
   
   gr->SetMarkerStyle(21);
   gr->SetTitle("NonLinear Fit");
   gr->GetXaxis()->SetTitle("[S]");
   gr->GetYaxis()->SetTitle("Rate");
   gr->GetHistogram()->SetMaximum(0.45);
   gr->GetHistogram()->SetMinimum(0.0);


   pfit1->SetLineColor(2);
   gr->Fit("fitfunction","V");
   Double_t pfit1chi2 = pfit1->GetChisquare();
   Double_t pfit1ndf = pfit1->GetNDF();
   Double_t pfit1chi2ndf = pfit1chi2/pfit1ndf;
   gr->Draw("AP");

   Double_t chi2=error_sum/(m-n);

   cout << endl;
   cout << " chi^2          = " << chi2*(m-n) << endl;
   cout << " NDf            = " << (m-n) << endl;
   cout << endl;
   
   for (k=0;k<n;k++){
	   cout << "beta" << k+1;
	   for (i=0;i<n;i++){
   	                cout << "    " << jtwj_array[k][i];
	   }
	   cout << endl;
           error[k]=pow(jtwj_array[k][k],0.5);
   }
   
   cout << endl;
   for (k=0;k<n;k++){
   	cout << " beta[" << k+1 << "] = " << parameter_matrix[k] << " +/- " << error[k] << endl;
   }	
   cout << endl;
   
   // TCanvas::Update() draws the frame, after which one can change it
   c1->Update();
   c1->GetFrame()->SetFillColor(21);
   c1->GetFrame()->SetBorderSize(12);
   c1->Modified();
}
