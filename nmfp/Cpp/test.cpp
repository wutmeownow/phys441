//
//  main.cpp
//  KaterTest
//
//  Created by Edward Brash on 11/3/14.
//  Copyright (c) 2014 Edward Brash. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <math.h>

using namespace std;

int main(int argc, const char * argv[]) {
    
    double x, M, m, Mbar, l1, h1, h2, D, L, rhs, lhs, Icm;
    double l2[1000],t1[1000],t2[1000];
    double g=9.810;
    double Pi=3.14159265;
    M=1.35928;
    m=0.72705;
    Mbar=2.90;
    D=0.9990;
    L=1.523;
    
    l1=D/2.0+0.0135+0.047523;
    
    double diff=1.0e99;
    double olddiff=1.0e99;
    int index=0;
    
    for(int i=0; i<1000; i++){
        l2[i]=0.500+(i/1000.0)*0.250;
        x=(M*l1-m*l2[i])/(M+m+Mbar);
        h2=D/2.0+x;
        h1=D/2.0-x;
        rhs=h1*h2;
        Icm=1.0/12.0*Mbar*L*L+Mbar*x*x+M*(l1-x)*(l1-x)+m*(l2[i]+x)*(l2[i]+x);
        lhs=Icm/(M+m+Mbar);
        diff = rhs-lhs;
        if (fabs(diff)<olddiff){olddiff=diff;index=i;}
        t1[i]=2*Pi*sqrt((h1*h1+lhs)/(g*h1));
        t2[i]=2*Pi*sqrt((h2*h2+lhs)/(g*h2));
        cout << l2[i] << " " << t1[i] << " " << t2[i] << endl;
        //cout << "i = " << i << " l2 = " << l2[i] << " rhs = " << rhs << " lhs = " << lhs << endl;
    }
    
    
    cout << "L2 position = " << l2[index] << " L1 position = " << l1 << endl;
    cout << "Predicted period T = " << t1[index]<< endl;

    return 0;
}
