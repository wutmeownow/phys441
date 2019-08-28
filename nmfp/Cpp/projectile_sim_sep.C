#include <ostream>
#include <TMath.h>

void projectile_sim_sep() {
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
  int iStep;
  const int maxStep = 10000;   // Maximum number of steps
  const int maxIter = 6;
  int npoints[maxIter+1];
  double xplot[maxIter][maxStep];  
  double yplot[maxIter][maxStep];
  double xNoAir[maxIter][maxStep]; 
  double yNoAir[maxIter][maxStep];
  double time[maxIter][maxStep];
  double xfinal[maxIter];

  double vscatter,tscatter;
  double vadjust,tadjust;
  double xfinal_central = speed*speed*sin(2.0*45.0*pi/180.0)/grav;
  Double_t max_y[maxIter];
  Double_t max_x[maxIter];
  Double_t max_t[maxIter];

  TH1F *h1 = new TH1F("h1", "X Final", 500, 0.0*xfinal_central, 1.0*xfinal_central);
  
  int iadjust;
  double adjust;
  cout << "Enter adjustment variable (1 = velocity, 2 = theta) " << endl;
  cin >> iadjust;
  cout << "Enter adjustment amount (absolute)" << endl;
  cin >> adjust;


  for (int i=0; i<maxIter; i++){

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
  
  vscatter = speed+i*vadjust;
  tscatter = theta+i*tadjust;
  v1[1] = vscatter*cos(tscatter*pi/180.);   // Initial velocity (x)
  v1[2] = vscatter*sin(tscatter*pi/180.);   // Initial velocity (y)
  r[1] = r1[1];  r[2] = r1[2];  // Set initial position and velocity
  v[1] = v1[1];  v[2] = v1[2];             


  int icounter=0;
  double localmax_x = 0.0;
  double localmax_y = 0.0;
  double localmax_t = 0.0;

  for( iStep=1; iStep<=maxStep; iStep++ ) {

    //* Record position (computed and theoretical) for plotting
    xplot[i][iStep] = r[1];   // Record trajectory for plot
    yplot[i][iStep] = r[2];
    //cout << "iStep = " << iStep << " xplot = " << xplot[i][iStep] << " yplot = " << yplot[i][iStep] << endl;
    double t = (iStep-1)*tau;     // Current time
    xNoAir[i][iStep] = r1[1] + v1[1]*t;
    yNoAir[i][iStep] = r1[2] + v1[2]*t - 0.5*grav*t*t;
  
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
    time[i][iStep]=tau*(iStep-1);
  
    //* If ball reaches ground (y<0), break out of the loop
    //if( r[1] > 20.0 )  {
    //if( r[2] > (0.9024-0.03) )  {
    //cout << "iStep = " << iStep << "  r[2] = " << r[2] << endl;
    if( r[2] < 0.001 )  {
	  v[2]=-v[2]*coeff_rest_y;
	  v[1]=v[1]*coeff_rest_x;
	  r[2]=0.001;
    }
    if( normV < 1.0 ) {
    //if( (v[2] < 0.0)&&(r[2] < 2.0) ) {
          xplot[i][iStep+1] = r[1];  // Record last values computed
    	  yplot[i][iStep+1] = r[2];
    	  time[i][iStep+1] = tau*iStep;
	  cout << "Final speed -> v_x: " << v[1] << " v_y = " << v[2] << endl; 
          break;                  // Break out of the for loop
    } 
    icounter++;
    if(xplot[i][iStep] > localmax_x){
	    localmax_x = xplot[i][iStep];
    }
    if(yplot[i][iStep] > localmax_y){
	    localmax_y = yplot[i][iStep];
    }
    if(time[i][iStep] > localmax_t){
	    localmax_t = time[i][iStep];
    }
    //cout << " ** Here ** " << endl;
    //if((iStep == 100)||(iStep == 1000)||(iStep == 3000)){
    //	    cout << " *** Here *** " << endl;
    //	    cout << "iStep = " << iStep << " xplot = " << xplot[i][iStep] << endl;
    //  }
  }
  // cout << xplot[0][100] << " " << yplot[0][100] << endl;
  // cout << xplot[0][1000] << " " << yplot[0][1000] << endl;
  // cout << xplot[0][3000] << " " << yplot[0][3000] << endl;
  max_y[i] = localmax_y;
  max_x[i] = localmax_x;
  max_y[i] = localmax_t;
  cout << "Max y = " << max_y[i] << endl; 
  npoints[i] = icounter;
  cout << "Npoints = " << npoints[i] << endl; 
  
  //* Print maximum range and time of flight

  cout << "Maximum range is " << r[1] << " meters" << endl;
  cout << "Time of flight is " << iStep*tau << " seconds" << endl;

  h1->Fill(r[1]);
  //h1->Fill(r[2]);

  } 

 
   //gStyle->SetOptFit(kFALSE);	
   gStyle->SetOptFit(1);	
   TCanvas *c1 = new TCanvas("c1","Vertical vs. Horizontal Position",200,400,1600,900);
   c1->SetFillColor(42);
   c1->SetGrid();
   TCanvas *c2 = new TCanvas("c2","Horizontal Postion vs. Time",200,400,1600,900);
   c2->SetFillColor(42);
   //TCanvas *c3 = new TCanvas("c3","Vertical Position vs. Time",300,500,1000,1000);
   //c3->SetFillColor(42);
   //c3->SetGrid();
   //TCanvas *c4 = new TCanvas("c4","Final Position",300,500,1000,1000);
   //c4->SetFillColor(42);
   //c4->SetGrid();

   TGraph *gr[maxIter];
   TGraph *grr[maxIter];
   TGraph *gxt[maxIter];
   TGraph *gxtt[maxIter];
   TGraph *gyt[maxIter];
   TGraph *gytt[maxIter];

   for (int i=0;i<maxIter;i++){
   	   //const Int_t n=npoints[i]
	   cout << "i= " << i << " Npoints = " << npoints[i] << endl;
	   //for(int j=0; j<npoints[i];j++){
	//	   cout << "j = " << j << " x = " << xplot[i][j] << " y = " << yplot[i][j] << endl;
	  // }
	   gr[i] = new TGraph(npoints[i],xplot[i],yplot[i]);
   	   grr[i] = new TGraph(npoints[i],xNoAir[i],yNoAir[i]);
           gxt[i] = new TGraph(npoints[i],time[i],xplot[i]);
           gxtt[i] = new TGraph(npoints[i],time[i],xNoAir[i]);
           gyt[i] = new TGraph(npoints[i],time[i],yplot[i]);
           gytt[i] = new TGraph(npoints[i],time[i],yNoAir[i]);
   

           gr[i]->SetMarkerColor(2+i);
           gr[i]->SetLineColor(2+i);
	   gr[i]->SetMarkerStyle(7);
           grr[i]->SetMarkerColor(3+i);
	   grr[i]->SetMarkerStyle(7);
           gr[i]->SetTitle("Sliotar Trajectory for Various Launch Angles");
           gr[i]->GetXaxis()->SetTitle("Horizontal Position (m)");
           gr[i]->GetYaxis()->SetTitle("Vertical Position (m)");
           gxt[i]->SetMarkerColor(2+i);
           gxt[i]->SetLineColor(2+i);
           gxt[i]->SetMarkerStyle(7);
           gxtt[i]->SetMarkerColor(3+i);
           gxtt[i]->SetMarkerStyle(7);
           gxt[i]->SetTitle("Time of Flight - Horizontal");
           gxt[i]->GetXaxis()->SetTitle("Time (s)");
           gxt[i]->GetYaxis()->SetTitle("Horizontal Position (m)");
           gyt[i]->SetMarkerColor(2+i);
           gyt[i]->SetLineColor(2+i);
           gyt[i]->SetMarkerStyle(7);
           gytt[i]->SetMarkerColor(3+i);
           gytt[i]->SetMarkerStyle(7);
           gyt[i]->SetTitle("Time of Flight - Vertical");
           gyt[i]->GetXaxis()->SetTitle("Time (s)");
           gyt[i]->GetYaxis()->SetTitle("Vertical Position (m)");
           //TAxis *axis = gr[i]->GetXaxis();
           //axis->SetLimits(-0.1*max_x[i],1.1*max_x[i]);
           //gr[i]->GetHistogram()->SetMaximum(0.6*max_x[i]);
           //gr[i]->GetHistogram()->SetMinimum(-0.1*max_x[i]);
           //TAxis *axisx = gxt[i]->GetXaxis();
           //axisx->SetLimits(-0.1*max_t[i],1.1*max_t[i]);
           //gxt[i]->GetHistogram()->SetMaximum(1.1*max_x[i]);
           //gxt[i]->GetHistogram()->SetMinimum(-0.1*max_x[i]);
           //TAxis *axisy = gyt[i]->GetXaxis();
           //axisy[i]->SetLimits(-0.1*max_t[i],1.1*max_t[i]);
           //gyt[i]->GetHistogram()->SetMaximum(1.1*max_y[i]);
           //gyt[i]->GetHistogram()->SetMinimum(-0.1*max_y[i]);
   }

   c1->cd();
   //grr->Draw("AP");
   for(int i=maxIter-1;i>=0;i--){
   	if(i==(maxIter-1)){
		gr[i]->Draw("AP");
	}else{
		gr[i]->Draw("P");
	}
   }
   Char_t message[80];
   TLegend *legend=new TLegend(0.68,0.60,0.90,0.90);
   legend->SetTextFont(72);
   legend->SetTextSize(0.03);
   legend->AddEntry(gr[0],"Angle = 20 Degrees","L");
   legend->AddEntry(gr[1],"Angle = 25 Degrees","L");
   legend->AddEntry(gr[2],"Angle = 30 Degrees","L");
   legend->AddEntry(gr[3],"Angle = 35 Degrees","L");
   legend->AddEntry(gr[4],"Angle = 40 Degrees","L");
   legend->AddEntry(gr[5],"Angle = 45 Degrees","L");
   legend->Draw();
   
   c2->Divide(2,1);
   TPad* c2_1=(TPad*)(c2->GetPrimitive("c2_1"));
   c2_1->cd();
   c2_1->SetGrid(kTRUE);
   //gxtt->Draw("AP");
   for(int i=maxIter-1;i>=0;i--){
   	if(i==(maxIter-1)){
		gxt[i]->Draw("AP");
	}else{
		gxt[i]->Draw("P");
	}
   }
   Char_t message[80];
   TLegend *legend=new TLegend(0.50,0.10,0.90,0.40);
   legend->SetTextFont(72);
   legend->SetTextSize(0.03);
   legend->AddEntry(gxt[0],"Angle = 20 Degrees","L");
   legend->AddEntry(gxt[1],"Angle = 25 Degrees","L");
   legend->AddEntry(gxt[2],"Angle = 30 Degrees","L");
   legend->AddEntry(gxt[3],"Angle = 35 Degrees","L");
   legend->AddEntry(gxt[4],"Angle = 40 Degrees","L");
   legend->AddEntry(gxt[5],"Angle = 45 Degrees","L");
   legend->Draw();

   TPad* c2_1=(TPad*)(c2->GetPrimitive("c2_2"));
   c2_2->cd();
   c2_2->SetGrid(kTRUE);
   //gytt->Draw("AP");
   for(int i=maxIter-1;i>=0;i--){
   	if(i==(maxIter-1)){
		gyt[i]->Draw("AP");
	}else{
		gyt[i]->Draw("P");
	}
   }
   Char_t message[80];
   TLegend *legend=new TLegend(0.50,0.60,0.90,0.90);
   legend->SetTextFont(72);
   legend->SetTextSize(0.03);
   legend->AddEntry(gyt[0],"Angle = 20 Degrees","L");
   legend->AddEntry(gyt[1],"Angle = 25 Degrees","L");
   legend->AddEntry(gyt[2],"Angle = 30 Degrees","L");
   legend->AddEntry(gyt[3],"Angle = 35 Degrees","L");
   legend->AddEntry(gyt[4],"Angle = 40 Degrees","L");
   legend->AddEntry(gyt[5],"Angle = 45 Degrees","L");
   legend->Draw();
   
   //c4->cd();
   //h1->Draw();
   //h1->Fit("gaus");
   
   // TCanvas::Update() draws the frame, after which one can change it
   c1->Update();
   c1->GetFrame()->SetFillColor(21);
   c1->GetFrame()->SetBorderSize(12);
   c1->Modified();
}

