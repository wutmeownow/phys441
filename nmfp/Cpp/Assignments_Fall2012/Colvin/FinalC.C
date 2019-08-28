void FinalC() {
	
	const int n = 15;
	
	Double_t VofT[n] = 0;
		VofT[0] = 103.1;
		VofT[1] = 145.8;
		VofT[2] = 178.5;
		VofT[3] = 206.1;
		VofT[4] = 230.5;
		VofT[5] = 252.5;
		VofT[6] = 272.7;
		VofT[7] = 291.5;
		VofT[8] = 309.2;
		VofT[9] = 325.9;
		VofT[10] = 341.8;
		VofT[11] = 356.8;
		VofT[12] = 371.4;
		VofT[13] = 385.2;
		VofT[14] = 398.3;

	Double_t T[n] = 0;
		T[0] = 20;
		T[1] = 40;
		T[2] = 60;
		T[3] = 80;
		T[4] = 100;
		T[5] = 120;
		T[6] = 140;
		T[7] = 160;
		T[8] = 180;
		T[9] = 200;
		T[10] = 220;
		T[11] = 240;
		T[12] = 260;
		T[13] = 280;
		T[14] = 300;

TCanvas *c1 = new TCanvas("c1","Final part C",200,10,700,500);
	gStyle->SetOptStat(1);
	gStyle->SetOptFit(1);
	gr = new TGraph(n,T,VofT);
	gr->SetLineColor(2);
	gr->SetLineWidth(4);
	gr->SetMarkerColor(4);
	gr->SetMarkerStyle(21);
	gr->SetTitle("Mean Velocity versus Temperature");
	gr->GetXaxis()->SetTitle("Mean Velovity");
	gr->GetYaxis()->SetTitle("Temperature");
	gr->Draw("ACP");
	c1->Update();

// This plot shows a standard temperature distribution. So it follows theoetical predictions. 
}
