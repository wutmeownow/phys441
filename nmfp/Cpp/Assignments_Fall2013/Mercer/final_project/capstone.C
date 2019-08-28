void capstone() {
	

	int n = 33;
	//int index=0;
	
	double Weight [33] = {7100.00, 7100.00, 7000.00, 7000.00, 6900.00, 6900.00, 6800.00, 
			6800.00, 6700.00, 6700.00, 6600.00, 6600.00, 6500.00, 6500.00, 6400.00, 6400.00, 
			6300.00, 6300.00, 6200.00, 6200.00, 6100.00, 6100.00, 6000.00, 6000.00, 5900.00, 
			5900.00, 5800.00, 5800.00, 5700.00, 5700.00, 5600.00, 5600.00, 5600.00};
	double Time [33] = {10.95, 11.05, 10.85, 10.95, 10.75, 10.85, 10.65, 10.75, 10.55, 10.65, 10.45, 10.55, 
			10.35, 10.45, 10.25, 10.35, 10.15, 10.25, 10.05, 10.15, 9.95, 10.05, 9.85, 9.95, 
			9.75, 9.85, 9.65, 9.75, 9.55, 9.65, 9.45, 9.55, 9.50};
			
	//for(int i = 0; i < 33; i++){
		//double t = 9.500;
		//double w = 5600.0
		//Weight[index] = 5600.0 + w;
		//Time[index] = 9.5;
		//cout << "Time = " << Time[index] << "  Weight = " << Weight[index] << endl;
		//index++;
		//t++;
		//w++;
	//}

	TCanvas *c1 = new TCanvas("c1","Physics 441: Capstone Assignment",200,10,700,500);
	c1->SetFillColor(29);
	c1->SetGrid();
	//c1->SetLogx();
	//c1->SetLogy();

	gr = new TGraph(n,Time,Weight);
   	gr->SetMarkerStyle(21);
	gr->SetTitle("Project Consistency: Expected Results");
   	gr->GetXaxis()->SetTitle("Time (seconds)");
   	gr->GetYaxis()->SetTitle("Mass (pounds)");
	gr->Draw("AP");

}
