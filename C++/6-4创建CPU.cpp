#include <iostream>
using namespace std;
/* 请在这里填写答案 */
enum CPU_Rank
{
    P1 = 1,
    P2,
    P3,
    P4,
    P5,
    P6,
    P7
};
class CPU
{
private:
    CPU_Rank Rank;

    double frequency;

    double voltage;

public:
    CPU()
    {
        Rank = P1;
        frequency = 2;
        voltage = 100;
        cout << "create a CPU!" << endl;
    }
    CPU(CPU &c)
    {
        Rank = c.Rank;
        frequency = c.frequency;
        voltage = c.voltage;
        cout << "create a CPU!" << endl;
    }

    CPU(CPU_Rank Rank, double frequency, double voltage)
    {
        this->Rank = Rank;
        this->frequency = frequency;
        this->voltage = voltage;
        cout << "create a CPU!" << endl;
    }
    void showinfo()
    {
        cout << "rank:" << Rank << endl;
        cout << "frequency:" << frequency << endl;
        cout << "voltage:" << voltage << endl;
    }
    ~CPU()
    {
        cout << "destruct a CPU!" << endl;
    }
};
int main()
{
    CPU a(P6, 3, 300);

    cout << "cpu a's parameter" << endl;
    a.showinfo(); //显示性能参数

    CPU b;
    cout << "cpu b's parameter" << endl;
    b.showinfo(); //显示性能参数

    CPU c(a);
    cout << "cpu c's parameter" << endl;
    c.showinfo(); //显示性能参数
}
