#include <stdio.h>
#include <string.h>
int main()
{
    char ch[1000];
    int length = 0;
    while (scanf("%s", &ch) != EOF)
    {
        length = strlen(ch);
        if (ch[length - 1] != '.')
        {
            printf(" %d ", length - 1);
        }
        else
        {
            printf(" %d ", length);
        }
    }
}