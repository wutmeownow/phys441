#!/usr/bin/env python
# coding: utf-8

# In[1]:


from math import *
from SimpleGraphics import *


# In[2]:


# Set constants
xcs = 0
ycs = 0
xce = 800
yce = 600
dx = 30
dy = 30
ticksize = 4
label_offset = 12
step = 1

# Determine origin position
ox = (xce-xcs)/2
oy = (yce-ycs)/2

# Determine minimum and maximum x- and y-axis limits
xmin = -int(ox/dx)
xmax = -xmin+1
ymin = -int(oy/dy)
ymax = -ymin+1

# Change the background white
setOutline("white")
background("white")


# In[3]:


# Draw the Axes

# Draw lines for axes
setOutline("black")
line(xcs,oy,xce,oy)
line(ox,ycs,ox,yce)

# Draw x-tick marks and x-labels
for i in range(xmin,xmax):
    xval = ox+i*dx
    ystart = oy-ticksize
    yend = oy+ticksize
    line(xval,ystart,xval,yend)
    xlabel = str(i)
    ytxt = oy+label_offset
    if i!=0:
        text(xval,ytxt,xlabel)
        
# Draw y-tick marks and y-labels
for i in range(ymin,ymax):
    xstart = ox-ticksize
    xend = ox+ticksize
    yval = oy+i*dy
    line(xstart,yval,xend,yval)
    ylabel = str(i)
    xtxt = ox+label_offset
    if i!=0:
        text(xtxt,yval,ylabel)


# In[4]:


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
    
    # If a blank line was NOT entered, plot the curve, as well as local maximum and minimum points
    if (looping):
        for xpixel in range(xcs,xce,step):
            x = (xpixel-ox)/dx
            xstart = x*dx+ox
            y = eval(expression)
            ystart = -y*dy+oy
            x = (xpixel+step-ox)/dx
            xend = x*dx+ox
            y = eval(expression)
            yend = -y*dy+oy
            line(xstart,ystart,xend,yend)
            
            if (xpixel > xcs):
                if (yend>ystart):
                    compare = True
                else:
                    compare = False
                if (compare != previous_step_increasing):
                    #print ("max/min at x = ",xstart,ystart)
                    if (compare == True):
                            setFill("purple")
                            setOutline("purple")
                    else:
                            setFill("orange")
                            setOutline("orange")
                    ellipse(xstart-ticksize,ystart-ticksize,2*ticksize,2*ticksize)
                    setFill(col)
                    setOutline(col)
              
            if (yend>ystart):
                previous_step_increasing = True
            else:
                previous_step_increasing = False
    
    # Increment the number of plotted curves
    count = count + 1

# Close the graphics window
close()
    


# In[ ]:





# In[ ]:





# In[ ]:




