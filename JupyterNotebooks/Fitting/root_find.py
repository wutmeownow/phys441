#!/usr/bin/python
# root_find - Program to find the roots of a polynomial of degree
# three using Newton's Method.
#
# Author:  Edward J. Brash
#

import numpy as np

pi = np.pi

a0 = -pi*pi*pi
a1 = 3*pi*pi
a2 = -3*pi
a3 = 1.0

epsilon = 1.0E-8
diff = 1.0E12

x0 = float(raw_input('Enter the starting value:'))

while (diff > epsilon):
	  f = a0 + a1*x0 + a2*x0*x0 + a3*x0*x0*x0
 	  fp = a1 + 2.0*a2*x0 + 3.0*a3*x0*x0 
  	  xnew = x0 - f/fp 
  	  diff = xnew - x0
	  print 'New x-value: ',xnew,' Diff: ',diff 
	  x0 = xnew
	  diff = abs(diff)	  

print 'Root = ',xnew
