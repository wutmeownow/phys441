#!/usr/bin/python

import numpy as np
import matplotlib
matplotlib.use('TkAgg')
import matplotlib.pyplot as plt
from scipy.optimize import curve_fit
import random

def generating_function(x):
    a=1.80
    b=-4.05
    c=0.40
    d=1.0000
    xp = np.array(x)
    return a+b*xp+c*xp*xp+d*xp*xp*xp

def fitfunction(x,a,b,c,d):
    xp = np.array(x)
    return a+b*xp+c*xp*xp+d*xp*xp*xp

x = []
y = []
walk = [-1,1,-.5,.5,0,-1,1,-.5,.5,0,-1,1,-.5,.5,0]

npoints = 15

for i in range (0,npoints):
    x.append(float(-4.0+8.0*i/npoints))
    y.append(float(generating_function(x[i]))+float(0.5*walk[i]))

fig = plt.figure()

ax1 = fig.add_subplot(111)

ax1.set_title("Cubic Fitting - No Errors")    
ax1.set_xlabel('X')
ax1.set_ylabel('Y')
ax1.set_yscale("linear",nonposy='clip')
ax1.grid(True)

ax1.scatter(x,y)

init_vals = [1.0,-1.0,1.0,1.0]
popt, pcov = curve_fit(fitfunction, x, y, p0=init_vals)

print (popt)

print (pcov)

yfit = []
chi2=0
for i in range (0,npoints):
    yfit.append(fitfunction(x[i],*popt))
    chi2 += (y[i]-yfit[i])*(y[i]-yfit[i])

print ("Chi^2 / dof = %.3E / %d" % (chi2,npoints-len(init_vals)))

param = []
rho = []
param.append(float(chi2))
param.append(npoints-len(init_vals))
for ii in range(0,len(init_vals)):
    param.append(float(popt[ii]))
    param.append(float(np.sqrt(pcov[ii][ii])))
    print("Fit Parameter %d: %.3E +/- %.3E" % (ii,popt[ii],np.sqrt(pcov[ii][ii])))
    for jj in range(0,len(init_vals)):
        rho.append(float(pcov[ii][jj])/float(pcov[ii][ii]*pcov[jj][jj]))
        if jj > ii:
            print("%d %d %.3E" % (ii,jj,rho[ii*len(init_vals)+jj]))

ax1.plot(x, fitfunction(x, *popt), 'r-', label = 'Chi^2/dof = %.3E / %d\np0 = %.3E +/- %.3E\np1 = %.3E +/- %.3E\np2 = %.3E +/- %.3E\np3 = %.3E +/- %.3E' % tuple(param))

leg = ax1.legend()
plt.show()
