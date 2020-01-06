public class PersonalInfo {
    private int age;
    private String name; // name and age are defined as private ... they cannot
                        // be accessed directly, but rather only through Set and Get
                        // methods!!!!  This is called "encapsulation".

    // Create a constructor method (that will be called anytime an object
    // is created.
    //
    public PersonalInfo(int initial_age, String initial_name) {
        this.SetAge(initial_age);
        this.SetName(initial_name); // the keyword 'this' means the current object
    }

    // Create a method to increment age by 1 year
    // This is a public method, as it will be called
    // by first creating an object of type PersonalInfoMethods
    // and then calling the IncrementAge() method on that object.
    //
    public void IncrementAge() {
        this.SetAge(this.GetAge()+1);
    }

    // Create set and get methods for the name and age
    //
    public void SetAge(int setage){
        this.age = setage;
    }

    public int GetAge(){
        return age;
    }

    public void SetName(String setname){
        this.name = setname;
    }

    public String GetName(){
        return name;
    }
}
