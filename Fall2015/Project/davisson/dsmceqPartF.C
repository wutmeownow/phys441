//  dsmceq - Dilute gas simulation using DSMC algorithm
//  This version illustrates the approach to equilibrium
         
#include "TMatrixD.h"
//#include <iostream>
//#include <fstream>
#include "TRandom3.h"
#include "TStopwatch.h"

using namespace std;

class SortList {

public:

// Class data (sorting lists)
int ncell, npart, *cell_n, *index, *Xref;

// Default Constructor. 
SortList() {
  initLists(1,1);
}

// Regular Constructor. 
SortList(int ncell_in, int npart_in) {
  initLists(ncell_in,npart_in);
}


// Destructor. Called when a SortList object goes out of scope.
~SortList() {
  delete [] cell_n;   // Release allocated memory
  delete [] index;
  delete [] Xref;
}

//*********************************************************

private:

// Initialization routine
void initLists(int ncell_in, int npart_in) {
  ncell = ncell_in;
  npart = npart_in;
  cell_n = new int [ncell+1];  // Allocate memory
  index = new int [ncell+1];
  Xref = new int [npart+1];
  int i;
  for( i=1; i<=ncell; i++ ) {
	cell_n[i] = 0;
	index[i] = 0;
  }
  for( i=1; i<=npart; i++ )
	Xref[i] = 0;
}

}; // Class SortList



//double rand( long& seed );
			  
void dsmceqPartF() {

  //* Initialize constants  (particle mass, diameter, etc.)
  TRandom3 *rnum = new TRandom3();
  TStopwatch *totalTime = new TStopwatch();
  TStopwatch *coliderTime = new TStopwatch();
  TStopwatch *sorterTime = new TStopwatch();
  totalTime->Start();
  const double pi = 3.141592654;
  const double boltz = 1.3806e-23;    // Boltzmann's constant (J/K)
  double mass = 6.63e-26;       // Mass of argon atom (kg)
  double diam = 3.66e-10;       // Effective diameter of argon atom (m)
  double T;               // Temperature (K)
  double density = 1.78;        // Density of argon at STP (kg/m^3)
  double L = 1e-6;              // System size is one micron
  //cout << "Enter number of simulation particles: "; 
  int npart=100; //cin >> npart;
  double eff_num = density/mass*L*L*L/npart;
  int numTemps=150;
  Double_t *velocityAverage=new Double_t[numTemps];
  Double_t *temperatures=new Double_t[numTemps];
  Double_t *velocityCount=new Double_t[numTemps];
  int counter=0;

  //cout << "Each particle represents " << eff_num << " atoms" << endl;
  //cout << "Enter the temperature (in Kelvin): ";
  //cin >> T;
  
  for(T=20;T<3000;T=T+20)
    {
      temperatures[counter]=T;
      cout<<"Temperature is at: "<<T<<endl;

  //* Assign random positions and velocities to particles
  //long seed = 1;       // Initial seed for rand (DO NOT USE ZERO)
  double v_init = sqrt(3.0*boltz*T/mass);    // Initial speed
  TMatrixD x(1,npart,1,1), v(1,npart,1,3);
  int i;
  for( i=1; i<=npart; i++ ) {
    x[i][1] = L*rnum->Rndm();   // Assign random positions
    int plusMinus = (1 - 2*((int)(2*rnum->Rndm())));
    v[i][1] = plusMinus * v_init;
	v[i][2] = 0.0;	// Only x-component is non-zero
	v[i][3] = 0.0;
  }

  //* Record inital particle speeds
  TMatrixD vmagI(1,npart,1,1);
  for( i=1; i<=npart; i++ )
	vmagI[i][1] = sqrt( v[i][1]*v[i][1] + v[i][2]*v[i][2] + v[i][3]*v[i][3] );

  //* Initialize variables used for evaluating collisions
  int ncell = 15;                       // Number of cells
  double tau = 0.2*(L/ncell)/v_init;    // Set timestep tau
  TMatrixD vrmax(1,ncell,1,1), selxtra(1,ncell,1,1);

  for (int i = 1; i<= ncell; i++){
    vrmax[i][1] = 3*v_init;
    selxtra[i][1] = 0.0;
  }

  double coeff = 0.5*eff_num*pi*diam*diam*tau/(L*L*L/ncell);
  int coltot = 0;         // Count total collisions

  //* Declare object for lists used in sorting
  SortList sortData(ncell,npart);  

  //* Loop for the desired number of time steps
  //cout << "Enter total number of time steps: ";
  int istep, nstep=1000; //cin >> nstep;
  for( istep = 1; istep<=nstep; istep++ ) {
	
    //* Move all the particles ballistically
	for( i=1; i<=npart; i++ ) {
      x[i][1] += v[i][1]*tau;          // Update x position of particle
      x[i][1] = fmod(x[i][1]+L,L);       // Periodic boundary conditions
	}
    //* Sort the particles into cells
      sorterTime->Start(kFALSE);
    sorter(x,L,sortData);
    sorterTime->Stop();
  
    //* Evaluate collisions among the particles
    coliderTime->Start(kFALSE);
    int col = colider(v,vrmax,tau,selxtra,coeff,sortData);
    coliderTime->Stop();
    coltot += col;	// Increment collision count
    
    //* Periodically display the current progress
    if( (istep%500) < 1 )
      cout << "Done " << istep << " of " << nstep << " steps; " << 
	         coltot << " collisions" << endl;
    
     TMatrixD vmagF(1,npart,1,1);
      for( i=1; i<=npart; i++ )
	{
	  vmagF[i][1] = sqrt( v[i][1]*v[i][1] + v[i][2]*v[i][2] + v[i][3]*v[i][3] );
	  if(vmagF[i][1]==vmagI[i][1])
	    {
	      velocityCount[counter]++;
	    }
	}

      if(velocityCount[counter]<=(npart*0.05))
	{
	  //cout<<"Number of steps: "<<velocityCount[counter]<<endl;
	  velocityCount[counter]=istep;
	  break;
	}
      else
	{
	  velocityCount[counter]=0;
	}
  }

  // Record final particle speeds


  //* Print out the plotting variables: vmagI, vmagF
  /*ofstream vmagIOut("vmagI.txt"), vmagFOut("vmagF.txt");
  for( i=1; i<=npart; i++ ) {
    vmagIOut << vmagI(i) << endl;
    vmagFOut << vmagF(i) << endl;
    }*/

 TH1D *hvi = new TH1D("hvi", "test", 75, 0, 1000);
  TH1D *hvf = new TH1D("hvf", "test", 75, 0, 1000);
  TMatrixD vmagF(1,npart,1,1);
  for( i=1; i<=npart; i++ )
	vmagF[i][1] = sqrt( v[i][1]*v[i][1] + v[i][2]*v[i][2] + v[i][3]*v[i][3] );
  for( i=0; i<npart; i++ ){
    hvi->Fill(vmagI[i+1][1]);
    cout << vmagF[i+1][1] << endl;
    hvf->Fill(vmagF[i+1][1]);
  }

  totalTime->Stop();
  
  double MBvelocity = sqrt((8*boltz*T)/(3.14159*mass));
  double MBrms = sqrt((3*boltz*T)/(mass));

      cout<<"Maxwell-Boltzmann Distribution Mean Velocity: "<<MBvelocity<<endl;
      cout<<"Simulation Mean Velocity: "<<hvf->GetMean()<<endl;
      cout<<"Maxwell-Boltzmann Distribution RMS: "<<MBrms<<endl;
      cout<<"Simulation RMS: "<<hvf->GetRMS()<<endl;
      cout<<""<<endl;

      cout<<"Total CPU time: "<<totalTime->CpuTime()<<endl;
      cout<<"Colider CPU time: "<<coliderTime->CpuTime()<<endl;
      cout<<"Sorter CPU time: "<<sorterTime->CpuTime()<<endl;
      cout<<""<<endl;

      cout<<"Total real time: "<<totalTime->RealTime()<<endl;      
      cout<<"Colider real time: "<<coliderTime->RealTime()<<endl;      
      cout<<"Sorter real time: "<<sorterTime->RealTime()<<endl;
      
      velocityAverage[counter]=hvf->GetMean();
      counter++;
      
    }      
   //gStyle->SetOptFit(kFALSE);	
   gStyle->SetOptFit(1);	
   TCanvas *c1 = new TCanvas("c1","Data",200,10,700,500);
   // c1->Divide(3,1);
   c1->SetFillColor(42);
   c1->SetGrid();
   /*	c1->cd(1);
	hvi->Draw();
	c1->cd(2);
	hvf->Draw();*/

   //c1->cd(3);
	TGraph *gr=new TGraph(numTemps,temperatures,velocityCount);
	gr->SetTitle("Temperature vs Number of Steps");
	gr->SetMarkerStyle(22);
	gr->GetXaxis()->SetTitle("Temperature");
	gr->GetYaxis()->SetTitle("Number of Steps"); 
	gr->Draw("ALP");


	c1->Update();
	c1->GetFrame()->SetFillColor(21);
	c1->GetFrame()->SetBorderSize(12);
	c1->Modified();

}

//double rand( long& seed );

int colider( TMatrixD& v, TMatrixD& crmax, double tau,
              TMatrixD& selxtra, double coeff, SortList& sD ) {

// colide - Function to process collisions in cells
// Inputs
//    v         Velocities of the particles
//    crmax     Estimated maximum relative speedN in a cell
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
  TRandom3 *rnum= new TRandom3();
  //* Loop over cells, processing collisions in each cell
  int jcell;
  for( jcell=1; jcell<=ncell; jcell++ ) {

    //* Skip cells with only one particle
    int number = sD.cell_n[jcell];
    if( number < 2 ) continue;  // Skip to the next cell

    //* Determine number of candidate collision pairs
    //  to be selected in this cell
    double select = coeff*number*(number-1)*crmax[jcell][1] + selxtra[jcell][1];
    int nsel = (int)(select);      // Number of pairs to be selected
    selxtra[jcell][1] = select-nsel;  // Carry over any left-over fraction
    double crm = crmax[jcell][1];     // Current maximum relative speed

    //* Loop over total number of candidate collision pairs
    int isel;
    for( isel=1; isel<=nsel; isel++ ) {

      //* Pick two particles at random out of this cell
      int k = (int)(rnum->Rndm()*number);
      int kk = ((int)(k+rnum->Rndm()*(number-1))+1) % number;
      int ip1 = sD.Xref[ k+sD.index[jcell] ];      // First particle
      int ip2 = sD.Xref[ kk+sD.index[jcell] ];     // Second particle

      //* Calculate pair's relative speed
      double cr = sqrt( pow(v[ip1][1]-v[ip2][1],2) +
                        pow(v[ip1][2]-v[ip2][2],2) +   // Relative speed
                        pow(v[ip1][3]-v[ip2][3],2) );
      if( cr > crm )         // If relative speed larger than crm,
        crm = cr;            // then reset crm to larger value

      //* Accept or reject candidate pair according to relative speed
      if( cr/crmax[jcell][1] > rnum->Rndm() ) {
        //* If pair accepted, select post-collision velocities
        col++;                     // Collision counter
        TMatrixD vcm(1,3,1,1), vrel(1,3,1,1);
        int k;
        for( k=1; k<=3; k++ )
          vcm[k][1] = 0.5*(v[ip1][k] + v[ip2][k]);      // Center of mass velocity
        double cos_th = 1.0 - 2.0*rnum->Rndm();      // Cosine and sine of
        double sin_th = sqrt(1.0 - cos_th*cos_th); // collision angle theta
        double phi = 2.0*pi*rnum->Rndm();            // Collision angle phi
        vrel[1][1] = cr*cos_th;             // Compute post-collision
        vrel[2][1] = cr*sin_th*cos(phi);    // relative velocity
        vrel[3][1] = cr*sin_th*sin(phi);
        for(  k=1; k<=3; k++ ) {
          v[ip1][k] = vcm[k][1] + 0.5*vrel[k][1];  // Update post-collision
          v[ip2][k] = vcm[k][1] - 0.5*vrel[k][1];  // velocities
        }

      } // Loop over pairs
      crmax[jcell] = crm;     // Update max relative speed
    }
  }   // Loop over cells
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

  //* Find the cell address for eac particle
  int ncell = sD.ncell;
  int npart = sD.npart;
  int ipart, *jx;
  jx = new int [npart+1];
  for( ipart=1; ipart<=npart; ipart++ ) {
    int j = (int)(x[ipart][1]*ncell/L) + 1;
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
  temp = new int [ncell+1];	  // Temporary array
  for( jcell=1; jcell<=ncell; jcell++ )
    temp[jcell] = 0;
  for( ipart=1; ipart<=npart; ipart++ )	{
    jcell = jx[ipart];       // Cell address of ipart
    int k = sD.index[jcell] + temp[jcell];
    sD.Xref[k] = ipart;
    temp[jcell] = temp[jcell] + 1;
  }

  delete [] jx;
  delete [] temp;
    }

