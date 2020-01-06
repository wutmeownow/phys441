/*******************************
 *
 * Application: IncrementAgeNonClass 
 * Purpose: Demonstrate the need for understanding local and global variables, and
 *          the difference between pass by reference vs. pass by value
 * Note: When we learn about objects and classes, this will come up again, and there
 *       is a really cool way to make our life easier!!!
 *
 * Author:  E.J. Brash
 * Date:  January 5, 2020
 *
 *******************************/

public class IncrementAgeNonClass {

    static void PlusAgeUseless(int age) {
        age = age + 1;
    }
    
    static int PlusAge(int age) {
        age = age + 1;
        return age;
    }

    public static void main(String [] args) {

        int age = 25;
        System.out.println("Current age = " + age);

        PlusAgeUseless(age);
        System.out.println("New age = " + age);
        
        age = PlusAge(age);
        System.out.println("New age = " + age);
    
    }

}
