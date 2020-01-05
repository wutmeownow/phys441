/*******************************
 *
 * Application:  Loop
 * Purpose: Demonstration of various types of loops in Java
 *
 * Author:  E.J. Brash
 * Date:  January 3, 2020
 *
 *******************************/

public class Loop {

    public static void main(String [] args) {

        System.out.println("Loop 1 ... ");
        int i = 0;
        boolean looping = true;
        while (looping) {
            System.out.println(i);
            i++;
            if (i == 5) looping = false;
        }

        System.out.println("\nLoop 2 ... ");
        i = 0;
        looping = true;
        do {
            System.out.println(i);
            i++;
            if (i == 5) looping = false;
        }
        while (looping);


        System.out.println("\nLoop 3 ... ");
        for (i = 0; i < 10; i = i + 2) {
            System.out.println(i);
        }

        System.out.println("\nLoop 4 ... ");
        String[] cars = {"Volvo", "BMW", "Ford", "Mazda"};
        for (String j : cars) {
            System.out.println(j);
        }


        System.out.println("\nLoop 5 ... ");
        for (String j : cars) {
            if (j == "Ford") break;  // break out of the loop (i.e. stop looping)
            System.out.println(j);
        }

        System.out.println("\nLoop 6 ... ");
        for (String j : cars) {
            if (j == "Ford") continue; // keep looping, but don't execute following code
            System.out.println(j);
        }

        System.out.println("\nLoop 7 ... ");
        i = 0;
        while (i < 10) {
            if (i == 4) {
                i++;
                continue; // increment the loop counter, and keep looping ...
            }
            System.out.println(i);
            i++;
        }

        System.out.println("\nFinished");
    
    }

}
