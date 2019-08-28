//  dsmceq - Dilute gas simulation using DSMC algorithm
//  This version illustrates the approach to equilibrium

#include "NumMeth.h"
#include "SortList.h"

// Random number generator; Uniform dist. in [0,1)
//double rand( long& seed ) {
// Input
//   seed    Integer seed (DO NOT USE A SEED OF ZERO)
// Output
//       rand    Random number uniformly distributed in [0,1)

//  const double a = 16807.0;
//  const double m = 2147483647.0;
//  double temp = a * seed;
//  seed = (long)(fmod(temp,m));
//  double rand = seed/m;
//  return( rand );
//}

int colider( Matrix& v, Matrix& crmax, double tau, long& seed,
              Matrix& selxtra, double coeff, SortList& sD ) {

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
    cout << "Loop over cells ... jcell = " << jcell << endl;
    int number = sD.cell_n[jcell];
    cout << "Point 1 " << endl;
    if( number < 2 ) continue;  // Skip to the next cell

    //* Determine number of candidate collision pairs
    //  to be selected in this cell
    cout << "Point 2 " << endl;
    double select = coeff*number*(number-1)*crmax(jcell) + selxtra(jcell);
    int nsel = (int)(select);      // Number of pairs to be selected
    selxtra(jcell) = select-nsel;  // Carry over any left-over fraction
    double crm = crmax(jcell);     // Current maximum relative speed

    //* Loop over total number of candidate collision pairs
    int isel;
    cout << "Point 3 " << endl;
    for( isel=1; isel<=nsel; isel++ ) {

      cout << "Loop over pairs ... isel = " << isel << endl;
      //* Pick two particles at random out of this cell
      int k = (int)(r->Uniform(0,1)*number);
      int kk = ((int)(k+r->Uniform(0,1)*(number-1))+1) % number;
      int ip1 = sD.Xref[ k+sD.index[jcell] ];      // First particle
      int ip2 = sD.Xref[ kk+sD.index[jcell] ];     // Second particle

      //* Calculate pair's relative speed
      cout << "Point 4 " << endl;
      double cr = sqrt( pow(v(ip1,1)-v(ip2,1),2) +
                        pow(v(ip1,2)-v(ip2,2),2) +   // Relative speed
                        pow(v(ip1,3)-v(ip2,3),2) );
      if( cr > crm )         // If relative speed larger than crm,
        crm = cr;            // then reset crm to larger value

      //* Accept or reject candidate pair according to relative speed
      cout << "Point 5 " << endl;
      if( cr/crmax(jcell) > r->Uniform(0,1) ) {
        cout << "Point 6 " << endl;
        //* If pair accepted, select post-collision velocities
        col++;                     // Collision counter
        cout << "Point 6b" << endl;
        Matrix vcm(3), vrel(3);
        cout << "Point 7 " << endl;
        int k;
        for( k=1; k<=3; k++ )
          vcm(k) = 0.5*(v(ip1,k) + v(ip2,k));      // Center of mass velocity
        double cos_th = 1.0 - 2.0*r->Uniform(0,1);      // Cosine and sine of
        double sin_th = sqrt(1.0 - cos_th*cos_th); // collision angle theta
        double phi = 2.0*pi*r->Uniform(0,1);            // Collision angle phi
        vrel(1) = cr*cos_th;             // Compute post-collision
        vrel(2) = cr*sin_th*cos(phi);    // relative velocity
        vrel(3) = cr*sin_th*sin(phi);
        for(  k=1; k<=3; k++ ) {
        cout << "Point 8 " << endl;
          v(ip1,k) = vcm(k) + 0.5*vrel(k);  // Update post-collision
          v(ip2,k) = vcm(k) - 0.5*vrel(k);  // velocities
        }

      } // Loop over pairs
      cout << "Point 9 " << endl;
      crmax(jcell) = crm;     // Update max relative speed
    }
  }   // Loop over cells
  cout << "Returning ... col = " << col << endl;
  return( col );
}

void sorter( Matrix& x, double L, SortList &sD ) {

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
    int j = (int)(x(ipart)*ncell/L) + 1;
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

void dsmceq() {

  //* Initialize constants  (particle mass, diameter, etc.)
  const double pi = 3.141592654;
  const double boltz = 1.3806e-23;    // Boltzmann's constant (J/K)
  double mass = 6.63e-26;       // Mass of argon atom (kg)
  double diam = 3.66e-10;       // Effective diameter of argon atom (m)
  double T;               // Temperature (K)
  double density = 1.78;        // Density of argon at STP (kg/m^3)
  double L = 1e-6;              // System size is one micron
  cout << "Enter number of simulation particles: ";
  int npart; cin >> npart;
  double eff_num = density/mass*L*L*L/npart;
  cout << "Each particle represents " << eff_num << " atoms" << endl;
  cout << "Enter the temperature (in Kelvin): ";
  cin >> T;
  TRandom3 *r = new TRandom3();


  //* Assign random positions and velocities to particles
  long seed = 1;       // Initial seed for rand (DO NOT USE ZERO)
  double v_init = sqrt(3.0*boltz*T/mass);    // Initial speed
  Matrix x(npart), v(npart,3);
  int i;
  for( i=1; i<=npart; i++ ) {
    x(i) = L*r->Uniform();   // Assign random positions
        int plusMinus = (1 - 2*((int)(2*r->Uniform())));
    v(i,1) = plusMinus * v_init;
        v(i,2) = 0.0;   // Only x-component is non-zero
        v(i,3) = 0.0;
  }

  //* Record inital particle speeds
  Matrix vmagI(npart);
  for( i=1; i<=npart; i++ )
        vmagI(i) = sqrt( v(i,1)*v(i,1) + v(i,2)*v(i,2) + v(i,3)*v(i,3) );

  //* Initialize variables used for evaluating collisions
  int ncell = 15;                       // Number of cells
  double tau = 0.2*(L/ncell)/v_init;    // Set timestep tau
  Matrix vrmax(ncell), selxtra(ncell);
  vrmax.set(3*v_init);    // Estimated max rel. speed
  selxtra.set(0.0);       // Used by routine "colider"
  double coeff = 0.5*eff_num*pi*diam*diam*tau/(L*L*L/ncell);
  int coltot = 0;         // Count total collisions

  //* Declare object for lists used in sorting
  SortList sortData(ncell,npart);

  //* Loop for the desired number of time steps
  cout << "Enter total number of time steps: ";
  int istep, nstep; cin >> nstep;
  for( istep = 1; istep<=nstep; istep++ ) {

    //* Move all the particles ballistically
        for( i=1; i<=npart; i++ ) {
      x(i) += v(i,1)*tau;          // Update x position of particle
      x(i) = fmod(x(i)+L,L);       // Periodic boundary conditions
        }
    //* Sort the particles into cells
    cout << "Calling sorter ... " << endl;
    sorter(x,L,sortData);

    //* Evaluate collisions among the particles
    cout << "Calling collider ... " << endl;
    int col = colider(v,vrmax,tau,seed,selxtra,coeff,sortData);
    cout << "Back from collider ... col = " << col << endl;
    coltot += col;      // Increment collision count

    //* Periodically display the current progress
    if( (istep%10) < 1 )
      cout << "Done " << istep << " of " << nstep << " steps; " <<
                 coltot << " collisions" << endl;
  }

  // Record final particle speeds
  Matrix vmagF(npart);
  for( i=1; i<=npart; i++ )
        vmagF(i) = sqrt( v(i,1)*v(i,1) + v(i,2)*v(i,2) + v(i,3)*v(i,3) );

  //* Print out the plotting variables: vmagI, vmagF
  ofstream vmagIOut("vmagI.txt"), vmagFOut("vmagF.txt");
  for( i=1; i<=npart; i++ ) {
    vmagIOut << vmagI(i) << endl;
    vmagFOut << vmagF(i) << endl;
  }
}

