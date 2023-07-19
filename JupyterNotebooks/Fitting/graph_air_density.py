
import matplotlib.pyplot as plt
import numpy as np
from scipy.optimize import curve_fit

def fitfunction(x,a,b,c):
    return a*np.exp(b*np.array(x)+c*np.power(np.array(x),1.5))

altitude = []
temp = []
gravity = []
pressure = []
density = []
viscosity = []

use_errors = True

with open('density.txt') as f:
    for line in f:
        data = line.split()
        altitude.append(float(data[0]))
        temp.append(float(data[1]))
        gravity.append(float(data[2]))
        pressure.append(float(data[3]))
        density.append(float(data[4]))
        viscosity.append(float(data[5]))

if use_errors == True:
    # create a list to hold the uncertainty in the density  
    density_uncertainty = [0.01,0.01,0.01,0.001,0.001,0.001,0.001,0.001,0.001,0.001,0.001,0.001,0.0001,0.0001,0.0001,0.00001,0.00001,0.000001,0.0000001,0.0000001]
else:
    density_uncertainty = [0.0]*len(density)

density_uncertainty = np.array(density_uncertainty)

fig = plt.figure()

ax1 = fig.add_subplot(111)

ax1.set_title("Density")    
ax1.set_xlabel('Altitude (m)')
ax1.set_ylabel('Density (kg/m^3)')
ax1.grid(True)

# make the y scale logaritmic
ax1.set_yscale("log")

# plot the data
ax1.errorbar(altitude,density,yerr=density_uncertainty,fmt='o',label='Data')

init_vals = [10.0,-0.0001,-0.0000001]
if use_errors == False:
    popt, pcov = curve_fit(fitfunction, altitude, density, p0=init_vals)
else:
    popt, pcov = curve_fit(fitfunction, altitude, density, sigma=density_uncertainty, absolute_sigma=True, p0=init_vals)

print (popt)

ax1.plot(altitude, fitfunction(altitude, *popt), 'r-', label = 'fit: Amplitude = %.3E, \nLinear = %.3E, \nQuadratic = %.3E' % tuple(popt))

leg = ax1.legend()
plt.show()

# add a printout of the figure to a pdf file
fig.savefig('density.pdf')

# add a printout of the figure to a png file    
fig.savefig('density.png')

