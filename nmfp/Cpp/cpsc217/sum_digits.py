#!/usr/bin/env python
# coding: utf-8

# In[68]:


import math

n1 = input('Enter the number whose digits you wish to sum: ')

while True:
    try:
        n = int(n1)
        if n<0:
            print ("The number must be greater than or equal to zero!!")
            break
            
        digits = []
        
        sum = 0
        ndigits = 0
        while n>0:
            digits.append(int(n%10))
            ndigits = ndigits + 1
            sum = sum + n%10
            n = (n - n%10)/10
            #print (n,sum)
            
        #print (ndigits,digits)
        
        output = ""
        for i in range(ndigits):
            index = ndigits-i-1
            if i<ndigits-1:
                output = output + ("%d + " % digits[index])
            else:
                output = output + ("%d = " % digits[index])
        
        output = output + str(int(sum))
        print (output)
        
        break
    except ValueError:
        print("The number must be an integer!!")
        break
    
print('Exiting ... bye!')


# In[ ]:





# In[ ]:





# In[ ]:





# In[ ]:





# In[ ]:





# In[ ]:




