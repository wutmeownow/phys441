void yahtzee(Int_t nrEvents=100000) {
	TRandom3 *r1=new TRandom3();

	TH1D *h1=new TH1D("h1","Keep One",5,1,6);
	TH1D *h2=new TH1D("h2","Keep Two",5,1,6);

	Int_t one[6];
	Int_t two[6];

	for (Int_t i=0; i<6; i++){
		one[i]=0;
		two[i]=0;
	}


	for (Int_t i=0; i<nrEvents; i++) {
	//for (Int_t i=0; i<10; i++) {
		
		one[0]=6;
		two[0]=6;
		two[1]=5;

		// First Roll!!
		one[1]=r1->Uniform(0,6)+1;
		one[2]=r1->Uniform(0,6)+1;
		one[3]=r1->Uniform(0,6)+1;
		one[4]=r1->Uniform(0,6)+1;
		one[5]=r1->Uniform(0,6)+1;
		
		two[2]=r1->Uniform(0,6)+1;
		two[3]=r1->Uniform(0,6)+1;	
		two[4]=r1->Uniform(0,6)+1;
		two[5]=r1->Uniform(0,6)+1;

		//cout << "One" << endl;
		for (Int_t j=0; j<6; j++) {
			//cout << one[j] << " ";
		}
		//cout << endl;


		// Analyze array after first roll and decide on best choice
		Int_t count_array_one[6]={0,0,0,0,0,0};
		for (Int_t j=0; j<6; j++){
			count_array_one[one[j]-1]++;
		}
		Int_t one_choice=1;
		//cout << "Count Array" << endl;
		for (Int_t j=0; j<6; j++){
			//cout << count_array_one[j] << " ";
			if(j>0){
				if(count_array_one[j]>=count_array_one[one_choice-1]) one_choice=j+1;
			}
		}
		//cout << endl;
		//cout << "One_choice = " << one_choice << endl;

		// Second Roll One!!
		Double_t one_count=0;
		for (Int_t j=0; j<6; j++) {
		       	if(one[j]!=one_choice){
		 		one[j]=r1->Uniform(0,6)+1;
 			}				
			//cout << one[j] << " ";
			if(one[j]==one_choice) one_count++;
		}	
		//cout << endl;
		
		//cout << "Two" << endl;
		for (Int_t j=0; j<6; j++) {
			//cout << two[j] << " ";
		}
		//cout << endl;

		// Analyze array after first roll and decide on best choice
		Int_t count_array_two[6]={0,0,0,0,0,0};
		for (Int_t j=0; j<6; j++){
			count_array_two[two[j]-1]++;
		}
		Int_t two_choice=1;
		//cout << "Count Array" << endl;
		for (Int_t j=0; j<6; j++){
			//cout << count_array_one[j] << " ";
			if(j>0){
				if(count_array_two[j]>=count_array_two[two_choice-1]) two_choice=j+1;
			}
		}
		//cout << endl;
		//cout << "Two_choice = " << two_choice << endl;

		// Second Roll Two!!
		Int_t two_count=0;
		for (Int_t j=0; j<6; j++) {
			if(two[j]!=two_choice){
				two[j]=r1->Uniform(0,6)+1;
			}
			//cout << two[j] << " ";
			if(two[j]==two_choice) two_count++;
		}
		//cout << endl;

		h1->Fill(one_count,1.0/nrEvents);
		h2->Fill(two_count,1.0/nrEvents);

	} 

	TCanvas *c1 = new TCanvas("c1","Yahtzee Data",200,10,700,500);
	c1->SetFillColor(42);
	c1->SetGrid();

        c1->cd();
	h2->SetLineColorAlpha(kBlue, 0.5);
	h2->Draw();
	h1->SetLineColorAlpha(kRed, 0.5);
	h1->Draw("SAME");
}
