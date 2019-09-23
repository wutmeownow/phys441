#!/usr/bin/env python

import math



r1 = input('Enter the radius: ')



while True:
    try:
        r = float(r1)
        if r<0:
            print ('The radius must be greater than or equal to zero!')
            break
        
        area = math.pi*math.pow(r,2)
        volume = 4.0/3.0*math.pi*math.pow(r,3)
        
        print("Area = %f" % area)
        print("Volume = %f" % volume)
        break
    except ValueError:
        print("The radius must be a real number!")
        break
    
print('Exiting ... bye!')

