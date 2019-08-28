#include "Riostream.h"
void basic() {
//  Read data from an ascii file and create a root file with an histogram and an ntuple.
//   see a variant of this macro in basic2.C
//Author: Rene Brun
      

// read file $ROOTSYS/tutorials/tree/basic.dat
// this file has 3 columns of float data
   TString dir = gSystem->UnixPathName(gInterpreter->GetCurrentMacroName());
   dir.ReplaceAll("basic.C","");
   dir.ReplaceAll("/./","/");
   ifstream in;
   in.open(Form("%svmagF.txt",dir.Data()));

   Float_t x;
   Int_t nlines = 0;
   TFile *f = new TFile("velocity_distribution.root","RECREATE");
   TH1F *h1 = new TH1F("h1","velocity distribution",200,0.0,1000.0);
   TNtuple *ntuple = new TNtuple("ntuple","velocity distribution","x");

   while (1) {
      in >> x;
      if (!in.good()) break;
      if (nlines < 5) printf("r=%8f\n",x);
      h1->Fill(x);
      ntuple->Fill(x);
      nlines++;
   }
   printf(" found %d points\n",nlines);

   in.close();

   f->Write();
   h1->Draw();
}
