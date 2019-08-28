#include <iostream>
#include "math.h"

void pen_graph(Double_t length=9.807) {

   		


  cout << "Choose a numerical method 1) Euler, 2) Verlet: ";
  int method; cin >> method;
					   

  cout << "Enter initial angle (in degrees): "; 
  double theta0; cin >> theta0;
  const double pi = 3.141592654;
  double theta = theta0*pi/180;   
  double omega = 0.0;             

  //* Set the physical constants and other variables
  double gravity = 9.807;
  double g_over_L = gravity/length;          
  double time = 0.0;           
  double time_old;                
  int irev = 0;                   
  cout << "Enter time step: ";
  double tau; cin >> tau;

  ///* Set physical parameters for air resistance
  double Cd = 0.35;      
  double area = .00314159;  
  double grav = 9.81;    
  double mass = 1.0;   
  double air_const = -0.5*Cd*1.2*area/mass; 

 
  double accel = -sin(theta);   
  double theta_old = theta - omega*tau + 0.5*tau*tau*accel;    

  //* Loop over desired number of steps with given time step
  //    and numerical method
  cout << "Enter number of time steps: ";
  int nStep;  cin >> nStep;
  double *t_plot, *th_plot, *period, *trev, *O_plot;  
  t_plot = new double [nStep+1]; th_plot = new double [nStep+1];
  period = new double [nStep+1]; trev = new double [nStep+1];

  int iStep;
  for( iStep=1; iStep<=nStep; iStep++ ) {  

    //* Record angle and time for plotting
    t_plot[iStep] = time;            
    th_plot[iStep] = theta*180/pi;  
    time += tau;
  
    //* Compute new position and velocity using 
    //    Euler or Verlet method
    double velo = sqrt(2*(1-cos(theta))); //velocity
    accel = -sin(theta);    // Gravitational acceleration

//guesses

    accel[1] = air_const*normV*v[1];   
    accel[2] = air_const*normV*v[2]-grav;  

    if( method == 1 ) {
      theta_old = theta;        
      theta += tau*omega;       
      omega += tau*accel; 
    }
    else {  
      double theta_new = 2*theta - theta_old + tau*tau*accel;
      theta_old = theta;	    
      theta = theta_new;  
    }
  
  
    if( theta*theta_old < 0 ) { 
      cout << "Turning point at time t = " << time << endl;
      if( irev == 0 )         
        time_old = time;      
      else {
        period[irev] = 2*(time - time_old);
	trev[irev] = time;
        time_old = time;
      }
      irev++;      
    }
  }
  int nPeriod = irev-1;  


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

   //gr->SetLineColor(2);
   //gr->SetLineWidth(4);
   gr->SetMarkerColor(kBlue);
   gr->SetMarkerStyle(21);
   gr->SetTitle("Simple Pendulum");
   gr->GetXaxis()->SetTitle("Time");
   gr->GetYaxis()->SetTitle("Theta");
   gr2->SetMarkerColor(kBlue);
   gr2->SetMarkerStyle(21);
   gr2->SetTitle("Simple Pendulum");
   gr2->GetXaxis()->SetTitle("X");
   gr2->GetYaxis()->SetTitle("Y");
     TAxis *axis = gr->GetXaxis();
     axis->SetLimits(-5.,5.);
     gr->GetHistogram()->SetMaximum(10.0);
     gr->GetHistogram()->SetMinimum(0.0);
   c1->cd();
   gr->Draw("AP");
   c2->cd();
   gr2->Draw("AP");

   c1->Update();
   c1->GetFrame()->SetFillColor(21);
   c1->GetFrame()->SetBorderSize(12);
   c1->Modified();
   c2->Update();
   c2->GetFrame()->SetFillColor(21);
   c2->GetFrame()->SetBorderSize(12);
   c2->Modified();
}
