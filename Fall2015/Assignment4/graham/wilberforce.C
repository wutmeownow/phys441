// orbit - Program to compute the orbit of a comet.
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

void wilberrk(double x[], double t, double param[], double deriv[]) {
//  Returns right-hand side of Kepler ODE; used by Runge-Kutta routines
//  Inputs
//    x      State vector [r(1) r(2) v(1) v(2)]
//    t      Time (not used)
//    param     Parameter G*M (gravitational const. * solar mass)
//  Output
//    deriv  Derivatives [dr(1)/dt dr(2)/dt dv(1)/dt dv(2)/dt]

  //* Compute acceleration
  double epsilon = param[1];
  double delta = param[2];
  double k = param[3];
  double m = param[4];
  double I = (delta*m)/k;
  double theta = x[1], z = x[2];     // Unravel the vector s into 
  double omega = x[3], v = x[4];     // position and velocity
  double angaccel = -(delta/I)*theta - (epsilon/(2*I))*z;
  double accel = -(k/m)*z - (epsilon/(2*m))*theta;

  //* Return derivatives
  deriv[1] = omega;       deriv[2] = v;
  deriv[3] = angaccel;   deriv[4] = accel;
}
         
void wilberforce() {
   //
   //Modified: Edward J. Brash
   //

  //* Set initial position and velocity of the comet.
  double r[2+1], v[2+1], state[4+1], accel[2+1];
  r[1] = 0; r[2] = 0.1;  v[1] = 0; v[2] = 10;
  state[1] = r[1]; state[2] = r[2];   // Used by R-K routines
  state[3] = v[1]; state[4] = v[2];
  int nState = 4;  // Number of elements in state vector

  //* Set physical parameters (mass, G*M)
  const double pi = 3.141592654;
  double epsilon = 0.00927;  // Grav. const. * Mass of Sun (au^3/yr^2)
  double delta = 0.000786;
  double k = 2.8;
  double m = 0.516;
  double param[4+1];  param[1] = epsilon; param[2] = delta; 
  param[3] = k; param[4] = m;
  double time = 0;

  //* Loop over desired number of steps using specified
  //  numerical method.
  //cout << "Enter number of steps: "; 
  int nStep = 10000;//  cin >> nStep;
  //cout << "Enter time step (yr): ";
  double tau = 0.01;//  cin >> tau; 
  double *thplot, *tplot, *zplot;  // Plotting variables
  thplot = new double [nStep+1];
  zplot = new double [nStep+1];
  tplot = new double [nStep+1];
  int iStep;
  for( iStep=1; iStep<=nStep; iStep++ ) {  

    //* Record position and energy for plotting.
    thplot[iStep] = r[1];
    zplot[iStep] = r[2];
    tplot[iStep] = time;
  
    //* Calculate new position and velocity using rk4 method.
    rk4( state, nState, time, tau, wilberrk, param );
    r[1] = state[1]; r[2] = state[2];   // 4th order Runge-Kutta
    v[1] = state[3]; v[2] = state[4];
    time += tau;
  }

   const Int_t n = nStep;
   Double_t th[n];
   Double_t z[n];
   Double_t t[n];
   Int_t i=0;

   for(i=0;i<n;i++){
	  th[i]=thplot[i+1];
	  z[i]=zplot[i+1];
	  t[i]=tplot[i+1];
   }
		
   //gStyle->SetOptFit(kFALSE);	
   gStyle->SetOptFit(1);	
   TCanvas *c2 = new TCanvas("c2","Wilberforce",200,10,700,500);
	c2->Divide(2,1);
   c2->SetFillColor(42);
   c2->SetGrid();
   gr = new TGraph(n,t,th);
   gz = new TGraph(n,t,z);
   gr->SetMarkerColor(kBlue);
   gz->SetMarkerColor(kRed);
   gr->SetMarkerStyle(22);
   gz->SetMarkerStyle(22);
   gr->SetTitle("Theta to Time Graph");
   gr->GetXaxis()->SetTitle("Time");
   gr->GetYaxis()->SetTitle("Theta");
   gz->SetTitle("Z to Time Graph");
   gz->GetXaxis()->SetTitle("Time");
   gz->GetYaxis()->SetTitle("Z");
	c2->cd(1);
   gr->Draw("AP");
	c2->cd(2);
   gz->Draw("AP");

   // TCanvas::Update() draws the frame, after which one can change it
   c2->Update();
   c2->GetFrame()->SetFillColor(21);
   c2->GetFrame()->SetBorderSize(12);
   c2->Modified();
}
