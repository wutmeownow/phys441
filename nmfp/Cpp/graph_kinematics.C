#include <ostream>

void graph_kinematics() {
   //
   //Modified: Edward J. Brash
   //		
  
   //gStyle->SetOptFit(kFALSE);	
   gStyle->SetOptFit(1);	
   TCanvas *c1 = new TCanvas("c1","Relativistic Kinematics",200,10,700,500);

   c1->SetFillColor(42);
   c1->SetGrid();
   c1->Divide(2,2);
   //c1->SetLogx();

   const Int_t n = 1000;
   Double_t pep[n], ppp[n], theta[n], phi[n],beta[n];
   Int_t i=0;

   Double_t mp=0.9382796;
   Double_t pe=6.0;
   Double_t Pi=3.14159265;

   for (i=0; i<n; i++){
	   theta[i]=45.0*(i/1000.0)+0.00001;
	   pep[i]=mp*pe/(mp+2.0*pe*sin((Pi/180.0)*theta[i]/2.0)*sin((Pi/180.0)*theta[i]/2.0));
	   phi[i]=180.0/Pi*atan(pep[i]*sin((Pi/180.0)*theta[i])/(pe-pep[i]*cos((Pi/180.0)*theta[i])));
	   ppp[i]=pep[i]*sin((Pi/180.0)*theta[i])/sin((Pi/180.0)*phi[i]);
	   Double_t gamma = sqrt(ppp[i]*ppp[i]+mp*mp)/mp;
	   beta[i]=sqrt(1.0-1.0/(gamma*gamma));
	   cout << "Theta = " << theta[i] << "  Gamma = " << gamma << " Ppp = " << ppp[i] << " Beta = " << beta[i] << endl;
   }

   const Int_t np=i;

   gr1 = new TGraph(np,theta,pep);
   gr2 = new TGraph(np,theta,ppp);
   gr3 = new TGraph(np,theta,phi);
   gr4 = new TGraph(np,theta,beta);

//   gr->SetLineColor(2);
//   gr->SetLineWidth(4);
   gr1->SetMarkerColor(kBlue);
   //gr1->SetMarkerStyle(21);
   gr1->SetTitle("Scattered Elecron Energy");
   gr1->GetXaxis()->SetTitle("theta");
   gr1->GetYaxis()->SetTitle("Electron Energy (GeV)");
   gr2->SetMarkerColor(kBlue);
   //gr2->SetMarkerStyle(21);
   gr2->SetTitle("Scattered Proton Momentum");
   gr2->GetXaxis()->SetTitle("theta");
   gr2->GetYaxis()->SetTitle("Proton Momentum (GeV/c)");
   gr3->SetMarkerColor(kBlue);
   //gr3->SetMarkerStyle(21);
   gr3->SetTitle("Scattered Proton Angle");
   gr3->GetXaxis()->SetTitle("theta");
   gr3->GetYaxis()->SetTitle("Proton Angle (degrees)");
   gr4->SetMarkerColor(kBlue);
   //gr4->SetMarkerStyle(21);
   gr4->SetTitle("Scattered Proton Beta");
   gr4->GetXaxis()->SetTitle("theta");
   gr4->GetYaxis()->SetTitle("Beta");
   c1->cd(1);
   gr1->Draw("AP");
   c1->cd(2);
   gr2->Draw("AP");
   c1->cd(3);
   gr3->Draw("AP");
   c1->cd(4);
   gr4->Draw("AP");

   // TCanvas::Update() draws the frame, after which one can change it
   c1->Update();
   c1->GetFrame()->SetFillColor(21);
   c1->GetFrame()->SetBorderSize(12);
   c1->Modified();
}
