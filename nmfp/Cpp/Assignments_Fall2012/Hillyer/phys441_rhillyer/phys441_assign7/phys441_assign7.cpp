#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <cmath>

using namespace std;

//input data of .308 caliber bullet
const double PI = 3.141592654;
const double DRAG_COEFF = 0.05;  //not sure if this is right
const double AREA = 4.80644e-5;  //front of bullet m^2
const double GRAVITY = 9.81;
const double MASS = .01;         //kg
const double DENSITY_OF_AIR = 1.2;  //kg/m^3
const int MAX_TIME_STEPS = 1000000;

typedef struct {
	double x;
	double y;
} data_pair;

vector<data_pair*>* compute_trajectory(data_pair*, data_pair*, double, double); //height x and y, velocities x and y, air resistance constant, tau; forward declaration
data_pair* calculate_velocity(double, double);                              //speed, angle; forward declaration
void write_trajectory_to_file(vector<data_pair*>*, char*);                   //x and y, filename; write data to file; forward delcaration


int main(int argc, char *argv[]) {
	double height = atof(argv[1]);     //read in height
	double speed = atof(argv[2]);      //read in speed
	double angle = atof(argv[3]);      //read in angle
	double tau = atof(argv[4]);        //read in the change in y
	int want_air_res = atoi(argv[5]);  //want air resistance or not?
	char* output_filename = argv[6];   //output to what filename
	double rho = 0.0;                  //first set of rho

	if ( want_air_res == 1) {	   //check to see if we need air resistance;
		rho = DENSITY_OF_AIR;
	}

	double air_resistance_constant = -0.5 * DRAG_COEFF * rho * AREA / MASS;  //define air resistance of the bullet

	data_pair* initial_velocity = calculate_velocity(speed, angle);
	data_pair initial_position;   //initializes position
	initial_position.x = 0; initial_position.y = height;    //sets initial position
	vector<data_pair*>* trajectories = compute_trajectory(&initial_position, initial_velocity, air_resistance_constant, tau);
	write_trajectory_to_file(trajectories, output_filename);
	
	delete trajectories;
	delete initial_velocity;
	return 0;
}

data_pair* calculate_velocity(double speed, double angle) {
	data_pair* velocity = new data_pair();

	velocity->x = speed * cos(angle * PI / 180.);  //find velocity of x
	velocity->y = speed * sin(angle * PI / 180.);  //find velocity of y

	return velocity;
}

vector<data_pair*>* compute_trajectory(data_pair* initial_position, data_pair* initial_velocity, double air_resistance_constant, double tau) {
	vector<data_pair*>* trajectory = new vector<data_pair*>();
	data_pair current_velocity(*initial_velocity);
	trajectory->push_back(initial_position);
	
	for ( int i = 1; i <= MAX_TIME_STEPS; ++i) {
		double normalized_velocity = sqrt(current_velocity.x * current_velocity.x + current_velocity.y * current_velocity.y);
		double accel_x = air_resistance_constant * normalized_velocity * current_velocity.x;
		double accel_y = (air_resistance_constant * normalized_velocity * current_velocity.y) - GRAVITY;
		
		data_pair* new_position = new data_pair();
		new_position->x = trajectory->at(i-1)->x + tau * current_velocity.x;
		new_position->y = trajectory->at(i-1)->y + tau * current_velocity.y;
		
		trajectory->push_back(new_position);
//		cout << trajectory->at(i)->x << " " << trajectory->at(i)->y << endl;
		current_velocity.x += tau * accel_x;
		current_velocity.y += tau * accel_y;

		if ( new_position->y < 0 ) {
			break;
		}
	}
	return trajectory;
}

void write_trajectory_to_file(vector<data_pair*>* trajectories, char* filename) {
	ofstream output(filename);
	
	for ( int i = 0; i < trajectories->size(); ++i) {
		output << trajectories->at(i)->x << "\t" << trajectories->at(i)->y << endl;
	}
}

