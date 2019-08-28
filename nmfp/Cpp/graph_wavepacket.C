void graph_wavepacket(Int_t ichoice = 1) {
   //Draw a simple graph
   // To see the output of this macro, click begin_html <a href="gif/graph.gif">here</a>. end_html
   //Author: Rene Brun
   
   TCanvas *c1 = new TCanvas("c1","A Simple Graph Example",200,10,700,500);

   c1->SetFillColor(42);
   c1->SetGrid();

   const Int_t n = 8000;
   double pi=3.14159265;
   double lambda=1.0;
   double xlow = -24.0*lambda;
   double dx = 48.0*lambda/n;
   double k=2.0*pi/lambda;
   double delta_k=0.05*k;
   Double_t x[n], y[n], yf[n];
   for (Int_t i=0;i<n;i++) {
     x[i] = xlow+i*dx+0.00001;
/*   Add several waves together of equal amplitude ... */
    
     double y1 = sin(k*x[i]);
     double y2 = sin((k-0.125*delta_k)*x[i]);
     double y3 = sin((k+0.125*delta_k)*x[i]);
     double y4 = sin((k-0.25*delta_k)*x[i]);
     double y5 = sin((k+0.25*delta_k)*x[i]);
     double y6 = sin((k-0.375*delta_k)*x[i]);
     double y7 = sin((k+0.375*delta_k)*x[i]);
     double y8 = sin((k-0.5*delta_k)*x[i]);
     double y9 = sin((k+0.5*delta_k)*x[i]);
     double y10 = sin((k-0.625*delta_k)*x[i]);
     double y11 = sin((k+0.625*delta_k)*x[i]);
     double y12 = sin((k-0.75*delta_k)*x[i]);
     double y13 = sin((k+0.75*delta_k)*x[i]);
     double y14 = sin((k-0.875*delta_k)*x[i]);
     double y15 = sin((k+0.875*delta_k)*x[i]);
     double y16 = sin((k-delta_k)*x[i]);
     double y17 = sin((k+delta_k)*x[i]);
     double ytemp  = 1/17.*(y1+y2+y3+y4+y5+y6+y7+y8+y9+
     			y10+y11+y12+y13+y14+y15+y16+y17);
     y[i] = ytemp*ytemp;

/*   Fourier transform with equal amplitude from k-delta_k to k_delta_k */

     yf[i] = sqrt(2.0/delta_k)*sin(k*x[i])*sin(delta_k*x[i])/x[i];
     yf[i] = yf[i]*yf[i];

     printf(" i %i %f %f \n",i,x[i],y[i]);
   }
   TGraph *gr = new TGraph(n,x,y);
   TGraph *grf = new TGraph(n,x,yf);
   gr->SetLineColor(4);
   gr->SetLineWidth(2);
   grf->SetLineColor(2);
   grf->SetLineWidth(2);
   gr->SetTitle("Wavepacket");
   gr->GetXaxis()->SetTitle("X");
   gr->GetYaxis()->SetTitle("Amplitude^2");
   gr->Draw("AL");
   if (ichoice >1) grf->Draw("L");

   // TCanvas::Update() draws the frame, after which one can change it
   c1->Update();
   c1->GetFrame()->SetFillColor(21);
   c1->GetFrame()->SetBorderSize(12);
   c1->Modified();
}
