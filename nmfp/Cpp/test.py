import numpy as np 
from scipy.optimize import curve_fit

#This is my function from which i need to get optimal coefficients 'a' and 'b'
def func(x, a, b):  
    return a*np.power(x,b*x)

#the arrays of input data                               
x = [1,2,3,4,5]
y =[6,7,8,9,10]

#default (guess) coefficients
p0 = [1, 1] 

popt, pcov = curve_fit(func, x, y, p0)
print popt
