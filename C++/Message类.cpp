#include <iostream>
#include <string>

using namespace std;
// Create a Message class with a constructor that takes a single string with a default value. Create a private member string, and in the constructor simply assign the argument string to your internal string. Create two overloaded member functions called print( ): one that takes no arguments and simply prints the message stored in the object, and one that takes a string argument, which it prints in addition to the internal message. Does it make sense to use this approach instead of the one used for the constructor?

class Message
{
private:
    string message;

public:
    Message(string s = "Message:") : message(s) {}
    void print()
    {
        cout << message << endl;
    }
    void print(string str)
    {
        cout << message << " " << str << endl;
    }
};
// Answer: when using two overloaded print functions, it's more flexible for the caller to
// print different messages with a prefix which has been created in the class before. Thus
// helps to improve the reusability of the code.
int main()
{
    Message m1;
    Message m2("abc:");
    m1.print();
    m2.print();
    m1.print("123");
    m2.print("456");
}
// outputs are like this below
// Message:
// abc:
// Message: 123
// abc: 456