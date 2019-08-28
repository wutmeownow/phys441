// Program to compute the motion of the Wilberforce pendulum
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

void wilberforce_rk(double x[], double t, double param[], double deriv[]) {
//  Returns right-hand sides of the Wilberforce ODEs; used by Runge-Kutta routines
//  Inputs
//    x      State vector [z theta vz vtheta]
//    t      Time (not used)
//    param     Parameter G*M (gravitational const. * solar mass)
//  Output
//    deriv  Derivatives [dr(1)/dt dr(2)/dt dv(1)/dt dv(2)/dt]

  //* Compute acceleration
  double k = param[1];
  double m = param[2];
  double I = param[3];
  double delta = param[4];
  double epsilon = param[5];
  double z = x[1], theta = x[2];     // Unravel the state vector into 
  double vz = x[3], vtheta = x[4];     // z,theta,vz,vtheta
  double az = -k/m*z-epsilon/(2.0*m)*theta;  // acceleration
  double atheta = -delta/I*theta-epsilon/(2.0*I)*z;

  //* Return derivatives [dr[1]/dt dr[2]/dt dv[1]/dt dv[2]/dt]
  deriv[1] = vz;   deriv[2] = vtheta;
  deriv[3] = az;   deriv[4] = atheta;
}
         
void graph_wilberforce() {
   //
   //Modified: Edward J. Brash
   //		
  
   //gStyle->SetOptFit(kFALSE);	
   gStyle->SetOptFit(1);	
   TCanvas *c1 = new TCanvas("c1","Cubic Data",200,10,700,500);
   c1->Divide(1,2);
   c1->SetFillColor(42);
   c1->SetGrid();

  //* Set initial position and velocity of the comet.
  double z0,theta0,I;
  z0=.1;
  theta0=0.0;
  cout << "Enter moment of inertia: "; cin >> I;  
  double r[2+1], v[2+1], state[4+1], accel[2+1];
  r[1] = z0; r[2] = theta0;  v[1] = 0; v[2] = 0;
  state[1] = r[1]; state[2] = r[2];   // Used by R-K routines
  state[3] = v[1]; state[4] = v[2];
  int nState = 4;  // Number of elements in state vector

  //* Set physical parameters
  double k,m,delta,epsilon;
  k = 2.80;
  m = 0.5164;
  delta=0.000786;
  epsilon = .00927;
  double param[5+1];
  param[1]=k;
  param[2]=m;
  param[3]=I;
  param[4]=delta;
  param[5]=epsilon;
  const double pi = 3.141592654;
  double adaptErr = 1.e-3;  // Error parameter used by adaptive Runge-Kutta
  double time = 0;

  //* Loop over desired number of steps using specified
  //  numerical method.
  cout << "Enter number of steps: "; 
  int nStep;  cin >> nStep;
  cout << "Enter time step (yr): ";
  double tau;  cin >> tau; 
  int method=3;
  double *rplot, *thplot, *tplot;  // Plotting variables
  rplot = new double [nStep+1];  thplot = new double [nStep+1];
  tplot = new double [nStep+1];
  int iStep;
  for( iStep=1; iStep<=nStep; iStep++ ) {  

    //* Record position and energy for plotting.
    rplot[iStep] = r[1];               // Record position for plotting
    thplot[iStep] = r[2];
    tplot[iStep] = time;
  
    //if( method == 3 ) {
      rk4( state, nState, time, tau, wilberforce_rk, param );
      r[1] = state[1]; r[2] = state[2];   // 4th order Runge-Kutta
      v[1] = state[3]; v[2] = state[4];
      time += tau;   
    //}
    //else {
    //  rka( state, nState, time, tau, adaptErr, wilberforce_rk, param );
    //  r[1] = state[1]; r[2] = state[2];   // Adaptive Runge-Kutta
    //  v[1] = state[3]; v[2] = state[4];
    //}
  
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
   Double_t xr[n], yr[n];
   Double_t xt[n], yt[n];
   Int_t i=0;

   for(i=0;i<n;i++){
	xr[i]=tplot[i+1];
	yr[i]=rplot[i+1];
	xt[i]=tplot[i+1];
	yt[i]=thplot[i+1];
   }

   TGraph *grr = new TGraph(n,xr,yr);
   TGraph *grt = new TGraph(n,xt,yt);

//   gr->SetLineColor(2);
//   gr->SetLineWidth(4);
   grr->SetMarkerColor(kBlue);
   grt->SetMarkerColor(kRed);
   //
   grr->SetMarkerStyle(22);
   grt->SetMarkerStyle(22);
   grr->SetTitle("Wilberforce Motion");
   grr->GetXaxis()->SetTitle("Time");
   grr->GetYaxis()->SetTitle("Z Position");
   grt->SetTitle("Wilberforce Motion");
   grt->GetXaxis()->SetTitle("Time");
   grt->GetYaxis()->SetTitle("Theta");

   c1->cd(1);
   grr->Draw("AL");
   c1->cd(2);
   grt->Draw("AL");
   
   c1->Update();
   c1->GetFrame()->SetFillColor(21);
   c1->GetFrame()->SetBorderSize(12);
   c1->Modified();
}
