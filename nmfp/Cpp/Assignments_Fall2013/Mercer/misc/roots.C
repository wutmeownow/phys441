#include <iostream>
#include <math.h>

void roots() {
	
	int n = 0;
	double x[20000], y[20000];
	
	int index = 0;

	for(double xval = -4; xval <= 4; xval = xval + .0008){
		x[index] = xval;
		y[index] = pow(x[index],3) + .4*pow(x[index],2) - 4.05*x[index] + 1.8;
		index++;
	}
	for(int n = 1; n <= 10000; n++){

	//cin >> n;
	int root = 0;
	int steps = 0;
	const int nn = 10000;
	double xp[nn],yp[nn];
	int nroots=0;
	
	const int g = 10000;
	double n_steps[g],sparse_size[g];
	
	for(int i = 0; i < 10000/n; i++){
		xp[i]=x[n*i];
		yp[i] = pow(x[n*i],3) + .4*pow(x[n*i],2) - 4.05*x[n*i] + 1.8;
	}

	
	for(int i = 0; i < 10000/n; i++){
		//cout << "point c " << yp[i] << " " << yp[i+1] << endl;
		double xlow, xhigh, xmid, flow, fmid, fhigh;
		if(yp[i+1]*yp[i] < 0){
			double diff=10000000.;
			double epsilon=.00001;
			//cout << "ylow = " << yp[i] << "  yhigh = " << yp[i+1] << endl;
			//cout << "xlow = " << xp[i] << "  xhigh = " << xp[i+1] << endl;
			xlow = xp[i];
			xhigh = xp[i+1];
			//cout << diff << " " << epsilon << endl;
			steps=steps+4;
			while (diff > epsilon){
				flow = pow(xlow,3)+.4*pow(xlow,2)-4.05*xlow+1.8;
				fhigh = pow(xhigh,3)+.4*pow(xhigh,2)-4.05*xhigh+1.8;
				xmid = (xlow+xhigh)/2.0;
				fmid = pow(xmid,3)+.4*pow(xmid,2)-4.05*xmid+1.8;
				//cout << xlow << " " << xmid << " " << xhigh << endl;
				//cout << flow << " " << fmid << " " << fhigh << endl;
			 	if (flow*fmid<0){
					xhigh = xmid;
				}else{
					xlow = xmid;
				}
				diff = fabs(fmid);
				//cout << diff << " " << epsilon << endl;
				steps=steps+8;
			}
			cout << " Found a root!!  x = " << xmid << endl;
			nroots++;
		}
		
	}
	if(nroots == 3){
		sparse_size[n] = n;
		n_steps[n] = steps;
		cout <<"steps taken: "<< steps <<endl;
	}else{
		sparse_size[n] = 0;
		n_steps[n] = 0;
	}
	}
	



	TCanvas *c1 = new TCanvas("c1","Assignment 2",200,10,700,500);
	c1->SetFillColor(42);
	c1->SetGrid();
	//c1->SetLogx();
	//c1->SetLogy();

	gr = new TGraph(n,sparse_size,n_steps);
   	gr->SetMarkerStyle(21);
	gr->SetTitle("(n_steps) vs. the sparsification size ");
   	gr->GetXaxis()->SetTitle("n");
   	gr->GetYaxis()->SetTitle("Steps Taken");
	gr->Draw("AP");
}

