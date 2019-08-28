
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



void gravrk(double x[], double t, double param[], double deriv[]) {
//  Returns right-hand side of Kepler ODE; used by Runge-Kutta routines
//  Inputs
//    x      State vector [r(1) r(2) v(1) v(2)]
//    t      Time (not used)
//    param     Parameter G*M (gravitational const. * solar mass)
//  Output
//    deriv  Derivatives [dr(1)/dt dr(2)/dt dv(1)/dt dv(2)/dt]

  //* Compute acceleration

  double epsilon=param[1];
  double delta=param[2];
  double k=param[3];
  double mass=param[4];

  double inertia = (delta*mass)/(k);
  double z = x[1], theta = x[2];     // Unravel the vector s into 
  double v = x[3], omega = x[4];     // position and velocity
  //double normR = sqrt( r1*r1 + r2*r2 );
  double accel = ((-k/mass)*z)-(((epsilon)/(2*mass))*theta);     //-GM*r1/(normR*normR*normR);  // Gravitational acceleration
  double angularAccel = (((-delta)/(inertia))*theta)-(((epsilon)/(2*inertia))*z);      //-GM*r2/(normR*normR*normR);

  //* Return derivatives [dr[1]/dt dr[2]/dt dv[1]/dt dv[2]/dt]
  deriv[1] = v;       deriv[2] = omega;
  deriv[3] = accel;   deriv[4] = angularAccel;
}
         
void wilberforce_pendulum() {
   //
   //Modified: Edward J. Brash
   //		
  
   //gStyle->SetOptFit(kFALSE);	
   gStyle->SetOptFit(1);	
   TCanvas *c1 = new TCanvas("c1","Cubic Data",200,10,700,500);
   c1->Divide(2,1);
   c1->SetFillColor(42);
   c1->SetGrid();

  //* Set initial position and velocity of the comet.
  double r0=0.1, v0=10;
  //cout << "Enter initial radial distance (AU): "; cin >> r0;  
  //cout << "Enter initial tangential velocity (AU/yr): "; cin >> v0;
  double r[2+1], v[2+1], state[4+1], accel[2+1];
  r[1] = r0; r[2] = 0;  v[1] = v0; v[2] = 0;
  state[1] = r[1]; state[2] = r[2];   // Used by R-K routines
  state[3] = v[1]; state[4] = v[2];
  int nState = 4;  // Number of elements in state vector

  //* Set physical parameters (mass, G*M)
  const double pi = 3.141592654;
  //double GM = 4*pi*pi;   
  // Grav. const. * Mass of Sun (au^3/yr^2)

  double epsilon = 0.00927;
  double delta = 0.000786;
  double k = 2.8;
  double mass = 0.5164;
  //  double inertia = (delta * mass)/(k);

  double param[4+1];  param[1] = epsilon;
  param[2]=delta;
  param[3]=k;
  param[4]=mass;
  //param[5]=inertia;

  //double mass = 1.;         // Mass of comet 
  double adaptErr = 1.e-3;  // Error parameter used by adaptive Runge-Kutta
  double time = 0;

  //* Loop over desired number of steps using specified
  //  numerical method.
  
  //cout << "Enter number of steps: "; 
  int nStep=10000;  //cin >> nStep;
  
  //cout << "Enter time step (yr): ";
  double tau=0.01;  
  
  //cin >> tau; 
  //cout << "Choose a numerical method:" << endl;
  //cout << "1) Euler,       2) Euler-Cromer, "	<< endl
  //   << "3) Runge-Kutta, 4) Adaptive R-K: ";

  int method=3;  //cin >> method;
  double *rplot, *thplot, *tplot, *kinetic, *potential;  // Plotting variables
  rplot = new double [nStep+1];  
  thplot = new double [nStep+1];
  tplot = new double [nStep+1];
  //kinetic = new double [nStep+1]; potential = new double [nStep+1];
  int iStep;

  for( iStep=1; iStep<=nStep; iStep++ ) {  

    //* Record position and energy for plotting.
    //double normR = sqrt( r[1]*r[1] + r[2]*r[2] );
    //double normV = sqrt( v[1]*v[1] + v[2]*v[2] );
    rplot[iStep] = r[1];               // Record position for plotting
    thplot[iStep] = r[2];//atan2(r[2],r[1]);
    tplot[iStep] = time;
    //kinetic[iStep] = 0.5*mass*normV*normV;   // Record energies
    //potential[iStep] = - GM*mass/normR;
  
    //* Calculate new position and velocity using desired method.
  
     
 
    else if( method == 3 ) {
      rk4( state, nState, time, tau, gravrk, param );
      r[1] = state[1]; r[2] = state[2];   // 4th order Runge-Kutta
      v[1] = state[3]; v[2] = state[4];
      time += tau;   
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
   Double_t xr[n], yr[n];
   Double_t xt[n], yt[n];
   Double_t xe[n], ye[n];
   Double_t xk[n], yk[n];
   Double_t xp[n], yp[n];
   Int_t i=0;

   for(i=0;i<n;i++){
	xr[i]=thplot[i+1];
	yr[i]=tplot[i+1];
	//xt[i]=tplot[i+1];
	yt[i]=rplot[i+1];
	//xe[i]=tplot[i+1];
	//ye[i]=potential[i+1]+kinetic[i+1];
	//xk[i]=tplot[i+1];
	//yk[i]=kinetic[i+1];
	//xp[i]=tplot[i+1];
	//yp[i]=potential[i+1];
   }

   TGraph * grr = new TGraph(n,yr,xr);
   grt = new TGraph(n,yr,yt);
   //gre = new TGraph(n,xe,ye);
   //grk = new TGraph(n,xk,yk);
   //grp = new TGraph(n,xp,yp);

//   gr->SetLineColor(2);
//   gr->SetLineWidth(4);
   grr->SetMarkerColor(kBlue);
   grt->SetMarkerColor(kRed);
   //gre->SetMarkerColor(kRed);
   //grk->SetMarkerColor(kGreen);
   //grp->SetMarkerColor(kBlue);
   //
   grr->SetMarkerStyle(22);
   grt->SetMarkerStyle(22);
   /*gre->SetMarkerStyle(22);
   grk->SetMarkerStyle(22);
   grp->SetMarkerStyle(22);
   gre->SetTitle("Keplerian Motion");
   gre->GetXaxis()->SetTitle("Time");
   gre->GetYaxis()->SetTitle("Energy");*/
   grr->SetTitle("Theta vs Time");
   grr->GetXaxis()->SetTitle("Time");
   grr->GetYaxis()->SetTitle("Theta");
   grt->SetTitle("Z vs Time");
   grt->GetXaxis()->SetTitle("Time");
   grt->GetYaxis()->SetTitle("Z");
//   TAxis *axis = gr->GetXaxis();
//   axis->SetLimits(-5.,5.);
   // gre->GetHistogram()->SetMaximum(30.0);
   //gre->GetHistogram()->SetMinimum(-45.0);
//   grt->GetHistogram()->SetMaximum(2.5);
//   grt->GetHistogram()->SetMinimum(0.5);

   //c1->cd(1);
   //grr->SetMaxRadial(1.5);
   //grr->SetMinRadial(0.0);
   c1->cd(1);
   grr->Draw("AP");

   c1->cd(2);
   grt->Draw("AP");
   c1->Update();
   /* c1->cd(2);
   grt->Draw("AP");
   c1->cd(3);
   gre->Draw("AP");
   grk->Draw("P");
   grp->Draw("P");*/

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
