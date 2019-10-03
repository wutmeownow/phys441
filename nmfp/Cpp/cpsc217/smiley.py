from SimpleGraphics import *

#generate input
x_smiley_centre = int(input("Please enter the X coordinate for the smiley face: "))
y_smiley_centre = int(input("Please enter the Y coordinate for the smiley face: "))

#smiley size parameters
width_smiley = 250
height_smiley = 250

#cat ears
setColor("black")
L_right_x = x_smiley_centre-1/4*width_smiley #left ear
L_right_y = y_smiley_centre-height_smiley*.44
L_top_x = x_smiley_centre-width_smiley*.4
L_top_y = y_smiley_centre-height_smiley*1/2
L_left_x = x_smiley_centre-width_smiley*.4
L_left_y = y_smiley_centre-height_smiley*.3
cat_ear_left = polygon(L_right_x, L_right_y, L_top_x, L_top_y, L_left_x, L_left_y)

R_right_x = x_smiley_centre+1/4*width_smiley #right ear
R_right_y = y_smiley_centre-height_smiley*.43
R_top_x = x_smiley_centre+width_smiley*.4
R_top_y = y_smiley_centre-height_smiley*1/2
R_left_x = x_smiley_centre+width_smiley*.4
R_left_y = y_smiley_centre-height_smiley*.3
cat_ear_right = polygon(R_right_x, R_right_y, R_top_x, R_top_y, R_left_x, R_left_y)

#smiley design
setOutline("black")
setFill("yellow")
x_smiley_leftcorner = x_smiley_centre-width_smiley*.5
y_smiley_leftcorner = y_smiley_centre-height_smiley*.5
smiley = ellipse(x_smiley_leftcorner, y_smiley_leftcorner, width_smiley, height_smiley)

#eyes
setFill("black")
eye_left_location_topx = x_smiley_centre-1/6*width_smiley #left eye
eye_left_location_topy = y_smiley_centre-1/4*height_smiley
eye_left_location_bottomx = x_smiley_centre-1/6*width_smiley
eye_left_location_bottomy = y_smiley_centre-1/8*height_smiley
eye_left = line(eye_left_location_topx, eye_left_location_topy, eye_left_location_bottomx, eye_left_location_bottomy)

eye_right_location_topx = x_smiley_centre+1/6*width_smiley #right eye
eye_right_location_topy = y_smiley_centre-1/4*height_smiley
eye_right_location_bottomx = x_smiley_centre+1/6*width_smiley
eye_right_location_bottomy = y_smiley_centre-1/8*height_smiley
eye_right = line(eye_right_location_topx, eye_right_location_topy, eye_right_location_bottomx, eye_right_location_bottomy)

#grin
grin_angle_start = 180
grin_angle_end = 180
grin_size_x = width_smiley/2
grin_size_y = height_smiley/2
grin_left_x = x_smiley_centre-1/4*width_smiley
grin_left_y = y_smiley_centre-1/5*height_smiley
grin = arc(grin_left_x, grin_left_y, grin_size_x, grin_size_y, grin_angle_start, grin_angle_start)

#line(x_smiley_centre, y_smiley_centre, 100, 100) #centre coordinates accuracy test


