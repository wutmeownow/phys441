/*******************************
 * This is a comment block
 *
 * Application:  HelloWorld
 * Purpose:  Print "Hello World!" to the standard output
 *
 * Author:  E.J. Brash
 * Date:  January 3, 2020
 *
 *******************************/

public class HelloWorld {

    // This is another way to make a comment, inline. Just begin the 
    // line with two forward slashes.
    //
    // Every Java application must start with a class definition whose name
    // is the same as the name of the file.  This file is HelloWorld.java, and 
    // so the class name must be HelloWorld
    // 
    // The entire class is surrounded by { } braces.
    //
    // We will make the class public (as opposed to private or protected, which
    // we will learn about later.
    //
    // Class definitions generally involve two broad categories:  defining members of
    // the class, and defining methods/functions of the class.
    //
    // The application class that we are definining here will only have a single method - main - 
    // which will get executed when we run the application.

    public static void main(String [] args) {
    
        // The main method will be public (other applications can call it)
        // It will be "static" - we will learn what this means later
        // It will return nothing  when it is called - this is called "void"
        // It can be called with a set of arguments, which will be put into an array/list of
        // String variables called args.
        //
        // From the Java standard library, we call the System.out.println() method/function ...
        // This method takes a string as its argument, and will print that string to the 
        // standard output.
        
        System.out.println("Hello World!");

    } // This curly brace closes the main method.

} // This curly brace closes the HelloWorld class definition.
