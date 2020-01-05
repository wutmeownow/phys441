/*******************************
 *
 * Application: Basic Array  
 * Purpose: Demonstrate a few basic array properties
 *
 * Author:  E.J. Brash
 * Date:  January 3, 2020
 *
 *******************************/

public class BasicArray {

    // Arrays in Java (and C++) are similar to lists in Python
    // However, they are strongly typed, and thus any Java array has 
    // a specific type to the elements (e.g. int, double, boolean, String, etc.).
    // All elements of any particular array are of the same type

    public static void main(String [] args) {

        String[] cars = {"Volvo", "BMW", "Ford", "Mazda"};
        int[] myNum = {10, 20, 30, 40};
        
        for (int i =0; i<4; i++){
            System.out.println(cars[i]);
            System.out.println(myNum[i]+"\n");
        }
    
        double[] myDouble = new double[4]; //create the array in memory but don't fill it!
        // Maybe the array will be initialized to zero, or maybe not!  Don't chance it!!
        for (int i =0; i<4; i++){
            System.out.println(myDouble[i]);
        }
        myDouble[0] = 4.5;
        myDouble[1] = 1.5;
        myDouble[2] = 3.5;
        myDouble[3] = 99.5;
        for (int i =0; i<4; i++){
            System.out.println(myDouble[i]);
        }

        // Multi-dimensional array
        // num.length will give the number of rows
        // num[i].length will give the number of columns in row i
        //
        int[][] num={ {1}, {1,2}, {1,2,3,4,5}, {1,2}, {1,2,3} };
        for (int i=0; i<(num.length); i++ ) {
            System.out.println("\n");
            for (int j=0;j<num[i].length;j++)
                System.out.println(num[i][j]);
            }
        }

}
