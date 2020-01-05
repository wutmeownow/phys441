/*******************************
 *
 * Application: MethodOne 
 * Purpose: Basic method class
 *
 * Author:  E.J. Brash
 * Date:  January 3, 2020
 *
 *******************************/

public class MethodOne {

    // MyMethod is the name of the method/function
    // void means that the method does not have a return value
    // static means that this method will belong to the class MethodOne, and
    // not to an object of the MethodOne class ... much more later on this!!!!
    //
    static void MyMethod(int i) {
        System.out.println("Execution number " + i);
    }

    public static void main(String [] args) {
        for (int i = 0; i<10; i++){
            MyMethod(i+1);
        }
    }

}
