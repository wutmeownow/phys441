#include <math.h>
void HwOneNewton(){
	
	Double_t X;
	cout << "Enter a guess at the root: ";
	cin >> X;
	Double_t Fxn = 0.0;
	Double_t FxnPrime = 0.0;
	Double_t Fraction = 0.0;
	Int_t Iterations;
	cout << "Enter the number of iterations desired: ";
	cin >> Iterations;
	for (int i = 1; i < Iterations+1; i++) {
		Fxn = pow(X,3)-9.42478*pow(X,2)+29.6088*X-31.00628;
		FxnPrime = 3*pow(X,2)-18.84956*X+29.6088;
		Fraction = Fxn/FxnPrime;
		X = X-Fraction;
		std::cout<<"The root for iteration "<<i<<" is: "<<X<<std::endl;
	}
}




