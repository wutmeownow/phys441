#!/usr/bin/env python
# coding: utf-8

# In[1]:


from array import array
import math
import numpy as np


# In[2]:


def generator_function(x,par,ichoice):
    sum = 0.0
    for i in range(len(par)):
        sum = sum + par[i]*math.pow(x,i)
    return sum


# In[3]:


def fitfunction(x,*paramlist):
    xp = np.array(x)
    print (xp,x)
    print (len(paramlist))
    print (paramlist)
    sum = 0
    for i in range(0,len(paramlist)):
        print (i,paramlist[i],sum)
        sum = sum + paramlist[i]*math.pow(xp,i)
    return sum


# In[4]:


ichoice = 6


# In[5]:


if ichoice == 1:
    m = 1
    n = 15
    par = array('d')
    par.append(1.80)
    par.append(4.05)
    jitter = array('d')
    jitter = [-2,2,-1,1,0,-2,2,-1,1,0,-2,2,-1,1,0]
    sigma = array('d')
    sigma = [7,6,5,4,3,2,1,.5,1,2,3,4,5,6,7]
    Title = "Linear Fit"
    xlow = -4.0
    xhigh = 4.0
elif ichoice == 2:
    m = 1
    n = 10
    par = array('d')
    par.append(6.81)
    par.append(0.656)
    jitter = array('d')
    jitter = [.3,.2,-.5,-.2,.2,.6,-.4,-1.5,.7,.5]
    sigma = array('d')
    sigma = [0.51,0.51,0.51,0.51,0.51,0.51,0.51,0.51,0.51,0.51]
    Title = "Linear Fit"
    xlow = 41.0
    xhigh = 50.0
elif ichoice == 3:
    m = 1
    n = 15
    par = array('d')
    par.append(1.80)
    par.append(4.05)
    jitter = array('d')
    jitter = [-2,2,-1,1,0,-2,2,-1,1,0,-2,2,-1,1,0] 
    sigma = array('d')
    sigma = [.7,6,5,4,3,2,1,.5,1,2,3,4,5,6,.7]
    Title = "Linear Fit"
    xlow = -4.0
    xhigh = 4.0
elif ichoice == 4:
    m = 1
    n = 15
    par = array('d')
    par.append(1.80)
    par.append(4.05)
    jitter = array('d')
    jitter = [-2,2,-1,1,0,-2,2,-1,1,0,-2,2,-1,1,0]
    sigma = array('d') 
    sigma = [1,2,3,4,5,6,7,8,7,6,5,4,3,2,1]
    Title = "Linear Fit"
    xlow = -4.0
    xhigh = 4.0
elif ichoice == 5:
    m = 3
    n = 15
    par = array('d')
    par.append(1.80)
    par.append(4.05)
    par.append(0.00)
    par.append(0.20)
    jitter = array('d')
    jitter = [-2,2,-1,1,0,-2,2,-1,1,0,-2,2,-1,1,0]
    sigma = array('d')
    sigma = [7,6,5,4,3,2,1,.5,1,2,3,4,5,6,7]
    Title = "Cubic Fit"
    xlow = -4.0
    xhigh = 4.0
elif ichoice == 6:
    m = 2
    n = 15
    par = array('d')
    par.append(1.80)
    par.append(4.05)
    par.append(5.10)
    jitter = array('d')
    jitter = [-2,2,-1,1,0,-2,2,-1,1,0,-2,2,-1,1,0]
    sigma = array('d')
    sigma = [1,2,3,4,5,6,7,8,7,6,5,4,3,2,1]
    Title = "Quadratic Fit"
    xlow = -4.0
    xhigh = 4.0
else:
    print("Invalid choice!!!!")


# In[6]:


x = array('d')
y = array('d')
ex = array('d')
ey = array('d')

rootfitstring = "pol"+str(m)


# In[7]:


for i in range(0,n):
    x.append(xlow+(xhigh-xlow)*i/(n-1))
    y.append(generator_function(x[i],par,ichoice)+jitter[i])
    ex.append(0.0)
    ey.append(sigma[i])


# In[8]:


m_params = m + 1
a = np.zeros(shape = (m_params,m_params))
v = np.zeros(shape = (m_params,1))


# In[9]:


for k in range(0,m_params):
    for i in range(0,n):
        v[k][0]=v[k][0]+y[i]*math.pow(x[i],k)/math.pow(ey[i],2)
    #print ("v[%d] = %f" % (k,v[k][0]))
    for j in range(0,m_params):
        for i in range(0,n):
            a[k][j]=a[k][j]+math.pow(x[i],k+j)/math.pow(ey[i],2)
        #print ("a[%d][%d] = %f" %(k,j,a[k][j]))
        
print ("A matrix = ")        
print (a)
print("V matrix = ")
print (v)

ainv = np.linalg.inv(a)
u1 = np.dot(a,ainv)

print ("A_inverse = ")
print (ainv)
print ("Diagonal Check:")
print (u1)
coeff = ainv*np.matrix(v)
print ("Coefficients:")
for k in range(0,m+1):
    print("k = %d, coeff = %f +/- %f" % (k,coeff[k],math.pow(ainv[k][k],0.5)))


# In[10]:


yfit = 0
chi2 = 0
rho = array('d')

for i in range(0,n):
    for j in range(0,m+1):
        yfit = yfit + coeff[j]*math.pow(x[i],j)
    print ("i = %d  y = %f  yfit = %f" % (i,y[i],yfit))
    chi2 = chi2 + math.pow(((yfit-y[i])/ey[i]),2)
    yfit = 0
    
chi2perdof = chi2/(n-m)
print ("chi2/dof = %f / %f" % (chi2,(n-m-1)))

rho = np.zeros(shape = (m_params,m_params))

for k in range(0,m_params):
    for j in range(0,m_params):
        rho[k][j]=rho[k][j]+ainv[k][j]/math.sqrt(ainv[k][k]*ainv[j][j])    
print (rho)


# In[ ]:





# In[11]:


xfiterr = array('d')
yfiterr = array('d')
yfitplus2 = array('d')
yfitminus2 = array('d')

for i in range(0,n):
    xfiterr.append(xlow+(xhigh-xlow)*i/(n-1))
    yerror2 = 0.0
    yval = 0.0
    for k in range(0,m+1):
        for j in range(0,m+1):
            term = rho[k][j]*math.pow(xfiterr[i],k)*math.pow(ainv[k][k],0.5)*(math.pow(xfiterr[i],j)*math.pow(ainv[j][j],0.5))
            #print (k,j,term)
            yerror2 = yerror2 + term
        yval = yval + coeff[k]*math.pow(xfiterr[i],k)
    yfiterr.append(yval)
    yfitplus2.append(yval+math.sqrt(yerror2))
    yfitminus2.append(yval-math.sqrt(yerror2))
    print(i,xfiterr[i],yval,math.sqrt(yerror2),yfitplus2[i],yfitminus2[i])


# In[12]:


#print (n,x,y)

from ROOT import TCanvas, TFile
from ROOT import TGraph, TF1, TGraphErrors
from ROOT import gStyle
gStyle.SetOptFit(1)

c1 = TCanvas( 'c1', 'Error Band Fitting Example', 200, 10, 1400, 1000 )
c1.SetGridx()
c1.SetGridy()
c1.GetFrame().SetFillColor( 21 )
c1.GetFrame().SetBorderMode(-1 )
c1.GetFrame().SetBorderSize( 5 )

gr = TGraphErrors(n,x,y,ex,ey)
grp = TGraph(n,xfiterr,yfitplus2)
grm = TGraph(n,xfiterr,yfitminus2)

pfit1 = TF1("pfit1",rootfitstring)

gr.SetMarkerStyle(21)
gr.SetTitle(Title)
gr.GetXaxis().SetTitle("X")
gr.GetYaxis().SetTitle("Y")
gr.GetXaxis().SetLimits(xlow-1.0,xhigh+6.0) 
#gr.GetHistogram().SetMaximum(5.0)
#gr.GetHistogram().SetMinimum(0.0)
gr.Fit("pfit1","q")
pfit1chi2 = pfit1.GetChisquare()
pfit1ndf = pfit1.GetNDF()
pfit1chi2ndf = pfit1chi2/pfit1ndf
print("Fit 1: %f %f \n" % (pfit1chi2,pfit1ndf))
gr.Draw("AP")
grp.SetLineColor(2)
grm.SetLineColor(2)
grp.Draw("L")
grm.Draw("L")
c1.Draw()

input("press enter to continue")

# In[13]:


import matplotlib.pyplot as plt
from scipy.optimize import curve_fit

fig = plt.figure()
ax1 = fig.add_subplot(111)

ax1.set_title(Title)
ax1.set_xlabel('X')
ax1.set_ylabel('Y')
ax1.set_yscale("linear",nonposy='clip')
ax1.grid(True)

ax1.errorbar(x,y,yerr=sigma,fmt='o')

init_vals = [0.0 for x in range(0,m_params)]
popt, pcov = curve_fit(fitfunction,x,y,p0=init_vals,sigma=sigma,absolute_sigma=True)

xi = linspace(np.min(x),np.max(x),5)
ps = np.random.multivariate_normal(popt,pcov,100)
ysample=np.asarray([fitfunction(xi,*pi) for pi in ps])
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
rhom = []
param.append(float(chi2))
param.append(npoints-len(init_vals))
for ii in range(0,len(init_vals)):
    param.append(float(popt[ii]))
    param.append(float(np.sqrt(pcov[ii][ii])))
    print("Fit Parameter %d: %.3E +/- %.3E" % (ii,popt[ii],np.sqrt(pcov[ii][ii])))
    for jj in range(0,len(init_vals)):
        rhom.append(float(pcov[ii][jj])/pow(float(pcov[ii][ii]*pcov[jj][jj]),0.5))
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


# In[ ]:


index=7
yfitvalue = 0.0
yerrorvalue = 0.0
for k in range(0,m_params):
    yfitvalue = yfitvalue + coeff[k]*math.pow(x[index],k)
    yerrorvalue = yerrorvalue + math.pow(math.pow(x[index],k)*math.pow(ainv[k][k],0.5),2)
yerrorvalue = math.sqrt(yerrorvalue)
print ("P201 Error Calculation = %f +/- %f " % (yfitvalue,yerrorvalue))
print ("Proper Error Calculation = %f +/- %f " % ((yfitplus2[index]+yfitminus2[index])/2.0,(yfitplus2[index]-yfitminus2[index])/2.0))


# In[ ]:





# In[ ]:





# In[ ]:




