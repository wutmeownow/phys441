#include <ostream>
#include <TMath.h>

void graph_human_projectile_fit(double area = 1.35) {

   //
   //Modified: Edward J. Brash
   //		
  

  //* Set initial position and velocity of the baseball
  double y1, speed, theta;
  double r1[2+1], v1[2+1], r[2+1], v[2+1], accel[2+1]; 
  //cout << "Enter initial height (meters): "; cin >> y1;
   y1=38969.0; // Baumgartner
  //y1=41419.0; // Eustace
  r1[1] = 0;  r1[2] = y1;     // Initial vector position
  //cout << "Enter initial speed (m/s): "; cin >> speed; 
  //cout << "Enter initial angle (degrees): "; cin >> theta;
  speed=0.0; theta=0.0;
  const double pi = 3.141592654; 
  v1[1] = speed*cos(theta*pi/180.);   // Initial velocity (x)
  v1[2] = speed*sin(theta*pi/180.);   // Initial velocity (y)
  r[1] = r1[1];  r[2] = r1[2];  // Set initial position and velocity
  v[1] = v1[1];  v[2] = v1[2];             

  //* Set physical parameters (mass, Cd, etc.)
  double Cd;      // Drag coefficient (dimensionless)
  //double area = 1.35;  // Cross-sectional area of projectile (m^2)
  double grav = 9.80665;    // Gravitational acceleration (m/s^2)
  double mass = 80.0;   // Mass of projectile (kg)
  double airFlag, rho;
  double Re=6.4E6;
  // Results of fit to density data
  double rho0_low=12.03;
  double rho_lin_low=-7.715e-05;
  double rho_quad_low=-2.948e-07;
  double rho0_high=21.18;
  double rho_lin_high=-1.62e-04;
  double rho_quad_high=-2.267e-08;
  // Results of fit to viscosity data
  double vis_cons=1.836;
  double vis_lin=-5.335e-5;
  double vis_quad=2.019e-9;
  double vis_cube=-2.083e-14;
  //
  double glocal;
  //cout << "Air resistance? (Yes:1, No:0): "; cin >> airFlag;
  airFlag=1;
  if( airFlag == 0 )
    rho = 0;      // No air resistance
  else{
	  glocal=grav*pow((Re/(Re+y1)),2);
	  if(y1 <= 10000){
	  	rho=(rho0_low*exp(rho_lin_low*y1+rho_quad_low*pow(y1,1.5)))/10.0;
	  }else{
	  	rho=(rho0_high*exp(rho_lin_high*y1+rho_quad_high*pow(y1,1.5)))/10.0;
          }
    	  //rho = 1.2;    // Density of air (kg/m^3)
  }
  double air_const = -0.5*Cd*rho*area/mass;  // Air resistance constant

  //* Loop until ball hits ground or max steps completed
  double tau;
  //cout << "Enter timestep, delta_t (sec): "; cin >> tau;
  tau=0.001;
  int iStep, maxStep = 1000000;   // Maximum number of steps
  double *xplot, *yplot, *xNoAir, *yNoAir, *time, *vplot, *vNoAir;
  xplot = new double [maxStep+1];  yplot = new double [maxStep+1];
  xNoAir = new double [maxStep+1]; yNoAir = new double [maxStep+1];
  vplot = new double [maxStep+2]; vNoAir = new double [maxStep+1];
  time = new double [maxStep+1];

  double v_max = 0.0;

  for( iStep=1; iStep<=maxStep; iStep++ ) {

    //* Record position (computed and theoretical) for plotting
    xplot[iStep] = r[1];   // Record trajectory for plot
    yplot[iStep] = r[2];
    vplot[iStep] = v[2];

    double t = (iStep-1)*tau;     // Current time
    xNoAir[iStep] = r1[1] + v1[1]*t;
    yNoAir[iStep] = r1[2] + v1[2]*t - 0.5*grav*t*t;
    vNoAir[iStep] = v1[2] - glocal*t;

    //* Calculate the acceleration of the ball 
    double normV = sqrt( v[1]*v[1] + v[2]*v[2] );
    accel[1] = air_const*normV*v[1];   // Air resistance
    accel[2] = air_const*normV*v[2]-glocal;   // Air resistance - Gravity
  
    //* Calculate the new position and velocity using Euler method
    r[1] += tau*v[1];                 		// Euler step
    r[2] += tau*v[2];                 
    //r[1] += tau*v[1]+0.5*accel[1]*tau*tau;      // Midpoint step
    //r[2] += tau*v[2]+0.5*accel[2]*tau*tau;                 
    v[1] += tau*accel[1];     
    v[2] += tau*accel[2];     

    // Calculate new local gravity value, pressure, temperature, rho, and air_const;
    glocal=grav*pow((Re/(Re+r[2])),2);
    if(r[2] <= 10000){
	rho=(rho0_low*exp(rho_lin_low*r[2]+rho_quad_low*pow(r[2],1.5)))/10.0;
    }else{
	rho=(rho0_high*exp(rho_lin_high*r[2]+rho_quad_high*pow(r[2],1.5)))/10.0;
    }
    double viscosity=(vis_cons+vis_lin*r[2]+vis_quad*r[2]*r[2]+vis_cube*r[2]*r[2]*r[2])*1.0e-5;
    double Reynolds = rho*normV*sqrt(area/3.14159265)/viscosity;
    if (Reynolds < 100000) {
	Cd = 0.50;
    }else if (Reynolds >=100000 && Reynolds <200000) {
	Cd = 0.15;
    }else if (Reynolds >=200000 && Reynolds <400000) {
	Cd = 0.30;
    }else if (Reynolds >=400000 && Reynolds <1000000) {
	Cd = 0.35;
    }else{
	Cd = 0.40;
    }

    //int vy = r[2]/100;
    //if (fabs(vy-r[2]/100.0) < 0.001) cout << "Altitude = " << r[2] << " Reynolds Number = " << Reynolds << endl;
    
    air_const = -0.5*Cd*rho*area/mass;  // Air resistance constant

    //* Fill time array
    time[iStep]=tau*(iStep-1);

    if (normV > v_max) v_max = normV;
  
    //* If ball reaches ground (y<0), break out of the loop
    if( r[2] < 2567.0 )  { // Baumgartner
    //if( r[2] < 3802.0 )  { // Eustace
          xplot[iStep+1] = r[1];  // Record last values computed
	  yplot[iStep+1] = r[2];
	  time[iStep+1] = tau*iStep;
	  vplot[iStep+1] = v[2];
          break;                  // Break out of the for loop
    } 
  }

  //* Print maximum range and time of flight

  cout << "Maximum range is " << r[1] << " meters" << endl;
  cout << "Time of flight is " << iStep*tau << " seconds" << endl;
  cout << "V_max is " << v_max << " meters/second" << endl;

  Double_t max_y = TMath::MaxElement(iStep,yNoAir)+1;
  Double_t max_x = TMath::MaxElement(iStep,xNoAir)+1;
  Double_t max_t = TMath::MaxElement(iStep,time)+1;
  Double_t max_v = TMath::MaxElement(iStep,vNoAir)+1;
  Double_t min_v = TMath::MinElement(iStep,vNoAir)+1;
  if(fabs(min_v) > fabs(max_v)) max_v=fabs(min_v);
 
   //gStyle->SetOptFit(kFALSE);	
   gStyle->SetOptFit(1);	
   TCanvas *c1 = new TCanvas("c1","XY Projectile",200,10,700,500);
   c1->SetFillColor(42);
   c1->SetGrid();
   TCanvas *c2 = new TCanvas("c2","XT Projectile",230,40,700,500);
   c2->SetFillColor(42);
   c2->SetGrid();
   TCanvas *c3 = new TCanvas("c3","YT Projectile",260,70,700,500);
   c3->SetFillColor(42);
   c3->SetGrid();
   TCanvas *c4 = new TCanvas("c4","YT Projectile",290,100,700,500);
   c4->SetFillColor(42);
   c4->SetGrid();

   const Int_t n=iStep;
   gr = new TGraph(n,xplot,yplot);
   grr = new TGraph(n,xNoAir,yNoAir);
   gxt = new TGraph(n,time,xplot);
   gxtt = new TGraph(n,time,xNoAir);
   gyt = new TGraph(n,time,yplot);
   gytt = new TGraph(n,time,yNoAir);
   gvt = new TGraph(n,time,vplot);
   gvtt = new TGraph(n,time,vNoAir);

//   gr->SetLineColor(2);
//   gr->SetLineWidth(4);
   gr->SetMarkerColor(kBlue);
   grr->SetMarkerColor(kRed);
   gr->SetMarkerStyle(21);
   grr->SetMarkerStyle(22);
   grr->SetTitle("Projectile XY");
   grr->GetXaxis()->SetTitle("X");
   grr->GetYaxis()->SetTitle("Y");
   gxt->SetMarkerColor(kBlue);
   gxtt->SetMarkerColor(kRed);
   gxt->SetMarkerStyle(21);
   gxtt->SetMarkerStyle(22);
   gxtt->SetTitle("Projectile XT");
   gxtt->GetXaxis()->SetTitle("X");
   gxtt->GetYaxis()->SetTitle("T");
   gyt->SetMarkerColor(kBlue);
   gytt->SetMarkerColor(kRed);
   gyt->SetMarkerStyle(21);
   gytt->SetMarkerStyle(22);
   gytt->SetTitle("Projectile YT");
   gytt->GetXaxis()->SetTitle("Y");
   gytt->GetYaxis()->SetTitle("T");
   gvt->SetMarkerColor(kBlue);
   gvtt->SetMarkerColor(kRed);
   gvt->SetMarkerStyle(21);
   gvtt->SetMarkerStyle(22);
   gvtt->SetTitle("Projectile VT");
   gvtt->GetXaxis()->SetTitle("V");
   gvtt->GetYaxis()->SetTitle("T");
   
   TAxis *axis = grr->GetXaxis();
   axis->SetLimits(-0.1*max_x,1.1*max_x);
   grr->GetHistogram()->SetMaximum(1.1*max_y*500./700.);
   grr->GetHistogram()->SetMinimum(-0.1*max_y*500./700.);

   TAxis *axisx = gxtt->GetXaxis();
   axisx->SetLimits(-0.1*max_t,1.1*max_t);
   gxtt->GetHistogram()->SetMaximum(1.1*max_x);
   gxtt->GetHistogram()->SetMinimum(-0.1*max_x);

   TAxis *axisy = gytt->GetXaxis();
   axisy->SetLimits(-0.1*max_t,1.1*max_t);
   gytt->GetHistogram()->SetMaximum(1.1*max_y);
   gytt->GetHistogram()->SetMinimum(-0.1*max_y);

   TAxis *axisv = gvtt->GetXaxis();
   axisv->SetLimits(-0.1*max_t,1.1*max_t);
   gvtt->GetHistogram()->SetMinimum(-1.1*max_v);
   gvtt->GetHistogram()->SetMaximum(0.1*max_v);

   c1->cd();
   grr->Draw("AP");
   gr->Draw("P");
   c2->cd();
   gxtt->Draw("AP");
   gxt->Draw("P");
   c3->cd();
   gytt->Draw("AP");
   gyt->Draw("P");
   c4->cd();
   gvtt->Draw("AP");
   gvt->Draw("P");
   
   // TCanvas::Update() draws the frame, after which one can change it
   c1->Update();
   c1->GetFrame()->SetFillColor(21);
   c1->GetFrame()->SetBorderSize(12);
   c1->Modified();
   c2->Update();
   c2->GetFrame()->SetFillColor(21);
   c2->GetFrame()->SetBorderSize(12);
   c2->Modified();
   c3->Update();
   c3->GetFrame()->SetFillColor(21);
   c3->GetFrame()->SetBorderSize(12);
   c3->Modified();
   c4->Update();
   c4->GetFrame()->SetFillColor(21);
   c4->GetFrame()->SetBorderSize(12);
   c4->Modified();
}

