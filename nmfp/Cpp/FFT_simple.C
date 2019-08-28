#include "TH1D.h"
#include "TVirtualFFT.h"
#include "TF1.h"
#include "TCanvas.h"
#include "TMath.h"

void FFT_simple()
{

//This tutorial illustrates the Fast Fourier Transforms interface in ROOT.
//FFT transform types provided in ROOT:
// - "C2CFORWARD" - a complex input/output discrete Fourier transform (DFT) 
//                  in one or more dimensions, -1 in the exponent
// - "C2CBACKWARD"- a complex input/output discrete Fourier transform (DFT) 
//                  in one or more dimensions, +1 in the exponent
// - "R2C"        - a real-input/complex-output discrete Fourier transform (DFT)
//                  in one or more dimensions,
// - "C2R"        - inverse transforms to "R2C", taking complex input 
//                  (storing the non-redundant half of a logically Hermitian array) 
//                  to real output
// - "R2HC"       - a real-input DFT with output in ¡Èhalfcomplex¡É format, 
//                  i.e. real and imaginary parts for a transform of size n stored as
//                  r0, r1, r2, ..., rn/2, i(n+1)/2-1, ..., i2, i1
// - "HC2R"       - computes the reverse of FFTW_R2HC, above
// - "DHT"        - computes a discrete Hartley transform
// Sine/cosine transforms:
//  DCT-I  (REDFT00 in FFTW3 notation)
//  DCT-II (REDFT10 in FFTW3 notation)
//  DCT-III(REDFT01 in FFTW3 notation)
//  DCT-IV (REDFT11 in FFTW3 notation)
//  DST-I  (RODFT00 in FFTW3 notation)
//  DST-II (RODFT10 in FFTW3 notation)
//  DST-III(RODFT01 in FFTW3 notation)
//  DST-IV (RODFT11 in FFTW3 notation)
//First part of the tutorial shows how to transform the histograms
//Second part shows how to transform the data arrays directly
//Authors: Anna Kreshuk and Jens Hoffmann


//********* Histograms ********//


   //prepare the canvas for drawing
   TCanvas *myc = new TCanvas("myc", "Fast Fourier Transform", 1200, 900);
   myc->SetFillColor(45);
   TPad *c1_1 = new TPad("c1_1", "c1_1",0.01,0.51,0.49,0.99);
   TPad *c1_2 = new TPad("c1_2", "c1_2",0.51,0.51,0.99,0.99);
   //TPad *c1_3 = new TPad("c1_3", "c1_3",0.01,0.34,0.49,0.65);
   //TPad *c1_4 = new TPad("c1_4", "c1_4",0.51,0.34,0.99,0.65);
   TPad *c1_5 = new TPad("c1_5", "c1_5",0.01,0.01,0.49,0.49);
   TPad *c1_6 = new TPad("c1_6", "c1_6",0.51,0.01,0.99,0.49);
   c1_1->Draw();
   c1_2->Draw();
   //c1_3->Draw();
   //c1_4->Draw();
   c1_5->Draw();
   c1_6->Draw();
   c1_1->SetFillColor(30);
   c1_1->SetFrameFillColor(42);
   c1_2->SetFillColor(30);
   c1_2->SetFrameFillColor(42);
   //c1_3->SetFillColor(30);
   //c1_3->SetFrameFillColor(42);
   //c1_4->SetFillColor(30);
   //c1_4->SetFrameFillColor(42);
   c1_5->SetFillColor(30);
   c1_5->SetFrameFillColor(42);
   c1_6->SetFillColor(30);
   c1_6->SetFrameFillColor(42);
   
   c1_1->cd();
   TH1::AddDirectory(kFALSE);
     
   //A function to sample
   //TF1 *fsin = new TF1("fsin", "sin(x)+sin(2*x)+sin(0.5*x)+1", 0, 4*TMath::Pi());
   //TF1 *fsin = new TF1("fsin", "1.0+0.1*cos(2*x)+0.05*cos(5*x)+0.02*cos(10.0*x)", 0, 4*TMath::Pi());
   TF1 *fsin = new TF1("fsin", "0.0*sin(2*x)+0.0*sin(5*x)+0.0*sin(10.0*x)", 0, 4*TMath::Pi());
   TRandom3 *r=new TRandom3();
   
   Int_t n=100;
   TH1D *hsin = new TH1D("hsin", "hsin", n+20, -0.1, 1.1);
   Double_t x,offset;

   Int_t npoints=1000000;
   for (Int_t i=0; i<npoints; i++){
	   Double_t val = r->Uniform(0,1);
	   hsin->Fill(val,1.0*n/npoints);
   }
   
   //Fill the histogram with function values
   Double_t *in = new Double_t[2*((n+1)/2+1)];
   for (Int_t i=0; i<n; i++){
      x = (Double_t(i)/n);
      offset = hsin->GetBinContent(i+11);
      in[i]=fsin->Eval(x)+offset;
      hsin->SetBinContent(i+11, in[i]);
   }
   hsin->Draw();
   //fsin->Draw("same");
   hsin->GetXaxis()->SetLabelSize(0.05);
   hsin->GetYaxis()->SetLabelSize(0.05);
}
