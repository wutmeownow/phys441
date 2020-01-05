public class AgeChecker {

  // Create a checkAge() method with an integer variable called age
  static void checkAge(int age) {

    // If age is less than 18, print "access denied"
    if (age < 18) {
      System.out.println("Access denied - You are not old enough!");

    // If age is greater than 18, print "access granted"
    } else {
      System.out.println("Access granted - You are old enough!");
    }

  }

  public static void main(String[] args) {
      if (args.length != 1){
          System.out.println("Wrong number of arguments!!!");
      } else {

        int age = Integer.parseInt(args[0]);
         checkAge(age); // Call the checkAge method and pass along the age to be checked.
      }
  }
}
