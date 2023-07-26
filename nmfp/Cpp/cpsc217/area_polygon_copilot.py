# import libraries
import math

# get the number of sides of the polygon from the user
n1 = input('Enter the number of sides of the polygon: ')
# convert the number of sides to an integer
n = int(n1)

# get the side length from the user
s1 = input('Enter the side length: ')

# convert the side length to a float
s = float(s1)

# check that the number of sides is greater than two
if n<3:
    print ("The number of sides must be greater than two!!")
    exit()

# check that the side length is greater than zero
if s<0:
    print ("The side length must be greater than zero!!")
    exit()

# compute the area of the polygon
area = n*s*s/(4.0*math.tan(math.pi/n))

# print the area of the polygon
print ("The area of a %d-sided regular polygon with side length, %f, is %f." % (n,s,area))

# print a message to the user
print('Exiting ... bye!')