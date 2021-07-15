#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAXLEN 10
typedef struct num
{
    int nume; // 分子
    int deno; // 分母
} Num;
int find_gcd(int x, int y)
{
    int z = y;
    while (x % y != 0)
    {
        z = x % y;
        x = y;
        y = z;
    }
    return z;
}
int main()
{
    int int_part = 0;               // 整数部分
    char not_loop[MAXLEN] = {'\0'}; // 小数部分的非循环节
    char loop[MAXLEN] = {'\0'};     // 小数部分的循环节
    scanf("%d", &int_part);         // 读取整数部分
    getchar();                      // 跳过小数点
    char ch[MAXLEN];                // 用来存放接下来的字符
    gets(ch);                       // 读取接下来缓冲区里的字符
    // printf("%s\n", ch);
    if (ch[0] == '(') //读一个字符，判断其是不是左括号,如果是左括号，则代表接下来的部分是循环节
    {
        sscanf(&ch[1], "%[^)]", loop); //遇到右括号就结束
    }
    else
    {
        sscanf(ch, "%[0-9]", not_loop); //遇到非数字就结束
    }
    int i = 0;
    for (i = 0; i < strlen(ch); i++)
    {
        if (ch[i] == '(') //跳过已经读取的not_loop部分
        {
            break;
        }
    }

    if (i < strlen(ch))
    {
        sscanf(&ch[i + 1], "%[^)]", loop); //遇到右括号结束
    }
    // printf("%d %s %s\n", int_part, not_loop, loop);

    // 接下来只需要将小数部分转化为真分数，然后再和整数部分相加即可得到最终结果
    // 将混循环小数化为分数，分子为{not_loop,loop} - {loop} ,分母为{9,0}，9的个数为not_loop的长度，0的个数为loop的长度
    // 然后再将分子分母约简即可
    Num a;
    // 处理分子
    char temp[MAXLEN] = {'\0'};
    strcpy(temp, not_loop);
    strcat(temp, loop);
    a.nume = atoi(temp);                        // 将字符串转化为int
    if (loop[0] != '\0' && not_loop[0] != '\0') // 混循环小数的分子部分是{not_loop,loop} - {loop}
    {
        a.nume -= atoi(not_loop);
    }
    // 处理分母
    strnset(temp, '9', strlen(loop));
    strnset(temp + strlen(loop), '0', strlen(not_loop));
    a.deno = atoi(temp);

    // printf("%d %d\n", a.nume, a.deno);
    // 这样处理完的情况只适用于存在循环小数的情况，如果不循环，则a.deno = 0
    // 接下来处理a.deno = 0的情况
    if (a.deno == 0)
    {
        a.deno = 1;
        for (int i = 0; i < strlen(not_loop); i++)
        {
            a.deno *= 10;
        }
    }
    // printf("%d %d\n", a.nume, a.deno);
    // 然后将a化为最简形式
    a.nume += int_part * a.deno; //将整数部分加上
    // 寻找分子分母的最大公因数
    int gcd = find_gcd(a.nume, a.deno);
    a.nume /= gcd;
    a.deno /= gcd;
    // 输出结果
    printf("%d/%d\n", a.nume, a.deno);
}