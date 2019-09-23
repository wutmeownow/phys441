#!/usr/bin/env python

# Data Types in Python
# 
#         integer
#         single precision floating point (7 decimal places - 32 bit)
#         double precision floating point (15 decimal places - 64 bit)
#         string
#         boolean
#         
#         int
#         float
#         double
#         str
#         bool
#         
# Python is NOT strongly typed!!!!
# 
# Whenever we get input from the user, we have to check all possibilities!!!!!!


bad_entry = True
debug = False

while bad_entry:

    small = input('Enter less than 1 liter bottle number: ')
    big = input('Enter larger than 1 liter bottle number: ')

    try:
        ismall = int(small)
        ibig = int(big)
        
        if ismall>=0 and ibig>=0:
            if debug:
                print(ismall,ibig)    
            bad_entry = False
        else:
            print ("hey dummy, you can't have negative bottle numbers!!")
        
    except ValueError:
        print ('hey stupid, you need to enter an integer!!!')
        
refund = 0.10*ismall + 0.20*ibig
print ("Refund is $%.2f" % refund)


