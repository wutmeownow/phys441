#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include <string>
#include <string.h>
#include <map>
#include <utility>

using namespace std;

const double PI = 3.14159;
const double M = pow(2,31) - 1;
const double A = 16807;

map<string, int>* compute_uniform(double);   //seed
map<string, int>* compute_triangular(double, double);   //seed
map<string, int>* compute_exp(double);   //seed
map<string, int>* compute_gauss(double, double);   //seed
double my_rand(double);
void safe_insert(map<string, int>*, double);
void dump_map(map<string, int>*);

int main(int argc, char *argv[]) {
	string distribution = argv[1];
	double seed_1 = atof(argv[2]);
	map<string, int>* histogram;
	
	if ( distribution == "uniform" ) {
		histogram = compute_uniform(seed_1);
	}
	else if ( distribution == "triangular" ) {
		double seed_2 = atof(argv[3]);
		histogram = compute_triangular(seed_1, seed_2);
	}
	else if ( distribution == "exp" ) {
		histogram = compute_exp(seed_1);
	
	}
	else if ( distribution == "gauss" )  {
		double seed_2 = atof(argv[3]);
		histogram = compute_gauss(seed_1, seed_2);
	}
	else {
		cerr << "invalid distribution" << endl;
		return 1;
	}
	
	dump_map(histogram);
	
	delete histogram;
	return 0;

}

double my_rand(double seed) {
	double rand = fmod((A*seed),M);
	return rand;
}

map<string, int>* compute_uniform(double seed) {
	map<string, int>* histogram = new map<string, int>();
//	safe_insert(histogram, -25.00);
	for ( int i = 0; i < 1000000; ++i) {
		safe_insert(histogram, (my_rand(seed)) / M);
		seed = my_rand(seed);
	}
	return histogram;
}

map<string, int>* compute_triangular(double seed_1, double seed_2) {
	map<string, int>* histogram = new map<string, int>();
	for ( int i = 0; i < 100000; ++i) {
		safe_insert(histogram, (my_rand(seed_1)/M) + (my_rand(seed_2)/M));
		seed_1 = my_rand(seed_1);
		seed_2 = my_rand(seed_2);
	}
	return histogram;
}

map<string, int>* compute_gauss(double seed_1, double seed_2) {
	map<string, int>* histogram = new map<string, int>();
	for ( int i = 0; i < 500000; ++i) {
		double mean = 0.0;
		double sigma = 1.0;
		double x = my_rand(seed_1)/M;
		double y = my_rand(seed_2)/M;
		safe_insert(histogram, pow(-2*log(x),.5)*sigma*cos(2*PI*y)+mean);
		seed_1 = my_rand(seed_1);
		seed_2 = my_rand(seed_2);
	}
	return histogram;
}
map<string, int>* compute_exp(double seed_1) {
	map<string, int>*histogram = new map<string, int>();
	for ( int i = 0; i < 1000000; ++i) {
		safe_insert(histogram, -log(1 - (my_rand(seed_1)/M)));
		seed_1 = my_rand(seed_1);
	}
	return histogram;
}
void safe_insert(map<string, int>* my_map, double value) {
	char trimmed_value[10];
	sprintf(trimmed_value, "%.3lf", value);
	if(my_map->count(trimmed_value) == 0) {
		my_map->insert(pair<string, int>(trimmed_value, 1));
	}
	else {
		(* my_map->find(trimmed_value)).second += 1;
	}
}

void dump_map(map<string, int>* my_map) {
	for ( map<string, int>::iterator ii = my_map->begin(); ii != my_map->end(); ++ii) {
		cout << ii->first << " " << ii->second << endl;	
	}
}


