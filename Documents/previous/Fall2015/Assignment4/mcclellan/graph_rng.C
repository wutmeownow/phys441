#include <iostream>
#include <fstream>
#include "math.h"

using namespace std;

void graph_rng() {

   double r1;
   double r2;
   double P;
   double mu;
   double sigma;
   double gauss_exp;
   double mb_exp;
   int check = 1;
   double pi = 3.141592654;
   double EXP = 2.71828;
   double mass = 6.63e-26;
   double kB = 1.3806485e-23;
   double T = 300;
   double a = pow(kB*T/mass,0.5);

   rng = new TRandom3();
   TH1D *h1 = new TH1D("Uniform", ";x;N", 1000, 0.0, 1.0);
   TH1D *h2 = new TH1D("Triangular", ";x;N", 1000, 0.0, 2.0);
   TH1D *h3 = new TH1D("Exp. Decay", ";x;N", 1000, 0.0, 2.0);
   TH1D *h4 = new TH1D("Gaussian 1", ";x;N", 1000, -3.0, 3.0);
   TH1D *h5 = new TH1D("Gaussian 2", ";x;N", 1000, 0.0, 2.0);
   TH1D *h6 = new TH1D("Max-Boltz", ";x;N", 1000, 0.0, 5*a);

   //uniform
   for(int i=0;i<100000;i++){
        h1->Fill(rng->Rndm());
   }

   cout << "uniform done" << endl;

   //triangular
   for(int i=0;i<100000;i++){
        while(check == 1){
            r1 = rng->Rndm()*2;
            P = -fabs(r1-1)+1;
            r2 = rng->Rndm();
            if(r2<P)check=0;
        }
        h2->Fill(r1);
        check=1;
   }

  cout << "triangular done" << endl;
   
   //exponential decay
   for(int i=0;i<100000;i++){
        while(check == 1){
            r1 = rng->Rndm()*2;
            P = pow(EXP,-r1);
            r2 = rng->Rndm();
            if(r2<P)check=0;
        }
        h3->Fill(r1);
        check=1;
   }
  
   cout << "exponential done" << endl;
 
   mu = 0.0;
   sigma = 1.0;

   //guassian 1
   for(int i=0;i<100000;i++){
        while(check == 1){
            r1 = mu - 3*sigma + rng->Rndm()*6*sigma;
            gauss_exp = -(r1 - mu)*(r1 - mu)/(2*sigma*sigma);
            P = pow(EXP,gauss_exp);
            r2 = rng->Rndm();
            if(r2<P)check=0;
        }
        h4->Fill(r1);
        check=1;
   }
   
   cout << "guassian 1 done" << endl;

   mu = 1.0;
   sigma = 0.3;

   //guassian 2
   for(int i=0;i<100000;i++){
        while(check == 1){
            r1 = mu - 3*sigma + rng->Rndm()*6*sigma;
            gauss_exp = -(r1 - mu)*(r1 - mu)/(2*sigma*sigma);
            P = pow(EXP,gauss_exp);
            r2 = rng->Rndm();
            if(r2<P)check=0;
        }
        h5->Fill(r1);
        check=1;
   }

   cout << "guassian 2 done" << endl;
   
   //maxwell-boltzmann
   for(int i=0;i<100000;i++){
        while(check == 1){
            r1 = rng->Rndm()*5*a;
            mb_exp = -mass*r1*r1/(2*kB*T);
            P = 4*pi*pow(mass/(2*pi*kB*T),1.5)*r1*r1*pow(EXP,mb_exp);
            r2 = rng->Rndm()*(0.6/a);
            if(r2<P)check=0;
        }
        h6->Fill(r1);
        check=1;

        if((i+1)%100 == 0) cout << i+1 << endl;
   }

   cout << "maxwell-boltzmann done" << endl;

   gStyle->SetOptFit(1);	
   TCanvas *c1 = new TCanvas("c1","Randomly Generated Distributions",150,10,1000,650);
   c1->Divide(3,2);
   c1->SetFillColor(42);
   c1->SetGrid();

   h1->SetMinimum(0.0);
   h2->SetMinimum(0.0);
   h3->SetMinimum(0.0);
   h4->SetMinimum(0.0);
   h5->SetMinimum(0.0);
   h6->SetMinimum(0.0);
   c1->cd(1);
   h1->Draw();
   c1->cd(2);
   h2->Draw();
   c1->cd(3);
   h3->Draw();
   c1->cd(4);
   h4->Draw();
   c1->cd(5);
   h5->Draw();
   c1->cd(6);
   h6->Draw();

}
