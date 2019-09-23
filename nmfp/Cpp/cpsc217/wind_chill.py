#!/usr/bin/env python
# coding: utf-8

# In[1]:


import math


# In[2]:


t = input('Enter the temperatue in degrees Celsius (less than 10C): ')
v = input('Enter the windspeed in kph (greater than 4.8 kph): ')


# In[3]:


while True:
    try:
        tt = float(t)
        vv = float(v)
        if vv<4.8:
            print ("Wind speed must be greater than or equal 4.8 kph!!!")
            break
        if tt>10.0:
            print ("Temperature must be less than 10.0 degrees Celsius!!!")
            break
        
        wc = 13.12 + 0.6215*tt - 11.37*math.pow(vv,0.16) + 0.3965*tt*math.pow(vv,0.36)
        wci = int(round(wc))
            
        print("WCI = %d" % wci)
        break
    except ValueError:
        print("The temperature and wind speeed must be real numbers!!!")
        break
    
print('Exiting ... bye!')


# In[ ]:





# In[ ]:




