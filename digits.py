digits = [str(i) for i in range(10)] + [chr(ord('a') + i) for i in range(26)]  # List of digits: 0-9, a-f
num_digits = int(input("Enter the number of digits: "))  # User input for the number of digits
possible_numbers = []  # List to store the possible numbers

def generate_numbers(digit_idx, number):
    if digit_idx == num_digits:
        possible_numbers.append(number)
        return
    for digit in digits:
        if digit_idx == 0 and digit == '0':
            continue  # Exclude leading zero
        generate_numbers(digit_idx + 1, number + digit)

generate_numbers(0, '')

# Print the list of possible numbers
#for number in possible_numbers:
#    print(number)

print ("length           = ", len(possible_numbers))
print ("predicted length = ",35*36**(num_digits-1))


