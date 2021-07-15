#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef double ElementType;
#define Infinity 1e8
#define Max_Expr 30
ElementType EvalPostFix(char *expr);
bool isdigit(char ch);
ElementType StrToNum(char nums[Max_Expr]);
int main()
{
    ElementType v;
    char expr[Max_Expr];
    gets(expr);
    v = EvalPostFix(expr);
    if (v < Infinity)
    {
        printf("%f\n", v);
    }
    else
    {
        printf("ERROR\n");
    }
    return 0;
}
ElementType EvalPostFix(char *expr)
{
    ElementType Stack[Max_Expr]; //栈数组
    char nums[Max_Expr];         //临时的字符串转换成double
    int top = -1;
    int i = 0;
    int j = 0;
    while (expr[i] != '\0') //遍历字符串
    {
        while (expr[i] == ' ') //跳过空格
        {
            i++;
        }
        if (isdigit(expr[i]) || expr[i] == '.') //如果是数字
        {
            nums[j++] = expr[i];                           //将这个数字暂时存在单独数字的数组中
            if (expr[i + 1] == ' ' || expr[i + 1] == '\0') //如果下一个字符是空白字符 或 结束符
            {
                nums[j] = '\0';                   //插入结束标志
                ElementType num = StrToNum(nums); //彻底存入栈中
                j = 0;                            //临时数组下表恢复0
                Stack[++top] = num;               //数字读入栈
            }
        }
        else //如果不是数字
        {
            if (isdigit(expr[i + 1])) //考虑数字前置符号 “+1” "-1"的可能
            {
                nums[j++] = expr[i];
            }
            else if (expr[i] == '+')
            {
                if (expr[i + 1] == ' ' || expr[i + 1] == '\0') //如果下一行是结束符
                {
                    if (top > 0) //至少有两个元素
                    {
                        ElementType num1 = Stack[top--];
                        ElementType num2 = Stack[top--];
                        num1 = num1 + num2;
                        Stack[++top] = num1; //入栈
                    }
                    else
                    {
                        return Infinity; //否则剩余的元素不够出栈说明出错了
                    }
                }
            }
            else if (expr[i] == '-')
            {
                if (expr[i + 1] == ' ' || expr[i + 1] == '\0') //如果下一行是结束符
                {
                    if (top > 0) //至少有两个元素
                    {
                        ElementType num1 = Stack[top--];
                        ElementType num2 = Stack[top--];
                        num1 = num2 - num1;
                        Stack[++top] = num1; //入栈
                    }
                    else
                    {
                        return Infinity; //否则剩余的元素不够出栈说明出错了
                    }
                }
            }
            else if (expr[i] == '*')
            {
                if (expr[i + 1] == ' ' || expr[i + 1] == '\0') //如果下一行是结束符
                {
                    if (top > 0) //至少有两个元素
                    {
                        ElementType num1 = Stack[top--];
                        ElementType num2 = Stack[top--];
                        num1 = num1 * num2;
                        Stack[++top] = num1; //入栈
                    }
                    else
                    {
                        return Infinity; //否则剩余的元素不够出栈说明出错了
                    }
                }
            }
            else if (expr[i] == '/')
            {
                if (expr[i + 1] == ' ' || expr[i + 1] == '\0') //如果下一行是结束符
                {
                    if (top > 0) //至少有两个元素
                    {
                        ElementType num1 = Stack[top--];
                        ElementType num2 = Stack[top--];
                        num1 = num2 / num1;
                        if (num1 >= Infinity) //除数为0的情况
                        {
                            return Infinity;
                        }
                        Stack[++top] = num1; //入栈
                    }
                    else
                    {
                        return Infinity; //否则剩余的元素不够出栈说明出错了
                    }
                }
            }
            else //如果不是以上的四种符号，也不是数字或小数点，说明输入有误
            {
                return Infinity;
            }
        }
        i++; //开启下一次遍历
    }
    if (top == 0) //最后只有最终结果一个数
    {
        return Stack[top];
    }
    else
    {
        return Infinity;
    }
}
bool isdigit(char ch)
{
    if (ch >= '0' && ch <= '9')
    {
        return true;
    }
    else
    {
        return false;
    }
}
ElementType StrToNum(char nums[Max_Expr])
{
    ElementType v = 0;
    sscanf(nums, "%lf", &v);
    return v;
}