void benford(Int_t nrEvents=10000000) {
	TRandom3 *r1=new TRandom3();

	TH1D *h1=new TH1D("h1","TRandom",120,0,12); 
	TH1D *h2=new TH1D("h1","TRandom",120,0,12); 
	for (Int_t i=0; i<nrEvents; i++) { 
		
		double choice = 10.0*abs(r1->Exp(1));
		if (choice > 10.0) choice=choice/10.0;
		while (choice < 1.0) {
			choice = 10.0*choice;
		}
		int ifill = choice;
	        h1->Fill(ifill);	
		
		choice = 10.0*abs(r1->Uniform(0,1));
		if (choice > 10.0) choice=choice/10.0;
		while (choice < 1.0) {
			choice = 10.0*choice;
		}
		ifill = choice;
	        h2->Fill(ifill);	
	}

	for (Int_t i=1; i<10; i++){
		double prob = (log10(1.0*i+1.0)-log10(i*1.0));
		cout << i << " " << prob << endl;
		double events = nrEvents*prob;
		double xval=i+0.5;
		h1->Fill(xval,events);
	}	

	TCanvas *c1 = new TCanvas("c1","Cubic Data",200,10,700,500);
	c1->SetFillColor(42);
	c1->SetGrid();
	c1->Divide(1,2);

        c1->cd(1);
	h1->Draw();
        c1->cd(2);
	h2->Draw();
}
