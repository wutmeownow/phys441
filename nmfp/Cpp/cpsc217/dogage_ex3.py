#!/usr/bin/env python


while True:
    n1 = input('Enter your name: ')
    a1 = input('Enter your age: ')
    
    try:
        n = str(n1)
        age = float(a1)
        if age<0:
            print ("Your age must be greater than zero!!")
            break
        elif age==0:
            print ("All done!")
            break
        elif (age < 2):
            dogage = age*10.5
        else:
            dogage = 21.0 + (age-2)*4.0


        print ("Wow, %s, your age is %.2f in dog years!" % (n,dogage))
        
    except ValueError:
        print("Your age must be a number")
        break
    
print('Exiting ... bye!')

