#!/usr/bin/env python
# coding: utf-8

# In[1]:


import math

l1 = input('Enter a length in feet (greater than zero): ')

while True:
    try:
        l = float(l1)
        if l<0:
            print ("The length must be greater than zero!!")
            break
    
        inches = l*12.0
        yards = l/3.0
        miles = l/5280.0

        print ("A length of %.3f feet is equivalent to %.3f inches, %.3f yards, and %.3f miles." % (l,inches,yards,miles))
        
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




