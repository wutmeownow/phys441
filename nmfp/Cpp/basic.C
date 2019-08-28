#include "Riostream.h"

Double_t fitfunction(Double_t *x, Double_t *par)
{
	Double_t Pi=3.14159265;
	Double_t a=0.5*pow(Pi/2.0,0.5)*par[1];
	Float_t xx = x[0];
	Double_t f = 1000.0/200.0*par[0]*pow(2.0/Pi,0.5)/pow(a,3)*xx*xx*exp(-1.0*xx*xx/(2.0*a*a));
	return f;
}

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
   ifstream inn;
   inn.open(Form("%svmagI.txt",dir.Data()));

   Float_t xf;
   Float_t xi;
   Int_t nlinesf = 0;
   Int_t nlinesi = 0;
   TFile *f = new TFile("velocity_distribution.root","RECREATE");
   TH1F *h1 = new TH1F("h1","Final velocity distribution",200,0.0,1000.0);
   TNtuple *ntuplef = new TNtuple("ntuple","final velocity distribution","xf");
   TH1F *h2 = new TH1F("h2","Initial velocity distribution",200,0.0,1000.0);
   TNtuple *ntuplei = new TNtuple("ntuple","initial velocity distribution","xi");

   while (1) {
      in >> xf;
      if (!in.good()) break;
      if (nlinesf < 5) printf("r=%8f\n",xf);
      h1->Fill(xf);
      ntuplef->Fill(xf);
      nlinesf++;
   }
   printf(" found %d points\n",nlinesf);
   while (1) {
      inn >> xi;
      if (!inn.good()) break;
      if (nlinesi < 5) printf("r=%8f\n",xi);
      h2->Fill(xi);
      ntuplei->Fill(xi);
      nlinesi++;
   }

   TF1 *pfit1 = new TF1("fitfunction",fitfunction,0.0,1000.0,2);
   pfit1->SetParameters(12000.0,400.0);
   pfit1->SetParNames("N","Mean");
   pfit1->SetLineColor(2);
   h1->Fit("fitfunction","V");

   in.close();
   inn.close();

   f->Write();
}
