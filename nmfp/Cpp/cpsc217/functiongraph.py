#!/usr/bin/env python

from math import *
from SimpleGraphics import *

ox = 400
oy = 300
dx = 30
dy = 30

# Change the background white
setOutline("white")
background("white")

# Draw the Axes

# Draw lines for axes
setOutline("black")
line(0,300,800,300)
line(400,0,400,600)

# Draw x-tick marks and x-labels
for i in range(-13,14):
    xval = ox+i*dx
    ystart = oy-4
    yend = oy+4
    line(xval,ystart,xval,yend)
    xlabel = str(i)
    ytxt = oy+12
    if i!=0:
        text(xval,ytxt,xlabel)
        
# Draw y-tick marks and y-labels
for i in range(-10,11):
    xstart = ox-4
    xend = ox+4
    yval = oy+i*dy
    line(xstart,yval,xend,yval)
    ylabel = str(i)
    xtxt = ox+12
    if i!=0:
        text(xtxt,yval,ylabel)

# Create variables to monitor whether blank line has been entered, and the number of curves plotted
looping = True
count = 0

# Loop until a blank line is entered
while (looping):
    expression = input("Enter an arithmetic expression (blank line to quit): ")
    if (expression == ""):
        looping = False

    # Calculate and set the color to use for the curve
    color = count % 3
    if (color == 0):
        col = "red"
    elif (color == 1):
        col = "green"
    elif (color == 2):
        col = "blue"
    setFill(col)
    setOutline(col)
    
    # If a blank line was NOT entered, plot the curve
    if (looping):
        step = 1
        for xpixel in range(0,800,step):
            x = (xpixel-ox)/dx
            xstart = x*dx+ox
            y = eval(expression)
            ystart = -y*dy+oy
            x = (xpixel+step-ox)/dx
            xend = x*dx+ox
            y = eval(expression)
            yend = -y*dy+oy
            line(xstart,ystart,xend,yend)
    
    # Increment the number of plotted curves
    count = count + 1

# Close the graphics window
close()
