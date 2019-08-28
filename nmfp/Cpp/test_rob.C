#include <iostream>
#include <TMath.h>

void test_rob() {
   //
   // Author: Edward J. Brash
  
//   gStyle->SetOptFit(kFALSE);	
   
    double m1, m2, b1, b2, dm1, dm2, db1, db2;

    m1=0.354674;
    dm1=0.0265094;
    b1=1.99396;
    db1=0.000775761;

    m2=0.451632;
    dm2=0.0156414;
    b2=1.99113;
    db2=0.000458786;

    double period = (m1*b2-m2*b1)/(m1-m2);

    double t1 = pow(m2,2)*pow((b1-b2),2)*pow(dm1,2)/pow((m1-m2),4);
    double t2 = pow(m1,2)*pow((b1-b2),2)*pow(dm2,2)/pow((m1-m2),4);
    double t3 = pow(m2,2)*pow(db1,2)/pow((m1-m2),2);
    double t4 = pow(m1,2)*pow(db2,2)/pow((m1-m2),2);

    double dperiod = pow((t1+t2+t3+t4),0.5);

    cout << "Period = " << period << " +/- " << dperiod << endl;

}
