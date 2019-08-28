def sudoku(grid):


    comp = [1,2,3,4,5,6,7,8,9]

    result = True

    for xs in range(0,8,3):
        for ys in range(0,8,3):
            temp = []
            for i in range(3):
                for j in range(3):
                    temp.append(grid[xs+i][ys+j])
            print (sorted(temp))
            if sorted(temp) != comp:
                result = False

    for i in range(9):
        temp = []
        for j in range(9):
            temp.append(grid[i][j])
        print (sorted(temp))
        if sorted(temp) != comp:
            result = False

    for j in range(9):
        temp = []
        for i in range(9):
            temp.append(grid[i][j])
        print (sorted(temp))
        if sorted(temp) != comp:
            result = False

    return result
 
def main():

    grid = [[1,3,2,5,4,6,9,8,7],[4,6,5,8,7,9,3,2,1],[7,9,8,2,1,3,6,5,4],
            [9,2,1,4,3,5,8,7,6],[3,5,4,7,6,8,2,1,9],[6,8,7,1,9,2,5,4,3],
            [5,7,6,9,8,1,4,3,2],[2,4,3,6,5,7,1,9,8],[8,1,9,3,2,4,7,6,5]]

    print ("Input grid = ",grid)

    result1 = sudoku(grid)

    print ("Result = ",result1)

    return

if __name__ == "__main__":
    main()

