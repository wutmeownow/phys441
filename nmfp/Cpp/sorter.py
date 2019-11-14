import numpy as np

def sorter(x,L,sD):
    """sorter - Function to sort particles into cells
       Inputs
       x    Positions of particles
       L    System size
       sD   Object containing sortig lists
    """
    
    #*  Find the cell address for each particle
    npart = sD.npart
    ncell = sD.ncell

    jx = np.empty(npart,dtype=int)
    for ipart in range(npart):
        jx[ipart] = int( x[ipart]*ncell/L )
        jx[ipart] = min(jx[ipart], (ncell-1) )

    #* Count the number of particles in each cell
    sD.cell_n = np.zeros(ncell)
    for ipart in range(npart):
        sD.cell_n[ jx[ipart] ] += 1

    #print(sD.cell_n)

    #* Build index list as cumulative sum of the
    #  number of particles in each cell
    m = 0
    for jcell in range(ncell):
        sD.index[jcell] = m
        m += sD.cell_n[jcell]

    #* Build cross-reference list
    temp = np.zeros(ncell, dtype=int)
    for ipart in range(npart):
        jcell = jx[ipart]
        k = sD.index[jcell] + temp[jcell]
        sD.Xref[k] = ipart
        temp[jcell] += 1
