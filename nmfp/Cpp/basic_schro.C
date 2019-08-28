#include "Riostream.h"

void basic_schro() {
//  Read data from an ascii file and create a root file with an histogram and an ntuple.
//   see a variant of this macro in basic2.C
//Author: Rene Brun
      

// read file $ROOTSYS/tutorials/tree/basic.dat
// this file has 3 columns of float data
   TString dir = gSystem->UnixPathName(gInterpreter->GetCurrentMacroName());
   dir.ReplaceAll("basic_schro.C","");
   dir.ReplaceAll("/./","/");
   ifstream in;
   in.open(Form("%sx.txt",dir.Data()));
   ifstream inn;
   inn.open(Form("%srpi.txt",dir.Data()));
   ifstream innn;
   innn.open(Form("%sipi.txt",dir.Data()));
   ifstream innnn;
   innnn.open(Form("%sp_plot.txt",dir.Data()));

   Double_t x[200];
   Double_t rpi[200];
   Double_t ipi[200];
   Double_t pp[200][1000];

   Int_t icountx=0;

   while (1) {

      in >> x[icountx];
      if (!in.good()) break;
      icountx++;
   }
   
   printf(" found %d points\n",icountx);
   icountx=0;

   while (1) {

      inn >> rpi[icountx];
      if (!inn.good()) break;
      icountx++;
   }

   printf(" found %d points\n",icountx);
   icountx=0;

   while (1) {

      innn >> ipi[icountx];
      if (!innn.good()) break;
      icountx++;
   }

   printf(" found %d points\n",icountx);
   
   TCanvas *c1 = new TCanvas("c1","Free Particle",200,10,700,500);
   c1->SetFillColor(42);
   c1->SetGrid();
   c1->Divide(1,2);

   grr = new TGraph(icountx-1,x,rpi);
   gri = new TGraph(icountx-1,x,ipi);
   grr->SetLineColor(4);
   gri->SetLineColor(4);

   c1->cd(1);
   grr->Draw("AL");
   c1->cd(2);
   grr->Draw("AL");

   in.close();
   inn.close();
   innn.close();
   innnn.close();

}
