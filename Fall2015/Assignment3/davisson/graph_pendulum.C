// pendul - Program to compute the motion of a simple pendulum
// using the Euler or Verlet method
#include <iostream>
#include "math.h"

void graph_pendulum(Double_t length=9.807) {
   //
   //Modified: Edward J. Brash
   //		

  //* Select the numerical method to use: Euler or Verlet

  double Cd = 0.35;      // Drag coefficient (dimensionless)
  //double area = 0.004359;  // Cross-sectional area of projectile (m^2)
  double radius =0.10;
  const double pi=3.141592653;
  double area = 4*pi*radius*radius; 
  double grav = 9.81;// Gravitational acceleration (m/s^2)
  double mass = 1.0;   // Mass of projectile (kg)
  double airFlag=1, rho;
  cout << "Air resistance? (Yes:1, No:0): "; cin >> airFlag;
  if( airFlag == 0 )
    rho = 0;      // No air resistance
  else
    rho = 1.2;    // Density of air (kg/m^3)
  double air_const = -0.5*Cd*rho*area/mass;
  cout<<air_const<<endl;
  cout << "Choose a numerical method 1) Euler, 2) Verlet: ";
  int method; cin >> method;
					   
  //* Set initial position and velocity of pendulum
  cout << "Enter initial angle (in degrees): "; 
  double theta0; cin >> theta0;
  // const double pi = 3.141592654;
  double theta = theta0*pi/180;   // Convert angle to radians
  double omega = 0.0;             // Set the initial velocity

  //* Set the physical constants and other variables
  double gravity = 9.807;
  double g_over_L = gravity/length;          // The constant g/L
  double time = 0.0;              // Initial time
  double time_old;                // Time of previous reversal
  int irev = 0;                   // Used to count number of reversals
  cout << "Enter time step: ";
  double tau; cin >> tau;

  //* Take one backward step to start Verlet
  double accel = -g_over_L*sin(theta);    // Gravitational acceleration
  double theta_old = theta - omega*tau + 0.5*tau*tau*accel;    

  //* Loop over desired number of steps with given time step
  //    and numerical method
  cout << "Enter number of time steps: ";
  int nStep;  cin >> nStep;
  double *t_plot, *th_plot, *period, *trev;  // Plotting variables
  t_plot = new double [nStep+1]; th_plot = new double [nStep+1];
  period = new double [nStep+1]; trev = new double [nStep+1];
  int iStep;
  for( iStep=1; iStep<=nStep; iStep++ ) {  

    //* Record angle and time for plotting
    t_plot[iStep] = time;            
    th_plot[iStep] = theta*180/pi;   // Convert angle to degrees
    time += tau;
  
    //* Compute new position and velocity using 
    //    Euler or Verlet method
    accel = -g_over_L*sin(theta); // Gravitational acceleration
    accel += air_const * fabs(omega)*omega*length;
    
    if( method == 1 ) {
      theta_old = theta;        // Save previous angle
      theta += tau*omega;       // Euler method
      omega += tau*accel; 
    }
    else {  
      double theta_new = 2*theta - theta_old + tau*tau*accel;
      theta_old = theta;	    // Verlet method
      theta = theta_new; 
      omega = (theta-theta_old)/tau;
      //cout<<omega<<endl;
    }
  
    //* Test if the pendulum has passed through theta = 0;
    //    if yes, use time to estimate period
    if( theta*theta_old < 0 ) { // Test position for sign change
      //cout << "Turning point at time t = " << time << endl;
      if( irev == 0 )          // If this is the first change,
        time_old = time;       // just record the time
      else {
        period[irev] = 2*(time - time_old);
	trev[irev] = time;
        time_old = time;
      }
      irev++;       // Increment the number of reversals
    }
  }
  int nPeriod = irev-1;    // Number of times period is measured

  //* Estimate period of oscillation, including error bar
  double AvePeriod = 0.0, ErrorBar = 0.0;
  int i;
  for( i=1; i<=nPeriod; i++ ) {
    AvePeriod += period[i];
  }
  AvePeriod /= nPeriod;
  for( i=1; i<=nPeriod; i++ ) {
    ErrorBar += (period[i] - AvePeriod)*(period[i] - AvePeriod);
  }
  ErrorBar = sqrt(ErrorBar/(nPeriod*(nPeriod-1)));
  cout << "Average period = " << AvePeriod << " +/- " << ErrorBar << endl;
  double t0=theta0*pi/180.0;
  cout << "Infinite series prediction = " << 2.0*pi/sqrt(g_over_L)*(1.0+t0*t0/16.0+pow(t0,4)*11.0/3072.0+pow(t0,6)*173.0/737280.0) << " +/- " << 2.0*pi/sqrt(g_over_L)*pow(t0,8)*22931.0/1321205760.0 << endl;

   const Int_t n = nStep;

   TCanvas *c1 = new TCanvas("c1","Cubic Data",200,10,700,500);
   c1->SetFillColor(42);
   c1->SetGrid();
   //gStyle->SetOptFit(kFALSE);	
   gStyle->SetOptFit(1);	
   
   TCanvas *c2 = new TCanvas("c2","Cubic Data",200,610,700,500);
   c2->SetFillColor(42);
   c2->SetGrid();
   
   gr = new TGraph(nStep,t_plot,th_plot);
   gr2 = new TGraph(nPeriod,trev,period);

//   gr->SetLineColor(2);
//   gr->SetLineWidth(4);
   gr->SetMarkerColor(kBlue);
   gr->SetMarkerStyle(21);
   gr->SetTitle("Simple Pendulum");
   gr->GetXaxis()->SetTitle("X");
   gr->GetYaxis()->SetTitle("Y");
   gr2->SetMarkerColor(kBlue);
   gr2->SetMarkerStyle(21);
   gr2->SetTitle("Simple Pendulum");
   gr2->GetXaxis()->SetTitle("X");
   gr2->GetYaxis()->SetTitle("Y");
//   TAxis *axis = gr->GetXaxis();
//   axis->SetLimits(-5.,5.);
//   gr->GetHistogram()->SetMaximum(10.0);
//   gr->GetHistogram()->SetMinimum(0.0);
   c1->cd();
   gr->Draw("AP");
   c2->cd();
   gr2->Draw("AP");

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
   c2->Update();
   c2->GetFrame()->SetFillColor(21);
   c2->GetFrame()->SetBorderSize(12);
   c2->Modified();
}
