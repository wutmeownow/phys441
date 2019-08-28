#include <iostream>
#include <math.h>
#include "bisection.h"

using namespace std;

int main(){
	nSteps = 0;
	int nOP = 10000;
	int minX = -4;
	int maxX = 4;
	int nSearch = 50;
	cout << "Enter division size: ";
	cin >> nSearch;
	cout << endl;
	int u = populateAndSearch(nOP, minX, maxX, nSearch);
	cout << endl << "Took " << u << " steps" << endl;
	return 0;
}
