#include <iostream>
#include <fstream>  
#include "math.h"
#include "TMatrixD.h"
#include "TRandom.h"
#include "SortList.h"         

using namespace std;

Double_t mb_fit(Double_t *x, Double_t *par){


    //par[0]=mass
    //par[1]=kB
    //par[2]=T

    
    Double_t pi = 3.141592654;
   Double_t EXP = 2.71828;

    Double_t f = 4*pi*pow(par[0]/(2*pi*par[1]*par[2]),1.5)*x[0]*x[0]*pow(EXP,-par[0]*x[0]*x[0]/(2*par[1]*par[2]));
    return f;

}

int colider( TMatrixD& v, TMatrixD& crmax, Double_t tau, TMatrixD& selxtra, Double_t coeff, SortList& sD ) {

// colide - Function to process collisions in cells
// Inputs
//    v         Velocities of the particles
//    crmax     Estimated maximum relative speed in a cell
//    tau       Time step
//    seed      Current random number seed
//    selxtra   Extra selections carried over from last timestep
//    coeff     Coefficient in computing number of selected pairs
//    sD        Object containing sorting lists
// Outputs
//    v         Updated velocities of the particles
//    crmax     Updated maximum relative speed
//    selxtra   Extra selections carried over to next timestep
//    col       Total number of collisions processed    (Return value)

  rand = new TRandom();
  int ncell = sD.ncell;
  int col = 0;          // Count number of collisions
  Double_t pi = 3.141592654;

  //* Loop over cells, processing collisions in each cell
  int jcell;
  for( jcell=0; jcell<ncell; jcell++ ) {

    //* Skip cells with only one particle
    int number = sD.cell_n[jcell];
    if( number < 2 ) continue;  // Skip to the next cell

    //* Determine number of candidate collision pairs
    //  to be selected in this cell
    Double_t select = coeff*number*(number-1)*crmax[jcell][0] + selxtra[jcell][0];
    int nsel = (int)(select);      // Number of pairs to be selected
    selxtra[jcell][0] = select-nsel;  // Carry over any left-over fraction
    Double_t crm = crmax[jcell][0];     // Current maximum relative speed

    //* Loop over total number of candidate collision pairs
    int isel;
    for( isel=0; isel<nsel; isel++ ) {

      //* Pick two particles at random out of this cell
      int k = (int)(rand->Rndm()*number);
      int kk = ((int)(k+rand->Rndm()*(number-1))+1) % number;
      int ip1 = sD.Xref[ k+sD.index[jcell] ];      // First particle
      int ip2 = sD.Xref[ kk+sD.index[jcell] ];     // Second particle

      //* Calculate pair's relative speed
      Double_t cr = sqrt( pow(v[ip1][0]-v[ip2][0],2) +
                        pow(v[ip1][1]-v[ip2][1],2) +   // Relative speed
                        pow(v[ip1][2]-v[ip2][2],2) );
      if( cr > crm )         // If relative speed larger than crm,
        crm = cr;            // then reset crm to larger value

      //* Accept or reject candidate pair according to relative speed
      if( cr/crmax[jcell][0] > rand->Rndm() ) {
        //* If pair accepted, select post-collision velocities
        col++;                     // Collision counter
        TMatrixD vcm(3,1);
        TMatrixD vrel(3,1);
        int k;
        for( k=0; k<3; k++ )
          vcm[k][0] = 0.5*(v[ip1][k] + v[ip2][k]);      // Center of mass velocity
        Double_t cos_th = 1.0 - 2.0*rand->Rndm();      // Cosine and sine of
        Double_t sin_th = sqrt(1.0 - cos_th*cos_th); // collision angle theta
        Double_t phi = 2.0*pi*rand->Rndm();            // Collision angle phi
        vrel[0][0] = cr*cos_th;             // Compute post-collision
        vrel[1][0] = cr*sin_th*cos(phi);    // relative velocity
        vrel[2][0] = cr*sin_th*sin(phi);
        for(  k=0; k<3; k++ ) {
          v[ip1][k] = vcm[k][0] + 0.5*vrel[k][0];  // Update post-collision
          v[ip2][k] = vcm[k][0] - 0.5*vrel[k][0];  // velocities
        }

      } // Loop over pairs
      crmax[jcell][0] = crm;     // Update max relative speed
    }
  }   // Loop over cells
  return( col );
}

void sorter( TMatrixD& x, Double_t L, SortList &sD ) {

// sorter - Function to sort particles into cells
// Inputs
//    x       Positions of particles
//    L       System size
//    sD      Object containing lists used in sorting
// Output
//    sD      Object containing lists used in sorting

  //* Find the cell address for each particle
  int ncell = sD.ncell;
  int npart = sD.npart;
  int ipart, *jx;
  jx = new int [npart];
  for( ipart=0; ipart<npart; ipart++ ) {
    int j = (int)(x[ipart][0]*ncell/L) + 1;
	jx[ipart] = ( j <= ncell ) ? j : ncell;
  }

  //* Count the number of particles in each cell
  int jcell;
  for( jcell=0; jcell<ncell; jcell++ )
	sD.cell_n[ jcell ] = 0;
  for( ipart=0; ipart<npart; ipart++ )
    sD.cell_n[ jx[ipart] ]++;

  //* Build index list as cumulative sum of the 
  //  number of particles in each cell
  int m=1;
  for( jcell=0; jcell<ncell; jcell++ ) {
    sD.index[jcell] = m;
    m += sD.cell_n[jcell];
  }

  //* Build cross-reference list
  int *temp;
  temp = new int [ncell];	  // Temporary array
  for( jcell=0; jcell<ncell; jcell++ )
    temp[jcell] = 0;
  for( ipart=0; ipart<npart; ipart++ )	{
    jcell = jx[ipart];       // Cell address of ipart
    int k = sD.index[jcell] + temp[jcell];
    sD.Xref[k] = ipart;
    temp[jcell] = temp[jcell] + 1;
  }

  delete [] jx;
  delete [] temp;

}
			  
int graph_gas_mean() {

  rand = new TRandom3();

  //* Initialize constants  (particle mass, diameter, etc.)
  Double_t pi = 3.141592654;
  Double_t boltz = 1.3806e-23;    // Boltzmann's constant (J/K)
  Double_t mass = 6.63e-26;       // Mass of argon atom (kg)
  Double_t diam = 3.66e-10;       // Effective diameter of argon atom (m)
  Double_t T = 20;               // Temperature (K)
  Double_t density = 1.78;        // Density of argon at STP (kg/m^3)
  Double_t L = 1e-6;              // System size is one micron
  cout << "Enter number of simulation particles: "; 
  int npart; cin >> npart;
  Double_t eff_num = density/mass*L*L*L/npart;
  cout << "Each particle represents " << eff_num << " atoms" << endl;

  for(int j=0;j<15;j++){

  //* Assign random positions and velocities to particles
  Double_t v_init = sqrt(3.0*boltz*T/mass);    // Initial speed
  TMatrixD x(npart,1);
  TMatrixD v(npart,3);
  int i;
  for( i=0; i<npart; i++ ) {
    x[i][0] = L*rand->Rndm();   // Assign random positions
	int plusMinus = (1 - 2*((int)(2*rand->Rndm())));
    v[i][0] = plusMinus * v_init;
	v[i][1] = 0.0;	// Only x-component is non-zero
	v[i][2] = 0.0;
  }

  //* Record inital particle speeds
  TMatrixD vmagI(npart,1);
  for( i=0; i<npart; i++ )
	vmagI[i][0] = sqrt( v[i][0]*v[i][0] + v[i][1]*v[i][1] + v[i][2]*v[i][2] );

  //* Initialize variables used for evaluating collisions
  int ncell = 15;                       // Number of cells
  Double_t tau = 0.2*(L/ncell)/v_init;    // Set timestep tau
  TMatrixD vrmax(ncell,1);
  TMatrixD selxtra(ncell,1);
  for(i=0;i<ncell;i++){
      vrmax[i][0] = 3*v_init;
  }
   for(i=0;i<ncell;i++){
      selxtra[i][0] = 0.0;
  }

  Double_t coeff = 0.5*eff_num*pi*diam*diam*tau/(L*L*L/ncell);
  int coltot = 0;         // Count total collisions

  //* Declare object for lists used in sorting
  SortList sortData(ncell,npart);  

  //* Loop for the desired number of time steps
  cout << "Enter total number of time steps: ";
  int istep, nstep; cin >> nstep;
  for( istep = 0; istep<nstep; istep++ ) {
	
    //* Move all the particles ballistically
	for( i=0; i<npart; i++ ) {
      x[i][0] += v[i][0]*tau;          // Update x position of particle
      x[i][0] = fmod(x[i][0]+L,L);       // Periodic boundary conditions
	}
    //* Sort the particles into cells
    sorter(x,L,sortData);
  
    //* Evaluate collisions among the particles
    int col = colider(v,vrmax,tau,selxtra,coeff,sortData);
    coltot += col;	// Increment collision count
    
    //* Periodically display the current progress
    if( (istep%10+1) < 1 )
      cout << "Done " << istep << " of " << nstep << " steps; " << 
	         coltot << " collisions" << endl;
  }

  // Record final particle speeds
  TMatrixD vmagF(npart,15);
  for( i=0; i<npart; i++ )
	vmagF[i][j] = sqrt( v[i][0]*v[i][0] + v[i][1]*v[i][1] + v[i][2]*v[i][2] );

  T+=20;
  cout << "T = " << T << endl;
  }

  gStyle->SetOptFit(1);	
   TCanvas *c1 = new TCanvas("c1","Equilibrium velocities",200,10,700,500);
   c1->SetFillColor(42);
   c1->SetGrid();

   TH1F *h1 = new TH1F("Equilibrium velocities", ";v;N", npart/10, 0.0, v_init*3);
   TH1F *h2 = new TH1F("Equilibrium velocities", ";v;N", npart/10, 0.0, v_init*3);
   TH1F *h3 = new TH1F("Equilibrium velocities", ";v;N", npart/10, 0.0, v_init*3);
   TH1F *h4 = new TH1F("Equilibrium velocities", ";v;N", npart/10, 0.0, v_init*3);
   TH1F *h5 = new TH1F("Equilibrium velocities", ";v;N", npart/10, 0.0, v_init*3);
   TH1F *h6 = new TH1F("Equilibrium velocities", ";v;N", npart/10, 0.0, v_init*3);
   TH1F *h7 = new TH1F("Equilibrium velocities", ";v;N", npart/10, 0.0, v_init*3);
   TH1F *h8 = new TH1F("Equilibrium velocities", ";v;N", npart/10, 0.0, v_init*3);
   TH1F *h9 = new TH1F("Equilibrium velocities", ";v;N", npart/10, 0.0, v_init*3);
   TH1F *h10 = new TH1F("Equilibrium velocities", ";v;N", npart/10, 0.0, v_init*3);
   TH1F *h11 = new TH1F("Equilibrium velocities", ";v;N", npart/10, 0.0, v_init*3);
   TH1F *h12 = new TH1F("Equilibrium velocities", ";v;N", npart/10, 0.0, v_init*3);
   TH1F *h13 = new TH1F("Equilibrium velocities", ";v;N", npart/10, 0.0, v_init*3);
   TH1F *h14 = new TH1F("Equilibrium velocities", ";v;N", npart/10, 0.0, v_init*3);
   TH1F *h15 = new TH1F("Equilibrium velocities", ";v;N", npart/10, 0.0, v_init*3);

   for(int i=0;i<npart;i++){
        h1->Fill(vmagF[i][0]);
        h2->Fill(vmagF[i][1]);
        h3->Fill(vmagF[i][2]);
        h4->Fill(vmagF[i][3]);
        h5->Fill(vmagF[i][4]);
        h6->Fill(vmagF[i][5]);
        h7->Fill(vmagF[i][6]);
        h8->Fill(vmagF[i][7]);
        h9->Fill(vmagF[i][8]);
        h10->Fill(vmagF[i][9]);
        h11->Fill(vmagF[i][10]);
        h12->Fill(vmagF[i][11]);
        h13->Fill(vmagF[i][12]);
        h14->Fill(vmagF[i][13]);
        h15->Fill(vmagF[i][14]);
   }

    Double_t means[15];
means[0]=h1->GetMean(1);
means[1]=h2->GetMean(1);
means[2]=h3->GetMean(1);
means[3]=h4->GetMean(1);
means[4]=h5->GetMean(1);
means[5]=h6->GetMean(1);
means[6]=h7->GetMean(1);
means[7]=h8->GetMean(1);
means[8]=h9->GetMean(1);
means[9]=h10->GetMean(1);
means[10]=h11->GetMean(1);
means[11]=h12->GetMean(1);
means[12]=h13->GetMean(1);
means[13]=h14->GetMean(1);
means[14]=h15->GetMean(1);
    Double_t x_axis[15];
    for(int i=0;i<15;i++){
       x_axis[i]=i+1;  
    }

    gr=new TGraph(15,x_axis,means);
    gr->SetMarkerStyle(6);
   gr->SetMarkerColor(4);
   gr->SetLineColor(4);
   gr->Draw("P");
   
   /*h1->SetMinimum(0.0);
   TF1 *mbfitline = new TF1("Maxwell-Boltzmann",mb_fit, 0, 1200,3);
   mbfitline->SetParameter(0,6.63e-26);
   mbfitline->SetParameter(1,1.3806485e-23);
   mbfitline->SetParameter(2,300);*/
   //h1->Fit("Maxwell-Boltzmann","V");
   //h1->Draw();
   cout << "a = " << a_const << endl;
   
   //par[0]=mass
    //par[1]=kB
    //par[2]=T

   
}
