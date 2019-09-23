#!/usr/bin/env python
# coding: utf-8

# In[7]:


import math

st1 = input('Enter the latitude of the first point in degrees: ')
sg1 = input('Enter the longitude of the first point in degrees: ')
st2 = input('Enter the latitude of the second point in degrees: ')
sg2 = input('Enter the longitude of the second point degrees: ')

while True:
    try:
        t1 = float(st1)*math.pi/180.0
        g1 = float(sg1)*math.pi/180.0
        t2 = float(st2)*math.pi/180.0
        g2 = float(sg2)*math.pi/180.0

        if t1<-math.pi/2.0 or t1>math.pi/2.0:
            print ("Latitude of first point outside of allowed range!!")
            break
        if t2<-math.pi/2.0 or t2>math.pi/2.0:
            print ("Latitude of second point outside of allowed range!!")
            break   
        if g1<-math.pi or g1>math.pi:
            print ("Longitude of first point outside of allowed range!!")
            break
        if g2<-math.pi or g2>math.pi:
            print ("Longitude of second point outside of allowed range!!")
            break
            
        term = math.sin(t1)*math.sin(t2)+math.cos(t1)*math.cos(t2)*math.cos(g1-g2)
        distance = 6371.01*math.acos(term)

        print ("The distance between the points (%.1f,%.1f) and (%.1f,%.1f) is %.1f km." % (float(st1),float(sg1),float(st2),float(sg2),distance))
        
        break
    except ValueError:
        print("The values must be real numbers!!")
        break
    
print('Exiting ... bye!')


# In[ ]:





# In[ ]:





# In[ ]:





# In[ ]:





# In[ ]:





# In[ ]:




