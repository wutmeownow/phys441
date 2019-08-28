#include <ostream>
#include <TMath.h>

void graph_advect() {

   //
   //Modified: Edward J. Brash
   //		
 
  //* Select numerical parameters (time step, grid spacing, etc.).
  cout << "Choose a numerical method: 1) FTCS, 2) Lax, 3) Lax-Wendroff : ";
  int method; cin >> method;
  cout << "Enter number of grid points: "; const int N; cin >> N;
  double L = 1.;     // System size
  double h = L/N;    // Grid spacing
  double c = 1;      // Wave speed
  cout << "Time for wave to move one grid spacing is " << h/c << endl;
  cout << "Enter time step: "; double tau; cin >> tau;
  double coeff = -c*tau/(2.*h);    // Coefficient used by all schemes
  double coefflw = 2*coeff*coeff;  // Coefficient used by L-W scheme
  cout << "Wave circles system in " << L/(c*tau) << " steps" << endl;
  cout << "Enter number of steps: "; int nStep; cin >> nStep;

  //* Set initial and boundary conditions.
  const double pi = 3.141592654;
  double sigma = 0.1;              // Width of the Gaussian pulse
  double k_wave = pi/sigma;        // Wave number of the cosine
  double x[N], a[N], a_start[N], a_new[N];
  int i,j;
  for( i=0; i<N; i++ ) {
  	x[i] = (i+0.5)*h - L/2;  // Coordinates of grid points
  	// Initial condition is a Gaussian-cosine pulse
 	a[i] = cos(k_wave*x[i]) * exp(-x[i]*x[i]/(2*sigma*sigma));
  	a_start[i]=a[i];
  }
  // Use periodic boundary conditions
  int *ip, *im;  ip = new int [N+1];  im = new int [N+1];
  for( i=1; i<N-1; i++ ) {
  ip[i] = i+1;    // ip[i] = i+1 with periodic b.c.
  im[i] = i-1;    // im[i] = i-1 with periodic b.c.
  }
  ip[0] = 1;  ip[N-1] = 0;
  im[0] = N-1;  im[N-1] = N-2;

  //* Initialize plotting variables.
  int iplot = 0;          // Plot counter
  const int nplotsd = 50;        // Desired number of plots
  double plotStep = ((double)nStep)/nplotsd;
  double aplot[N][nplotsd+1], tplot[nplotsd+1];
  tplot[0] = 0;       // Record the initial time (t=0)
  for( i=0; i<N; i++ )
  	aplot[i][0] = a[i];  // Record the initial state

  //* Loop over desired number of steps.^M
  int iStep;
  for( iStep=0; iStep<nStep; iStep++ ) {
  
     //* Compute new values of wave amplitude using FTCS, 
     //  Lax or Lax-Wendroff method.
     if( method == 1 ) {      ////// FTCS method //////
         for( i=0; i<N; i++ ){
         	a_new[i] = a[i] + coeff*( a[ip[i]]-a[im[i]] );
	 }
     } else if( method == 2 ) { ////// Lax method //////
    	 for( i=0; i<N; i++ ) {
              a_new[i] = 0.5*( a[ip[i]]+a[im[i]] ) + coeff*( a[ip[i]]-a[im[i]] );
	 }
     } else {                   ////// Lax-Wendroff method //////
         for( i=0; i<N; i++ ) {
              a_new[i] = a[i] + coeff*( a[ip[i]]-a[im[i]] ) + coefflw*( a[ip[i]]+a[im[i]]-2*a[i] );
	 }
     }

     for ( i=0; i<N; i++) a[i] = a_new[i];   // Reset with new amplitude values
   
     //* Periodically record a(t) for plotting.
     if( fmod((double)iStep,plotStep) < 1 ) {
	tplot[iplot]=tau*iStep;
        for( i=0; i<N; i++ )
            aplot[i][iplot] = a[i];       // Record a(i) for ploting
      	iplot++;
        cout << iStep << " out of " << nStep << " steps completed" << endl;
     }
  }        
  int nplots = iplot;   // Actual number of plots recorded
  int npoints = N;

  TH2D *h1 = new TH2D("h1","xx",npoints,x[0],x[N-1],nplots,0,nplots-1);
  for (i=0;i<N;i++){
	  for(j=0;j<nplots;j++){
		  h1->Fill(x[i],j,aplot[i][j]);
	  }
  }
 
  cout << "Done ... " <<endl; 

   TCanvas *c1 = new TCanvas("c1","Initial and Final Pulses",200,10,700,500);
   c1->SetFillColor(42);
   c1->SetGrid();
   TCanvas *c2 = new TCanvas("c2","Time Evolution of Pulse",200,10,700,500);
   c2->SetFillColor(42);
   c2->SetGrid();

   grstart = new TGraph(npoints,x,a_start);
   grend = new TGraph(npoints,x,a);
   
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

