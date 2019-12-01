from SimpleGraphics import *
import math
import sys

# Set screen size and find center x position
width = 800
height = 600
center_x = width/2.0

# Fram will be a rectangle with a header on the top, and then
# a border all around.  The gap between destinations, the width of vertical
# end bars and how much to indent from the frame edge also need to be set
header_width = 50
border_width = 50
gap = 10
bar_width = 20
indent = 100

# calculate the frame width and height
frame_width = width - 2*border_width
frame_height = height - header_width - 2*border_width # = 450

# set a gray background
setOutline("gray")
background("gray")

try:
    # get the filename from the first argument
    nargs = len(sys.argv)-1 # python3 assignment4.py ripken.txt -> 2 args 
    
    if (nargs == 1):
        filename = sys.argv[1]
    elif (nargs == 0):
        filename = input('Enter the filename containing data: ')

    # open the file
    f = open(filename)
    print ("File ",filename," opened successfully!")
    
    print ("Reading data from ",filename)
    
    # read the first two lines from the file to get the title and source label
    temp = f.readline()
    title = temp.rstrip('\n')
    temp = f.readline()
    sourcelabel = temp.rstrip('\n')

    # draw the source label on the left - right justified ("e" = "East")
    setOutline("black")
    fsi = int(16)
    fs = str(fsi)
    setFont("Comic Sans", fs)
    vpos = height/2
    hpos = border_width + indent - 1.5*bar_width
    text(hpos, vpos, sourcelabel, "e")

    # draw the title - default is center justified
    fsi = int(24)
    fs = str(fsi)
    setFont("Comic Sans", fs)
    vpos = header_width
    hpos = width/2
    text(hpos, vpos, title)

    f.close()
    
except:
    # Check error conditions - either number of arguments was incorrect, or file
    # could not be opened

    print ("# args = ",len(sys.argv)-1)
    if (len(sys.argv)-1 >= 1):
        print ("Incorrect number of arguments (should equal 2)!!!")
        print ("Exiting now.")
    else:
        print ("File could not be opened!!!")
        print ("Exiting now.")
