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

typedef struct {
	double A;
	double B;
} data_pair;

std::vector<data_tuple*>* read_data(char* filename);
boost::numeric::ublas::matrix<double>* compute_jacobian(std::vector<data_tuple*>*, data_pair*);
boost::numeric::ublas::matrix<double>* compute_weights(std::vector<data_tuple*>*);
boost::numeric::ublas::matrix<double>* invert_matrix(boost::numeric::ublas::matrix<double>*);
boost::numeric::ublas::matrix<double>* compute_delta_y(std::vector<data_tuple*>*, data_pair*);
data_pair* process_data(std::vector<data_tuple*>*, data_pair*);

int main(int argc, char *argv[]) {
	char* inputfile = argv[1];
	double A = atof(argv[2]);
	double B = atof(argv[3]);
	int iterations = atoi(argv[4]);

	data_pair* pair = new data_pair();
	pair->A = A;
	pair->B = B;
	std::vector<data_tuple*>* raw_data = read_data(inputfile);	

	for(int i = 0; i < iterations; ++i) {
		
		data_pair* new_pair = process_data(raw_data, pair);
		delete pair;
		pair = new_pair;
		std::cout<<i<<"\t"<<pair->A<<"\t"<<pair->B<<std::endl;
	}
	

/*	for (int i = 0; i < raw_data->size(); ++i) {
		std::cout << raw_data->at(i)->x << "\t" << raw_data->at(i)->y << "\t" << raw_data->at(i)->dy << std::endl;
	}
*/
	delete raw_data;


	return 0;
}

data_pair* process_data(std::vector<data_tuple*>* raw_data, data_pair* pair) {
	boost::numeric::ublas::matrix<double>* jacobian = compute_jacobian(raw_data, pair);
	boost::numeric::ublas::matrix<double> jacobian_t = boost::numeric::ublas::trans(*jacobian);
//	std::cout<<jacobian_t<<std::endl;
	boost::numeric::ublas::matrix<double>* weights = compute_weights(raw_data);
	boost::numeric::ublas::matrix<double>* delta_y = compute_delta_y(raw_data, pair);
	boost::numeric::ublas::matrix<double> jacobian_t_weights = boost::numeric::ublas::prod(jacobian_t, *weights);
//	std::cout<<jacobian_t_weights<<std::endl;
	boost::numeric::ublas::matrix<double> jacobian_t_weights_jacobian = boost::numeric::ublas::prod(jacobian_t_weights, *jacobian);
//	std::cout<<jacobian_t_weights_jacobian<<std::endl;
	boost::numeric::ublas::matrix<double> jacobian_t_weights_delta_y = boost::numeric::ublas::prod(jacobian_t_weights, *delta_y);
	boost::numeric::ublas::matrix<double>* jacobian_t_weights_jacobian_inverse = invert_matrix(&jacobian_t_weights_jacobian);
	std::cout<<*jacobian_t_weights_jacobian_inverse<<std::endl;
	boost::numeric::ublas::matrix<double> delta_b = boost::numeric::ublas::prod(*jacobian_t_weights_jacobian_inverse, jacobian_t_weights_delta_y);	

	delete jacobian;
	delete weights;

	data_pair* new_pair = new data_pair();
	new_pair->A = pair->A + delta_b(0,0);
	new_pair->B = pair->B + delta_b(1,0);
	return new_pair;
}

//compute jacobian
boost::numeric::ublas::matrix<double>* compute_jacobian(std::vector<data_tuple*>* data, data_pair* pair) {
	boost::numeric::ublas::matrix<double>* jacobian = new boost::numeric::ublas::matrix<double>(data->size(), 2);
	for(int i = 0; i < data->size(); ++i) {
		jacobian->insert_element(i, 0, data->at(i)->x / (pair->B + data->at(i)->x));
		jacobian->insert_element(i, 1, (pair->A * data->at(i)->x) / (pow((pair->B + data->at(i)->x), 2)));
	}
//	std::cout<<*jacobian<<std::endl;
	return jacobian;
}

//compute weights
boost::numeric::ublas::matrix<double>* compute_weights(std::vector<data_tuple*>* data) {
	boost::numeric::ublas::matrix<double>* weights = new boost::numeric::ublas::matrix<double>(data->size(),data->size());
	
	for(int i = 0; i < data->size(); ++i) {
		weights->insert_element(i, i, 1.0 / pow(data->at(i)->dy, 2));
	}
//	std::cout<<*weights<<std::endl;
	return weights;
}

//compute delta y
boost::numeric::ublas::matrix<double>* compute_delta_y(std::vector<data_tuple*>* data, data_pair* pair) {
	boost::numeric::ublas::matrix<double>* delta_y = new boost::numeric::ublas::matrix<double>(data->size(),1);

	for (int i = 0; i < data->size(); ++i) {
		delta_y->insert_element(i, 0, data->at(i)->y - (pair->A * data->at(i)->x) / (pair->B + data->at(i)->x));
	}
//	std::cout<<*delta_y<<std::endl;
	return delta_y;
}

//invert matrix
boost::numeric::ublas::matrix<double>* invert_matrix(boost::numeric::ublas::matrix<double>* input) {
	boost::numeric::ublas::matrix<double> a(*input);
	boost::numeric::ublas::permutation_matrix<double> pm(a.size1());
	
	if (boost::numeric::ublas::lu_factorize(a, pm) != 0)
		return NULL;
	
	boost::numeric::ublas::matrix<double>* inverse = new boost::numeric::ublas::matrix<double>(input->size1(),input->size1());
	inverse->assign(boost::numeric::ublas::identity_matrix<double>(a.size1()));
	
	boost::numeric::ublas::lu_substitute(a, pm, *inverse);
	return inverse;	
}

//compute new A

//read in raw data
std::vector<data_tuple*>* read_data(char* filename) {
	std::vector<data_tuple*>* data = new std::vector<data_tuple*>();
	
	FILE *inputfile = fopen(filename, "r");
	
	while (!feof(inputfile)) {
		data_tuple* dt = new data_tuple;
		fscanf(inputfile, "%lf %lf %lf\n", &(dt->x), &(dt->y), &(dt->dy));
//		std::cout<<dt->x<<"\t"<<dt->y<<std::endl;
		data->push_back(dt);
	}

	fclose(inputfile);

	return data;
}


