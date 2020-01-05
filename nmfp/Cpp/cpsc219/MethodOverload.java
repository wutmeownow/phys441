/*******************************
 *
 * Application: MethodOverload 
 * Purpose: Demonstrate method overloading
 *
 * Author:  E.J. Brash
 * Date:  January 3, 2020
 *
 *******************************/

public class MethodOverload {

    static int plusMethod(int x, int y) {
        return x + y;
    }

    static double plusMethod(double x, double y) {
        return x + y;
    }
    
    static String plusMethod(String x, String y) {
        return x + y;
    }


    public static void main(String[] args) {
        int myNum1 = plusMethod(8, 5);
        double myNum2 = plusMethod(4.3, 6.26);
        String myString = plusMethod("Olivia ","Brash");
        System.out.println("int: " + myNum1);
        System.out.println("double: " + myNum2);
        System.out.println("String: " + myString);
    }

}
