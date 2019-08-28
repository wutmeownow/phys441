// orbit - Program to compute wilberforce pendulum
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



void gravrk(double x[], double t, double param[], double deriv[]) {
//  Returns right-hand side of Kepler ODE; used by Runge-Kutta routines
//  Inputs
//    x      State vector [r(1) r(2) v(1) v(2)]
//    t      Time (not used)
//    param     Parameter G*M (gravitational const. * solar mass)
//  Output
//    deriv  Derivatives [dr(1)/dt dr(2)/dt dv(1)/dt dv(2)/dt]

  //* Compute acceleration
  double GM = param[1];
  double z1 = x[1], z2 = x[2];     // Unravel the vector s into 
  double theta1 = x[3], theta2 = x[4];     // position and velocity
  double normR = sqrt( z1*z1 + z2*z2 );
  double accel1 = -GM*theta1/(normR*normR*normR);  // Gravitational acceleration
  double accel2 = -GM*theta2/(normR*normR*normR);

  //* Return derivatives [dr[1]/dt dr[2]/dt dv[1]/dt dv[2]/dt]
  deriv[1] = theta1;       deriv[2] = theta2;
  deriv[3] = accel1;   deriv[4] = accel2;
}
         
void graph_wilberforce_pen() {
   //
   //Modified: Austin Doll-Hennis
	// basically for this code, the goal is to find the value of I at the time step at which wz = w0. 
	//wz^2 = k/m
	//w0^2 = delta / I;
   //		
  
   //gStyle->SetOptFit(kFALSE);	
   gStyle->SetOptFit(1);	
   TCanvas *c1 = new TCanvas("c1","Theta vs Time",200,10,700,500);
   //c1->Divide(3,1);
   c1->SetFillColor(42);
   c1->SetGrid();

  //main equations

  ///w1 = w +- (epsilon/4w)*sqrt(mass*I);

  //* Set initial factors for the PENDULUM

  double z0 = 0.10; 		//initial z displacement, r0
  double theta0 = 0.0;		//initial theta, v0
  double mass = .5164;		
  double k = 2.80;		//
  double delta = 0.000786;	//
  double epsilon = 0.00972;	//

  double wz = mass/k;
  //double w0 = delta / iGoal;
 //S double w1 = 

  double z[2+1], theta[2+1], state[4+1], accel[2+1];
  z[1] = z0; z[2] = 0;  theta[1] = 0; theta[2] = theta0;
  state[1] = z[1]; state[2] = z[2];   // Used by R-K routines
  state[3] = theta[1]; state[4] = theta[2];
  int nState = 4;  // Number of elements in state vector

  //* Set physical parameters (mass, G*M)
  const double pi = 3.141592654;
  double GM = 4*pi*pi;      // Grav. const. * Mass of Sun (au^3/yr^2)
  double param[1+1];  param[1] = GM;
  double time = 0;

  //* Loop over desired number of steps using specified
  //  numerical method.
  cout << "Enter number of steps: "; 
  int nStep;  cin >> nStep;
  cout << "Enter time step (seconds): ";
  double tau;  cin >> tau; 
  double *rplot, *thplot, *tplot, *kinetic, *potential;  // Plotting variables
  rplot = new double [nStep+1];  thplot = new double [nStep+1];
  tplot = new double [nStep+1];
  kinetic = new double [nStep+1]; potential = new double [nStep+1];
  int iStep;
  for( iStep=1; iStep<=nStep; iStep++ ) {  

    //* Record position and energy for plotting.
    double normR = sqrt( z[1]*z[1] + z[2]*z[2] );
    double normV = sqrt( theta[1]*theta[1] + theta[2]*theta[2] );
    rplot[iStep] = normR;               // Record position for plotting
    thplot[iStep] = atan2(z[2],z[1]);
    tplot[iStep] = time;
    //double thetaplot[iStep] = 
    kinetic[iStep] = 0.5*mass*normV*normV;   // Record energies
    potential[iStep] = - GM*mass/normR;
  
    //* Calculate new theta from rk4
      rk4( state, nState, time, tau, gravrk, param );
      z[1] = state[1]; z[2] = state[2];   // 4th order Runge-Kutta
      theta[1] = state[3]; theta[2] = state[4];
      time += tau;   
    }
  

   const Int_t n = nStep;
   Double_t xt[n], yt[n];
   Int_t i=0;

   for(i=0;i<n;i++){

	xt[i]=thplot[i+1];
	yt[i]=thplot[i+1];
   }

   grt = new TGraph(n,xt,yt);
   grt->SetMarkerColor(kBlue);
   grt->SetMarkerStyle(22);
   grt->SetTitle("Theta Vs Time");
   grt->GetXaxis()->SetTitle("Time");
   grt->GetYaxis()->SetTitle("Theta");

   c1->Update();
   grt->Draw("AP");
   c1->GetFrame()->SetFillColor(21);
   c1->GetFrame()->SetBorderSize(12);
   c1->Modified();
}
