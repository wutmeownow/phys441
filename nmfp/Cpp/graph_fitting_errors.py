from pylab import *
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

def fitfunction(x,*paramlist):
    xp = np.array(x)
    sum = 0
    for i in range(0,len(paramlist)):
        sum = sum + paramlist[i]*pow(xp,i)
    return sum

x = []
y = []
#sigma = [1,1,1,1,1,1,1,1,1,1,1,1,1,1,1]
sigma = [2,2,2,4,4,4,2,2,2,6,6,6,2,2,2]
walk = [-1,1,-.5,.5,0,-1,1,-.5,.5,0,-1,1,-.5,.5,0]

npoints = 15
polynomial_order = 3
m = polynomial_order + 1

for i in range (0,npoints):
    x.append(float(-4.0+8.0*i/npoints))
    y.append(float(generating_function(x[i]))+float(1.5*walk[i]))

v = [[0] for y in range(0,m)]
coeff_matrix = [[0] for y in range(0,m)]

xkj = [[0 for x in range(0,m)] for y in range(0,m)]
rho_by_hand = [[0 for x in range(0,m)] for y in range(0,m)]

for k in range(0,m):
    for i in range(0,npoints):
        v[k][0]=v[k][0]+y[i]*pow(float(x[i]),float(k))/pow(float(sigma[i]),2)
    #print("v[%d][0] = %.5E" % (k,v[k][0]))
    for j in range(0,m):
        for i in range(0,npoints):
            xkj[k][j] = xkj[k][j]+pow(float(x[i]),float(k+j))/pow(float(sigma[i]),2)
        #print("xkj[%d][%d] = %.5E" % (k,j,xkj[k][j]))

xkj_matrix = np.matrix(xkj)
v_matrix = np.matrix(v)
xkj_inverse_matrix = np.linalg.inv(xkj_matrix)
coeff_matrix = np.matmul(xkj_inverse_matrix,v_matrix)
coeff = np.matrix.tolist(coeff_matrix)
xkj_inverse = np.matrix.tolist(xkj_inverse_matrix)

off_diagonal_matrix = np.matmul(xkj_inverse_matrix,xkj_matrix)
off_diagonal = np.matrix.tolist(off_diagonal_matrix)
print ("Off Diagonal Elements")
print (off_diagonal)

error = [0 for x in range(0,m)]
for k in range(0,m):
    error[k] = pow(xkj_inverse[k][k],0.5)
    for j in range(0,m):
        if j>k:
            rho_by_hand[k][j] = xkj_inverse[k][j]/pow(float(xkj_inverse[k][k]*xkj_inverse[j][j]),0.5)
print("Rho_by_hand")
print (rho_by_hand)

print("Coefficients")
print (coeff) #equivalent of popt from curve_fit !!
print ("Errors")
print (error)
print("Covariance Matrix")
print (xkj_inverse) #equivalent of pcov from curve_fit !!

fig = plt.figure()

ax1 = fig.add_subplot(111)

ax1.set_title("Cubic Fitting - with Errors")
ax1.set_xlabel('X')
ax1.set_ylabel('Y')
ax1.set_yscale("linear",nonposy='clip')
ax1.grid(True)

ax1.errorbar(x,y,yerr=sigma,fmt='o')

init_vals = [0 for x in range(0,m)]
popt, pcov = curve_fit(fitfunction, x, y, p0=init_vals, sigma=sigma, absolute_sigma=True)
#popt, pcov = curve_fit(fitfunction, x, y, p0=init_vals)

xi = linspace(np.min(x),np.max(x),100)
ps = np.random.multivariate_normal(popt,pcov,10000)
ysample = np.asarray([fitfunction(xi,*pi) for pi in ps])
lower = percentile(ysample,16.0,axis=0)
upper = percentile(ysample,84.0,axis=0)

print("Coefficients (from curve_fit)")
print (popt)
print("Covariance Matrix (from curve_fit)")
print (pcov)

yfit = []
chi2=0
for i in range (0,npoints):
    yfit.append(fitfunction(x[i],*popt))
    #chi2 += (y[i]-yfit[i])*(y[i]-yfit[i])
    chi2 += (y[i]-yfit[i])*(y[i]-yfit[i])/(sigma[i]*sigma[i])

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
        rho.append(float(pcov[ii][jj])/pow(float(pcov[ii][ii]*pcov[jj][jj]),0.5))
        if jj > ii:
            print("%d %d %.3E" % (ii,jj,rho[ii*len(init_vals)+jj]))

mylabel = "Chi^2/dof = %.3E / %d\n"
for i in range(0,len(init_vals)):
    code = "p" + str(i)
    mylabel = mylabel + code + " = %.3E +/- %.3E\n"

ax1.plot(xi, fitfunction(xi, *popt), 'r--', label = mylabel % tuple(param))
ax1.plot(xi,lower,'b--')
ax1.plot(xi,upper,'b--')

leg = ax1.legend()
plt.show()
