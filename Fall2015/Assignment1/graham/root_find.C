#include <TRandom.h>

double function(double x){
    double a0 = 1.80;
    double a1 = -4.05;
    double a2 = 0.40;
    double a3 = 1.00;
	return a0+a1*x+a2*x*x+a3*x*x*x;
}

std::vector<double> root_finder(int nsearch) {
  std::vector<double> output(1);

  double f, xmid, fa, fb, fc;

  double xlow = -4.0;
  double xhigh = 4.0;
  const int npoints = 10007;
  //* arrays to store the function
  double xval[npoints];
  double yval[npoints];
  //* arrays to store the positions of the roots
  double xroots[npoints];
  double yroots[npoints];
  //* step size in x
  double dx = (xhigh-xlow)/npoints;

  for (int i = 0; i<npoints;i++){
	xval[i]=xlow+i*dx;
	yval[i]=function(xval[i]);
  }

  int niter = npoints/nsearch;
  double ycomp=yval[0];
  int nsteps=0;
  int nroots_found=0;

  //* Main iteration loop

  for (int i=1; i<niter; i++){
	double y=yval[nsearch*i];
        //* check to see if the endpoint of the chunk is a root
	if (y == 0.0) {
		output[output.size()-1] = xval[nsearch*i];
		output.resize(output.size()+1);
		nsteps=nsteps+1;
		//* store the position of the found root
		xroots[nroots_found]=xval[nsearch*i];
		yroots[nroots_found]=0.0;
		nroots_found++;
	}
	nsteps++;
	if (y*ycomp < 0.0){
		//* Found a root in this interval
		xlow = xval[nsearch*(i-1)];
		xhigh = xval[nsearch*i];
		nsteps=nsteps+2;
  		double epsilon = 1.0E-10;
  		double diff = 1.0E12;
		while (diff > epsilon){
			fa = function(xlow);
			fb = function(xhigh);
			xmid = (xhigh + xlow)/2.0;
			fc = function(xmid);
			nsteps=nsteps+4;
			double product = fa*fc;
			if (product < 0) {
				xhigh = xmid;
				fb = fc;
				nsteps=nsteps+2;
			} else {
				xlow = xmid;
				fa = fc;
				nsteps=nsteps+2;
			}

			diff = fabs(fc);
			nsteps++;
		}
		//* store the position of the found root 
		output[output.size()-1] = xmid;
		output.resize(output.size()+1);
		xroots[nroots_found]=xmid;
		yroots[nroots_found]=0.0;
		nroots_found++;
		ycomp=y;
		nsteps++;
	}
	else{
		ycomp=y;
		nsteps++;
	}
  }
  output[output.size()-1] = nsteps;

  return output;
}

void root_find(){
	const int size = 10007;
	double steps[size];
	double chunk[size];
	for (int j = 1; j<size+1;j++){
		std::vector<double> value = root_finder(j);
		if (j==1){
			for (int i = 0; i < value.size()-1; i++){
				cout << "Root [" << (i+1) << "] = " << value[i] << endl;
			}
		}
		steps[j-1] = value[value.size()-1];
		chunk[j-1] = j;
	}
	gStyle->SetOptFit(kFALSE);
    TCanvas *c1 = new TCanvas("c1","Root Find Analysis",200,10,700,500);
    c1->SetFillColor(42);
    c1->SetGrid();
    c1->SetLogx();
    c1->SetLogy();
	TGraph *g1 = new TGraph(size,chunk,steps);
    g1->SetMarkerStyle(21);
    g1->SetTitle("Steps vs. Size");
    g1->GetXaxis()->SetTitle("Chunk Size");
    g1->GetYaxis()->SetTitle("Steps");
    g1->Draw("AL");

   // TCanvas::Update() draws the frame, after which one can change it
   c1->Update();
   c1->GetFrame()->SetFillColor(21);
   c1->GetFrame()->SetBorderSize(12);
   c1->Modified();
}
