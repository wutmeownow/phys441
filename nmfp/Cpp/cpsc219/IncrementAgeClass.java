/*******************************
 *
 * Application: IncrementAgeClass
 * Purpose: Demonstrate the need for understanding local and global variables, and
 *          the difference between pass by reference vs. pass by value
 *
 * Author:  E.J. Brash
 * Date:  January 5, 2020
 *
 *******************************/

public class IncrementAgeClass {

    int age;
    String name;

    public static void main(String [] args) {

        // Create an object of type IncrementAgeClass called MyAge
        // This object will have two member variables - age and name.
        IncrementAgeClass MyAge = new IncrementAgeClass();

        MyAge.age = 25;
        MyAge.name = "Olivia";

        System.out.println("Name, age = " + MyAge.name + ", " + MyAge.age);
        
        // Create a second object called DadAge
        IncrementAgeClass DadAge = new IncrementAgeClass();

        DadAge.age = 53;
        DadAge.name = "Dad";

        System.out.println("Name, age = " + DadAge.name + ", " + DadAge.age);

    }

}
