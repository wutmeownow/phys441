void graph_wavepacket_random() {
   //Draw a simple graph
   // To see the output of this macro, click begin_html <a href="gif/graph.gif">here</a>. end_html
   //Author: Rene Brun
   
   TCanvas *c1 = new TCanvas("c1","A Simple Graph Example",200,10,700,500);

   c1->SetFillColor(42);
   c1->SetGrid();
   //c1->SetLogy();

   const Int_t n = 8000;
   double pi=3.14159265;
   double lambda=1.0;
   double xlow = -48.0*lambda;
   double dx = 96.0*lambda/n;
   double k=2.0*pi/lambda;
   double delta_k=0.05*k;

   TRandom3 *rnum = new TRandom3();

   Double_t x[n], y[n], yf[n];
   for (Int_t i=0;i<n;i++) {
     x[i] = xlow+i*dx+0.00001;
/*   Add several waves together of equal amplitude ... */
     Double_t ysum=0.0;
     Int_t n_waves=1000;
     for (Int_t j=0; j<n_waves; j++){
	     //Double_t knew = k+rnum->Uniform(-delta_k,delta_k);
	     Double_t knew = k+rnum->Gaus(0.0,delta_k/2.0);
	     ysum=ysum+sin(knew*x[i]);
     }
     //y[i]=(2.0*delta_k)*ysum*ysum/(n_waves*n_waves);
     //y[i]=sqrt(2.0*delta_k)*ysum/(n_waves);
     y[i]=pow(2,0.25)*pow(delta_k/2.0,0.5)/pow(pi,0.25)*ysum/(n_waves);
     y[i]=y[i]*y[i];
/*   Fourier transform with equal amplitude from k-delta_k to k_delta_k */

     //yf[i] = pow(sqrt(2.0/delta_k)*sin(k*x[i])*sin(delta_k*x[i])/x[i],2);
     //yf[i] = sqrt(2.0/delta_k)*sin(k*x[i])*sin(delta_k*x[i])/x[i];
     yf[i] = pow(2,0.25)*pow(delta_k/2.0,0.5)/pow(pi,0.25)*sin(k*x[i])*exp(-pow(delta_k*x[i]/2.0,2));
     yf[i]=yf[i]*yf[i];
     //printf(" i %i %f %f \n",i,x[i],y[i]);
   }
   TGraph *gr = new TGraph(n,x,y);
   gr->SetLineColor(4);
   gr->SetLineWidth(2);
   gr->SetTitle("Wavepacket Random");
   gr->GetXaxis()->SetTitle("X");
   gr->GetYaxis()->SetTitle("Amplitude^2");
   TGraph *gr2 = new TGraph(n,x,yf);
   gr2->SetLineColor(2);
   gr2->SetLineWidth(2);
   gr2->SetMarkerColor(3);
   gr->Draw("AL");
   gr2->Draw("L");

   // TCanvas::Update() draws the frame, after which one can change it
   c1->Update();
   c1->GetFrame()->SetFillColor(21);
   c1->GetFrame()->SetBorderSize(12);
   c1->Modified();
}
