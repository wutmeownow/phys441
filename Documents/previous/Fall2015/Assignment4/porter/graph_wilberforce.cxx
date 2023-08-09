// orbit - Program to compute the orbit of a comet.
#include <iostream>
#include <fstream>
#include "math.h"

#include <TStopwatch>

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
	double mass = 0.5164;
	double k = 2.80;
	double delta = 0.000786;
	double Inertia = 0.0002;
	double epsilon = (delta*mass)/k;
	double r1 = x[1], r2 = x[2];     // Unravel the vector s into 
	double v1 = x[3], v2 = x[4];     // position and velocity
	double normR1 = sqrt( r1*r1 );
	double normR2 = sqrt( r2*r2 );
	double accel1 = -(k*r1 + epsilon*r2)/mass;  // Gravitational acceleration
	double accel2 = -(delta*r2 + epsilon*r1)/Inertia;

	//* Return derivatives [dr[1]/dt dr[2]/dt dv[1]/dt dv[2]/dt]
	deriv[1] = v1;       deriv[2] = v2;
	deriv[3] = accel1;   deriv[4] = accel2;
}
         
void graph_wilberforce() {
	//
	//Modified: Edward J. Brash
	//	

	//gStyle->SetOptFit(kFALSE);	
	gStyle->SetOptFit(1);	
	TCanvas *c1 = new TCanvas("c1","Wilberforce",200,10,700,500);
	
	c1->SetFillColor(42);
	//c1->SetGrid();

	//* Set initial position and velocity
	double r0, v0;
	double r[2+1], v[2+1], state[4+1], accel[2+1];
	r[1] = 0.1; r[2] = 0;  v[1] = 0; v[2] = 0;
	state[1] = r[1]; state[2] = r[2];   // Used by R-K routines
	state[3] = v[1]; state[4] = v[2];
	int nState = 4;  // Number of elements in state vector

	//* Set physical parameters
	const double pi = 3.141592654;
	double delta = 0.000786;
	double epsilon = 0.00927;
	double k = 2.80;
	double param[1+1];
	double mass = 0.5164;         // Mass of pendulum
	double Inertia = (delta*mass)/k;
	double adaptErr = 1.e-3;  // Error parameter used by adaptive Runge-Kutta
	double time = 0;

	//* Loop over desired number of steps using specified
	cout << "Enter number of steps: "; 
	int nStep;  cin >> nStep;
	cout << "Enter time step: ";
	double tau;  cin >> tau; 

	double *rplot, *thplot, *tplot, *kinetic, *potential;  // Plotting variables
	rplot = new double [nStep+1];  thplot = new double [nStep+1];
	tplot = new double [nStep+1];
	kinetic = new double [nStep+1]; potential = new double [nStep+1];
	int iStep;
	for( iStep=1; iStep<=nStep; iStep++ ) {  

		//* Record position and energy for plotting.
		double normR1 = sqrt( r[1]*r[1] );
		double normR2 = sqrt( r[2]*r[2] );
		double normV1 = sqrt( v[1]*v[1] );
		double normV2 = sqrt( v[2]*v[2] );
		rplot[iStep] = r[2]; // Record position for plotting
		thplot[iStep] = atan2(r[2],r[1]);
		tplot[iStep] = time;
		kinetic[iStep] = 0.5*mass*normV1*normV1 + 0.5*Inertia*normV2*normV2; // Record energies
		potential[iStep] = -0.5*k*normR1*normR1 - 0.5*delta*normR2*normR2 - 0.5*epsilon*normR1*normR2;
  
		//* Calculate new position and velocity using desired method.
		rka( state, nState, time, tau, adaptErr, gravrk, param );
		r[1] = state[1]; r[2] = state[2];   // Adaptive Runge-Kutta
		v[1] = state[3]; v[2] = state[4];
		
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
	Double_t xe[n], ye[n];
	Double_t xk[n], yk[n];
	Double_t xp[n], yp[n];
	Int_t i=0;

	for(i=0;i<n;i++){
		xr[i]=thplot[i+1];
		yr[i]=rplot[i+1];
		xt[i]=tplot[i+1];
		yt[i]=rplot[i+1];
		xe[i]=tplot[i+1];
		ye[i]=potential[i+1]+kinetic[i+1];
		xk[i]=tplot[i+1];
		yk[i]=kinetic[i+1];
		xp[i]=tplot[i+1];
		yp[i]=potential[i+1];
	}

	grr = new TGraph(n,xt,yr);

	//gr->SetLineColor(2);
	//gr->SetLineWidth(4);
	//grr->SetMarkerColor(kBlue);
	grr->SetLineColor(kBlue);

	grr->SetMarkerStyle(22);
	grr->SetTitle("Keplerian Motion");
	grr->GetXaxis()->SetTitle("time");
	grr->GetYaxis()->SetTitle("theta");



	//c1->cd(1);
	grr->Draw("LA");
	c1->Update();
	//c1->cd(2);
	//c1->cd(3);



	//TCanvas::Update() draws the frame, after which one can change it
	c1->Update();
	c1->GetFrame()->SetFillColor(21);
	c1->GetFrame()->SetBorderSize(12);
	c1->Modified();
}
