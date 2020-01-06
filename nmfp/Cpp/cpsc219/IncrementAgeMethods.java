/*******************************
 *
 * Application: IncrementAgeMethods
 * Purpose: Demonstrate the need for understanding local and global variables, and
 *          the difference between pass by reference vs. pass by value
 *
 * Author:  E.J. Brash
 * Date:  January 5, 2020
 *
 *******************************/

public class IncrementAgeMethods {

    // Why is main declared as 'public static'?
    //
    // The public keyword is an access specifier, which allows the programmer 
    // to control the visibility of class members. When a class member is preceded 
    // by public, then that member may be accessed by code outside the class 
    // in which it is declared. In this case, main must be declared as public, since 
    // it must be called by code outside of its class when the program is started. 
    //
    // The keyword static allows main to be called without having to instantiate 
    // a particular instance of the class. Without having declared main method static, 
    // your program will successfully compile but won't execute and report error at 
    // run time. This is necessary since main is called by the Java interpreter before 
    // any objects are made.
    public static void main(String [] args) {

        // Create an object of type PersonalInfoMethods called Olivia
        // This object will have two member variables - age and name.
        //
        PersonalInfoMethods Olivia = new PersonalInfoMethods();

        Olivia.age = 25;
        Olivia.name = "Olivia";

        System.out.println("Name, age = " + Olivia.name + ", " + Olivia.age);
        
        // Increment the age
        Olivia.IncrementAge();
        
        System.out.println("Name, age = " + Olivia.name + ", " + Olivia.age);

    }

}
