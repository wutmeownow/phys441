#include <ostream>
#include <TMath.h>
#include <TMatrixD.h>

void graph_schro() {

   //
   //Modified: Edward J. Brash
   //		
 
  //* Initialize parameters (time step, grid spacing, etc.).
  //* Hartree atomic units:  e = m_e = h_bar = k_e = k_B = 1
  //* Length scale = Bohr radius = 0.529 x 10^-11 m
  //* Energy scale = 27.211 eV = 2 Rydbergs
  //* Time scale = 2.149 x 10^-17 seconds
  //
  //* Note:  For an electron in the ground state of hydrogen, in Hartree units:
  //
  //		velocity = 1
  //		radius = 1
  //		angular momentum = 1
  //		ionization energy = 0.5
  //
  //		(In the Bohr Model)
  //
  cout << "Enter number of grid points: "; Int_t N; cin >> N;
  const Int_t NN = N;
  double L = 100.;     // System extends from -L/2 to L/2 (+/- 25 Angstroms)
  double h = L/(N-1);    // Grid spacing
  double h_bar = 1; double mass = 1;     // Natural Hartree atomic units
  cout << "Enter time step: "; Double_t tau; cin >> tau;
  TMatrixD x(NN,1);
  int i,j,k;

  for (i=0;i<N;i++){
	  x[i][0]=h*i-L/2;
  }

  //* Initialize Identity and Hamiltonian Matrices
  TMatrixD eye(NN,NN), ham(NN,NN);
  double coeff = -h_bar*h_bar/(2.0*mass*h*h);
  for(i=0;i<N;i++){
	  //cout << "i: " << i << endl;
	  for(j=0;j<N;j++){
		  if(j==i-1){
			  ham[i][j]=coeff;
			  eye[i][j]=0.0;
		  }else if(j==i+1){
			  ham[i][j]=coeff;
			  eye[i][j]=0.0;
		  }else if(j==i){
			  ham[i][j]=-2.0*coeff;
			  eye[i][j]=1.0;
		  }else{
			  ham[i][j]=0.0;
			  eye[i][j]=0.0;
		  }
		  if(i==0 && j==N-1) ham[0][N-1]=coeff;
		  if(i==N-1 && j==0) ham[N-1][0]=coeff;
		  //cout << "j: " << j << " " << ham[i][j] << " ";
	  }
	  //cout << endl;
  }
  
  //* Periodic Boundary Conditions first and last rows
  //ham[0][N-1]=coeff; ham[0][0]=-2.0*coeff; ham[0][1]=coeff;
  //ham[N-1][N-2]=coeff; ham[N-1][N-1]=-2.0*coeff; ham[N-1][0]=coeff;
  
  //* Crank-Nicolson Matrix
  TMatrixD RealA(NN,NN), ImagA(NN,NN), RealB(NN,NN), ImagB(NN,NN);
  TMatrixD CMatrix(2*NN,2*NN);

  for(i=0;i<N;i++){
	  for(j=0;j<N;j++){
		  RealA[i][j]=eye[i][j];
		  ImagA[i][j]=0.5*tau/h_bar*ham[i][j];
		  RealB[i][j]=eye[i][j];
		  ImagB[i][j]=-0.5*tau/h_bar*ham[i][j];
		  CMatrix[i][j]=RealA[i][j]; CMatrix[i][j+N]=ImagA[i][j];
		  CMatrix[i+N][j]=-ImagA[i][j]; CMatrix[i+N][j+N]=RealA[i][j];
	  }
  }

  Double_t det;
  CMatrix.InvertFast(&det);

  TMatrixD RealAi(NN,NN), ImagAi(NN,NN);

  for(i=0;i<N;i++){
	  for(j=0;j<N;j++){
		  RealAi[i][j]=CMatrix[i][j];
		  ImagAi[i][j]=CMatrix[i][j+N];
	  }
  }
  
  TMatrixD RealD(NN,NN), ImagD(NN,NN);

  for(i=0;i<N;i++){
	  for(j=0;j<N;j++){
		  RealD[i][j]=0.0;
		  ImagD[i][j]=0.0;
		  for(k=0;k<N;k++){
			  RealD[i][j] += RealAi[i][k]*RealB[k][j] - ImagAi[i][k]*ImagB[k][j];
			  ImagD[i][j] += RealAi[i][k]*ImagB[k][j] + ImagAi[i][k]*RealB[k][j];
		  }
	  }
  }
  
  //* Initialize the wavefunction 
  const double pi = 3.141592654;
  double x0 =0;				// Location of the center of wavepacket
  double velocity = 0.5;		// Average velocity of wavepacket
  					// From T= 1/2 m v^2:  T = 0.5*1*0.5^2 = 0.125 Hartree
					// T = 27.2*0.125 = 3.4 eV
					// Using L = 100 * 0.529x10^11m = 5.29x10^-9 m
					// v_actual = sqrt(2T/m) = 1.0935 x 10^6 m/s
					// time = 4.837 x 10^-15 seconds
					// time = 4.837x10^-15/2.419x10^-17 = 200 units
					// So, for a timestep of 1, require 200 steps
					//     for a timestep of 0.1, require 2000 steps
					//
  double k0 = mass*velocity/h_bar;	// Average wavenumber
  double sigma0 = L/10.0;		// Std. Dev. of the WF
  double Norm_psi = 1.0/(sqrt(sigma0*sqrt(pi)));	// Normalization
  TMatrixD RealPsi(NN,1), ImagPsi(NN,1);
  double rpi[N], ipi[N], rpf[N], ipf[N], xplot[N];
  
  for( i=0; i<N; i++ ) {
	  double expFactor = exp(-(x[i][0]-x0)*(x[i][0]-x0)/(2*sigma0*sigma0));
	  RealPsi[i][0] = Norm_psi*cos(k0*x[i][0])*expFactor;
	  ImagPsi[i][0] = Norm_psi*sin(k0*x[i][0])*expFactor;
	  rpi[i]=RealPsi[i][0];
	  ipi[i]=ImagPsi[i][0];
	  xplot[i]=x[i][0];
  }

  //* Initialize loop variables
  int nStep = (int)(L/(velocity*tau)); 	// Particle should circle system
  const int nplotsd = 20;			// Number of plots to record
  double plotStep = nStep/nplotsd;	// Iterations between plots
  double p_plot[N][nplotsd+1], tplot[nplotsd+1];

  //* Record intitial prob dist and time
  for( i=0; i<N; i++ ) {
	  p_plot[i][0]= RealPsi[i][0]*RealPsi[i][0]+ImagPsi[i][0]*ImagPsi[i][0];
  }
  tplot[0]=0;
  int iplot = 0;
 
  //* Loop over desired number of steps.^M
  int iStep;
  TMatrixD RealNewPsi(NN,1), ImagNewPsi(NN,1);
  for( iStep=0; iStep<nStep; iStep++ ) {

	  for (i=0;i<N;i++){
		  RealNewPsi[i][0]=0; ImagNewPsi[i][0]=0;
	  }
	  
	  for (i=0;i<N;i++){
		  for (j=0;j<N;j++ ){
			  RealNewPsi[i][0] += RealD[i][j]*RealPsi[j][0] - ImagD[i][j]*ImagPsi[j][0];
			  ImagNewPsi[i][0] += RealD[i][j]*ImagPsi[j][0] + ImagD[i][j]*RealPsi[j][0];
		  }
	  }

	  for (i=0;i<N;i++){
	  		RealPsi[i][0] = RealNewPsi[i][0];  // Copy new values into Psi
	  		ImagPsi[i][0] = ImagNewPsi[i][0];
	  }
	  
	  //for (i=0;i<N;i++){
	  //  cout << RealPsi[i][0] << " ";
	  //}
	  //cout << endl;
	  //for (i=0;i<N;i++){
	  //	  cout << ImagPsi[i][0] << " ";
	  //}
	  //cout << endl;

     //* Periodically record a(t) for plotting.
     if( fmod((double)(iStep+1),plotStep) < 1 ) {
	tplot[iplot]=tau*iStep;
        for( i=0; i<N; i++ ){
            p_plot[i][iplot] = RealPsi[i][0]*RealPsi[i][0]+ImagPsi[i][0]*ImagPsi[i][0];       // Record for plotting
	}
	iplot++;
        cout << iStep+1 << " out of " << nStep << " steps completed" << endl;
     }
  }        
  int nplots = iplot;   // Actual number of plots recorded
  int npoints = N;

  TH2D *h1 = new TH2D("h1","xx",npoints,xplot[0],xplot[N-1],nplots,0,nplots);
  for (i=0;i<N;i++){
	  rpf[i]=RealPsi[i][0];
	  ipf[i]=ImagPsi[i][0];
	  for(j=0;j<nplots;j++){
		  h1->Fill(xplot[i],j,p_plot[i][j]);
	  }
  }
 
  cout << "Done ... " <<endl; 

   TCanvas *c1 = new TCanvas("c1","Initial and Final States",200,10,700,500);
   c1->SetFillColor(42);
   c1->SetGrid();
   c1->Divide(1,2);
   TCanvas *c2 = new TCanvas("c2","Time Evolution of Probability Density",200,10,700,500);
   c2->SetFillColor(42);
   c2->SetGrid();

   TGraph* grstart = new TGraph(npoints,xplot,rpi);
   TGraph *grend = new TGraph(npoints,xplot,rpf);
   TGraph *gistart = new TGraph(npoints,xplot,ipi);
   TGraph *giend = new TGraph(npoints,xplot,ipf);
   
   grstart->SetLineColor(2);
   grend->SetLineColor(4);
   gistart->SetLineColor(2);
   giend->SetLineColor(4);
   
   c1->cd(1);
   grend->Draw("AL");
   grstart->Draw("L");
   c1->cd(2);
   giend->Draw("AL");
   gistart->Draw("L");
   c2->cd();
   h1->Draw("LEGO");

   // TCanvas::Update() draws the frame, after which one can change it
   c1->Update();
   c1->GetFrame()->SetFillColor(21);
   c1->GetFrame()->SetBorderSize(12);
   c1->Modified();
}

