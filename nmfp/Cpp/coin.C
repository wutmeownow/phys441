#include <iostream>
#include <fstream>
#include <string>
#include "Math/DistFunc.h"

void coin() {
//  Original: Read data from an ascii file and create a root file with an histogram and an ntuple.
//            see a variant of this macro in basic2.C
//            Author: Rene Brun
//  Modified:  Read string data on coin flips from a file and parse strings
//  	       Author:  Edward J. Brash
      


   ROOT::Math::MathMoreLibrary::Load();

   TCanvas *c1 = new TCanvas("c1","Coin Flip", 200, 10, 700, 500);
   c1->SetFillColor(42);
   c1->SetGrid();

   const int ntrials_max=400;
   const int nflips=10;

   char mysequence[nflips];
   int nheads[ntrials_max];
   char headcomp[1];
   headcomp[0]='H';
   Int_t nlinesf = 0;
   bool iflag = true;

   TH1I *h1 = new TH1I("h1","Data Distribution",13,-1,12);
   
   ifstream infile("Coin.txt");

   if (infile.is_open()){
      	while (infile.good()){
      		infile >> mysequence;
      		//if (nlinesf < ntrials_max) cout << mysequence << " first character = " << mysequence[0] << endl;
      		nheads[nlinesf]=0;
      		for (int i=0;i<nflips;i++){
	      		//cout << "character = " << mysequence[i] << endl;
	      		if(mysequence[i]==headcomp[0]){
		      		//cout << "Detected heads!" << endl;
		      		nheads[nlinesf]++;
	      		}
      		}
      		nlinesf++;
      	}
   }else{
   	cout << "unable to open file" << endl;
   }
   printf("Read in %d sequences.\n",nlinesf);
   cout << endl;

   for(int i=0;i<nlinesf;i++){
	cout << "i = " << i << " nheads = " << nheads[i] << endl;
	h1->Fill(nheads[i]);
   }

   double pfair = 0.50;
   double mu = nflips*pfair;
   double sigma = sqrt(nflips*pfair*(1.0-pfair));

   double ybar = h1->GetMean();
   double s = h1->GetStdDev();
   int n = h1->GetEntries();

   cout << "Expected Std. Deviation = " << sigma << endl;
   cout << "Sample Std. Deviation = " << s << endl;
   cout << endl;
   double chisquared = (n-1)*s*s/(sigma*sigma);
   cout << "Chi^2 = " << chisquared << endl; 
   if(chisquared/(n-1) < 1.0){
   	cout << "Chi^2 P-value = " << ROOT::Math::chisquared_cdf(chisquared,n-1) << endl;
   }else{
   	cout << "Chi^2 P-value = " << ROOT::Math::chisquared_cdf_c(chisquared,n-1) << endl;
   }
   cout << endl;
   cout << "Sample Size = " << n << endl;
   cout << "Sample Mean = " << ybar << " +/- " << s/sqrt(n) << endl;
   cout << endl;
   double t = (ybar - mu)/(s/sqrt(n));
   double pvalue = 1.0-ROOT::Math::tdistribution_cdf(t,n-1); 
   cout << "T statistic " << t << endl;
   cout << "P-value = " << pvalue << endl;
   cout << "Chances of an unfair coin = 1 in " << int(1.0/pvalue) << endl;

   h1->Draw();

}
