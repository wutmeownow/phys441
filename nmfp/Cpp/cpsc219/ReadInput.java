/*******************************
 *
 * Application: ReadInput 
 * Purpose: Demonstrate Java packages, including the java scanner class
 *
 * Author:  E.J. Brash
 * Date:  January 3, 2020
 *
 *******************************/

import java.util.Scanner;

public class ReadInput {

    public static void main(String [] args) {

    Scanner myReader = new Scanner(System.in);
    System.out.println("Enter username: ");

    String userName = myReader.nextLine();
    System.out.println("Username is: " + userName);
    
    }

}
