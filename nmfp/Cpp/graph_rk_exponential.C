// Program to compute the 4th order Runge Kutta approximation to x = Ae^-kt 
#include <iostream>
#include <fstream>
#include "math.h"

using namespace std;

void rk4(double x[], int nX, double t, double tau, 
void (*derivsRK)(double x[], double t, double param[], double deriv[]),
double param[]) {
// Runge-Kutta integrator (4th order)
// Inputs
//   x          Current value of dependent variable
//   nX         Number of elements in dependent variable x^M
//   t          Independent variable (usually time)
//   tau        Step size (usually time step)
//   derivsRK   Right hand side of the ODE; derivsRK is the
//              name of the function which returns dx/dt
//              Calling format derivsRK(x,t,param,dxdt).
//   param      Extra parameters passed to derivsRK
// Output
//   x          New value of x after a step of size tau

  double *F1, *F2, *F3, *F4, *xtemp;
  F1 = new double [nX+1];  F2 = new double [nX+1];
  F3 = new double [nX+1];  F4 = new double [nX+1];
  xtemp = new double [nX+1];

  //* Evaluate F1 = f(x,t).
  (*derivsRK)( x, t, param, F1 );

  //* Evaluate F2 = f( x+tau*F1/2, t+tau/2 ).
  double half_tau = 0.5*tau;
  double t_half = t + half_tau;
  int i;
  for( i=1; i<=nX; i++ )
    xtemp[i] = x[i] + half_tau*F1[i];
  (*derivsRK)( xtemp, t_half, param, F2 );

  //* Evaluate F3 = f( x+tau*F2/2, t+tau/2 ).
  for( i=1; i<=nX; i++ )
    xtemp[i] = x[i] + half_tau*F2[i];
  (*derivsRK)( xtemp, t_half, param, F3 );

  //* Evaluate F4 = f( x+tau*F3, t+tau ).
  double t_full = t + tau;
  for( i=1; i<=nX; i++ )
    xtemp[i] = x[i] + tau*F3[i];
  (*derivsRK)( xtemp, t_full, param, F4 );

  //* Return x(t+tau) computed from fourth-order R-K.
  for( i=1; i<=nX; i++ )
    x[i] += tau/6.*(F1[i] + F4[i] + 2.*(F2[i]+F3[i]));

}

void rka( double x[], int nX, double& t, double& tau, double err,
void (*derivsRK)(double x[], double t, double param[], double deriv[]),
double param[]) {
// Adaptive Runge-Kutta routine
// Inputs
//   x          Current value of the dependent variable
//   nX         Number of elements in dependent variable x
//   t          Independent variable (usually time)
//   tau        Step size (usually time step)
//   err        Desired fractional local truncation error
//   derivsRK   Right hand side of the ODE; derivsRK is the
//              name of the function which returns dx/dt
//              Calling format derivsRK(x,t,param).
//   param      Extra parameters passed to derivsRK
// Outputs
//   x          New value of the dependent variable
//   t          New value of the independent variable
//   tau        Suggested step size for next call to rka

  //* Set initial variables
  double tSave = t;      // Save initial value
  double safe1 = 0.9, safe2 = 4.0;  // Safety factors

  //* Loop over maximum number of attempts to satisfy error bound
  double *xSmall, *xBig;
  xSmall = new double [nX+1];  xBig = new double [nX+1];
  int i, iTry, maxTry = 100;
  for( iTry=1; iTry<=maxTry; iTry++ ) {

    //* Take the two small time steps
    double half_tau = 0.5 * tau;
    for( i=1; i<=nX; i++ )
      xSmall[i] = x[i];
    rk4(xSmall,nX,tSave,half_tau,derivsRK,param);
    t = tSave + half_tau;
    rk4(xSmall,nX,t,half_tau,derivsRK,param);

    //* Take the single big time step
    t = tSave + tau;
    for( i=1; i<=nX; i++ )
      xBig[i] = x[i];
    rk4(xBig,nX,tSave,tau,derivsRK,param);

    //* Compute the estimated truncation error
    double errorRatio = 0.0, eps = 1.0e-16;
    for( i=1; i<=nX; i++ ) {
      double scale = err * (fabs(xSmall[i]) + fabs(xBig[i]))/2.0;
      double xDiff = xSmall[i] - xBig[i];
      double ratio = fabs(xDiff)/(scale + eps);
      errorRatio = ( errorRatio > ratio ) ? errorRatio:ratio;
    }

    //* Estimate new tau value (including safety factors)
    double tau_old = tau;
    tau = safe1*tau_old*pow(errorRatio, -0.20);
    tau = (tau > tau_old/safe2) ? tau:tau_old/safe2;
    tau = (tau < safe2*tau_old) ? tau:safe2*tau_old;

    //* If error is acceptable, return computed values
    if (errorRatio < 1)  {
      for( i=1; i<=nX; i++ )
        x[i] = xSmall[i];
      return;
    }
  }

  //* Issue error message if error bound never satisfied
  cout << "ERROR: Adaptive Runge-Kutta routine failed" << endl;
}

void exponential_rk(double x[], double t, double param[], double deriv[]) {
//  Returns right-hand side of Exponential Decay DE; used by Runge-Kutta routines
//  Inputs
//    x      1D State vector [x v]
//    t      Time
//    param  param[1] = A, param[2]=k
//  Output
//    deriv  Derivative [dx/dt dv/dt]

  //* Compute acceleration
  double A = param[1];
  double k = param[2];

  //* Return derivative [dx[1]/dt]
  deriv[1] = -k*x[1];
  deriv[2] = -k*x[2];
}
         
void graph_rk_exponential() {
   //
   //Modified: Edward J. Brash
   //		
  
   //gStyle->SetOptFit(kFALSE);	
   gStyle->SetOptFit(1);	
   TCanvas *c1 = new TCanvas("c1","Cubic Data",200,10,1400,1000);
   c1->Divide(2,1);
   c1->SetFillColor(42);
   c1->SetGrid();

  //* Set initial position and velocity of the comet.
  double A, k;
  cout << "Enter amplitude of exponential: "; cin >> A;  
  cout << "Enter decay constant of exponential: "; cin >> k;
  double x[1+1], v[1+1], accel[1+1], state[2+1];
  x[1] = A;
  v[1] = -k*A;
  state[1] = x[1]; state[2] = v[1];  // Used by R-K routines
  int nState = 2;  // Number of elements in state vector

  //* Set physical parameters (mass, G*M)
  double param[2+1];  param[1] = A; param[2]=k;
  double adaptErr = 1.e-3;  // Error parameter used by adaptive Runge-Kutta
  double time = 0;

  //* Loop over desired number of steps using specified
  //  numerical method.
  cout << "Enter number of steps: "; 
  int nStep;  cin >> nStep;
  cout << "Enter time step (yr): ";
  double tau;  cin >> tau; 
  cout << "Choose a numerical method:" << endl;
  cout << "1) Euler,       2) Euler-Cromer, "	<< endl
	   << "3) Runge-Kutta, 4) Adaptive R-K: ";
  int method;  cin >> method;
  double *xplot, *vplot, *tplot, *xexact, *vexact;  // Plotting variables
  xplot = new double [nStep+1];  
  vplot = new double [nStep+1];  
  xexact = new double [nStep+1];  
  vexact = new double [nStep+1];  
  tplot = new double [nStep+1];  
  int iStep;
  for( iStep=1; iStep<=nStep; iStep++ ) {  

    //* Record position for plotting.
    xplot[iStep] = x[1];               // Record position for plotting
    vplot[iStep] = v[1];               // Record velocity for plotting
    xexact[iStep] = A*exp(-k*time);               // Record position for plotting
    vexact[iStep] = -A*k*exp(-k*time);               // Record velocity for plotting
    tplot[iStep] = time;               // Record time for plotting
  
    //* Calculate new position and velocity using desired method.
    if( method == 1 ) {
      accel[1] = -k*v[1];   
      x[1] += tau*v[1];             // Euler step
      v[1] += tau*accel[1]; 
      time += tau;  
    } 
    else if( method == 2 ) {
      accel[1] = -k*v[1];   
      v[1] += tau*accel[1]; 
      x[1] += tau*v[1];             // Euler-Cromer step
      time += tau;  
    }
    else if( method == 3 ) {
      rk4( state, nState, time, tau, exponential_rk, param );
      x[1] = state[1];    // 4th order Runge-Kutta
      v[1] = state[2];
      time += tau;   
    }
    else {
      rka( state, nState, time, tau, adaptErr, exponential_rk, param );
      x[1] = state[1];   // Adaptive Runge-Kutta
      v[1] = state[2];
    }
  
  }

  //* Print out the plotting variables: 
  //    thplot, rplot, potential, kinetic
//  ofstream rplotOut("rplot.txt"),
//	   tplotOut("tplot.txt"), energyOut("total.txt"), potentialOut("potential.txt"),
//	   kineticOut("kinetic.txt");
//  int i;
//  for( i=1; i<=nStep; i++ ) {
//    rplotOut << thplot[i] << " " << rplot[i] << endl;
//    tplotOut << tplot[i] << " " << rplot[i] << endl;
//    energyOut << tplot[i] << " " << potential[i]+kinetic[i] << endl;
//    potentialOut << tplot[i] << " " << potential[i] << endl;
//    kineticOut << tplot[i] << " " << kinetic[i] << endl;
//  }

   const Int_t n = nStep;
   Double_t xx[n], yx[n];
   Double_t xv[n], yv[n];
   Double_t xxe[n], yxe[n];
   Double_t xve[n], yve[n];
   Int_t i=0;

   for(i=0;i<n;i++){
	xx[i]=tplot[i+1];
	yx[i]=xplot[i+1];
	xv[i]=tplot[i+1];
	yv[i]=vplot[i+1];
	xxe[i]=tplot[i+1];
	yxe[i]=xexact[i+1];
	xve[i]=tplot[i+1];
	yve[i]=vexact[i+1];
   }

   grx = new TGraph(n,xx,yx);
   grv = new TGraph(n,xv,yv);
   grxe = new TGraph(n,xxe,yxe);
   grve = new TGraph(n,xve,yve);

//   gr->SetLineColor(2);
//   gr->SetLineWidth(4);
   grx->SetMarkerColor(kBlue);
   grv->SetMarkerColor(kBlue);
   grxe->SetMarkerColor(kRed);
   grve->SetMarkerColor(kRed);
   //
   grx->SetMarkerStyle(22);
   grv->SetMarkerStyle(22);
   grxe->SetMarkerStyle(22);
   grve->SetMarkerStyle(22);
   grx->SetTitle("Exponential Decay");
   grx->GetXaxis()->SetTitle("Time");
   grx->GetYaxis()->SetTitle("Position");
   grv->SetTitle("Exponential Decay");
   grv->GetXaxis()->SetTitle("Time");
   grv->GetYaxis()->SetTitle("Velocity");
//   TAxis *axis = gr->GetXaxis();
//   axis->SetLimits(-5.,5.);
//   grt->GetHistogram()->SetMaximum(2.5);
//   grt->GetHistogram()->SetMinimum(0.5);

   c1->cd(1);
   grx->Draw("AP");
   grxe->Draw("P");
   c1->Update();
   c1->cd(2);
   grv->Draw("AP");
   grve->Draw("P");

   c1->Update();
   c1->GetFrame()->SetFillColor(21);
   c1->GetFrame()->SetBorderSize(12);
   c1->Modified();
}
