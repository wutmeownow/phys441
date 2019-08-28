void dice_sim(Int_t nrEvents=50000) {

	TRandom3 *r3=new TRandom3();

	TH1D *h1 = new TH1D("h1","Count Histogram",300,0,300);

	int icount=0;
	for (Int_t i=0; i<nrEvents; i++) { 
		bool rolling = true;

		while (rolling){
			double roll = r3->Uniform(0,1);
			icount++;
			if (roll < 1./64.) rolling = false;
		}

		cout << "Experiment " << i << " nrolls = " << icount << endl;	
		h1->Fill(icount);
		icount=0;
	}
	
	TCanvas *c1 = new TCanvas("c1","Cubic Data",200,10,700,500);
	c1->SetFillColor(42);
	c1->SetGrid();
	c1->Divide(1,1);

        c1->cd(1);
	h1->Draw();
	h1->Fit("expo");

}
