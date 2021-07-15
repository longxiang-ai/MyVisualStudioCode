#include <iostream>
#include <string>
using namespace std;

template <class T>
T fibonacci(T n)
{
    if (n <= 1)
        return 1;
    else
        return fibonacci(n - 1) + fibonacci(n - 2);
}

int main()
{
    int n;
    cin >> n;
    cout << fibonacci(n) << endl;
    double x;
    cin >> x;
    cout << fibonacci(x) << endl;
}
