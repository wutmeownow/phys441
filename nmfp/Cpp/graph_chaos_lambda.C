//
// Chaos Theory Example - lambda dependence
//

#include <ostream>

Double_t growthfunction(Double_t *x, Double_t *par)
{
	Double_t f = par[0]*x[0]*(1.0-x[0]);
	return f;
}

void graph_chaos_lambda(Int_t nstart = 1000, Int_t npoints = 100, Int_t lambda_points = 1000, Double_t lambda_min = 0.0, Double_t lambda_max = 3.5) {
   //
   //Modified: Edward J. Brash
   //		
  
   //gStyle->SetOptFit(kFALSE);	
   gStyle->SetOptFit(1);	
   TCanvas *c1 = new TCanvas("c1","Population vs. Time",200,10,800,1000);

   c1->SetFillColor(42);
   c1->SetGrid();
   //c1->SetLogy();
   //c1->SetLogx();

   const Int_t n = nstart+npoints;
   const Int_t nvalues = npoints;
   const Int_t lambda_n = lambda_points;
   Double_t population[n],year[n];
   Double_t lambda[lambda_n],lambda_now[1];
   Double_t xvalue[1];

   for (Int_t j=0;j<lambda_n;j++){
       lambda[j]=lambda_min + (lambda_max-lambda_min)*j/lambda_n;
       year[0]=0;
       population[0]=0.3;
       lambda_now[0]=lambda[j];
       
       Double_t myvalues[nvalues];
       Double_t lambdavalues[nvalues];
       for (Int_t i=1; i<n; i++){
            year[i]=i;
            xvalue[0]=population[i-1];
            population[i]=growthfunction(xvalue,lambda_now);
            if (i>=nstart){
                myvalues[i-nstart]=population[i];
                lambdavalues[i-nstart]=lambda_now[0];
            }
       }

       TGraph *gr = new TGraph(nvalues,lambdavalues,myvalues);

//   gr->SetLineColor(2);
//   gr->SetLineWidth(4);
       TAxis *axis = gr->GetXaxis();
       axis->SetLimits(lambda_min,lambda_max);
       gr->GetHistogram()->SetMaximum(1.0);
       gr->GetHistogram()->SetMinimum(0.0);
       gr->SetMarkerColor(kBlue);
       gr->SetMarkerStyle(20);
       gr->SetMarkerSize(0.2);
       gr->SetTitle("Growth Function: lambda*x*(1-x)");
       gr->GetXaxis()->SetTitle("Lambda");
       gr->GetYaxis()->SetTitle("Equilibrium Population");
       if(j==0){
         gr->Draw("AP");
       }else{
         gr->Draw("P");
       }
   }

   // TCanvas::Update() draws the frame, after which one can change it
   c1->Update();
   c1->GetFrame()->SetFillColor(21);
   c1->GetFrame()->SetBorderSize(12);
   c1->Modified();
}
