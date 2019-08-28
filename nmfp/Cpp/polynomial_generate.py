#! python
# Program to generate a data file containing x and y values
# of the given polynomial between user-specified limits.
# 
# Author:  Edward J. Brash
# 

from numpy import *

pi = 3.14159265

a0 = -pi*pi*pi
a1 = 3*pi*pi
a2 = -3*pi
a3 = 1.0

poly = open("poly.dat", "w")
deriv = open("deriv.dat", "w")

npoints = int(raw_input("Enter the number of data points:"))
xlow = float(raw_input("Enter the lower range:"))
xhigh = float(raw_input("Enter the upper range:"))

n = npoints-1
x = [0]*(n)
xd = [0]*(n-2)
d = [0]*(n-2)
f = [0]*(n)
step = (xhigh - xlow)/npoints

for i in range(0,n):
    x[i] = xlow + i*step
    f[i] = a0 + a1*x[i] + a2*x[i]*x[i] + a3*x[i]*x[i]*x[i]
    print "X-value: ",x[i]," F(x): ",f[i]
    poly.write("%s %s\n" %(x[i],f[i]))

for i in range(1,n-1):
    d[i-1]=(f[i+1]-f[i-1])/(2.0*step)
    xd[i-1]=x[i]
    print "X-value: ",xd[i-1],"F`(x): ",d[i-1]
    deriv.write("%s %s\n" %(xd[i-1],d[i-1]))

poly.close()
deriv.close()
