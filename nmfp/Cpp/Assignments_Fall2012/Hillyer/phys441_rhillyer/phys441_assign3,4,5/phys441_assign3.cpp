#include <iostream>
#include <cstdio>
#include <vector>
#include <cstdlib>
#include <cmath>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/lu.hpp>
#include <boost/numeric/ublas/io.hpp>

using namespace boost::numeric::ublas;
//using namespace std;

int order = 0;

typedef struct {
	double x;
	double y;
	double o;
} data_pair;

std::vector<data_pair*>* read_data(void);
vector<double>* compute_v(std::vector<data_pair*>*);
matrix<double>* compute_a(std::vector<data_pair*>*);
matrix<double>* invert_matrix(matrix<double>*);
//matrix<double>* multiply_matrix(matrix<double>*);

int main(int argc, char *argv[]) {
	order = atoi(argv[1]);
	std::vector<data_pair*>* raw_data = read_data();
	vector<double>* v = compute_v(raw_data);
	matrix<double>* a = compute_a(raw_data);
	matrix<double>* a_i = invert_matrix(a);

	std::cout << prod(*a_i,*v) << std::endl;
//	std::cout << (*v) << std::endl;
	
	delete a_i;
	delete v;
	delete a;
	delete raw_data;
	return 0;
}

std::vector<data_pair*>* read_data(void) {
	std::vector<data_pair*>* data = new std::vector<data_pair*>();
	double x; double y; double o;
	
	while (std::cin >> x >> y >> o) {
		data_pair* d = new data_pair;
		d->x = x;
		d->y = y;
		d->o = o;
//		std::cout <<(o) << std::endl;
		data->push_back(d);
	}
	return data;
}

vector<double>* compute_v(std::vector<data_pair*>* data) {
	vector<double>* v = new vector<double>(order);
	for (int i = 0; i < order; i++) {
		double temp = 0;
		for (int j = 0; j < data->size(); j++) {
			temp += pow(data->at(j)->x, i) * data->at(j)->y; 
		}
		v->insert_element(i,temp);
		std::cout << (temp) << std::endl;
//		std::cout << (*v)(i,0) << std::endl;
	}
	return v;
}

matrix<double>* compute_a(std::vector<data_pair*>* data) {
	matrix<double>* a = new matrix<double>(order,order);
	
	for (int i = 0; i < order; i++) {
		for(int j = 0; j < order; j++) {
			double temp = 0;
			for(int k = 0; k < data->size(); k++) {
				temp += pow(data->at(k)->x,i+j)/data->at(k)->o;
			}
			a->insert_element(i,j,temp);
//			std::cout << (temp) << std::endl;
//			std::cout << (*a)(i,j) << std::endl;
		}
	}
	return a;
}

matrix<double>* invert_matrix(matrix<double>* input) {
	matrix<double> a(*input);
	permutation_matrix<double> pm(a.size1());
	
	if (lu_factorize(a, pm) != 0)
		return NULL;
	
	matrix<double>* inverse = new matrix<double>(order,order);
	inverse->assign(identity_matrix<double>(a.size1()));
	
	lu_substitute(a, pm, *inverse);
	return inverse;	
}
