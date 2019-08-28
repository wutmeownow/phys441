#include <iostream>
#include <math.h>

void roots() {
	
	int n = 0;
	double x[10000], y[10000];
	
	int index = 0;

	for(double xval = -4; xval <= 4; xval = xval + .0008){
		x[index] = xval;
		y[index] = pow(x[index],3) + .4*pow(x[index],2) - 4.05*x[index] + 1.8;
		index++;
	}
	
	cout <<"Enter n = ";
	cin >> n;
	int root = 0;
	int steps = 0;
	const int nn = 10000/n;
	double xp[nn],yp[nn];
	int nroots;
	
	
	for(int i = 0; i < 10000/n; i++){
		xp[i]=x[n*i];
		yp[i] = pow(x[n*i],3) + .4*pow(x[n*i],2) - 4.05*x[n*i] + 1.8;
	}


	for(int i = 0; i < 10000/n; i++){
		double xlow, xhigh, xmid, flow, fmid, fhigh;
		if(yp[i+1]*yp[i] < 0){
			double diff=10000000.;
			double epsilon=.000000001;
			cout << "ylow = " << yp[i] << "  yhigh = " << yp[i+1] << endl;
			cout << "xlow = " << xp[i] << "  xhigh = " << xp[i+1] << endl;
			xlow = xp[i];
			xhigh = xp[i+1];
			cout << diff << " " << epsilon << endl;
			steps=steps+4;
			while (diff > epsilon){
				flow = pow(xlow,3)+.4*pow(xlow,2)-4.05*xlow+1.8;
				fhigh = pow(xhigh,3)+.4*pow(xhigh,2)-4.05*xhigh+1.8;
				xmid = (xlow+xhigh)/2.0;
				fmid = pow(xmid,3)+.4*pow(xmid,2)-4.05*xmid+1.8;
				cout << xlow << " " << xmid << " " << xhigh << endl;
			 	if (flow*fmid<0){
					xhigh = xmid;
				}else{
					xlow = xmid;
				}
				cout << diff << " " << epsilon << endl;
				diff = abs(fmid);
				steps=steps+8;
			}
			cout << " Found a root!!  x = " << xmid;
			nroots++;
		}

	}
if(nroots == 3){
cout <<"steps taken: "<< steps <<endl;
}

}

