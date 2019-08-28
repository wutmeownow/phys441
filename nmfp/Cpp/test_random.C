void test_random(Int_t nrEvents=50000000) {
	TRandom *r1=new TRandom(); 
	TRandom2 *r2=new TRandom2(); 
	TRandom3 *r3=new TRandom3();

	TH1D *h1=new TH1D("h1","TRandom",500,0,1); 
	TH1D *h2=new TH1D("h2","TRandom2",500,0,1); 
	TH1D *h3=new TH1D("h3","TRandom3",500,0,1);
	
	TStopwatch *st=new TStopwatch();
	
	st->Start();
	for (Int_t i=0; i<nrEvents; i++) { h1->Fill(r1->Uniform(0,1)); } 
	st->Stop(); cout << "Random: " << st->CpuTime() << endl;

	st->Start();
	for (Int_t i=0; i<nrEvents; i++) { h2->Fill(r2->Uniform(0,1)); } 
	st->Stop(); cout << "Random2: " << st->CpuTime() << endl;
	
	st->Start();
	for (Int_t i=0; i<nrEvents; i++) { h3->Fill(r3->Uniform(0,1)); } 
	st->Stop(); cout << "Random3: " << st->CpuTime() << endl;

	TCanvas *c1 = new TCanvas("c1","Cubic Data",200,10,700,500);
	c1->SetFillColor(42);
	c1->SetGrid();
	c1->Divide(3,1);

        c1->cd(1);
	h1->Draw();
	c1->cd(2);
	h2->Draw();
	c1->cd(3);
	h3->Draw();
}
