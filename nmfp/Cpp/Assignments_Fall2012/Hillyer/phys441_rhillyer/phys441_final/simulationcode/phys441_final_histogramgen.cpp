#include <iostream>
#include <cmath>
#include <map>


using namespace std;

void feed_into_histogram(map<int, int>*, double);

int main (void) {
	double value;
	int counter = 0;

	
	map<int, int> histogram;
	
	while(cin >> value) {
		feed_into_histogram(&histogram, value);
		counter++;
	}
	
	for (map<int, int>::iterator ii = histogram.begin(); ii != histogram.end(); ii++) {
		cout << ii->first << " " << (((double)(ii->second)) / counter) * 100.0 << endl;
	}
	return 0;
}

void feed_into_histogram(map<int, int> *histogram, double value) {
	int truncated_value = floor(value);

	if (histogram->count(truncated_value) == 0) {
		histogram->insert(pair<int, int>(truncated_value, 1));
	}
	else {
		map<int, int>::iterator ii = histogram->find(truncated_value);
		ii->second += 1;
	}
}
