/*******************************
 *
 * Application:  CastingExample
 *
 * Author:  E.J. Brash
 * Date:  January 3, 2020
 *
 *******************************/

public class CastingExample {

    public static void main(String [] args) {
   
        // Widening Casting
        
        int a = 9;
        double b = a; // Automatic casting - int to double - this is a widening cast

        System.out.println(a);
        System.out.println(b);

        // Narrowing Casting
        
        double c = 9.78;
        int d = (int) c; // Narrowing casting ... since we are going from double down to the narrower
                         // int, we need to specify the cast explicitly.

        System.out.println(c);
        System.out.println(d);
    }

}
