#include <ostream>
#include "TRandom.h"

void graph_fitting_quiz_simulation(Double_t mu = 0.61, Double_t sigma = 0.20) {
   //
   //Modified: Edward J. Brash
   //		
  
   //gStyle->SetOptFit(kFALSE);	
   gStyle->SetOptFit(1);	
   TCanvas *c1 = new TCanvas("c1","Quiz Data",200,10,700,500);
   TCanvas *c2 = new TCanvas("c2","Quiz Data",1200,510,700,500);

   // Set the order of the fitting polynomial here.
   
   c1->SetFillColor(42);
   c1->SetGrid();
   c2->SetFillColor(42);
   c2->SetGrid();
   //c2->Divide(1,2);

   const unsigned int n = 12;
   const unsigned int m = 4;
   Double_t x[n], y[n], ex[n],ey[n];
   Int_t i;

   y[0]=0.01;
   y[1]=0.02;
   y[2]=0.03;
   y[3]=0.06;
   y[4]=0.07;
   y[5]=0.09;
   y[6]=0.12;
   y[7]=0.12;
   y[8]=0.15;
   y[9]=0.15;
   y[10]=0.12;
   y[11]=0.06;

   const unsigned int Npeople=3278;
   const unsigned int Npeople_sim=100000;
   
   for (i=0;i<n;i++){
           x[i]=i+1;
	   ex[i]=0.0;
	   ey[i]=1.96*sqrt(y[i]*(1.0-y[i])/Npeople);
	   //ey[i]=0.01;
   }
   
   TRandom r;
   Int_t n_correct;
   Double_t n_tally[n],n_tally2[n];

   TH1F *h1 = new TH1F("h1","All Correct Distribution",100,0.0,1.0);
   TH1F *h2 = new TH1F("h2","One Incorrect Distribution",100,0.0,1.0);
   TH1F *h3 = new TH1F("h3","Distribution of Respondents",100,0.0,1.0);

   for(i=0;i<n;i++){
	n_tally[i]=0;
        n_tally2[i]=0;
   }

   for (i=0;i<Npeople_sim;i++){
        n_correct=0;
	Double_t p_success = r.Gaus(mu,sigma);
        for(int nq=0; nq<n; nq++){
          if (p_success < 0.0) p_success=-0.0000001;
	  if (p_success > 1.0) p_success=1.00000001;
          Double_t trial = r.Uniform(0,1);
	  if(trial < p_success) {
		n_correct++;
	  }else{
		Double_t trial2 = r.Uniform(0,1);
		if (trial2 < 1.0/m) n_correct++;
	  }
         }
         if (n_correct == n) h1->Fill(p_success);
         if (n_correct == n-1) h2->Fill(p_success);
         h3->Fill(p_success);
	 n_tally[n_correct]++;
   }

  Double_t psum=0;
  for(i=0;i<=n;i++){
	cout << "x = " << i << " n_tally[x] = " << n_tally[i] << endl;
  	psum=psum+n_tally[i];   
  }
  cout << "Integrated probability = " << psum << endl;
  Double_t chi2=0;
  for(i=0;i<=n;i++){
	n_tally[i]=n_tally[i]/psum;
        if (i > 0) chi2=chi2+pow((y[i-1]-n_tally[i])/ey[i-1],2);
  }
  
  for(i=0;i<n;i++){
	n_tally2[i]=n_tally[i+1];
  }

  chi2=chi2/(n-2);
  cout << "mu = " << mu << " Chi^2/dof = " << chi2 << endl;
  

   gr = new TGraphErrors(n,x,y,ex,ey);
   gr2 = new TGraph(n,x,n_tally2);

//   gr->SetLineColor(2);
//   gr->SetLineWidth(4);
   gr2->SetMarkerColor(4);
   gr->SetMarkerStyle(21);
   gr2->SetMarkerStyle(21);
   gr->SetTitle("Simulation vs. Data");
   gr->GetXaxis()->SetTitle("X");
   gr->GetYaxis()->SetTitle("Y");
   TAxis *axis = gr->GetXaxis();
   axis->SetLimits(1.0,12.0);
//   gr->GetHistogram()->SetMaximum(10.0);
//   gr->GetHistogram()->SetMinimum(0.0);


   c1->cd();
   gr->Draw("AP");
   gr2->Draw("L");
   //cout << "Fit Order = " << polynomial_order << " Chi2/dof = " << chi2 << endl;

   // draw the legend
   Char_t message[80];
   TLegend *legend=new TLegend(0.4,0.15,0.88,0.35);
   legend->SetTextFont(72);
   legend->SetTextSize(0.04);
   legend->AddEntry(gr,"Data","lpe");
//   legend->Draw();

   // TCanvas::Update() draws the frame, after which one can change it
   c2->cd();
   h3->SetLineColor(kBlack);
   h3->Draw();
   h2->SetLineColor(kRed);
   h2->Draw("SAME");
   h1->SetLineColor(kBlue);
   h1->Draw("SAME");

   c1->Update();
   c1->GetFrame()->SetFillColor(21);
   c1->GetFrame()->SetBorderSize(12);
   c1->Modified();
   c2->Update();
   c2->GetFrame()->SetFillColor(21);
   c2->GetFrame()->SetBorderSize(12);
   c2->Modified();
}
