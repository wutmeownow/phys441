/*******************************
 *
 * Application:  Switch
 *
 * Author:  E.J. Brash
 * Date:  January 3, 2020
 *
 *******************************/

public class Switch {

    public static void main(String [] args) {
   
        if (args.length != 1) {
            System.out.println("Wrong number of arguments!!!");
        } else {
            int day = Integer.parseInt(args[0]);
            switch (day) {
                case 1:
                    System.out.println("Monday");
                    break;
                case 2:
                    System.out.println("Tuesday");
                    break;
                case 3:
                    System.out.println("Wednesday");
                    break;
                case 4:
                    System.out.println("Thursday");
                    break;
                case 5:
                    System.out.println("Friday");
                    break;
                case 6:
                    System.out.println("Saturday");
                    break;
                case 7:
                    System.out.println("Sunday");
                    break;
                default:
                    System.out.println("This is not one of the days of the week!");
            }

        }

    }

}
