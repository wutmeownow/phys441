#include "Riostream.h"

void profile() {
//  Read data from an ascii file and create a root file with an histogram and an ntuple.
//   see a variant of this macro in basic2.C
//Author: Rene Brun
      

// read file $ROOTSYS/tutorials/tree/basic.dat
// this file has 3 columns of float data
   TString dir = gSystem->UnixPathName(gInterpreter->GetCurrentMacroName());
   dir.ReplaceAll("profile.C","");
   dir.ReplaceAll("/./","/");
   ifstream in;
   //in.open(Form("%sprofile.dat",dir.Data()));
   in.open(Form("%sprofile2.dat",dir.Data()));

   Int_t nlines = 0;

   int i = 0;
   const int narr=100;
   double npart[narr],nsteps[narr],ttotal[narr],tmover[narr],tcolider[narr],tsorter[narr];
   double ex[narr],ey[narr];
   while (1) {
      in >> npart[i] >> nsteps[i] >> ttotal[i] >> tcolider[i] >> tsorter[i] >> tmover[i];
      ex[i]=0.0;
      ey[i]=sqrt(tcolider[i]);
      if (!in.good()) break;
      i++;
   }
   printf(" found %d points\n",i);

   gr = new TGraphErrors(i,npart,tcolider,ex,ey);
   gr->SetMarkerStyle(22);
   gr->SetMarkerColor(kRed);
   gr->Draw("AP");
   gr->Fit("pol1");
}
