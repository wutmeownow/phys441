import sys
import numpy as np
import matplotlib
matplotlib.use('TkAgg')
import matplotlib.pyplot as plt
import math
import argparse

def get_args():
    '''This function parses and returns arguments passed in'''
    parser = argparse.ArgumentParser()
    parser.add_argument(
        '-a','--a',type=float,help='First Term',required=True)
    parser.add_argument(
        '-r','--r',type=float,help='Multiplier',required=True)
    parser.add_argument(
        '-t','--t',type=int,help='Number of Terms',required=True)
    args = parser.parse_args()
    a = args.a
    r = args.r
    t = args.t
    return a,r,t

a,r,t = get_args()

sum = 0.0
term = a

for i in range(0,t):
    sum = sum + term
    term = term*r

sumtheory = a*(1-math.pow(r,t))/(1-r)

print (sum,sumtheory)

