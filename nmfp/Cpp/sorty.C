void sorty()
{
	double array_size=5;
	const Double_t aray[5] = { 3, 1, 7, 9, 2 };
	const int index[5];

	aray= TMath::Sort(5,aray,index,0);

	for(int i=0;i<5;i++){
		cout << aray[i] << " ";
	}
        cout << endl;

	for(int i=0;i<5;i++){
		cout << index[i] << " " << aray[index[i]] << endl;
	}
	cout << endl;
}
