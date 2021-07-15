#include <iostream>
using namespace std;

const int MAXSIZE = 3;
class Overflow
{
};
class Underflow
{
};
template <typename T1, typename T2 = T1>
class Stack
{
public:
    Stack(int size = MAXSIZE);
    ~Stack();
    void Push(T1 item);
    T2 Pop();

private:
    T1 *m_stk;
    int m_size;
    int m_top;
};

template <typename T1, typename T2>
Stack<T1, T2>::Stack<T1, T2>(int size)
{
    m_size = size;
    m_stk = new T[m_size];
    m_top = -1;
}

template <typename T1, typename T2>
Stack<T1, T2>::~Stack<T1, T2>()
{
    delete[] m_stk;
}

template <typename T1, typename T2>
void Stack<T1, T2>::Push(T1 item)
{
    if (++m_top < m_size)
    {
        m_stk[m_top] = item;
    }
    else
    {
        m_top--;
        throw Overflow();
    }
}

template <typename T1, typename T2>
T2 Stack<T1, T2>::Pop()
{
    if (m_top < 0)
    {
        throw Underflow();
    }
    else
    {
        return T2(m_stk[m_top--]);
    }
}

void F(Stack<double, double> *sp)
{
    try
    {
        sp->Push(123.456);
        sp->Push(234.567);
        sp->Push(1.23);
    }
    catch (Overflow)
    {
        std::cout << "堆栈溢出" << std::endl;
    }
    catch (Underflow)
    {
        std::cout << "堆栈下溢" << std::endl;
    }
    std::cout << sp->Pop() << std::endl;
    std::cout << sp->Pop() << std::endl;
    std::cout << sp->Pop() << std::endl;
}

int main()
{
    Stack<double, double> s;
    F(&s);
}