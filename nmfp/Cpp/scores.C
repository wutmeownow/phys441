void scores() {

	Double_t weights[6][3]={60,15,25,50,30,20,45,35,20,45,30,25,45,25,30,35,35,30};
	Double_t score[7]={1,1.5,2,2.5,3,3.5,4};

	TH1D *h1 = new TH1D("h","h",10000,0.9,4.1);
	TH1D *hr1 = new TH1D("hr1","hr1",10000,0.9,4.1);
	TH1D *hr2 = new TH1D("hr2","hr2",10000,0.9,4.1);
	TH1D *hr3 = new TH1D("hr3","hr3",10000,0.9,4.1);
	TH1D *hr4 = new TH1D("hr4","hr3",10000,0.9,4.1);

	for (Int_t i = 0; i<6; i++){
			for (Int_t k=0; k<7; k++){
				for (Int_t l=0; l<7; l++) {
					for (Int_t m=0; m<7; m++) {
						Double_t final_score = score[k]*weights[i][0]/100.0+score[l]*weights[i][1]/100.0+score[m]*weights[i][2]/100.0;
						Int_t index=m+l*7+k*7*7+i*7*7*7;
//						cout << "Index = " << index << " Score = " << final_score << endl;
						h1->Fill(final_score);
					}
				}
			}
	}

	TCanvas *c1 = new TCanvas("c1","Scores",1200,520,700,500);
	h1->Draw();

	TRandom3 *r = new TRandom3();

	Double_t sumr1=0;
	Double_t sumr2=0;
	Double_t sumr3=0;

	for (Int_t icount=0; icount < 100000; icount ++){
		
		//Double_t r1 = r->Gaus(3.25,0.8);
		Double_t r1 = r->Uniform(2.0,4.5);
		Int_t i1 = 2*r1;
		Double_t r1a = i1/2.0;
		if (r1a > 4.0) r1a=4.0;
		if (r1a < 2.0) r1a=2.0;
		sumr1 += r1a;
		hr1->Fill(r1a);
		
		//Double_t r2 = r->Gaus(3.25,0.8);
		Double_t r2 = r->Uniform(2.0,4.5);
		Int_t i2 = 2*r2;
		Double_t r2a = i2/2.0;
		if (r2a > 4.0) r2a=4.0;
		if (r2a < 2.0) r2a=2.0;
		sumr2 += r2a;
		hr2->Fill(r2a);
		
		//Double_t r3 = r->Gaus(3.25,0.8);
		Double_t r3 = r->Uniform(2.0,4.5);
		Int_t i3 = 2*r3;
		Double_t r3a = i3/2.0;
		if (r3a > 4.0) r3a=4.0;
		if (r3a < 2.0) r3a=2.0;
		sumr3 += r3a;
		hr3->Fill(r3a);
						
		Int_t i4 = r->Uniform(0,7);
		Double_t final_score2 = r1a*weights[i4][0]/100.0+r2a*weights[i4][1]/100.0+r3a*weights[i4][2]/100.0;
		hr4->Fill(final_score2);

//		cout << "r = " << r1a << " " << r2a << " " << r3a << endl;
	}

	cout << "r1 average = " << sumr1/100000.0 << endl;
	cout << "r2 average = " << sumr2/100000.0 << endl;
	cout << "r3 average = " << sumr3/100000.0 << endl;
	
	TCanvas *c2 = new TCanvas("c2","Scores",1200,520,700,500);
	c2->Divide(2,2);
	
	c2->cd(1);
	hr1->Draw();
	c2->cd(2);
	hr2->Draw();
	c2->cd(3);
	hr3->Draw();
	c2->cd(4);
	hr4->Draw();

}
