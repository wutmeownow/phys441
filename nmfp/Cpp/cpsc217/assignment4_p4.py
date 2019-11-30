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
frame_height = height - header_width - 2*border_width

# set a gray background
setOutline("gray")
background("gray")


# Function to create the dictionary that will be used to
# look up flow rates for each destination category
def create_dict(f): 

    keys = []
    values = []
    
    for line in f:
        temp = line.rstrip('\n') # strip off the linefeed at the end of each line
        mylist = temp.split(',') # create a list assuming comma separators
        keys.append(mylist[0])
        values.append(float(mylist[1]))
    
    mydict = {keys[i]: values[i] for i in range(len(keys))}
    return mydict

# Function to draw the Sankey diagram
def draw_sankey(dictionary):
    
    # Determine the sum of all flow values, as well as the number of destination
    # categories.
    val_sum = 0.0
    length = 0
    for entry in dictionary:
        val_sum = val_sum + dictionary[entry]
        length = length + 1

    # Calculate the number of available pixels in the frame, as well as the
    # pixels/flow calibration factor
    pixel_avail = frame_height - (length-1)*gap
    pixel_per_flow = float(pixel_avail/val_sum)
        
    #print (val_sum,pixel_avail,pixel_per_flow)
    
    # Create a list of destination category sizes (in pixels).  Also
    # calculate the total number of pixels in all categories.
    h_source = int(val_sum * pixel_per_flow)
    h_dest = []
    dest_sum = 0
    for entry in dictionary:
        h_dest.append(int(dictionary[entry]*pixel_per_flow))
        dest_sum = dest_sum + int(dictionary[entry]*pixel_per_flow)
        
    # Check that the source height and the total destination height without
    # gaps are equal (they may not be due to rounding errors).  Reset the source
    # height if there is any difference.
    print (h_source,h_dest,dest_sum)
    if (dest_sum != h_source):
        h_source = dest_sum
        print ("Reset: ",h_source,h_dest,dest_sum)
        
    # Determine the position of the top left corner of the source vertical bar
    # and the top left corner of the first destination bar
    x_source = border_width + indent
    x_dest = width - border_width - indent
    y_source = header_width + border_width + frame_height/2 - h_source/2
    y_dest = header_width + border_width + frame_height/2 - h_source/2 - (length-1)*gap/2
    
    # Draw the source bar
    setFill("black")
    setOutline("black")
    rect(x_source,y_source,bar_width,h_source)
    
    # Draw the destination bars, and place text to the right of each bar
    # halfway down each destination bar
    i = 0
    for entry in dictionary:
        setFill("black")
        setOutline("black")
        rect(x_dest,y_dest, bar_width, h_dest[i])
        y_dest_txt = y_dest + h_dest[i]/2
        nchar = len(entry)
        x_dest_txt = x_dest + 1.5*bar_width
        fsi = int(12)
        fs = str(fsi)
        setFont("Comic Sans", fs)
        print (x_dest_txt, y_dest_txt)
        setFill("black")
        setOutline("black")
        text(x_dest_txt, y_dest_txt, entry, "w") # "w" = "West" = left justified
        # update y position and counter
        y_dest = y_dest + h_dest[i] + gap
        i = i + 1


    # Draw the connecting bars
    #
    # Start by determing coordinates of the left (source) and right (dest) sides
    # of the connecting bars
    x_source = x_source + bar_width
    y_source = header_width + border_width + frame_height/2 - h_source/2
    y_dest = header_width + border_width + frame_height/2 - h_source/2 - (length-1)*gap/2

    # Set the initial y values before looping
    ya = y_source
    yb = y_dest
    
    # Loop to draw the bars
    i=0
    step = 10
    for entry in dictionary:
        xa = x_source # x-value of left side
        xb = x_dest  # x-value of right side
        for x in range(xa,xb+1,step):
            fraction = (x-xa)/(xb-xa) # fraction of the way across from left to right
            y1 = ya+fraction*(yb-ya)  # y-value of top of connecting bar
            y2 = y1 + h_dest[i] # y-value of botttom of connecting bar
            # diagnostic print statement to follow
            if (x == xa):
                print ("loop",x,y1,y2)
            setFill("black")
            setOutline("black")

            # draw a rectangle at this x-value
            rect(x,y1,step,(y2-y1))
        
        # increment counter and y-values
        ya = ya + h_dest[i]
        yb = yb + h_dest[i]+gap
        i = i + 1

    # End of the drawing function

try:
    # get the filename from the first argument
    nargs = len(sys.argv)-1
    
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

    # create the dictionary by calling the create_dict function
    dictionary = create_dict(f)
    print ('dictionary = ',dictionary)
    
    # draw the diagram
    draw_sankey(dictionary)
    
    # draw the source label on the left - right justified ("e" = "East")
    setOutline(0,0,0)
    nchar = len(sourcelabel)
    fsi = int(16)
    fs = str(fsi)
    setFont("Comic Sans", fs)
    vpos = height/2
    hpos = border_width + indent - 1.5*bar_width
    text(hpos, vpos, sourcelabel, "e")

    # draw the title - default is center justified
    nchar = len(title)
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
    if (len(sys.argv)-1 != 1):
        print ("Incorrect number of arguments (should equal 2)!!!")
        print ("Exiting now.")
    else:
        print ("File could not be opened!!!")
        print ("Exiting now.")
