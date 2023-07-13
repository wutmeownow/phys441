import numpy as np
class sortList:

    def __init__(self,ncell_in,npart_in):
        self.ncell = ncell_in
        self.npart = npart_in
        self.cell_n = np.zeros(ncell_in,dtype = int)
        self.index = np.empty(ncell_in,dtype = int)
        self.Xref = np.empty(npart_in,dtype = int)

