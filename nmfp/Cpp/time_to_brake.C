void time_to_brake(Double_t zeroTo100=5.6, Double_t topSpeed=160.0, Double_t D_b=92.0, Double_t D_r=400.0) {

	Double_t c=0.277777777777; // convert from km/hr to m/s
	Double_t V_100 = 100*c;

	Double_t A = V_100/zeroTo100;
	Double_t A_b = -1.0*V_100*V_100/(2.0*D_b);

	Double_t V_max = topSpeed*c;

	Double_t T_a = V_max/A;
	Double_t T_b = -1.0*V_max/A_b;

	Double_t D_a = (A/2)*T_a*T_a;
	Double_t D_br = -1.0*(A_b/2)*T_b*T_b;

	Double_t T;

	cout << "D_a = " << D_a << "  D_br = " << D_br << endl;
	cout << "T_a = " << T_a << "  T_b = " << T_b << endl;
	cout << "A = " << A << "  A_b = " << A_b << endl;
	
	if (D_a+D_br > D_r) {
		// Top speed will cause overrun
		T = sqrt(2.0*D_r/(A - A*A/A_b));
		cout << "Max speed not reached!! Time to brake = " << T << endl;
	}else{
		// Top speed reached
		T = T_a + ((D_r - (D_a+D_br))/V_max);
		cout << "Max speed reached!! Time to brake = " << T << endl;
	}
}
