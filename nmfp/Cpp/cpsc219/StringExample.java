/*******************************
 *
 * Application:  StringExample
 *
 * Author:  E.J. Brash
 * Date:  January 3, 2020
 *
 *******************************/

public class StringExample {

    public static void main(String [] args) {
   
        // Lots of Examples of string things
        
        String txt = "AbCdEfGhIjKlMnOpQrSyUvWxYz";

        int stringlength = txt.length();
        String upper = txt.toUpperCase();
        String lower = txt.toLowerCase();

        int myIndex = txt.indexOf("Gh");

        String newtxt = txt + " Olivia";
        String newtxt2 = txt.concat(" Olivia");

        int theNumber = 42;
        String theString = txt + theNumber;

        String myMessage = "Olivia is a so-called \"Geek\".";
        String myMessage2 = "But it\'s ok!";


        System.out.println(txt);
        System.out.println(stringlength);
        System.out.println(upper);
        System.out.println(lower);
        System.out.println(myIndex);
        System.out.println(newtxt);
        System.out.println(newtxt2);
        System.out.println(theString);
        System.out.println(myMessage);
        System.out.println(myMessage2);
    }

}
