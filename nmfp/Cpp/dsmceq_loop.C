//  dsmceq - Dilute gas simulation using DSMC algorithm
//  This version illustrates the approach to equilibrium
//  
//  Modifications:  Edward J. Brash
//  1.  Replace linear congruential random number generation with ROOT Mersenne Twister algorithm (TRandom3)
//  2.  Replace roll-your-own matrix class with ROOT matrix classes
//  3.  Add loop over number of particles and number of time steps to generate plots of these dependencies


#include <iostream>
#include <fstream>
#include "math.h"
#include "TMatrixD.h"
#include "SortList.h"
#include "TStopwatch.h"

Double_t fitfunction(Double_t *x, Double_t *par)
{
	Double_t Pi=3.14159265;
	Double_t a=0.5*pow(Pi/2.0,0.5)*par[1];
	Float_t xx = x[0];
	Double_t f = 1000.0/200.0*par[0]*pow(2.0/Pi,0.5)/pow(a,3)*xx*xx*exp(-1.0*xx*xx/(2.0*a*a));
	return f;
}

int colider( TMatrixD& v, TMatrixD& crmax, double tau, long& seed,
              TMatrixD& selxtra, double coeff, SortList& sD ) {

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

  int ncell = sD.ncell;
  int col = 0;          // Count number of collisions
  const double pi = 3.141592654;
  TRandom3 *r = new TRandom3();

  //* Loop over cells, processing collisions in each cell
  int jcell;
  for( jcell=1; jcell<=ncell; jcell++ ) {

    //* Skip cells with only one particle
    //cout << "Loop over cells ... jcell = " << jcell << endl;
    int number = sD.cell_n[jcell];
    //cout << "Point 1 " << endl;
    if( number < 2 ) continue;  // Skip to the next cell

    //* Determine number of candidate collision pairs
    //  to be selected in this cell
    //cout << "Point 2 " << endl;
    double select = coeff*number*(number-1)*crmax[jcell-1][0] + selxtra[jcell-1][0];
    int nsel = (int)(select);      // Number of pairs to be selected
    selxtra[jcell-1][0] = select-nsel;  // Carry over any left-over fraction
    double crm = crmax[jcell-1][0];     // Current maximum relative speed

    //* Loop over total number of candidate collision pairs
    int isel;
    //cout << "Point 3 " << endl;
    for( isel=1; isel<=nsel; isel++ ) {

      //cout << "Loop over pairs ... isel = " << isel << endl;
      //* Pick two particles at random out of this cell
      int k = (int)(r->Uniform(0,1)*number);
      int kk = ((int)(k+r->Uniform(0,1)*(number-1))+1) % number;
      int ip1 = sD.Xref[ k+sD.index[jcell] ];      // First particle
      int ip2 = sD.Xref[ kk+sD.index[jcell] ];     // Second particle

      //* Calculate pair's relative speed
      //cout << "Point 4 " << endl;
      double cr = sqrt( pow(v[ip1-1][0]-v[ip2-1][0],2) +
                        pow(v[ip1-1][1]-v[ip2-1][1],2) +   // Relative speed
                        pow(v[ip1-1][2]-v[ip2-1][2],2) );
      if( cr > crm )         // If relative speed larger than crm,
        crm = cr;            // then reset crm to larger value

      //* Accept or reject candidate pair according to relative speed
      //cout << "Point 5 " << endl;
      if( cr/crmax[jcell-1][0] > r->Uniform(0,1) ) {
        //cout << "Point 6 " << endl;
        //* If pair accepted, select post-collision velocities
        col++;                     // Collision counter
        //cout << "Point 6b" << endl;
        TMatrixD vcm(3,1), vrel(3,1);
        //cout << "Point 7 " << endl;
        int k;
        for( k=1; k<=3; k++ )
          vcm[k-1][0] = 0.5*(v[ip1-1][k-1] + v[ip2-1][k-1]);      // Center of mass velocity
        double cos_th = 1.0 - 2.0*r->Uniform(0,1);      // Cosine and sine of
        double sin_th = sqrt(1.0 - cos_th*cos_th); // collision angle theta
        double phi = 2.0*pi*r->Uniform(0,1);            // Collision angle phi
        vrel[0][0] = cr*cos_th;             // Compute post-collision
        vrel[1][0] = cr*sin_th*cos(phi);    // relative velocity
        vrel[2][0] = cr*sin_th*sin(phi);
        for(  k=1; k<=3; k++ ) {
        //cout << "Point 8 " << endl;
          v[ip1-1][k-1] = vcm[k-1][0] + 0.5*vrel[k-1][0];  // Update post-collision
          v[ip2-1][k-1] = vcm[k-1][0] - 0.5*vrel[k-1][0];  // velocities
        }

      } // Loop over pairs
      //cout << "Point 9 " << endl;
      crmax[jcell-1][0] = crm;     // Update max relative speed
    }
  }   // Loop over cells
  //cout << "Returning ... col = " << col << endl;
  return( col );
}

void sorter( TMatrixD& x, double L, SortList &sD ) {

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
  jx = new int [npart+1];
  for( ipart=1; ipart<=npart; ipart++ ) {
    int j = (int)(x[ipart-1][0]*ncell/L) + 1;
        jx[ipart] = ( j <= ncell ) ? j : ncell;
  }

  //* Count the number of particles in each cell
  int jcell;
  for( jcell=1; jcell<=ncell; jcell++ )
        sD.cell_n[ jcell ] = 0;
  for( ipart=1; ipart<=npart; ipart++ )
    sD.cell_n[ jx[ipart] ]++;

  //* Build index list as cumulative sum of the 
  //  number of particles in each cell
  int m=1;
  for( jcell=1; jcell<=ncell; jcell++ ) {
    sD.index[jcell] = m;
    m += sD.cell_n[jcell];
  }

  //* Build cross-reference list
  int *temp;
  temp = new int [ncell+1];       // Temporary array
  for( jcell=1; jcell<=ncell; jcell++ )
    temp[jcell] = 0;
  for( ipart=1; ipart<=npart; ipart++ ) {
    jcell = jx[ipart];       // Cell address of ipart
    int k = sD.index[jcell] + temp[jcell];
    sD.Xref[k] = ipart;
    temp[jcell] = temp[jcell] + 1;
  }

  delete [] jx;
  delete [] temp;

}

using namespace std;

void dsmceq_loop() {

  //* Initialize constants  (particle mass, diameter, etc.)
  const double pi = 3.141592654;
  const double boltz = 1.3806e-23;    // Boltzmann's constant (J/K)
  double mass = 6.63e-26;       // Mass of argon atom (kg)
  double diam = 3.66e-10;       // Effective diameter of argon atom (m)
  double T;               // Temperature (K)
  double density = 1.78;        // Density of argon at STP (kg/m^3)
  double L = 1e-6;              // System size is one micron
  //cout << "Enter number of simulation particles: ";
  //int npart; cin >> npart;
  int npart;

  TCanvas *c1 = new TCanvas("c1","Velocity Distributions",200,10,700,500);
  c1->Divide(1,1);
  TCanvas *c4 = new TCanvas("c4","Velocity Moments",200,10,700,500);
  c4->Divide(1,1);

  int iteration=0;
  
  double time_colider[100];
  double time_sorter[100];
  double time_mover[100];
  double time_total[100];
  double nparticles[100];
  double fitmean[100];
  double fitmeanerror[100];
  double ex[100];

  for(int icount=0; icount<100; icount++){
	  time_colider[icount]=0.0;
	  time_sorter[icount]=0.0;
	  time_mover[icount]=0.0;
	  time_total[icount]=0.0;
	  nparticles[icount]=0.0;
	  fitmean[icount]=0.0;
	  fitmeanerror[icount]=0.0;
	  ex[icount]=0.0;
  }

  npart=15000;
  for (T=300; T<301; T=T+20){

  nparticles[iteration]=T;	  

  double eff_num = density/mass*L*L*L/npart;
  cout << "Each particle represents " << eff_num << " atoms" << endl;
  //cout << "Enter the temperature (in Kelvin): ";
  //cin >> T;
  TRandom3 *r = new TRandom3();


  //* Assign random positions and velocities to particles
  long seed = 1;       // Initial seed for rand (DO NOT USE ZERO)
  double v_init = sqrt(3.0*boltz*T/mass);    // Initial speed
  TMatrixD x(npart,1), v(npart,3);
  int i;
  for( i=0; i<npart; i++ ) {
    x[i][0] = L*r->Uniform();   // Assign random positions
        int plusMinus = (1 - 2*((int)(2*r->Uniform())));
    v[i][0] = plusMinus * v_init;
        v[i][1] = 0.0;   // Only x-component is non-zero
        v[i][2] = 0.0;
  }

  //* Record inital particle speeds
  TMatrixD vmagI(npart,1);
  for( i=0; i<npart; i++ )
        vmagI[i][0] = sqrt( v[i][0]*v[i][0] + v[i][1]*v[i][1] + v[i][2]*v[i][2] );

  //* Initialize variables used for evaluating collisions
  int ncell = 15;                       // Number of cells
  double tau = 0.2*(L/ncell)/v_init;    // Set timestep tau
  TMatrixD vrmax(ncell,1), selxtra(ncell,1);
  for (i=0;i<ncell;i++){
	  vrmax[i][0]=3*v_init;
	  selxtra[i][0]=0.0;
  }
  double coeff = 0.5*eff_num*pi*diam*diam*tau/(L*L*L/ncell);
  int coltot = 0;         // Count total collisions

  //* Declare object for lists used in sorting
  SortList sortData(ncell,npart);

  //* Loop for the desired number of time steps
  //cout << "Enter total number of time steps: ";
  int istep, nstep;
  //nstep = 1024000/npart;
  nstep=40;

  TStopwatch timer_colider;
  TStopwatch timer_sorter;
  TStopwatch timer_total;
  TStopwatch timer_mover;
  timer_total.Start();
  for( istep = 0; istep<nstep; istep++ ) {

    //* Move all the particles ballistically
    timer_mover.Start();
    for( i=0; i<npart; i++ ) {
      	x[i][0] += v[i][0]*tau;          // Update x position of particle
      	x[i][0] = fmod(x[i][0]+L,L);       // Periodic boundary conditions
    }
    timer_mover.Stop();
    time_mover[iteration]+=timer_mover.RealTime();

    //* Sort the particles into cells
    //cout << "Calling sorter ... " << endl;
    timer_sorter.Start();
    sorter(x,L,sortData);
    timer_sorter.Stop();
    time_sorter[iteration]+=timer_sorter.RealTime();

    //* Evaluate collisions among the particles
    //cout << "Calling collider ... " << timer_colider.RealTime() << endl;
    timer_colider.Start();
    int col = colider(v,vrmax,tau,seed,selxtra,coeff,sortData);
    timer_colider.Stop();
    time_colider[iteration]+=timer_colider.RealTime();
    //cout << "Back from collider ... " << timer_colider.RealTime() << endl;
    //cout << "Back from collider ... col = " << col << endl;
    coltot += col;      // Increment collision count

    //* Periodically display the current progress
    if( (istep%10) < 1 )
      cout << "Done " << istep << " of " << nstep << " steps; " <<
                 coltot << " collisions" << endl;
  }

  timer_total.Stop();
  time_total[iteration]+=timer_total.RealTime();



  // Record final particle speeds
  TMatrixD vmagF(npart,1);
  TH1F *h1 = new TH1F("h1","Final velocity distribution",200,0.0,1000.0);
  TH1F *h2 = new TH1F("h2","Initial velocity distribution",200,0.0,1000.0);
  TH1F *h3 = new TH1F("h3","Final velocity first moment",200,0.0,1000.0);
  TH1F *h4 = new TH1F("h4","Initial velocity first moment",200,0.0,1000.0);
  for( i=1; i<=npart; i++ ) {
        vmagF[i-1][0] = sqrt( v[i-1][0]*v[i-1][0] + v[i-1][1]*v[i-1][1] + v[i-1][2]*v[i-1][2] );
  	//* Print out the plotting variables: vmagI, vmagF
  	h1->Fill(vmagF[i-1][0]);
	h2->Fill(vmagI[i-1][0]);
  	h3->Fill(vmagF[i-1][0],vmagF[i-1][0]);
	h4->Fill(vmagI[i-1][0],vmagI[i-1][0]);
  }

  
  TF1 *pfit1 = new TF1("fitfunction",fitfunction,0.0,1000.0,2);
  pfit1->SetParameters(12000.0,400.0);
  pfit1->SetParNames("N","Mean");
  pfit1->SetLineColor(2);
  c1->cd(iteration+1);
  h1->Fit("fitfunction","V");
  fitmean[iteration]=pfit1->GetParameter(1);
  fitmeanerror[iteration]=pfit1->GetParError(1);
  c4->cd(iteration+1);
  h3->Draw();

  cout << endl;
  cout << "Colider Real time = " << time_colider[iteration] << endl;
  cout << "Sorter Real time = " << time_sorter[iteration] << endl;
  cout << "Mover Real time = " << time_mover[iteration] << endl;
  cout << "Sum Total = " << time_mover[iteration]+time_colider[iteration]+time_sorter[iteration] << endl;
  cout << "Total Real time = " << time_total[iteration] << endl;
  cout << endl;
  
  iteration++;
  
  }  //end loop over different particle numbers

  TCanvas *c2 = new TCanvas("c2","Timing Dependencies",200,10,700,500);
  c2->Divide(2,2);
  c2->cd(1);
  gr1 = new TGraph(iteration,nparticles,time_total);
  gr1->SetMarkerStyle(22);
  gr1->Draw("ALP");
  c2->cd(2);
  gr2 = new TGraph(iteration,nparticles,time_colider);
  gr2->SetMarkerStyle(22);
  gr2->Draw("ALP");
  c2->cd(3);
  gr3 = new TGraph(iteration,nparticles,time_sorter);
  gr3->SetMarkerStyle(22);
  gr3->Draw("ALP");
  c2->cd(4);
  gr4 = new TGraph(iteration,nparticles,time_mover);
  gr4->SetMarkerStyle(22);
  gr4->Draw("ALP");
  
  TCanvas *c3 = new TCanvas("c3","Mean of Fit",200,10,700,500);
  c3->cd();
  grmean = new TGraphErrors(iteration,nparticles,fitmean,ex,fitmeanerror);
  grmean->SetMarkerStyle(22);
  grmean->Draw("AP");


  //ofstream vmagIOut("vmagI.txt"), vmagFOut("vmagF.txt");
  //for( i=1; i<=npart; i++ ) {
  //  vmagIOut << vmagI[i-1][0] << endl;
  //  vmagFOut << vmagF[i-1][0] << endl;
  //}
}

