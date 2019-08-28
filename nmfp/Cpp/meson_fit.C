#include <iostream>
#include <TMath.h>

void meson_fit() {
   //
   // Author: Edward J. Brash
  
//   gStyle->SetOptFit(kFALSE);	
   TCanvas *c1 = new TCanvas("c1","Meson Mass",800,800);

   c1->SetFillColor(42);
   c1->SetGrid();
   
   double mu=308.0;
   double md=308.0;
   double ms=483.0;
   double spin1=0.25;
   double spin0=-0.75;
   double q_mass[8];
   double q_den[8];
   double spin_spin[8];
   double x[8];
   double y[8];

   q_mass[0]=mu+md;
   q_mass[1]=mu+ms;
   q_mass[2]=1/6*(mu+mu)+1/6*(md+md)+4/6*(ms+ms);
   q_mass[3]=1/3*(mu+mu)+1/3*(md+md)+1/3*(ms+ms);
   q_mass[4]=mu+md;
   q_mass[5]=mu+ms;
   q_mass[6]=1/2*(mu+mu)+1/2*(md+md);
   q_mass[7]=ms+ms;

   q_den[0]=mu*md;
   q_den[1]=mu*ms;
   q_den[2]=1/6*(mu*mu)+1/6*(md*md)+4/6*(ms*ms);
   q_den[3]=1/3*(mu*mu)+1/3*(md*md)+1/3*(ms*ms);
   q_den[4]=mu*md;
   q_den[5]=mu*ms;
   q_den[6]=1/2*(mu*mu)+1/2*(md*md);
   q_den[7]=ms*ms;

   spin_spin[0]=spin0;
   spin_spin[1]=spin0;
   spin_spin[2]=spin0;
   spin_spin[3]=spin0;
   spin_spin[4]=spin1;
   spin_spin[5]=spin1;
   spin_spin[6]=spin1;
   spin_spin[7]=spin1;

   y[0]=138.0;
   y[1]=496.0;
   y[2]=548.0;
   y[3]=958.0;
   y[4]=776.0;
   y[5]=894.0;
   y[6]=783.0;
   y[7]=1020.0;

   for(int i=0; i<8; i++){
	   x[i]=spin_spin[i]/q_den[i];
   } 

    TGraph *gra = new TGraph(8,x,y);
    
    gra->Draw("AP");

   c1->Update();
   c1->GetFrame()->SetFillColor(21);
   c1->GetFrame()->SetBorderSize(12);
   c1->Modified();
}
