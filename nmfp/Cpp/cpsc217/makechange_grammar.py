#!/usr/bin/env python
# coding: utf-8

# We begin by importing the math library, which we typically need in a lot of programs.

# In[7]:


import math


# Next, we define two lists - coins, which will hold the value of each coin, and ncoins, which will hold the number of each coin type needed to make the correct change.

# In[8]:


coins = [200,100,25,10,5,1]
ncoins = [0,0,0,0,0,0]

coin_names_singular = ['toonie','loonie','quarter','dime','nickel','penny']
coin_names_plural = ['toonies','loonies','quarters','dimes','nickels','pennies']
coin_names = []

ntype = 6

print("Starting ...")


# Get the number of cents to make change for, from the user.

# In[9]:


money = input("Enter the number of cents of change: ")


# 1.  We will use a try/except trap to make sure that the user enters an integer number of cents.
# 
# 2.  The algorithm is that we will start with the largest coin value (toonie), and subtract that from the total over and over until we get a negative number, incrementing the number of that type of coin each time.  At the point that we have gone too far, we will move on to the next lower value coin tyoe, and add back in the amount that we mistakenly subtracted. 

# In[10]:


while True:
    try:
        value = int(money)
        value_save = value
        
        index = 0
        while value > 0:
            value = value - coins[index]
            if value >=0:
                ncoins[index]=ncoins[index]+1
            else:
                value = value + coins[index]
                index = index + 1
                
        for i in range(ntype):
            if ncoins[i]==1:
                coin_names.append(coin_names_singular[i])
            else:
                coin_names.append(coin_names_plural[i])
        
        print("For %d cents, the change should be %d %s, %d %s, %d %s, %d %s, %d %s, and %d %s." % (value_save,ncoins[0],coin_names[0],ncoins[1],coin_names[1],ncoins[2],coin_names[2],ncoins[3],coin_names[3],ncoins[4],coin_names[4],ncoins[5],coin_names[5]))
        break
        
    except ValueError:
        print ("You nee to enter an integer number of cents!  Exiting ... bye!")
        break
        
print ("Finished!")


# In[ ]:





# In[ ]:





# In[ ]:





# In[ ]:





# In[ ]:





# In[ ]:





# In[ ]:




