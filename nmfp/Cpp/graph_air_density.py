#!/usr/bin/python

import numpy as np
import matplotlib.pyplot as plt
from scipy.optimize import curve_fit

def fitfunction(x,a,b,c):
    return a*np.exp(b*np.array(x)+c*np.power(np.array(x),1.5))

altitude = []
temp = []
gravity = []
pressure = []
density = []
viscosity = []

with open('density.txt') as f:
    for line in f:
        data = line.split()
        altitude.append(float(data[0]))
        temp.append(float(data[1]))
        gravity.append(float(data[2]))
        pressure.append(float(data[3]))
        density.append(float(data[4]))
        viscosity.append(float(data[5]))

fig = plt.figure()

ax1 = fig.add_subplot(111)

ax1.set_title("Density")    
ax1.set_xlabel('Altitude (m)')
ax1.set_ylabel('Density (kg/m^3)')
ax1.set_yscale("log",nonposy='clip')
ax1.grid(True)

ax1.scatter(altitude,density)

init_vals = [10.0,-0.0001,-0.0000001]
popt, pcov = curve_fit(fitfunction, altitude, density, p0=init_vals)

print (popt)

ax1.plot(altitude, fitfunction(altitude, *popt), 'r-', label = 'fit: Amplitude = %.3E, Linear = %.3E, Quadratic = %.3E' % tuple(popt))

leg = ax1.legend()
plt.show()
