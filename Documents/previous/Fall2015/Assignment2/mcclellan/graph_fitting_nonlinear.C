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

void graph_fitting_nonlinear() {
  
   //FILE *f = fopen("nonlinear.dat","r");

   // Set the order of the fitting polynomial here.
   Int_t beta_order = 2;


   const Int_t m = 7;
   Double_t x[m], y[m], ex[m],ey[m];
   Double_t xvalue[1];
   Double_t par_actual[1];
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

   y[0]=0.050;
   y[1]=0.127;
   y[2]=0.094;
   y[3]=0.2122;
   y[4]=0.2729;
   y[5]=0.2665;
   y[6]=0.3317;

   ey[0]=0.010;
   ey[1]=0.010;
   ey[2]=0.030;
   ey[3]=0.030;
   ey[4]=0.030;
   ey[5]=0.020;
   ey[6]=0.010;

   TRandom r;


   /*for(i=0;i<m;i++){
	   xvalue[0]=x[i];
	   Double_t rand=r.Gaus(0.0,0.005);
	   y[i]=fitfunction(xvalue,par_actual)+rand;
   }*/

   // number of parameters
   const Int_t n = beta_order;

   // iteration number
   Int_t k = 0;

   cout << "test2" << endl;

   Int_t j =0;
   TMatrixD Jacobian(m,n);
   TMatrixD residuals(m,1);
   TMatrixD betas(n,1);
   TMatrixD W_error(m,m);
   Double_t det;

   cout << "test3" << endl;

   for (i=0; i<m; i++){
	for (j=0; j<m; j++){
		if (i == j) {
			W_error[i][j] = 1.0/pow(ey[i],2);
		}
		else {
			W_error[i][j] = 0;
		}
	}
   }

   cout << "test4" << endl;

   betas[0][0]=0.30;
   betas[1][0]=0.75;
   Double_t parameter_matrix[n];
   Double_t parameter_matrix_dbeta[n];
   parameter_matrix[0]=betas[0][0];
   parameter_matrix[1]=betas[1][0];
   Double_t jacobian;
   Double_t function_value;
   Double_t dbetamax=10000;
   Double_t dbeta=0;
   Double_t epsilon=0.000001;
   Double_t f0, f1, epsilon_beta=0.01;

      cout << "test5" << endl;

   while (dbetamax > epsilon){
   	for (i=0;i<m;i++){
	   	xvalue[0]=x[i];
	   	function_value = fitfunction(xvalue,parameter_matrix);
	   	residuals[i][0]=y[i]-function_value;
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

   cout << dbetamax << endl;

   	TMatrixD JacobianT(TMatrixD::kTransposed,Jacobian);

	TMatrixD JTW(JacobianT,TMatrixD::kMult,W_error);

	TMatrixD JTr(JacobianT,TMatrixD::kMult,residuals);

   	TMatrixD JTWJ(JTW,TMatrixD::kMult,Jacobian);

   	JTWJ.InvertFast(&det);

   	TMatrixD Delta(JTWJ,TMatrixD::kMult,JTr);

        cout << "Delta = " << Delta[0][0] << endl;

	dbetamax = 0;

   	for (j=0;j<n;j++){
	   	parameter_matrix[j]=parameter_matrix[j]-Delta[j][0];
		dbeta = fabs(Delta[j][0]/parameter_matrix[j]);
		if (dbeta > dbetamax){dbetamax = dbeta;}
   	}

    cout << dbetamax << endl;	
   }
   cout << "test8" << endl;


   Double_t error_sum=0;
   Double_t yfit=0;
   Double_t error[m];
   for (j=0; j<m; j++){
	   	xvalue[0]=x[j];
	   	yfit = fitfunction(xvalue,parameter_matrix);
           	cout << " i y fit = " << j << " " << y[j] << " " << yfit << endl; 
	   	error_sum = error_sum + pow((yfit-y[j]),2);
	   	yfit = 0;
   }

   const int nbins=101;

   Double_t pars[n];
   Double_t s[nbins][nbins];
   Double_t b1[nbins],b2[nbins];

   Double_t xwidth = 2.5;
   Double_t ywidth = 2.5;
   Double_t zmax = 50.0;
   Double_t xlow = parameter_matrix[0]-xwidth/2.0;
   Double_t xhigh = parameter_matrix[0]+xwidth/2.0;
   Double_t ylow = parameter_matrix[1]-ywidth/2.0;
   Double_t yhigh = parameter_matrix[1]+ywidth/2.0;

   h3 = new TH3D("h3","S-squared Histogram",101,xlow,xhigh,101,ylow,yhigh,100,0.0,zmax);
   for (j=0; j<nbins; j++){
	   pars[0]=parameter_matrix[0]+(j-(nbins-1.0)/2.0)/(nbins-1.0)*xwidth;
	   b1[j]=pars[0];
	   for (k=0; k<=100; k++){
		   s[j][k]=0.0;
		   pars[1]=parameter_matrix[1]+(k-(nbins-1.0)/2.0)/(nbins-1.0)*ywidth;
		   b2[k]=pars[1];
		   for (i=0;i<m;i++){
			   xvalue[0]=x[i];
			   yfit=fitfunction(xvalue,pars);
			   s[j][k]=s[j][k]+pow((y[i]-yfit),2);
		   }
		   cout << j << " " << b1[j] << " " << k << " " << b2[k] << " " << s[j][k] << endl;
		   h3->Fill(b1[j],b2[k],s[j][k]);
	   }
   }

   const Double_t numsteps = 10000;
   Double_t x_fit[m*numsteps];
   Double_t y_fit[m];
   Double_t y_fit_graph[m*numsteps];

   

   

   //gStyle->SetOptFit(kFALSE);	
   gStyle->SetOptFit(1);	
   TCanvas *c1 = new TCanvas("c1","Non Linear Fit",200,10,700,500);
   TCanvas *c2 = new TCanvas("c2","S-squred",200,600,700,500);
   c1->SetFillColor(42);
   c1->SetGrid();
   c2->SetFillColor(42);
   c2->SetGrid();
   
   
   c2->cd();
   //c2->SetLogz();
   h3->GetXaxis()->SetTitle("Beta1");
   h3->GetYaxis()->SetTitle("Beta2");
   h3->GetZaxis()->SetTitle("S");
   h3->SetMarkerColor(1);
   h3->Draw();

   c1->cd();

   for (i=0; i<m; i++){
        xvalue[0] = x[i];
	y_fit[i] = fitfunction(xvalue,parameter_matrix);
   }

   for (i=0; i<=numsteps; i++){
        x_fit[i] = (m/numsteps)*i;
	xvalue[0] = x_fit[i];
	y_fit_graph[i] = fitfunction(xvalue,parameter_matrix);
   }

   Double_t CHI_2 = 0;
   Double_t NDF = 4;

   for (i=0; i<m; i++) {
	CHI_2 += pow(y[i] - y_fit[i],2.0);
   }

   Double_t uncertain[2];

   for (i=0; i<2; i++) {
	uncertain[i] = sqrt(parameter_matrix[i]*CHI_2/NDF);
   }

   gr = new TGraphErrors(m,x,y,0,ey);
   /*TF1 *pfit1 = new TF1("fitfunction",fitfunction,0.0,4.0,2);
   pfit1->SetParameters(0.30,0.75);
   pfit1->SetParNames("Vmax","Km");*/
   
   gr->SetMarkerStyle(21);
   gr->SetTitle("NonLinear Fit");
   gr->GetXaxis()->SetTitle("[S]");
   gr->GetYaxis()->SetTitle("Rate");
//   TAxis *axis = gr->GetXaxis();
//   axis->SetLimits(-5.,5.);
   gr->GetHistogram()->SetMaximum(0.45);
   gr->GetHistogram()->SetMinimum(0.0);

   /*pfit1->SetLineColor(2);
   gr->Fit("fitfunction","V");
   Double_t pfit1chi2 = pfit1->GetChisquare();
   Double_t pfit1ndf = pfit1->GetNDF();
   Double_t pfit1chi2ndf = pfit1chi2/pfit1ndf;*/
//   printf("Fit 1: %f %f \n",pfit1chi2,pfit1ndf);
   //gr->Draw("AP");

  gr2 = new TGraph(numsteps,x_fit,y_fit_graph);
   gr2->SetMarkerStyle(6);
   gr2->SetMarkerColor(4);
   gr2->SetLineColor(4);
   //gr2->Draw("AL");
   mg = new TMultiGraph();
   mg->Add(gr,"P");
   mg->Add(gr2,"P");
   mg->Draw("A");

   Double_t chi2=error_sum/(m-n);

   cout << endl;
   cout << " chi^2          = " << chi2*(m-n) << endl;
   cout << " NDf            = " << (m-n) << endl;
   cout << endl;
   
   for (k=0;k<n;k++){
	   cout << "beta" << k+1;
	   for (i=0;i<n;i++){
   	                cout << "    " << chi2*JTWJ[k][i];
	   }
	   cout << endl;
           error[k]=pow(chi2*JTWJ[k][k],0.5);
   }
   
   cout << endl;
   for (k=0;k<n;k++){
   	cout << " beta[" << k+1 << "] = " << parameter_matrix[k] << " +/- " << error[k] << endl;
   }	
   cout << endl;

   cout << " chi squared = " << CHI_2 << endl;
   cout << " NDF = " << NDF << endl;

   for (i=0; i<2; i++) {
	cout << " Uncertainty in beta " << i << " = " << uncertain[i] << endl;
   }
   
   // TCanvas::Update() draws the frame, after which one can change it
   c1->Update();
   c1->GetFrame()->SetFillColor(21);
   c1->GetFrame()->SetBorderSize(12);
   c1->Modified();
}
