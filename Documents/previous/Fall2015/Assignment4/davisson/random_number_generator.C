#include <iostream>
#include <fstream>
#include "math.h"
#include "TRandom.h"

//using namspace std;

void random_number_generator()
{
  const int loopNumber=1000000;

  TCanvas *c1 = new TCanvas("c1","Uniform Random",200,10,1400,1200);
  c1->Divide(2,3);
  TRandom3 *rnum=new TRandom3();
  
  const int numberOfGenerators=5;
  TH1D *h[numberOfGenerators];
  for(int i=0;i<5;i++)
    {
      h[i]= new TH1D("Uniform Random","Uniform Random",150,-3,3);
      h[i]->SetFillColor(38);
    }
  
  for(int i=0;i<loopNumber;i++)
    {    
      Double_t random=rnum->Uniform(0,1);
      h[0]->Fill(random);
      while(true)
	{
	  Double_t random1=rnum->Uniform(0,2);
	  Double_t function=-1*fabs(random1-1)+1;
	  //cout<<function<<endl;
	  Double_t randomCheck=rnum->Uniform(0,2);
	  if(randomCheck<function)
	    {
	      h[1]->Fill(random1);
	      break;
	    }
	}
      Double_t random2=rnum->Exp(1);
      h[2]->Fill(random2);
      Double_t random3=rnum->Gaus(0,1);
      h[3]->Fill(random3);
      Double_t random4=rnum->Gaus(1,0.3);
      h[4]->Fill(random4);
    }  

  for(int i=0;i<5;i++)
    {
      c1->cd(i+1);
      h[i]->Draw();
      //c1->cd(i+2);
    }
  
  
}
