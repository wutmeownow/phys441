#include <iostream>
#include <cmath>

using namespace std;

int main (void) {
	double total = 0.0;
	double x;
	int counter = 0;
	
	while(cin >> x) {
		total += x;
		counter++;
	}
	
	cout << (total / counter) << endl;
}
