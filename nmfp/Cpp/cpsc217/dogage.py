#!/usr/bin/env python

n1 = input('Enter your name: ')
a1 = input('Enter your age: ')

while True:
    try:
        n = str(n1)
        age = float(a1)
        if age<=0:
            print ("Your age must be greater than zero!!")
            break
       
        dogage = age*7.0
        print ("Wow, %s, your age is %.2f in dog years!" % (n,dogage))
        
        break
    except ValueError:
        print("Your age must be a number")
        break
    
print('Exiting ... bye!')

