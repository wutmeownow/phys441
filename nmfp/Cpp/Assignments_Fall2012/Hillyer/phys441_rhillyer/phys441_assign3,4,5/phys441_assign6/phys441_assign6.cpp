#include <iostream>
#include <cstdio>
#include <vector>
#include <cstdlib>
#include <cmath>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/lu.hpp>
#include <boost/numeric/ublas/io.hpp>

//construct input data
typedef struct {
	double x;
	double y;
	double dy;
} data_tuple;

std::vector<data_tuple*>* read_data(char* filename);
boost::numeric::ublas::matrix<double>* compute_jacobian(std::vector<data_tuple*>*, double, double);
boost::numeric::ublas::matrix<double>* compute_weights(std::vector<data_tuple*>*);
boost::numeric::ublas::matrix<double>* invert_matrix(boost::numeric::ublas::matrix<double>*);
boost::numeric::ublas::matrix<double>* compute_delta_y(boost::numeric::ublas::matrix<double>*);

int main(int argc, char *argv[]) {
	char* inputfile = argv[1];
	double A = atof(argv[2]);
	double B = atof(argv[3]);
	std::vector<data_tuple*>* raw_data = read_data(inputfile);
	
/*	for (int i = 0; i < raw_data->size(); ++i) {
		std::cout << raw_data->at(i)->x << "\t" << raw_data->at(i)->y << "\t" << raw_data->at(i)->dy << std::endl;
	}
*/

	return 0;
}

//compute jacobian
boost::numeric::ublas::matrix<double>* compute_jacobian(std::vector<data_tuple*>* data, double A, double B) {
	boost::numeric::ublas::matrix<double>* jacobian = new boost::numeric::ublas::matrix<double>(data->size(), 2);
	for(int i = 0; i < data-size(); ++i) {
		jacobian[i][0] = data->at(i)->x / (B + data->at(i)->x);
		jacobian[i][1] = (A * data->at(i)->x) / (pow((B + data->at(i)->x), 2));
	}

	return jacobian;
}

//compute weights
boost::numeric::ublas::matrix<double>* compute_weights(std::vector<data_tuple*>* data) {
	boost::numeric::ublas::matrix<double>* weights = new boost::numeric::ublas::matrix<double>(data->size(),data->size());
	
	for(int i = 0; i < data->size(); ++i) {
		weights[i][i] = 1.0 / pow(data->at(i)->dy,2);
	}
	return weights;
}

//compute delta y
boost::numeric::ublas::matrix<double>* compute_delta_y(std::vector<data_tuple*>* data) {
	boost::numeric::ublas::matrix<double>* delta_y = new boost::numeric::ublas::matrix<double>(data->size(),1);
	for (int i = 0; i < data->size(); ++i) {
		delta_y[i][0] = data->at(i)->y - (A * data->at(i)->x) / (B + data->at(i)->x);
	}
	return delta_y;
}

//invert matrix
boost::numeric::ublas::matrix<double>* invert_matrix(boost::numeric::ublas::matrix<double>* input) {
	boost::numeric::ublas::matrix<double> a(*input);
	boost::numeric::ublas::permutation_matrix<double> pm(a.size1());
	
	if (boost::numeric::ublas::lu_factorize(a, pm) != 0)
		return NULL;
	
	boost::numeric::ublas::matrix<double>* inverse = new boost::numeric::ublas::matrix<double>(order,order);
	inverse->assign(boost::numeric::ublas::identity_matrix<double>(a.size1()));
	
	boost::numeric::ublas::lu_substitute(a, pm, *inverse);
	return inverse;	
}



//read in raw data
std::vector<data_tuple*>* read_data(char* filename) {
	std::vector<data_tuple*>* data = new std::vector<data_tuple*>();
	
	FILE *inputfile = fopen(filename, "r");
	
	while (!feof(inputfile)) {
		data_tuple* dt = new data_tuple;
		fscanf(inputfile, "%lf %lf %lf\n", &(dt->x), &(dt->y), &(dt->dy));
		data->push_back(dt);
	}

	fclose(inputfile);

	return data;
}


