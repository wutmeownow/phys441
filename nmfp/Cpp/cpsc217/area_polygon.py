#!/usr/bin/env python

import math

n1 = input('Enter the number of sides of the polygon: ')
s1 = input('Enter the side length: ')

while True:
    try:
        n = int(n1)
        if n<3:
            print ("The number of sides must be greater than two!!")
            break
        s = float(s1)
        if s<0:
            print ("The side length must be greater than zero!!")
            break
       
        area = n*s*s/(4.0*math.tan(math.pi/n))
        print ("The area of a %d-sided regular polygon with side length, %f, is %f." % (n,s,area))
        
        break
    except ValueError:
        print("The values must be numbers!!")
        break
    
print('Exiting ... bye!')



