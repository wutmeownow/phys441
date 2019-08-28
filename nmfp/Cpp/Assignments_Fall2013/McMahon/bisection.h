#include <iostream>
#include <math.h>

using namespace std;

int nSteps;

double func(double x){
	double val = x*x*x + 0.40*x*x - 4.05*x + 1.80;
	//double val = 0.40*x*x - 4.05*x + 1.80;
	return val;
}

double indexToVal(int i){
	//	((double)i*(maxX-minX)/numberOfPoints)-minX
	return ((double)i*8/10000)-4;
}

void bisectionAlg(int low, int high){
	//bisection algorithm
	double limitForZero = 1.0E-10;
	double currentValue = 1.0E12;
	double mid;
	double lowIndex = indexToVal(low);
	double highIndex = indexToVal(high);
	nSteps += 2;
	while(currentValue > limitForZero){
		double fLow = func(lowIndex);
		double fHigh = func(highIndex);
		mid = (lowIndex + highIndex)/2;
		double fMid = func(mid);		
		if(fLow*fMid < 0){
			highIndex = mid;
			fHigh = fMid;
		}else{
			lowIndex = mid;
			fLow = fMid;
		}
		currentValue = fabs(fMid);
		nSteps += 8;
	}
    //Uncomment this to see roots!
	//cout << "Found root at " << mid << endl;
}

int populateAndSearch(const int nOP, int minX, int maxX, int n_search){
	//const int numberOfPoints = nOP;
	//double dataPoints[numberOfPoints];
	//double deltaX = (maxX-minX)/(double)numberOfPoints;
	
	double dataPoints[nOP];
	double deltaX = (maxX-minX)/(double)nOP;

	cout << "In populateAndSearch: " << nOP << " " << minX << " " << maxX << " " << n_search << endl;

	cout << deltaX << endl;
	cout << "numberOfPoints = " << nOP << endl;
	
	nSteps=0;

	for(int i = 0; i<nOP; i+=1){
		//Populate the array
		dataPoints[i] = func(indexToVal(i));
		//cout << dataPoints[i] << " ";
		
		
	}
	for(int i = 0; i<=nOP-n_search; i+=n_search){
		//Search the array
		if(dataPoints[i]*dataPoints[i+n_search] < 0){
			bisectionAlg(i,i+n_search);
		}
		else{
			//cout << "y = " << dataPoints[i] << endl;
			nSteps++;
		}
	}
	return nSteps;
}
