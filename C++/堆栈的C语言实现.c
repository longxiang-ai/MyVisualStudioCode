// �������ƣ� ��ջ��Stack����
// ���ݶ��󼯣� һ���� 0 ������Ԫ�ص������
// �������� ����Ϊ max_size �Ķ�ջ S �� Stack�� ��ջԪ�� item �� int��

/////////////////////////////
// ���ߣ�����ΰ             //
// ѧ�ţ�3190106234        //
////////////////////////////

#include <stdio.h>
#include <malloc.h>
// ����malloc.h���е�malloc��������ɿռ��������

typedef int ElementType; // ������ջ��Ԫ������Ϊint
typedef int bool;        // C����û��bool�ͱ�������int����
enum bool
{
    false = 0,
    true = 1
};
// ջ�Ľṹ�嶨�壬stack ��������Ԫ�أ�array ָ����ջ��Ԫ�أ�max_size���ջ�������������top����ջ����λ��
typedef struct Stack
{
    ElementType *array; // �������ջ��Ԫ�ص�����
    int max_size;       // �洢ջ�����Ԫ�ظ���
    int top;            // ջ��Ԫ��Index
} stack;

stack create_stack(int max_size);     // ���ɿն�ջ�� ����󳤶�Ϊ max_size��
bool is_full(stack *s, int max_size); // �ж϶�ջ S �Ƿ�������
void push(stack *s, int item);        // ��Ԫ�� item ѹ���ջ��
bool is_empty(stack *s);              // �ж϶�ջ S �Ƿ�Ϊ�գ�
int pop(stack *s);                    // ɾ��������ջ��Ԫ�أ�

// ������ջ
stack create_stack(int max_size)
{
    int *array = (int *)malloc(max_size * sizeof(int));
    stack s;
    s.array = array;
    s.max_size = max_size;
    s.top = -1;
    return s;
}
// �ж�ջ�Ƿ���
bool is_full(stack *s, int max_size)
{
    if (s->top + 1 == max_size)
        return true;
    else
        return false;
}
// ѹ��ջ
void push(stack *s, int item)
{
    if (is_full(s, s->max_size))
    {
        printf("ջ��������ջʧ��\n");
        return;
    }
    s->array[++s->top] = item;
}
// �ж�ջ�Ƿ��ǿյ�
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
// ��ջ�������ǿշ���ջ��Ԫ�أ���ջ����
int pop(stack *s)
{
    if (!is_empty(s))
    {
        return s->array[s->top--];
    }
    else
    {
        printf("ջ�Ѿ����ˣ��޷���ջ");
        return -1;
    }
}
// ������������
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