#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>
//using namespace std;
void graph();
double toRadians(double deg);
double theta, vi, yi,xi=0, dt ,a=-9.81,t,d,vf,y[100000],x[100000],yr[100000],xr[100000],yt[100000],xt[100000];
//for a baseball 
double mass=.145, R=.037;


void projectile(){
cout<<"Initial angle (0-90): ";
cin>>theta;
theta=toRadians(theta);
cout<<"Initial velocity: ";
cin>>vi;
cout<<"Initial Height: ";
cin>>yi;
cout<<"Time step: ";
cin>>dt;

//dt=.01;theta=45;vi=50;yi=10;

//***FIND W/O FRICTION***\\
double viy = vi*sin(theta);
double vix = vi*cos(theta);

double tc=0;//current time



//ideal
int i=0;
while(true){
	y[i] = yi+viy*tc+.5*a*tc*tc;
	x[i]=vix*tc;
	if(y[i]<0){break;}
	tc+=dt;
	i++;
}



//forward derivative
tc=dt;
int ir=1;
double vy[100000];
vy[0] = viy;yr[0]=yi;
while(true){
	double fxdt = viy*(tc+dt)+.5*a*(tc+dt)*(tc+dt);
	double fx = viy*tc+.5*a*tc*tc;
	vy[ir]=(fxdt-fx)/dt;
	
	yr[ir]=yr[ir-1]+ vy[ir]*dt;

	xr[ir]=vix*tc;
	
//cout<<"vy: "<<vy[ir]<<"     tc: "<<tc<<"   y: "<<yr[ir]<<endl;
	if(yr[ir]<0){break;}
	tc+=dt;
	ir++;
}


//forward derivative with air resistance

//force friction = -.5*Cd*rho*A*v^2
//               = -.5*.35*1.2*(pi)R^2*v^2
//               = -9.03176*10^-4*v^2
//divide by m to get ax due to friction   =.0062288
//ax=.0062288*vx^2         ay=-g-.0062288*vy^2


tc=dt;
int it=1;
double vyt[100000];
double vxt[100000];
vyt[0] = viy;yt[0]=yi;vxt[0]=vix;
double vterm = -1*sqrt((mass*9.81)/(.35*1.2*.00430084));
cout<<vterm<<endl;
while(true){
	double ax = -.0062288*vxt[it-1]*vxt[it-1];
if(vyt[it-1]>=0){
	double ay = a-(.0062288*vyt[it-1]*vyt[it-1]);
	}
if(vyt[it-1]<0){
	double ay = a+(.0062288*vyt[it-1]*vyt[it-1]);
	}	
/*	double fxdt = vix*(tc+dt)+.5*ax*(tc+dt)*(tc+dt);
	double fx = vix*tc+.5*ax*tc*tc;
	vxt[it]=((fxdt-fx)/dt);
	
	double fydt = viy*(tc+dt)+.5*ay*(tc+dt)*(tc+dt);
	double fy = viy*tc+.5*ay*tc*tc;
	vyt[it]=((fydt-fy)/dt);
*/
//ideal velocity values NOT using forward derivative
	vxt[it]=vxt[it-1]+ax*dt;
	vyt[it]=vyt[it-1]+ay*dt;
//	if(vyt[it]<vterm){vyt[it]=vterm;}


	yt[it]=yt[it-1]+vyt[it]*dt;
	xt[it]=xt[it-1]+vxt[it]*dt;
//cout<<"vx:  "<<vxt[it]<<"  vy: "<<vyt[it]<<"  vxf: "<<vxt[it]<<"  vyf: "<<vyt[it]<<endl;
	if(yt[it]<0){break;}
	tc+=dt;
	it++;
}

graph(i,ir,it);
}





void graph(int n,int nr, int nt){
	TCanvas *c1 = new TCanvas("canvas","HW7",40,40,600,600);
	//set options
	gStyle->SetOptStat(0); //turns on(1)/off(0) stat box
	gStyle->SetOptFit(0);  //turns on(1)/off(0) fit box
	c1->ToggleEventStatus(); //turns on event status bar
	g = new TGraph(n,x,y);	
	g->SetMarkerColor(4);
	g->SetMarkerStyle(21);
	h = new TGraph(nr,xr,yr);	
	h->SetMarkerColor(2);
	h->SetMarkerStyle(21);
	j = new TGraph(nt,xt,yt);	
	j->SetMarkerColor(3);
	j->SetMarkerStyle(21);
	
	TMultiGraph *gg = new TMultiGraph();
	gg->Add(g,"lp");
	gg->Add(h,"lp");
	gg->Add(j,"lp");
	gg->Draw("a");
	c1->Update();
}
double toRadians(double deg){
	double rad = deg*(3.14159265/180.0);
	return(rad);
}
