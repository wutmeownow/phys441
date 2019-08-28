#include <math.h>
void Hwbuzzah(){

	Double_t X = 3.17;
	Double_t Fxn = 0.0;
	Double_t FxnPrime = 0.0;
	Double_t Fraction = 0.0;
	Int_t Iterations = 10;
	for(int i = 0; i < Iterations; i++) {
		Fxn = pow(X,3)-9.42478*pow(X,2)+29.60881*X-31.00628;
		FxnPrime = 3*pow(X,2)-18.84956*X+29.60881;
		Fraction = Fxn/FxnPrime;
		X = X-Fraction;
	}
	std::cout<<X<<std::endl;
}




