void pi_random(Int_t nrEvents=1000000000) {
	TRandom3 *r3=new TRandom3();

	TStopwatch *st=new TStopwatch();
	Int_t divisor = 100000;
	const Int_t nbins = nrEvents/divisor;

	Double_t sum = 0.0;
	Double_t pi_current[nbins], ex[nbins], epi[nbins], time[nbins];


		
	st->Start();
	for (Int_t i=0; i<nrEvents; i++) { 
		
		Double_t x = r3->Uniform(0,1);
		Double_t y = r3->Uniform(0,1);
		Double_t theta = 2.0*TMath::Pi()*r3->Uniform(0,1);
		Double_t x_end = x+TMath::Cos(theta);
		Double_t y_end = y+TMath::Sin(theta);
		//cout << x << " " << x_end << " " << theta*180.0/TMath::Pi() << endl;
		//if(x_end > 0.0 && x_end < 1.0 && y_end > 0.0 && y_end < 1.0) {
		if(x_end > 0.0 && x_end < 1.0) {
			//cout << " success!! " << endl; 
			sum++;
		}
		if(i % 10000 == 0) {
			Int_t bin_number = i/divisor;
			pi_current[bin_number] = (1.0+sum/((i+1-sum)))*2.0;
			epi[bin_number]=1.0/TMath::Sqrt(i+1);
			ex[bin_number]=0.0;
			time[bin_number]=bin_number;
			//cout << "i = " << i << " bin_number = " << bin_number << 
			//	"  pi_current = " << pi_current[bin_number] << endl;
		}
	}

	cout << "Trials = " << i << "  Successes = " << sum << endl;
	cout << "Success / Failures = " << sum/(i+1-sum) << endl;
	cout << "Pi = " << (1.0+sum/((i+1-sum)))*2.0 << endl;

	gr = new TGraphErrors(nbins,time,pi_current,ex,epi);
		
	st->Stop(); cout << "Random3: " << st->CpuTime() << endl;

	TCanvas *c1 = new TCanvas("c1","Cubic Data",200,10,700,500);
	c1->SetFillColor(42);
	c1->SetGrid();

	gr->Draw();

}
