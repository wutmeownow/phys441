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

void wilber_rk(double x[], double t, double param[], double deriv[]) {
//  Returns right-hand side of Kepler ODE; used by Runge-Kutta routines
//  Inputs
//    x      State vector [r(1) r(2) v(1) v(2)]
//    t      Time (not used)
//    param     Parameter G*M (gravitational const. * solar mass)
//  Output
//    deriv  Derivatives [dr(1)/dt dr(2)/dt dv(1)/dt dv(2)/dt]

  //* Compute acceleration
  double m = param[1];
  double k = param[2];
  double delta = param[3];
  double epsilon = param[4];
  double inertia = param[5];

  double r1 = x[1], r2 = x[2];     // Unravel the vector s into 
  double v1 = x[3], v2 = x[4];     // position and velocity
  
  double accel1 = -(k*r1+0.5*epsilon*r2)/m;
  double accel2 = -(delta*r2+0.5*epsilon*r1)/inertia;

  //* Return derivatives [dr[1]/dt dr[2]/dt dv[1]/dt dv[2]/dt]
  deriv[1] = v1;       deriv[2] = v2;
  deriv[3] = accel1;   deriv[4] = accel2;
}
         
void graph_wilber() {
   //
   //Modified: Edward J. Brash
   //		
  
   gStyle->SetOptFit(1);	
   TCanvas *c1 = new TCanvas("c1","Wilberforce Pendulum",200,10,700,500);
   //c1->Divide(2,1);
   c1->SetFillColor(42);
   c1->SetGrid();

  //* Set initial position and velocity of the pendulum.
  double z0, theta0, vz0, vtheta0;
  z0 = 0.1;
  theta0 = 0.0;
  vz0 = 0.0;
  vtheta0 = 0.0;  

  double r[2+1], v[2+1], state[4+1], accel[2+1];
  r[1] = z0; r[2] = theta0;  v[1] = vz0; v[2] = vtheta0;
  state[1] = r[1]; state[2] = r[2];   // Used by R-K routines
  state[3] = v[1]; state[4] = v[2];
  int nState = 4;  // Number of elements in state vector

  //* Set physical parameters (mass, G*M)
  const double pi = 3.141592654;

  double m = 0.5164; //mass of pendulum
  double k = 2.80; //spring constant
  double delta = 0.000786; //rotational spring constant
  double epsilon = 0.00927; //cross parameter
  double inertia = delta*m/k; //moment of inertia of pendulum at resonance

  double param[5+1];
  param[1] = m;
  param[2] = k;
  param[3] = delta;
  param[4] = epsilon;
  param[5] = inertia;

  double adaptErr = 1.e-3;  // Error parameter used by adaptive Runge-Kutta
  double time = 0;

  //* Loop over desired number of steps using specified
  //  numerical method.
  cout << "Enter number of steps: "; 
  int nStep;  cin >> nStep;
  cout << "Enter time step (sec): ";
  double tau;  cin >> tau; 
  double *rplot, *thplot, *tplot, *kinetic, *potential;  // Plotting variables
  rplot = new double [nStep+1];  thplot = new double [nStep+1];
  tplot = new double [nStep+1];
  kinetic = new double [nStep+1]; potential = new double [nStep+1];
  int iStep;
  for( iStep=1; iStep<=nStep; iStep++ ) {  

    //* Record position and energy for plotting.
    rplot[iStep] = r[1];               // Record position for plotting
    thplot[iStep] = r[2];
    tplot[iStep] = time;
    /*kinetic[iStep] = 0.5*mass*normV*normV;   // Record energies
    potential[iStep] = - GM*mass/normR;*/
  
      rk4( state, nState, time, tau, wilber_rk, param );
      r[1] = state[1]; r[2] = state[2];   // 4th order Runge-Kutta
      v[1] = state[3]; v[2] = state[4];
      time += tau;   
  
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
   Double_t xt[n], yt[n];
   Int_t i=0;

   for(i=0;i<n;i++){
	xt[i]=tplot[i+1];
	yt[i]=thplot[i+1];
   }

   grt = new TGraph(n,xt,yt);
   grt->SetMarkerColor(kBlue);
   grt->SetMarkerStyle(22);
   grt->SetTitle("Wilberforce Pendulum");
   grt->GetXaxis()->SetTitle("Time");
   grt->GetYaxis()->SetTitle("Angle");

   grt->Draw("AP");
   

   // draw the legend
//   Char_t message[80];
//   TLegend *legend=new TLegend(0.4,0.15,0.88,0.35);
//   legend->SetTextFont(72);
//   legend->SetTextSize(0.04);
//   legend->AddEntry(gr,"Data","lpe");
//   sprintf(message,"Cubic Fit: #chi^{2}/NDF = %.5f",pfit1chi2ndf);
//   legend->AddEntry(pfit1,message);
//   legend->Draw();

   // TCanvas::Update() draws the frame, after which one can change it
   c1->Update();
   c1->GetFrame()->SetFillColor(21);
   c1->GetFrame()->SetBorderSize(12);
   c1->Modified();
}
