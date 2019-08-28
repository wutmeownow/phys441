#include <TRandom.h>

void graph_error() {
   //
   //Modified: Edward J. Brash
   //		
  
   //gStyle->SetOptFit(kFALSE);	
   gStyle->SetOptFit(1);	
   TCanvas *c1 = new TCanvas("c1","Cubic Data",400,400,800,800);
   c1->Divide(2,1);
   c1->SetFillColor(42);
   c1->SetGrid();

	Double_t x,y,dx,dy,z,dz,a,da,b,db;
	x=1.234;
	y=1.003;
	dx=0.001;
	dy=0.002;

	a = x*y;
	b = x - y;
	z=a/b;

	da = fabs(a*(fabs(dx/x)+fabs(dy/y)));
	db = dx + dy;
	dz = fabs(z*(fabs(da/a)+fabs(db/b)));

	cout << "z = " << z << " dz = " << dz << endl;


	dz = fabs(y*y/(x-y)/(x-y)*dx)+fabs(x*x/(x-y)/(x-y)*dy);

	cout << "z = " << z << " dz = " << dz << endl;

	Double_t xmax = x + dx;
	Double_t xmin = x - dx;
	Double_t ymax = y + dy;
	Double_t ymin = y - dy;

	Double_t zmax = xmax*ymax/(xmax-ymax);
	Double_t zmed1 = xmax*ymin/(xmax-ymin);
	Double_t zmed2 = xmin*ymax/(xmin-ymax);
	Double_t zmin = xmin*ymin/(xmin-ymin);

	cout << "zmax = " << zmax << endl;
	cout << "zmed1 = " << zmed1 << endl;
	cout << "zmed2 = " << zmed2 << endl;
	cout << "zmin = " << zmin << endl;

	Double_t zbar = (zmed1 + zmed2)/2.0;
	Double_t dzbar = fabs((zmed1 - zmed2))/2.0;

	cout << "z = " << zbar << " dz = " << dzbar << endl;

	double zbarmin=99999999.;
	double zbarmax=-99999999.;

	TH2D *h1 = new TH2D("h1","xx",500,xmin-dx/2.,xmax+dx/2.,500,ymin-dy/2.,ymax+dy/2.);
	TH2D *h2 = new TH2D("h2","xy",100,xmin*ymin,xmax*ymax,100,xmin-ymax,xmax-ymin);

	int i,j;
	for(i=0;i<100;i++){
		double xnew = xmin+i*(xmax-xmin)/100.;
		for(j=0;j<100;j++){
			double ynew = ymin+j*(ymax-ymin)/100.;
			double znew = xnew*ynew/(xnew-ynew);
			h1->Fill(xnew,ynew,(znew-(zbar-dzbar)));
			h2->Fill(xnew*ynew,xnew-ynew);
			if(znew < zbarmin){zbarmin = znew;}
			if(znew > zbarmax){zbarmax = znew;}
		}
	}

	zbar = (zbarmin + zbarmax)/2.0;
	dzbar = fabs((zbarmin - zbarmax))/2.0;


	cout << "z = " << zbar << " dz = " << dzbar << endl;

	c1->cd(1);
	h1->Draw("LEGO");
	c1->cd(2);
	h2->Draw();


   // TCanvas::Update() draws the frame, after which one can change it
   c1->Update();
   c1->GetFrame()->SetFillColor(21);
   c1->GetFrame()->SetBorderSize(12);
   c1->Modified();
}
