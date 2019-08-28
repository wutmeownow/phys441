#include "Riostream.h"

Double_t fitfunction(Double_t *x, Double_t *par)
{
	Double_t Pi=3.14159265;
	Double_t a=0.5*pow(Pi/2.0,0.5)*par[1];
	Float_t xx = x[0];
	Double_t f = 1000.0/200.0*par[0]*pow(2.0/Pi,0.5)/pow(a,3)*xx*xx*exp(-1.0*xx*xx/(2.0*a*a));
	return f;
}

void basic_p() {
//  Read data from an ascii file and create a root file with an histogram and an ntuple.
//   see a variant of this macro in basic2.C
//Author: Rene Brun
      

// read file $ROOTSYS/tutorials/tree/basic.dat
// this file has 3 columns of float data
   TString dir = gSystem->UnixPathName(gInterpreter->GetCurrentMacroName());
   dir.ReplaceAll("basic.C","");
   dir.ReplaceAll("/./","/");
   ifstream in;
   in.open(Form("nsteps.dat",dir.Data()));

   Float_t xf;
   Int_t nlinesf = 0;
   TH1F *h1 = new TH1F("h1","Final velocity distribution",200,0.0,1000.0);

   while (1) {
      in >> xf;
      if (!in.good()) break;
      if (nlinesf < 5) printf("r=%8f\n",xf);
      h1->Fill(xf);
      nlinesf++;
   }
   printf(" found %d points\n",nlinesf);

   TF1 *pfit1 = new TF1("fitfunction",fitfunction,0.0,1000.0,2);
   pfit1->SetParameters(12000.0,400.0);
   pfit1->SetParNames("N","Mean");
   pfit1->SetLineColor(2);
   h1->Fit("fitfunction","V");

   in.close();
}
