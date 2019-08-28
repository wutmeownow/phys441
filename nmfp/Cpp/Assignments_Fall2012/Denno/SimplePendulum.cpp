Double_t pi=3.14159265358979323846;      //Euler Theta:Verlet Theta:Time  **Change number for amount of desired steps**
Double_t ET[100]; Double_t VT[100]; Double_t time[100]; Double_t ts=40; Double_t dt=.5;
//theta vs time plot
Int_t Euler(Double_t theta){
    Double_t xn=theta;
    Double_t w0sq=1;
    Double_t vn=0;
    Double_t vnp1,xnp1;
    for(int i=0; i<ts; i++){
        vnp1=vn-w0sq*sin(xn)*dt;
        xnp1=xn+vn*dt;
        ET[i]=xn;
        xn=xnp1;
        vn=vnp1;
    }
return 0;
}

Int_t Verlet(Double_t theta){
    Double_t x=theta;
    Double_t xn;
    Double_t a=-sin(theta);
    Double_t xold=theta+a*dt*dt;
    for(int i=0; i<ts; i++){
        xn=2*x-xold-dt*dt*sin(x);
        xold=x;
        VT[i]=x;
        x=xn;
    }
}

void Pendulum(){
    Double_t theta0; cout<<"Enter Initial Theta: "; cin>>theta0;
    theta0*=(pi/180);
    cout<<theta0<<"\n";
    for(int i=0; i<ts; i++){time[i]=dt*i;}
    Euler(theta0); Verlet(theta0);

    TCanvas *c1=new TCanvas("c1","Euler",200,10,700,500);
    c1->SetFillColor(42);
    c1->SetGrid();

    gr=new TGraph(ts,time,ET);
    gr->SetTitle("Euler");
    gr->SetLineWidth(2);
    gr->Draw("ACP");

    c1->Update();
    c1->GetFrame()->SetFillColor(21);
    c1->GetFrame()->SetBorderSize(12);
    c1->Modified();

    TCanvas *c2=new TCanvas("c2","Verlet",200,10,700,500);
    c2->SetFillColor(42);
    c2->SetGrid();

    gr1=new TGraph(ts,time,VT);
    gr1->SetTitle("Verlet");
    gr1->Draw("ACP");
    gr1->SetLineWidth(2);

    c2->Update();
    c2->GetFrame()->SetFillColor(21);
    c2->GetFrame()->SetBorderSize(12);
    c2->Modified();

}

