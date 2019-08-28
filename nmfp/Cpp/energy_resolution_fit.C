#include <ostream>
#include "TMatrixD.h"

Double_t fitfunction(Double_t *x, Double_t *par)
{
	Float_t xx = x[0];
    Float_t binsize = x[1];
	Double_t f = binsize*par[0]/sqrt(2.0*3.14159265*pow(par[2],2))*pow(2.718281828,-0.5*pow((xx-par[1]),2)/pow(par[2],2));
//	cout << "function: " << xx << " " << f << endl;
	return f;	
}

Double_t myfitfunction(Double_t *x, Double_t *par)
{
	Float_t xx = x[0];
	Double_t f = 0.40*par[0]/sqrt(2.0*3.14159265*pow(par[2],2))*pow(2.718281828,-0.5*pow((xx-par[1]),2)/pow(par[2],2));
    //	cout << "function: " << xx << " " << f << endl;
	return f;
}


Double_t jacobian_beta1(Double_t *x, Double_t *par)
{	
	Float_t xx = x[0];
    Float_t binsize = x[1];
	Double_t f = -binsize/sqrt(2.0*3.14159265*pow(par[2],2))*pow(2.718281828,-0.5*pow((xx-par[1]),2)/pow(par[2],2));
//	cout << "beta1: " << xx << " " << f << endl;
	return f;
}

Double_t jacobian_beta2(Double_t *x, Double_t *par)
{	
	Float_t xx = x[0];
    Float_t binsize = x[1];
	Double_t f = -binsize*((xx-par[1])/pow(par[2],2))*par[0]/sqrt(2.0*3.14159265*pow(par[2],2))*pow(2.718281828,-0.5*pow((xx-par[1]),2)/pow(par[2],2));
//	cout << "beta2: " << xx << " " << f << endl;
	return f;
}

Double_t jacobian_beta3(Double_t *x, Double_t *par)
{	
	Float_t xx = x[0];
    Float_t binsize = x[1];
	Double_t f = -binsize*((pow((xx-par[1]),2)/pow(par[2],2)-1)/par[2])*par[0]/sqrt(2.0*3.14159265*pow(par[2],2))*pow(2.718281828,-0.5*pow((xx-par[1]),2)/pow(par[2],2));
//	cout << "beta3: " << xx << " " << f << endl;
	return f;
}


void graph_fitting_gaussian_errors() {
  
   //gStyle->SetOptFit(kFALSE);	
   gStyle->SetOptFit(1);	
   TCanvas *c1 = new TCanvas("c1","Cubic Data",200,10,700,500);
   FILE *f = fopen("gaussian_errors.dat","r");

   // Set the order of the fitting polynomial here.
   Int_t beta_order = 3;

   c1->SetFillColor(42);
   c1->SetGrid();

   const Int_t n = 10000;
   Double_t x[n], y[n], ex[n],ey[n];
   Int_t i=0;

   while (!feof(f)){
	  fscanf(f,"%lf %lf %lf\n",&x[i],&y[i],&ey[i]);
          printf("%i %f %f %f\n",i,x[i],y[i],ey[i]);
	  ex[i]=0.0;
	  i++;
   }

   const Int_t n = i;
   const Int_t m = beta_order;
   Int_t k = 0;
   Int_t j =0;
    Double_t step_size = (x[n-1]-x[0])/n;
    cout << "Step size = " << step_size << endl;

   TMatrixD Jacobian(n,m);
   TMatrixD Weights(n,n);
   TMatrixD residuals(n,1);
   TMatrixD betas(m,1);
   Double_t det;

   betas[0][0]=20000;
   betas[1][0]=45.0;
   betas[2][0]=5.0;
   Double_t parameter_matrix[m];
   Double_t parameter_matrix_dbeta[m];
   parameter_matrix[0]=betas[0][0];
   parameter_matrix[1]=betas[1][0];
   parameter_matrix[2]=betas[2][0];
   Double_t jacobian;
   Double_t function_value;
   Double_t xvalue[2];
   Double_t dbetamax=10000;
   Double_t dbeta=0;
   Double_t epsilon=0.001;
   Double_t f0, f1, epsilon_beta=0.01;

   while (dbetamax > epsilon){
   	for (i=0;i<n;i++){
	   	xvalue[0]=x[i];
        xvalue[1]=step_size;
	   	function_value = fitfunction(xvalue,parameter_matrix);
	   	residuals[i][0]=(y[i]-function_value);
		for (k=0;k<n;k++){
			if(i == k){
				Weights[i][k]=1.0/(ey[i]*ey[i]);
			}else{
				Weights[i][k]=0.0;
			}
		}
//	   	cout << "Residual:  " << i << " " << y[i] << " " << function_value << " " << residuals[i][0] << endl; 
//			for (j=0;j<m;j++){
//				for (k=0; k<m;k++){
//						if (k==j){
//							parameter_matrix_dbeta[k]=parameter_matrix[j]+epsilon_beta;
//							}else
//							{
//							parameter_matrix_dbeta[k]=parameter_matrix[j];
//			a				}
//				}
//				f0 = fitfunction(xvalue,parameter_matrix);
//				f1 = fitfunction(xvalue,parameter_matrix_dbeta);
//				jacobian = (f0-f1)/epsilon_beta;
//		       		cout << "Jacobian: " << i << " " << j << " " << jacobian << endl;
//				Jacobian[i][j]=jacobian;
//			}
//	}
							
		for (j=0;j<m;j++){
			if (j==0){	
				jacobian = jacobian_beta1(xvalue,parameter_matrix);
//		       		cout << "Jacobian1: " << i << " " << j << " " << jacobian << endl;
		       		Jacobian[i][j]=jacobian;
			}
			if (j==1){
				jacobian = jacobian_beta2(xvalue,parameter_matrix);
//		       		cout << "Jacobian2: " << i << " " << j << " " << jacobian << endl;
		       		Jacobian[i][j]=jacobian;
			}	
			if (j==2){
				jacobian = jacobian_beta3(xvalue,parameter_matrix);
//		       		cout << "Jacobian3: " << i << " " << j << " " << jacobian << endl;
		       		Jacobian[i][j]=jacobian;
			}
		}
   	}


   	TMatrixD JacobianT(TMatrixD::kTransposed,Jacobian);
	TMatrixD JTW(JacobianT,TMatrixD::kMult,Weights);     		
   	TMatrixD JTWr(JTW,TMatrixD::kMult,residuals);

	TMatrixD WJ(Weights,TMatrixD::kMult,Jacobian);
   	TMatrixD JTWJ(JacobianT,TMatrixD::kMult,WJ);

   	JTWJ.InvertFast(&det);

   	TMatrixD Delta(JTWJ,TMatrixD::kMult,JTWr);

	dbetamax = 0;

   	for (j=0;j<m;j++){
	   	parameter_matrix[j]=parameter_matrix[j]-Delta[j][0];
		dbeta = fabs(Delta[j][0]/parameter_matrix[j]);
		if (dbeta > dbetamax){dbetamax = dbeta;}
//		cout << "Beta: " << j << " " << parameter_matrix[j] << " +/- " << -Delta[j][0] << " " << dbetamax << endl;
   	}	
   }


   Double_t error_sum=0;
   Double_t yfit=0;
   Double_t error[m];
   for (j=0; j<n; j++){
	   	xvalue[0]=x[j];
        xvalue[1]=step_size;
	   	yfit = fitfunction(xvalue,parameter_matrix);
//           	cout << " i y yfit error = " << j << " " << y[j] << " " << yfit << " " << (yfit-y[j])/ey[j] << endl;
	   	error_sum = error_sum + pow(((yfit-y[j])/ey[j]),2);
	   	yfit = 0;
   }

   	
   gr = new TGraphErrors(n,x,y,ex,ey);
   TF1 *pfit1 = new TF1("fitfunction",myfitfunction,15,75,3);
   pfit1->SetParameters(20000,45,5);
   pfit1->SetParNames("Nsamples","Mu","Sigma");
   
   gr->SetMarkerStyle(21);
   gr->SetTitle("Gaussian Fit");
   gr->GetXaxis()->SetTitle("X");
   gr->GetYaxis()->SetTitle("N");
//   TAxis *axis = gr->GetXaxis();
//   axis->SetLimits(-5.,5.);
   gr->GetHistogram()->SetMaximum(1200);
   gr->GetHistogram()->SetMinimum(0.0);


   pfit1->SetLineColor(2);
   gr->Fit("fitfunction","V");
   Double_t pfit1chi2 = pfit1->GetChisquare();
   Double_t pfit1ndf = pfit1->GetNDF();
   Double_t pfit1chi2ndf = pfit1chi2/pfit1ndf;
//   printf("Fit 1: %f %f \n",pfit1chi2,pfit1ndf);
   gr->Draw("AP");

   Double_t chi2=error_sum/(n-m);

   cout << endl;
   cout << " chi^2          = " << chi2*(n-m) << endl;
   cout << " NDf            = " << (n-m) << endl;
   cout << endl;
   
   for (k=0;k<m;k++){
	   cout << "beta" << k+1;
	   for (i=0;i<m;i++){
   	                cout << "    " << JTWJ[k][i];
	   }
	   cout << endl;
           error[k]=pow(JTWJ[k][k],0.5);
   }
   
   cout << endl;
   for (k=0;k<m;k++){
   	cout << " beta[" << k+1 << "] = " << parameter_matrix[k] << " +/- " << error[k] << endl;
   }	
   cout << endl;
   
   // TCanvas::Update() draws the frame, after which one can change it
   c1->Update();
   c1->GetFrame()->SetFillColor(21);
   c1->GetFrame()->SetBorderSize(12);
   c1->Modified();
}
