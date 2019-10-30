#include <ostream>
#include <TMath.h>

void graph_traffic() {

   //
   //Modified: Edward J. Brash
   //		
 
  //* Select numerical parameters (time step, grid spacing, etc.).
  cout << "Choose a numerical method: 1) FTCS, 2) Lax, 3) Lax-Wendroff : ";
  int method; cin >> method;
  cout << "Enter number of grid points: "; const int N; cin >> N;
  double L = 800.;     // System size
  double h = L/N;    // Grid spacing
  double v_max = 25;      // Wave speed
  cout << "Suggested timestep is " << h/v_max << endl;
  cout << "Enter time step: "; double tau; cin >> tau;
  cout << "Last car starts moving after "
       << (L/8)/(v_max*tau) << " steps" << endl;
  cout << "Enter number of steps: "; const int nStep; cin >> nStep;
  double coeff = tau/(2.*h);    // Coefficient used by all schemes
  double coefflw = 2*coeff*coeff;  // Coefficient used by L-W scheme
  double cp, cm; 	// Variable used by Lax-Wendroff

  //* Set initial and boundary conditions.
  double rho_max = 1.0;                  // Maximum density
  double Flow_max = 0.25*rho_max*v_max;  // Maximum Flow
  // Initial condition is a square pulse from x = -L/4 to x = 0
  double rho[N], rho_new[N], rho_start[N];
  int i,j, iBack=N/8, iFront=N/4-1;
  for( i=0; i<N; i++ ) {
	  if ( iBack <=i && i <= iFront) {
		  rho[i]=rho_max;
	  }else{
		  rho[i]=0.0;
	  }
	  rho_start[i]=rho[i];
  }
  rho[iFront+1] = rho_max/2;
  // Use periodic boundary conditions
  int *ip, *im;  ip = new int [N+1];  im = new int [N+1];
  for( i=1; i<N-1; i++ ) {
  ip[i] = i+1;    // ip[i] = i+1 with periodic b.c.
  im[i] = i-1;    // im[i] = i-1 with periodic b.c.
  }
  ip[0] = 1;  ip[N-1] = 0;
  im[0] = N-1;  im[N-1] = N-2;

  //* Initialize plotting variables.
  int iplot = 1;
  double tplot[nStep+1], xplot[N], rplot[N][nStep+1];
  tplot[0] = 0.0;             // Record initial time
  for( i=0; i<N; i++ ) {
	    xplot[i] = (i + 0.5)*h - L/2;  // Record x scale for plot
	    rplot[i][0] = rho[i];           // Record the initial state
  }

  //* Loop over desired number of steps.^M
  double Flow[N];
  int iStep;
  for( iStep=0; iStep<nStep; iStep++ ) {

    //* Compute the flow = (Density)*(Velocity)
    for( i=0; i<N; i++ ) {
	    Flow[i] = rho[i] * (v_max*(1.0 - rho[i]/rho_max));
    }
     //* Compute new values of wave amplitude using FTCS, 
     //  Lax or Lax-Wendroff method.
     if( method == 1 ) {      ////// FTCS method //////
         for( i=0; i<N; i++ ){
         	rho_new[i] = rho[i] - coeff*( Flow[ip[i]]-Flow[im[i]] );
	 }
     } else if( method == 2 ) { ////// Lax method //////
    	 for( i=0; i<N; i++ ) {
              rho_new[i] = 0.5*( rho[ip[i]]+rho[im[i]] ) - coeff*( Flow[ip[i]]-Flow[im[i]] );
	 }
     } else {                   ////// Lax-Wendroff method //////
         for( i=0; i<N; i++ ) {
	      cp = v_max*(1 - (rho[ip[i]]+rho[i])/rho_max);
	      cm = v_max*(1 - (rho[i]+rho[im[i]])/rho_max);
              rho_new[i] = rho[i] - coeff*( Flow[ip[i]]-Flow[im[i]] ) + coefflw*( cp*(Flow[ip[i]]-Flow[i]) - cm*(Flow[i]-Flow[im[i]]) );
	 }
     }

     for ( i=0; i<N; i++) {
	     rho[i] = rho_new[i];   // Reset with new amplitude values
     }

     tplot[iplot]=tau*(iStep+1);
     for( i=0; i<N; i++ ) {
	     rplot[i][iplot] = rho[i];       // Record a(i) for ploting
     }
     iplot++;
  }        

  int nplots = iplot;   // Actual number of plots recorded
  int npoints = N;

  TH2D *h1 = new TH2D("h1","xx",npoints,xplot[0],xplot[N-1],nplots,tplot[0],tplot[nplots-1]);
  for (i=0;i<N;i++){
	  for(j=0;j<nplots;j++){
		  h1->Fill(xplot[i],tplot[j],rplot[i][j]);
	  }
  }
 
  cout << "Done ... " <<endl; 

   TCanvas *c1 = new TCanvas("c1","Initial and Final Pulses",200,10,700,500);
   c1->SetFillColor(42);
   c1->SetGrid();
   TCanvas *c2 = new TCanvas("c2","Time Evolution of Pulse",200,10,700,500);
   c2->SetFillColor(42);
   c2->SetGrid();

   TGraph *grstart = new TGraph(npoints,xplot,rho_start);
   TGraph *grend = new TGraph(npoints,xplot,rho);
   
   grstart->SetLineColor(2);
   grend->SetLineColor(4);
   
   c1->cd();
   grend->Draw("AL");
   grstart->Draw("L");
   c2->cd();
   h1->Draw("LEGO");

   // TCanvas::Update() draws the frame, after which one can change it
   c1->Update();
   c1->GetFrame()->SetFillColor(21);
   c1->GetFrame()->SetBorderSize(12);
   c1->Modified();
}

