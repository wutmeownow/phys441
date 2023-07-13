import numpy as np
import matplotlib.pyplot as plt

from sortList import sortList
from collider import collider
from sorter import sorter

boltz = 1.3806E-23
mass = 6.63E-26         # argon
diam = 3.66E-10         # effective diameter
T = 273.
density = 1.78          # argon gas at STP in kg/m^3
L = 1.0E-6              # system size = 1 micron^3
npart = int(input('Enter number of simulation particles: '))
eff_num = density/mass*L**3/npart

print('Each particle represents ',eff_num,' atoms.')

np.random.seed(0)

x = np.empty(npart)
for i in range(npart):
    x[i] = np.random.uniform(0.,L)
v_init = np.sqrt(3.0*boltz*T/mass)
v = np.zeros((npart,3))
for i in range(npart):
    v[i,0] = v_init * (1 - 2*np.floor(2.*np.random.random()))

vmag = np.sqrt(v[:,0]**2+v[:,1]**2+v[:,2]**2)
#plt.hist( vmag, bins=20, range=(0,1000) )
#plt.title('Initial speed distributions')
#plt.xlabel('Speed (m/s)')
#plt.ylabel('N')
#plt.show()

# initialize varibles
ncell = 15
tau = 0.2*(L/ncell)/v_init
vrmax = 3*v_init*np.ones(ncell)
selxtra = np.zeros(ncell)

coeff = 0.5*eff_num*np.pi*diam**2*tau/(L**3/ncell)
coltot = 0

sortData =  sortList(ncell,npart)

nstep = int(input('Enter total number of timesteps: '))
for istep in range(nstep):
    
    x = x + v[:,0]*tau
    x = np.remainder(x+L,L)

    sorter(x,L,sortData)

    col = collider(v,vrmax,tau,selxtra,coeff,sortData)
    coltot = coltot + col

vmag = np.sqrt(v[:,0]**2+v[:,1]**2+v[:,2]**2)
plt.hist( vmag, bins=101, range=(0,1000) )
plt.title('Final speed distributions')
plt.xlabel('Speed (m/s)')
plt.ylabel('N')
plt.show()


