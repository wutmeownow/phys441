import math
import numpy as np

def gravrk(x, t, param):
    GM = param[0]
    r = math.sqrt(x[0]**2 + x[1]**2)
    deriv = np.zeros(4)
    deriv[0] = x[2]
    deriv[1] = x[3]
    deriv[2] = -GM * x[0] / (r**3)
    deriv[3] = -GM * x[1] / (r**3)
    return deriv

def rk4(x, nX, t, tau, param):
    xtemp = np.zeros(nX+1)
    k1 = np.zeros(nX+1)
    k2 = np.zeros(nX+1)
    k3 = np.zeros(nX+1)
    k4 = np.zeros(nX+1)
    n = len(x)
    h = tau / n
    for i in range(0, n):
        k1[i] = h * gravrk(x, t, param)[i]
    t1 = t + h / 2
    for i in range(0, n):
        xtemp[i] = x[i] + k1[i] / 2
    for i in range(0, n):
        k2[i] = h * gravrk(xtemp, t1, param)[i]
    for i in range(0, n):
        xtemp[i] = x[i] + k2[i] / 2
    for i in range(0, n):
        k3[i] = h * gravrk(xtemp, t1, param)[i]
    t1 = t + h
    for i in range(0, n):
        xtemp[i] = x[i] + k3[i]
    for i in range(0, n):
        k4[i] = h * gravrk(xtemp, t1, param)[i]
    for i in range(0, n):
        x[i] = x[i] + (k1[i] + 2 * (k2[i] + k3[i]) + k4[i]) / 6

def rka(x, nX, t, tau, err, param):
    S = 0.9
    C = 5.0
    SAFETY = 0.9
    EPS = np.finfo(float).eps
    h = tau / nX
    hNext = h
    safe = False
    while not safe:
        h = hNext
        rk4(x, nX, t, h, param)
        xSmall = np.copy(x)
        h = h / 2
        rk4(xSmall, nX, t, h, param)
        rk4(xSmall, nX, t + h, h, param)
        error = 0.0
        for i in range(0, nX):
            scale = err * (abs(x[i]) + abs(xSmall[i])) / 2
            xDiff = xSmall[i] - x[i]
            ratio = abs(xDiff) / (scale + EPS)
            if ratio > error:
                error = ratio
        error /= SAFETY
        if error <= 1.0:
            safe = True
            hNext = h * min(S, max(1.0 / C, SAFETY * error**(-0.25)))
        else:
            hNext = h * min(S, max(1.0 / C, SAFETY * error**(-0.2)))
    t += tau
    return t, h

def fitfunction(t, param):
    # Define the function for fitting here
    return 0

if __name__ == '__main__':
    # Set initial position and velocity of the comet
    r0 = float(input("Enter initial radial distance (AU): "))
    v0 = float(input("Enter initial tangential velocity (AU/yr): "))
    r = [r0, 0]
    v = [0, v0]
    state = r + v
    nState = 4  # Number of elements in state vector

    # Set physical parameters (mass, G*M)
    pi = math.pi
    GM = 4 * pi**2  # Grav. const. * Mass of Sun (au^3/yr^2)
    param = [GM]
    mass = 1.0  # Mass of comet
    adaptErr = 1.e-3  # Error parameter used by adaptive Runge-Kutta
    time = 0

    # Loop over desired number of steps using specified numerical method
    nStep = int(input("Enter number of steps: "))
    tau = float(input("Enter time step (yr): "))
    method = int(input("Choose a numerical method:\n1) Euler\n2) Euler-Cromer\n3) Runge-Kutta\n4) Adaptive R-K: "))

    rplot = np.zeros(nStep+1)
    thplot = np.zeros(nStep+1)
    tplot = np.zeros(nStep+1)
    kinetic = np.zeros(nStep+1)
    potential = np.zeros(nStep+1)

    for iStep in range(1, nStep+1):
        # Record position and energy for plotting
        normR = math.sqrt(r[0]**2 + r[1]**2)
        normV = math.sqrt(v[0]**2 + v[1]**2)
        rplot[iStep] = normR
        thplot[iStep] = math.atan2(r[1], r[0])
        tplot[iStep] = time
        kinetic[iStep] = 0.5 * mass * normV**2
        potential[iStep] = -GM * mass / normR

        # Calculate new position and velocity using desired method
        if method == 1:
            accel = [-GM * r[0] / normR**3, -GM * r[1] / normR**3]
            r[0] += tau * v[0]
            r[1] += tau * v[1]
            v[0] += tau * accel[0]
            v[1] += tau * accel[1]
            time += tau
        elif method == 2:
            accel = [-GM * r[0] / normR**3, -GM * r[1] / normR**3]
            v[0] += tau * accel[0]
            v[1] += tau * accel[1]
            r[0] += tau * v[0]
            r[1] += tau * v[1]
            time += tau
        elif method == 3:
            rk4(state, nState, time, tau, param)
            r = state[:2]
            v = state[2:]
            time += tau
        else:
            rka(state, nState, time, tau, adaptErr, param)
            r = state[:2]
            v = state[2:]
            time += tau

    # Print out the plotting variables: thplot, rplot, potential, kinetic
    with open("rplot.txt", "w") as rplotOut, open("tplot.txt", "w") as tplotOut, \
            open("total.txt", "w") as energyOut, open("potential.txt", "w") as potentialOut, \
            open("kinetic.txt", "w") as kineticOut:
        for i in range(1, nStep+1):
            rplotOut.write(f"{thplot[i]} {rplot[i]}\n")
            tplotOut.write(f"{tplot[i]} {rplot[i]}\n")
            energyOut.write(f"{tplot[i]} {potential[i] + kinetic[i]}\n")
            potentialOut.write(f"{tplot[i]} {potential[i]}\n")
            kineticOut.write(f"{tplot[i]} {kinetic[i]}\n")
