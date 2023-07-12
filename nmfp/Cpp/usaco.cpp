#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
	ifstream infile("in.dat");

	const int size = 30;

	int N;
	const int NN = N;
	char dir[NN];
	int x[NN], y[NN];
	int location[size][size];
	int conflict[NN];

	for (int i=0; i<size; i++){
		for(int j=0; j<size; j++){
			location[i][j]=0;
			cout << location[i][j] << " ";
		}
		cout << endl;
	}


	if (infile.is_open()) {
		infile >> N;
		cout << "N = " << N << endl; 
		for (int i=0; i<N; i++) {
			infile >> dir[i] >> x[i] >> y[i];
		        //cout << dir << " " << x << " " << y << endl;
			location[x[i]][y[i]]=i+1;
		}
	} else cout << "Unable to open file" << endl;

        cout << "----------" << endl;

	for (int i=0; i<size; i++){
		for(int j=0; j<size; j++){
			cout << location[i][j] << " ";
		}
		cout << endl;
	}

	for (int i=0;i<N;i++) {
		conflict[i] = 0;
	}

	cout << "----------" << endl;

	int moves = 1;

	while (moves > 0) {
	  moves = 0;
	  for (int i=0; i<N; i++){
		cout << dir[i] << endl;
		if (dir[i] == 'N') {
			cout << "here North" << endl;
			cout << location[x[i]][y[i]+1] << endl;
			if (y[i]+1<size) {
				if (location[x[i]][y[i]+1] == 0) {
					location[x[i]][y[i]+1] = i+1;
					moves++;
				} else {
					dir[i] = 'S';
					conflict[location[x[i]][y[i]+1]-1]=conflict[location[x[i]][y[i]+1]-1]+1+conflict[location[x[i]][y[i]]-1];
				}
				y[i]=y[i]+1;
			}
		} else if (dir[i] == 'E') {
			cout << "here East" << endl;
			cout << location[x[i]+1][y[i]] << endl;
			if (x[i]+1<size) {
				if (location[x[i]+1][y[i]]==0) {
					location[x[i]+1][y[i]] = i+1;
					moves++;
				} else {
					dir[i] = 'S';
					conflict[location[x[i]+1][y[i]]-1]=conflict[location[x[i]+1][y[i]]-1]+1+conflict[location[x[i]][y[i]]-1];
				}
				x[i]=x[i]+1;
			}
		}

	  }
	  cout << moves << endl;
	}

	cout << moves << endl;

	for (int i=0; i<size; i++){
		for(int j=0; j<size; j++){
			cout << location[i][j] << " ";
		}
		cout << endl;
	}

	for (int i=0;i<N;i++) {
		cout << conflict[i] << endl;
	}

	return 0;	
}
