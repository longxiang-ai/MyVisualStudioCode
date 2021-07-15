// 类型名称： 堆栈（Stack）。
// 数据对象集： 一个有 0 个或多个元素的又穷表。
// 操作集： 长度为 max_size 的堆栈 S ∈ Stack， 堆栈元素 item ∈ int。

/////////////////////////////
// 作者：李明伟             //
// 学号：3190106234        //
////////////////////////////

#include <stdio.h>
#include <malloc.h>
// 调用malloc.h库中的malloc函数来完成空间申请分配

typedef int ElementType; // 本题内栈的元素类型为int
typedef int bool;        // C语言没有bool型变量，用int代替
enum bool
{
    false = 0,
    true = 1
};
// 栈的结构体定义，stack 定义三个元素，array 指针存放栈内元素，max_size存放栈的最大容量，而top代表栈顶的位置
typedef struct Stack
{
    ElementType *array; // 用来存放栈内元素的数组
    int max_size;       // 存储栈的最大元素个数
    int top;            // 栈顶元素Index
} stack;

stack create_stack(int max_size);     // 生成空堆栈， 其最大长度为 max_size；
bool is_full(stack *s, int max_size); // 判断堆栈 S 是否已满；
void push(stack *s, int item);        // 将元素 item 压入堆栈；
bool is_empty(stack *s);              // 判断堆栈 S 是否为空；
int pop(stack *s);                    // 删除并返回栈顶元素；

// 创建堆栈
stack create_stack(int max_size)
{
    int *array = (int *)malloc(max_size * sizeof(int));
    stack s;
    s.array = array;
    s.max_size = max_size;
    s.top = -1;
    return s;
}
// 判断栈是否满
bool is_full(stack *s, int max_size)
{
    if (s->top + 1 == max_size)
        return true;
    else
        return false;
}
// 压入栈
void push(stack *s, int item)
{
    if (is_full(s, s->max_size))
    {
        printf("栈已满，入栈失败\n");
        return;
    }
    s->array[++s->top] = item;
}
// 判断栈是否是空的
bool is_empty(stack *s)
{
    if (s->top == -1)
    {
        return true;
    }
    else
    {
        return false;
    }
}
// 出栈函数，非空返回栈顶元素，空栈报错
int pop(stack *s)
{
    if (!is_empty(s))
    {
        return s->array[s->top--];
    }
    else
    {
        printf("栈已经空了，无法出栈");
        return -1;
    }
}
// 测试用主程序
int main()
{
    stack a = create_stack(100);
    for (int i = 0; i < 100; i++)
    {
        push(&a, i);
    }
    push(&a, 1);
    for (int i = 0; i < 100; i++)
    {
        printf("%d\n", pop(&a));
    }
    return 0;
}