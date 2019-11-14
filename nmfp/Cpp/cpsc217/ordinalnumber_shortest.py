# Olivia Brash 30079931
#
# Define int2ordinal function with user input integer as the parameter
# Return the result
# Result is tuser input with its appropriate suffix as a string for the result
#
#

def int2ordinal (user_integer):
    ending = ['th','st','nd','rd']; return str(user_integer)+ending[int((int((user_integer%100 - user_integer%10)/10))!=1)*(1-int((int(user_integer%10))>3))*(int(user_integer%10))]

# Demonstrate the int2ordinal function by reading a day, month and year and
# displaying the entered values as ordinal numbers as part of a longer message.
def main():
  day = int(input("Enter a day between 1 and 31: "))
  month = int(input("Enter a month between 1 and 12: "))
  year = int(input("Enter a year between 1 and 2100: "))

  print("On the", int2ordinal(day), "day of the", int2ordinal(month), \
        "month of the", int2ordinal(year), "year, something amazing happened!")

# Call the main function
main()
