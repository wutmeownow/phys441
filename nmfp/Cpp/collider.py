import numpy as np
def collider(v,crmax,tau,selxtra,coeff,sD):
    """collider - Function to process collisions in cells
       Inputs
         v          Velocities of the particles
         crmax      Estimated maximum relative speed in a cell
         tau        Time step
         selxtra    Extra selections carried over from last timestep
         coeff      Coefficient in computing number of selected pairs
         sD         Object containing sorting lists
       Outputs
         col        Total number of collisions processed
    """

    ncell = sD.ncell
    col = 0
    vrel = np.empty(3)

    for jcell in range(ncell):

        number = sD.cell_n[jcell]
        if number > 1:

            select = coeff*number*(number-1)*crmax[jcell] + selxtra[jcell]
            nsel = int(select)
            selxtra[jcell] = select - nsel
            crm = crmax[jcell]

            for isel in range(nsel):
                k = int( np.floor( np.random.uniform(0,number) ) )
                kk = int(np.ceil( k + np.random.uniform(0,number-1) ) % number )
                ip1 = sD.Xref[k+sD.index[jcell]]
                ip2 = sD.Xref[kk+sD.index[jcell]]

                cr = np.linalg.norm( v[ip1,:] - v[ip2,:] )
                if cr > crm:
                    crm = cr

                if (cr/crmax[jcell])**2 > np.random.random():
                    col += 1
                    vcm = 0.5*( v[ip1,:] + v[ip2,:] )
                    cos_th = 1. - 2.*np.random.random()
                    sin_th = np.sqrt(1. - cos_th**2)
                    phi = 2*np.random.random()*np.pi
                    vrel[0] = cr*cos_th
                    vrel[1] = cr*sin_th*np.cos(phi)
                    vrel[2] = cr*sin_th*np.sin(phi)
                    v[ip1,:] = vcm + 0.5*vrel
                    v[ip2,:] = vcm - 0.5*vrel

            crmax[jcell] = crm

    return col
