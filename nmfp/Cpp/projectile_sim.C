#include <ostream>
#include <TMath.h>

void projectile_sim() {
   //
   //Modified: Edward J. Brash
   //		
  
  TRandom3 *rnum = new TRandom3();

  //* Set initial position and velocity of the baseball
  double y1, speed, theta;
  int isize;
  double r1[2+1], v1[2+1], r[2+1], v[2+1], accel[2+1];
  cout << "Enter sliotar size (4 or 5): "; cin >> isize;
  cout << "Enter initial height (meters): "; cin >> y1;
  r1[1] = 0;  r1[2] = y1;     // Initial vector position
  cout << "Enter initial speed (m/s): "; cin >> speed; 
  cout << "Enter initial angle (degrees): "; cin >> theta;
  //speed = 45.0;
  //theta = 0.0;
  const double pi = 3.141592654; 

  if (isize == 5){
  	double diameter = .0753;
  	double mass = 0.115;
  }else{
  	double diameter = .0668;
  	double mass = 0.100;
  }
  
  double radius = diameter/2.0;
  double area = pi*radius*radius;
  double coeff_rest_x = 0.90;
  double coeff_rest_y = 0.30;

  //* Set physical parameters (mass, Cd, etc.)
  double grav = 9.81;    // Gravitational acceleration (m/s^2)
  double airFlag, rho;
  //cout << "Air resistance? (Yes:1, No:0): "; cin >> airFlag;
  airFlag = 1.0;
  if( airFlag == 0 )
    rho = 0;      // No air resistance
  else
    rho = 1.2;    // Density of air (kg/m^3)

  double viscosity = 18.27E-06;
  double Re = speed*rho*diameter/viscosity;
  cout << "Reynolds Number = " << Re << endl;
  double Cd = 0.30;      // Drag coefficient (dimensionless)


  double air_const = -0.5*Cd*rho*area/mass;  // Air resistance constant

  //* Loop until ball hits ground or max steps completed
  double tau;
  //cout << "Enter timestep, delta_t (sec): "; cin >> tau;
  tau = .001;
  int iStep, maxStep = 1000000;   // Maximum number of steps
  int maxIter = 6;
  double *xplot, *yplot, *xNoAir, *yNoAir, *time, *xfinal;
  xplot = new double [maxStep+1];  yplot = new double [maxStep+1];
  xNoAir = new double [maxStep+1]; yNoAir = new double [maxStep+1];
  time = new double [maxStep+1];
  xfinal = new double [maxIter+1];

  double vscatter,tscatter;
  double vadjust,tadjust;
  double xfinal_central = speed*speed*sin(2.0*45.0*pi/180.0)/grav;

  TH1F *h1 = new TH1F("h1", "X Final", 500, 0.0*xfinal_central, 1.0*xfinal_central);
  
  int iadjust;
  double adjust;
  cout << "Enter adjustment variable (1 = velocity, 2 = theta) " << endl;
  cin >> iadjust;
  cout << "Enter adjustment amount (absolute)" << endl;
  cin >> adjust;


  for (int i=1; i<=maxIter; i++){

  vadjust=0.0;
  tadjust=0.0;
  if (iadjust == 1){
	  //vadjust = rnum->Uniform(-adjust,adjust);
	  vadjust = adjust;
  }else{
	  //tadjust = rnum->Uniform(-adjust,adjust);
	  tadjust = adjust;
  }
  //cout << "Adjustment = " << vadjust << endl;
  
  vscatter = speed+(i-1)*vadjust;
  tscatter = theta+(i-1)*tadjust;
  v1[1] = vscatter*cos(tscatter*pi/180.);   // Initial velocity (x)
  v1[2] = vscatter*sin(tscatter*pi/180.);   // Initial velocity (y)
  r[1] = r1[1];  r[2] = r1[2];  // Set initial position and velocity
  v[1] = v1[1];  v[2] = v1[2];             


  int icounter=0;
  for( iStep=(i-1)*maxStep+1; iStep<=(i-1)*maxStep+maxStep+100000; iStep++ ) {

    //* Record position (computed and theoretical) for plotting
    xplot[iStep] = r[1];   // Record trajectory for plot
    yplot[iStep] = r[2];
    double t = (iStep-(i-1)*maxStep-1)*tau;     // Current time
    xNoAir[iStep] = r1[1] + v1[1]*t;
    yNoAir[iStep] = r1[2] + v1[2]*t - 0.5*grav*t*t;
  
    //* Calculate the acceleration of the ball 
    double normV = sqrt( v[1]*v[1] + v[2]*v[2] );
    accel[1] = air_const*normV*v[1];   // Air resistance
    accel[2] = air_const*normV*v[2]-grav;   // Air resistance - Gravity
  
    //* Calculate the new position and velocity using Euler method
    r[1] += tau*v[1];                 		// Euler step
    r[2] += tau*v[2];                 
    //r[1] += tau*v[1]+0.5*accel[1]*tau*tau;      // Midpoint step
    //r[2] += tau*v[2]+0.5*accel[2]*tau*tau;                 
    v[1] += tau*accel[1];     
    v[2] += tau*accel[2];     

    //* Fill time array
    time[iStep]=tau*(iStep-(i-1)*maxStep-1);
  
    //* If ball reaches ground (y<0), break out of the loop
    //if( r[1] > 20.0 )  {
    //if( r[2] > (0.9024-0.03) )  {
    cout << "iStep = " << iStep << "  r[2] = " << r[2] << endl;
    if( r[2] < 0.001 )  {
	  v[2]=-v[2]*coeff_rest_y;
	  v[1]=v[1]*coeff_rest_x;
	  r[2]=0.001;
    }
    if( normV < 1.0 ) {
          xplot[iStep+1] = r[1];  // Record last values computed
    	  yplot[iStep+1] = r[2];
    	  time[iStep+1] = tau*(iStep-(i-1)*maxStep);
	  cout << "Final speed -> v_x: " << v[1] << " v_y = " << v[2] << endl; 
          break;                  // Break out of the for loop
    } 
    icounter++;
  }
  maxStep = icounter;
  
  //* Print maximum range and time of flight

  cout << "Maximum range is " << r[1] << " meters" << endl;
  cout << "Time of flight is " << (iStep-(i-1)*maxStep)*tau << " seconds" << endl;

  h1->Fill(r[1]);
  //h1->Fill(r[2]);

  } 

  Double_t max_y = TMath::MaxElement(iStep,yplot)+1;
  Double_t max_x = TMath::MaxElement(iStep,xplot)+1;
  Double_t max_t = TMath::MaxElement(iStep,time)+1;
  cout << "Max y = " << max_y << endl; 
 
   //gStyle->SetOptFit(kFALSE);	
   gStyle->SetOptFit(1);	
   TCanvas *c1 = new TCanvas("c1","Vertical vs. Horizontal Position",200,400,1600,900);
   c1->SetFillColor(42);
   c1->SetGrid();
   TCanvas *c2 = new TCanvas("c2","Horizontal Postion vs. Time",200,400,900,900);
   c2->SetFillColor(42);
   c2->SetGrid();
   TCanvas *c3 = new TCanvas("c3","Vertical Position vs. Time",300,500,1000,1000);
   c3->SetFillColor(42);
   c3->SetGrid();
   TCanvas *c4 = new TCanvas("c4","Final Position",300,500,1000,1000);
   c3->SetFillColor(42);
   c3->SetGrid();

   const Int_t n=iStep;
   gr = new TGraph(n,xplot,yplot);
   grr = new TGraph(n,xNoAir,yNoAir);
   gxt = new TGraph(n,time,xplot);
   gxtt = new TGraph(n,time,xNoAir);
   gyt = new TGraph(n,time,yplot);
   gytt = new TGraph(n,time,yNoAir);

//   gr->SetLineColor(2);
//   gr->SetLineWidth(4);
   gr->SetMarkerColor(kBlue);
   grr->SetMarkerColor(kRed);
   //gr->SetMarkerStyle(21);
   //grr->SetMarkerStyle(22);
   gr->SetTitle("Vertical vs. Horizontal Position");
   gr->GetXaxis()->SetTitle("Horizontal Position (m)");
   gr->GetYaxis()->SetTitle("Vertical Position (m)");
   gxt->SetMarkerColor(kBlue);
   gxtt->SetMarkerColor(kRed);
   //gxt->SetMarkerStyle(21);
   //gxtt->SetMarkerStyle(22);
   gxt->SetTitle("Time of Flight");
   gxt->GetXaxis()->SetTitle("Time (s)");
   gxt->GetYaxis()->SetTitle("Horizontal Position (m)");
   gyt->SetMarkerColor(kBlue);
   gytt->SetMarkerColor(kRed);
   //gyt->SetMarkerStyle(21);
   //gytt->SetMarkerStyle(22);
   gyt->SetTitle("Time of Flight");
   gyt->GetXaxis()->SetTitle("Time (s)");
   gyt->GetYaxis()->SetTitle("Vertical Position (m)");
   
   TAxis *axis = gr->GetXaxis();
   axis->SetLimits(-0.1*max_x,1.1*max_x);
   gr->GetHistogram()->SetMaximum(0.6*max_x);
   gr->GetHistogram()->SetMinimum(-0.1*max_x);

   TAxis *axisx = gxt->GetXaxis();
   axisx->SetLimits(-0.1*max_t,1.1*max_t);
   gxt->GetHistogram()->SetMaximum(1.1*max_x);
   gxt->GetHistogram()->SetMinimum(-0.1*max_x);

   TAxis *axisy = gyt->GetXaxis();
   axisy->SetLimits(-0.1*max_t,1.1*max_t);
   gyt->GetHistogram()->SetMaximum(1.1*max_y);
   gyt->GetHistogram()->SetMinimum(-0.1*max_y);


   c1->cd();
   //grr->Draw("AP");
   gr->Draw("AP");
   c2->cd();
   //gxtt->Draw("AP");
   gxt->Draw("AP");
   c3->cd();
   //gytt->Draw("AP");
   gyt->Draw("AP");
   c4->cd();
   h1->Draw();
   //h1->Fit("gaus");
   
   // TCanvas::Update() draws the frame, after which one can change it
   c1->Update();
   c1->GetFrame()->SetFillColor(21);
   c1->GetFrame()->SetBorderSize(12);
   c1->Modified();
}

