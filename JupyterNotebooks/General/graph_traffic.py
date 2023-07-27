import numpy as np
import matplotlib.pyplot as plt

def graph_traffic():
    # Select numerical parameters (time step, grid spacing, etc.).
    method = int(input("Choose a numerical method: 1) FTCS, 2) Lax, 3) Lax-Wendroff : "))
    Ngrid = int(input("Enter number of grid points: "))
    N = Ngrid
    L = 800.0        # System size
    h = L / N        # Grid spacing
    v_max = 25       # Wave speed
    print("Suggested timestep is", h / v_max)
    tau = float(input("Enter time step: "))
    print("Last car starts moving after", (L / 8) / (v_max * tau), "steps")
    nStepvar = int(input("Enter number of steps: "))
    nStep = nStepvar
    coeff = tau / (2.0 * h)           # Coefficient used by all schemes
    coefflw = 2 * coeff * coeff       # Coefficient used by L-W scheme

    # Set initial and boundary conditions.
    rho_max = 1.0                  # Maximum density
    Flow_max = 0.25 * rho_max * v_max  # Maximum Flow
    # Initial condition is a square pulse from x = -L/4 to x = 0
    rho = np.zeros(N)
    rho_start = np.zeros(N)
    print("At init: ",len(rho))
    iBack, iFront = N // 8, N // 4 - 1
    for i in range(N):
        if iBack <= i <= iFront:
            rho[i] = rho_max
        else:
            rho[i] = 0.0
        rho_start[i] = rho[i]
    rho[iFront + 1] = rho_max / 2

    # Use periodic boundary conditions
    ip = np.zeros(N)
    im = np.zeros(N)

    for i in range(1, N - 1):
        ip[i] = i+1  # ip[i] = i+1 with periodic b.c.
        im[i] = i-1  # im[i] = i-1 with periodic b.c.
    ip[0] = 1
    ip[N - 1] = 0
    im[0] = N - 1
    im[N - 1] = N - 2


    print("plus/minus: ",len(im),len(ip))

    # Initialize plotting variables.
    iplot = 1
    tplot = np.zeros(nStep + 1)
    xplot = np.zeros(N)
    rplot = np.zeros((N, nStep + 1))
    tplot[0] = 0.0            # Record initial time
    for i in range(N):
        xplot[i] = (i + 0.5) * h - L / 2  # Record x scale for plot
        rplot[i][0] = rho[i]           # Record the initial state

    # Loop over desired number of steps.
    Flow = np.zeros(N)
    for iStep in range(nStep):
        # Compute the flow = (Density) * (Velocity)
        for i in range(N):
            Flow[i] = rho[i] * (v_max * (1.0 - rho[i] / rho_max))

        rho_new = np.zeros(N)

        print("rho: ",len(rho),iStep)

        if method == 1:      # FTCS method
            for i in range(N):
                rho_new[i] = rho[i] - coeff * (Flow[int(ip[i])] - Flow[int(im[i])])
        elif method == 2:    # Lax method
            for i in range(N):
                print(i,ip[i],im[i])
                rho_new[i] = 0.5 * (rho[int(ip[i])] + rho[int(im[i])]) - coeff * (Flow[int(ip[i])] - Flow[int(im[i])])
        else:                # Lax-Wendroff method
            for i in range(N):
                cp = v_max * (1 - (rho[int(ip[i])] + rho[i]) / rho_max)
                cm = v_max * (1 - (rho[i] + rho[int(im[i])]) / rho_max)
                rho_new[i] = rho[i] - coeff * (Flow[int(ip[i])] - Flow[int(im[i])]) + coefflw * (
                        cp * (Flow[int(ip[i])] - Flow[i]) - cm * (Flow[i] - Flow[int(im[i])]))

        for i in range(N):
            rho[i] = rho_new[i]

        tplot[iplot] = tau * (iStep + 1)
        print(len(rho))
        for i in range(N):
            print(i,rho[i])
            rplot[i][iplot] = rho[i]   # Record a(i) for plotting
        iplot += 1

    nplots = iplot        # Actual number of plots recorded
    npoints = N

    # Plot the results
    plt.figure()
    plt.plot(xplot, rho_start, label="Initial Pulse", color="red")
    plt.plot(xplot, rho, label="Final Pulse", color="blue")
    plt.xlabel("Position")
    plt.ylabel("Density")
    plt.title("Initial and Final Pulses")
    plt.legend()
    plt.grid()

    plt.figure()
    X, T = np.meshgrid(xplot, tplot[:nplots])
    plt.pcolormesh(X, T, rplot.T, shading='auto')
    plt.colorbar()
    plt.xlabel("Position")
    plt.ylabel("Time")
    plt.title("Time Evolution of Pulse")
    plt.grid()

    plt.show()

# Call the function to run the simulation
graph_traffic()
