#!/usr/bin/env python

import math

s1 = input('Enter the first side of the triangle: ')
s2 = input('Enter the second side of the triangle: ')
s3 = input('Enter the third side of the triangle: ')

while True:
    try:
        s1r = float(s1)
        s2r = float(s2)
        s3r = float(s3)
        if s1r<=0 or s2r<=0 or s3r<=0:
            print ("The side lengths must be greater than zero!!")
            break
        
        s = (s1r+s2r+s3r)/2.0
        term = 
        area = math.sqrt(s*(s-s1r)*(s-s2r)*(s-s3r))
        print ("The area of a triangle with side lengths, %.3f, %.3f, and %.3f is %.3f." % (s1r,s2r,s3r,area))
        
        break
    except ValueError:
        print("The values must be real numbers!!")
        break
    
print('Exiting ... bye!')

