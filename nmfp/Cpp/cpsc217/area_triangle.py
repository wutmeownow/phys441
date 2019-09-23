#!/usr/bin/env python

import math

b1 = input('Enter the base of the triangle: ')
h1 = input('Enter the height of the triangle: ')

while True:
    try:
        b = float(b1)
        if b<=0:
            print ("The base must be greater than zero!!")
            break
        h = float(h1)
        if h<=0:
            print ("The height must be greater than zero!!")
            break
       
        area = 0.5*b*h
        print ("The area of a triangle withe base, %f, and height, %f, is %f." % (b,h,area))
        
        break
    except ValueError:
        print("The values must be real numbers!!")
        break
    
print('Exiting ... bye!')

