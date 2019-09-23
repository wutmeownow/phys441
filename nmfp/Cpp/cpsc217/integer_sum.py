#!/usr/bin/env python
# coding: utf-8

# In[74]:


import math

n1 = input('Enter a positive integer: ')

while True:
    try:
        n = int(n1)
        if n<=0:
            print ("The integer must be positive!!!")
            break
       
        sum = n*(n+1)/2
        print ("The sum of integers from 1 to %d is %d." % (n,sum))
        
        break
    except ValueError:
        print("The values must be integer!!")
        break
    
print('Exiting ... bye!')


# In[ ]:





# In[ ]:





# In[ ]:





# In[ ]:





# In[ ]:





# In[ ]:




