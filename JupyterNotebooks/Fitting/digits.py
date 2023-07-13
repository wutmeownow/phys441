def longestDigitsPrefix(inputString):

    istart = 0
    iend = 0
    flag = True
    
    for i in range(len(inputString)):
        if inputString[i].isdigit() and flag:
            iend += 1
        else:
            flag = False
    
    return inputString[istart:iend]

def main():

    inputString = "123abc"
    result1 = longestDigitsPrefix(inputString)

    print ("Result 1 = ",result1)

    return

if __name__ == "__main__":
    main()

