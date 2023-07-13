#!/usr/local/bin/python

from PIL import Image, ImageFilter
import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D 

im = Image.open('face.png')

width = im.size[0]
height = im.size[1]

print ("Width of image is %d, Height of image is %d" % (width,height))
print (" ")

px = im.load()

# split image into 50 x 50 grid

threshold = 200
nxbins = 100
nybins = 100
xsize = int(width/nxbins)
ysize = int(height/nybins)
x_pixelstart = int((width - xsize*nxbins)/2)
y_pixelstart = int((height - ysize*nybins)/2)

print ("X Grid Size = %d, Y Grid Size = %d" % (xsize,ysize))
print ("X Pixel Start = %d, Y Pixel Start = %d" % (x_pixelstart,y_pixelstart))

xwhite =[0 for x in range(nxbins)]
ywhite =[0 for x in range(nybins)]
whitecount = [[0 for x in range(nybins)] for x in range(nxbins)]

for icount in range(nxbins):
    xwhite[icount]=icount
    xstartpixel=icount*xsize+x_pixelstart
    xendpixel=xstartpixel+xsize
    for jcount in range(nybins):
        ywhite[jcount]=jcount
        ystartpixel=jcount*ysize+y_pixelstart
        yendpixel=ystartpixel+ysize
        for xcount in range(xstartpixel,xendpixel):
            for ycount in range(ystartpixel,yendpixel):
#                print ("XPixel = %d, YPixel = %d, Pixel Value = %s" % (xcount,ycount,px[xcount,ycount]))
                if (px[xcount,ycount][0] > threshold) and (px[xcount,ycount][1] > threshold) and (px[xcount,ycount][2] > threshold):
                    whitecount[icount][jcount] = whitecount[icount][jcount]+1
#        print ("I = %d, J = %d, WhiteCount = %d" % (icount,jcount,whitecount[icount][jcount]))

fig = plt.figure()
ax1 = fig.add_subplot(111,projection='3d')

data_array = np.array(whitecount)
x_data, y_data = np.meshgrid(xwhite,ywhite )

x_data = x_data.flatten()
y_data = y_data.flatten()
z_data = data_array.flatten()
ax1.bar3d( x_data, y_data, np.zeros(len(z_data)),1,1,z_data )

plt.show()
