// pendul - Program to compute the motion of a simple pendulum
// using the Euler or Verlet method
#include <iostream>
#include "math.h"

void graph_pendulum_air(Double_t length=9.807) {
   //
   //Modified: Edward J. Brash
   //		

  //* Select the numerical method to use: Euler or Verlet
  //cout << "Choose a numerical method 1) Euler, 2) Verlet: ";
  //Int_t method; cin >> method;

  Int_t method = 2;
					   
  //* Set initial position and velocity of pendulum
  //cout << "Enter initial angle (in degrees): "; 
  //Double_t theta0; cin >> theta0;
  Double_t theta0=45.0;
  const Double_t pi = 3.141592654;
  Double_t theta = theta0*pi/180;   // Convert angle to radians
  Double_t omega = 0.0;             // Set the initial velocity

  //* Set physical parameters (mass, Cd, etc.)
  Double_t Cd = 0.50;      // Drag coefficient (dimensionless)
  Double_t area = pi*0.10*0.10;  // Cross-sectional area of projectile (m^2)
  Double_t grav = 9.807;    // Gravitational acceleration (m/s^2)
  Double_t mass = 1.00;   // Mass of projectile (kg)
  Double_t rho = 1.2;     // Density of air (kg/m^3)
  Double_t air_const = 0.5*Cd*rho*area/mass;
  //

  //* Set the physical constants and other variables
  Double_t g_over_L = grav/length;          // The constant g/L
  Double_t time = 0.0;              // Initial time
  Double_t time_old;                // Time of previous reversal
  Int_t irev = 0;                   // Used to count number of reversals
  cout << "Enter time step: ";
  Double_t tau; cin >> tau;

  Double_t norm_omega = sqrt(omega*omega);

  //* Take one backward step to start Verlet
  Double_t accel = -g_over_L*sin(theta)-air_const*norm_omega*omega*length;    // Gravitational acceleration + Air resistance
  Double_t theta_old = theta - omega*tau + 0.5*tau*tau*accel;
  Double_t omega_old = (theta - theta_old)/tau;  
  //cout << "alpha_air = " << air_const*norm_omega*omega*length << endl;

  //* Loop over desired number of steps with given time step
  //    and numerical method
  cout << "Enter number of time steps: ";
  Int_t nStep;  cin >> nStep;
  Double_t *t_plot, *th_plot, *period, *period_theory, *trev;  // Plotting variables
  t_plot = new Double_t [nStep+1]; th_plot = new Double_t [nStep+1];
  period = new Double_t [nStep+1]; trev = new Double_t [nStep+1]; period_theory = new Double_t [nStep+1];
  Int_t iStep;
  Double_t tmax = 0.0;
  for( iStep=1; iStep<=nStep; iStep++ ) {  

    //* Record angle and time for plotting
    t_plot[iStep] = time;            
    th_plot[iStep] = theta*180/pi;   // Convert angle to degrees
    time += tau;
  
    //* Compute new position and velocity using 
    //    Euler or Verlet method
    norm_omega=sqrt(omega*omega);
    accel = -g_over_L*sin(theta)-air_const*norm_omega*omega*length;    // Gravitational acceleration + Air resistance
    //cout << "a0 = " << -g_over_L*sin(theta) << " a1 = " << accel << endl;
    //cout << "alpha_air = " << air_const*norm_omega*omega*length << endl;
    //cout << air_const << " " << norm_omega << " "  << omega << " " << length << endl;
    if( method == 1 ) {
      theta_old = theta;        // Save previous angle
      theta += tau*omega;       // Euler method
      omega += tau*accel; 
    }
    else {  
      Double_t theta_new = 2*theta - theta_old + tau*tau*accel;
      omega = (theta_new - theta_old)/(2.0*tau);
      theta_old = theta;	    // Verlet method
      theta = theta_new;
      //cout << "theta_new = " << theta << "  theta_old = " << theta_old << endl;
      //cout << "omega = " << omega << endl;  
    }

    if(fabs(theta)>tmax){tmax=fabs(theta);}
  
    //* Test if the pendulum has passed through theta = 0;
    //    if yes, use time to estimate period
    if( theta*theta_old < 0 ) { // Test position for sign change
      cout << "Turning point at time t = " << time << endl;
      Double_t t1 = tmax;
      tmax=0.0;
      if( irev == 0 )          // If this is the first change,
        time_old = time;       // just record the time
      else {
        period[irev] = 2*(time - time_old);
	cout << t1 << endl;
	period_theory[irev] = 2.0*pi/sqrt(g_over_L)*(1.0+t1*t1/16.0+pow(t1,4)*11.0/3072.0+pow(t1,6)*173.0/737280.0);
	trev[irev] = time;
        time_old = time;
      }
      irev++;       // Increment the number of reversals
    }
  }
  Int_t nPeriod = irev-1;    // Number of times period is measured

  //* Estimate period of oscillation, including error bar
  Double_t AvePeriod = 0.0, ErrorBar = 0.0;
  Int_t i;
  for( i=1; i<=nPeriod; i++ ) {
    AvePeriod += period[i];
  }
  AvePeriod /= nPeriod;
  for( i=1; i<=nPeriod; i++ ) {
    ErrorBar += (period[i] - AvePeriod)*(period[i] - AvePeriod);
  }
  ErrorBar = sqrt(ErrorBar/(nPeriod*(nPeriod-1)));
  cout << "Average period = " << AvePeriod << " +/- " << ErrorBar << endl;
  Double_t t0=theta0*pi/180.0;
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
   gr3 = new TGraph(nPeriod,trev,period_theory);

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
   gr3->SetMarkerColor(kRed);
   gr3->SetMarkerStyle(21);
   gr3->SetTitle("Simple Pendulum");
   gr3->GetXaxis()->SetTitle("X");
   gr3->GetYaxis()->SetTitle("Y");
//   TAxis *axis = gr->GetXaxis();
//   axis->SetLimits(-5.,5.);
//   gr->GetHistogram()->SetMaximum(10.0);
//   gr->GetHistogram()->SetMinimum(0.0);
   c1->cd();
   gr->Draw("AP");
   c2->cd();
   gr2->Draw("AP");
   gr3->Draw("P");

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
