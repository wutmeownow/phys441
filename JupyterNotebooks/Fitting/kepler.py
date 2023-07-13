import numpy as np
import matplotlib.pyplot as plt
import math


def keplerfunction(Einitial,ecc,M):
    Efinal = ecc*math.sin(Einitial) + M
    return Efinal

# Inputs: Perihelion and Aphelion of Halley's Comet
rp = 0.586 # in AU
ra = 35.082 # in AU
# Inputs: Perihelion and Aphelion of Newton's Comet
#rp = 0.00622 # in AU
#ra = 889.0 # in AU
# Number of points and orbits to calculate
npts = 10000
norbits = 1

# Calculate eccentricity, semi-major and semi-minor axes of elliptical orbit
ecc = (ra - rp)/(ra + rp)
a = rp/(1.0-ecc)
b = math.sqrt(a*a*(1 - ecc*ecc))

print("Eccentricity = ",ecc)
print("Semi-major axis = ",a," AU.")
print("Semi-minor axis = ",b," AU.")

# Define arrays to hold (x,y) positions
x = [0 for i in range(0,npts)]
y = [0 for i in range(0,npts)]
M = [0 for i in range(0,npts)]
E = [0 for i in range(0,npts)]

# Calculation of E, x, and y
for i in range(0,npts):
    M[i] = norbits*2.0*math.pi*((i+1)/(npts))

    # Initial "guess" for E depends upon eccentricity
    if (ecc < 0.8):
        E[i] = M[i]
    else:
        E[i] = 2*math.pi

    looping = True
    epsilon = 0.0000001
    icounter = 0
    
    # Solve the problem iteratively, by calculating E repeatedly
    # until convergence is reached.
    while (looping):
        icounter = icounter + 1
        Eval = float(E[i])
        mean = float(M[i])
        keplerfunctionvalue = keplerfunction(Eval,ecc,mean)
        if (abs(Eval-keplerfunctionvalue) < epsilon): looping = False
        E[i] = keplerfunctionvalue
        #print (Eval*180.0/math.pi,icounter)

    # Calculate the (x,y) position
    x[i] = a*(math.cos(E[i])-ecc)
    y[i] = b*math.sin(E[i])
    #print (mean[i]*180.0/math.pi,E[i]*180.0/math.pi,x[i],y[i])

# plot the results
fig = plt.figure(1)
ax1 = fig.add_subplot(111)
ax1.set_title("Elliptical Orbit (Halley's Comet)")
ax1.set_xlabel('X Position (AU)')
ax1.set_ylabel('Y Position (AU)')
ax1.set_yscale("linear",nonposy='clip')
ax1.grid(True)
#ax1.scatter(x, y, c='b')
ax1.plot(x, y)

fig = plt.figure(2)
ax2 = fig.add_subplot(111)
ax2.set_title("Elliptical Orbit (Halley's Comet)")
ax2.set_xlabel('M (radians)')
ax2.set_ylabel('E (radians)')
ax2.set_yscale("linear",nonposy='clip')
ax2.grid(True)
#ax2.scatter(mean, Eval, c='b')
ax2.plot(M, E)

plt.show()
