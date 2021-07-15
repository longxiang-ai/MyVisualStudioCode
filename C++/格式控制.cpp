// 编程实现以下数据输入/输出。
// (1）以左对齐方式输出整数，域宽为12；
// (2）以八进制、十进制、十六进制输入/输出整数；
// (3）实现浮点数的指数格式和定点格式的输入/输出，并指定精度；
// (4）把字符串读入字符型数组变量中，从键盘输入，要求输入串的空格也全部读入，以回车符结束。
#include <iostream>
#include <iomanip>
using namespace std;
int main()
{
    // 左对齐方式输出整数，域宽为12
    int a = 1234567;
    cout << setiosflags(ios::left) << setw(12) << a;
    cout << "*******" << endl;
    // 八、十、十六进制
    int b, c;
    cin >> setbase(8) >> a;
    cin >> setbase(10) >> b;
    cin >> setbase(16) >> c;
    cout << a << endl;
    cout << b << endl;
    cout << c << endl;
    cout << setbase(8) << a << endl;
    cout << setbase(10) << b << endl;
    cout << setbase(16) << c << endl;
    // 浮点数的指数格式，定点格式输入、输出
    const double PI = 3.1415926535;
    cout << PI << endl;
    cout << fixed << setprecision(2) << PI << endl;
    cout << setfill('x') << setw(20) << setprecision(10) << PI << endl;
    cout << setfill('x') << setw(20) << setprecision(10) << left << PI << endl;
    cout << scientific << setprecision(10) << PI << endl;
    cout << scientific << uppercase << setprecision(10) << PI << endl;
    double aa;
    cin >> aa;
    cout << aa << endl;
    cout << setprecision(2) << aa << endl;
    // 把字符串读入字符数组变量中，以回车结束
    char str[100];
    cin.get(str, 100);
    cout << str << endl;
    return 0;
}