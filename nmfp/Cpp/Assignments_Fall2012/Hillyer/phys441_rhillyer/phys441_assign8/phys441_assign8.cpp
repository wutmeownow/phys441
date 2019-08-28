#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <cmath>

using namespace std;

//input data of the pendulum
const double PI = 3.141592654;
const double GRAVITY = 9.81;
const int MAX_TIME_STEPS = 10000;

typedef struct {
	double theta;
	double time;
} data_pair;

vector<data_pair*>* compute_pendulum_trajectory(double, double, double);

int main(int argc, char *argv[]) {
	double length = atof(argv[1]); //read in length of pendulum
	double initial_theta = atof(argv[2]);  //initial theta
	double tau = atof(argv[3]);
	char* out_filename = argv[4];

	vector<data_pair*>* pendulum_trajectory = compute_pendulum_trajectory(length, initial_theta, tau);	

	for (int i = 0; i < pendulum_trajectory->size(); ++i) {
		cout << pendulum_trajectory->at(i)->time << "\t" << (180.0 * pendulum_trajectory->at(i)->theta) / PI << endl;
	}

	delete pendulum_trajectory;

	return 0;
}

vector<data_pair*>* compute_pendulum_trajectory(double length, double initial_theta, double tau) {
	vector<data_pair*>* trajectory = new vector<data_pair*>();

	double g_l = GRAVITY / length;

	data_pair* current  = new data_pair;
	data_pair* one_back = new data_pair;
	
	current->theta = (initial_theta * PI) / 180.0;
	current->time  = 0.0;


	double acceleration = -1.0 * (g_l * sin(current->theta));
	one_back->theta = current->theta + 0.5 * tau * tau * acceleration;
	one_back->time  = 0.0 - tau;
	
	trajectory->push_back(one_back);
	trajectory->push_back(current);	
	
	for (int i = 2; i <= MAX_TIME_STEPS + 1; ++i) {
		current = new data_pair;
		
		acceleration = -1.0 * (g_l * sin(trajectory->at(i - 1)->theta));
		double theta    = 2 * trajectory->at(i - 1)->theta  + (tau * tau * acceleration) - trajectory->at(i - 2)->theta;
		
		current->theta = theta;
		current->time  = trajectory->at(i - 1)->time + tau;

		trajectory->push_back(current);
	}

	// remove that reverse trajectory item
	trajectory->erase(trajectory->begin(), trajectory->begin() + 1);
	
	return trajectory;		
}

