public class PersonalInfoSetGet {
    int age;
    String name; // name cannot be overwritten or changed.

    // Create a constructor method (that will be called anytime an object
    // is created.
    //
    public PersonalInfoSetGet(int initial_age, String initial_name) {
        age = initial_age;
        name = initial_name;
    }

    // Create a method to increment age by 1 year
    // This is a public method, as it will be called
    // by first creating an object of type PersonalInfoMethods
    // and then calling the IncrementAge() method on that object.
    //
    public void IncrementAge() {
        age = age + 1;
    }

    // Create set and get methods for the name and age
    //
    public void SetAge(int setage){
        age = setage;
    }

    public int GetAge(){
        return age;
    }

    public void SetName(String setname){
        name = setname;
    }

    public String GetName(){
        return name;
    }
}
