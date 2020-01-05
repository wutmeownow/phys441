/*******************************
 *
 * Application:  Conditional
 *
 * Author:  E.J. Brash
 * Date:  January 3, 2020
 *
 *******************************/

public class Conditional {

    public static void main(String [] args) {
   
        // First, check the number of arguments ... if there is anything
        // other than one argument, we have a problem, otherwise we can
        // continue.
        
        if (args.length != 1) {
            System.out.println("Wrong number of arguments!!!");
        } else {
            // args[*] is an array of Strings, and so we must convert
            // the String value of the time to an integer.  To do this,
            // we use a system-provided parser.
            int time = Integer.parseInt(args[0]);

            if (time < 18) {
                System.out.println("Good morning!");
            } else {
                System.out.println("Good evening!");
            }

            // We could have also used the following short-hand notation
            //String result = (time < 18) ? "Good morning!" : "Good evening!";
            //System.out.println(result);
        }

    }

}
