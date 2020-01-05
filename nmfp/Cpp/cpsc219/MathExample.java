/*******************************
 *
 * Application:  MathExample
 *
 * Author:  E.J. Brash
 * Date:  January 3, 2020
 *
 *******************************/

public class MathExample {

    public static void main(String [] args) {
   
        // Examples of math things
        
        int x = 5;
        int y = 10;

        int z = x + y;
        int zmax = Math.max(x,y);
        int zmin = Math.min(x,y);

        double sinz = Math.sin(x*Math.PI/2.0);
        double sqrtz = Math.sqrt(x);

        System.out.println(x);
        System.out.println(y);
        System.out.println(z);
        System.out.println(zmax);
        System.out.println(zmin);
        System.out.println(sinz);
        System.out.println(sqrtz);
    }

}
