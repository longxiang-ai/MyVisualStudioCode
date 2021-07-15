// Create a class with member functions that throw exceptions. Within this class, make a nested class to use as an exception object. It takes a single *char** as its argument; this represents a description string. Create a member function that throws this exception. (State this in the function’s exception specification.) Write a try block that calls this function and a catch clause that handles the exception by printing out its description string.
#include <cstdio>
#include <iostream>
#include <exception>
using namespace std;

class MyError1
{
    string message;

public:
    class MyError2
    {
        string message;
        MyError2(string msg = 0) : message(msg)
        {
            fthrow();
        }
        MyError2()
        {
            fthrow();
        }
        void fthrow()
        {
            throw "something bad happened";
        }
    };
    MyError1()
    {
        try
        {
            MyError2 b;
        }
        catch(string)
        {
            cout << "error" << endl;
        }
        
    }
};