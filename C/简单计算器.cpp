#include <stdio.h>
int main()
{
    int x1, x2 = 0;
    int error = 0;
    char op;
    scanf("%d", &x1);
    while (true)
    {
        scanf("%c", &op);
        if (op == '=' || error == 1)
        {
            break;
        }
        else
        {
            scanf("%d", &x2);
            switch (op)
            {
            case ('+'):
                x1 = x1 + x2;
                break;
            case ('-'):
                x1 = x1 - x2;
                break;
            case ('*'):
                x1 = x1 * x2;
                break;
            case ('/'):
                if (x2 == 0)
                {
                    error = 1;
                    break;
                }
                x1 = x1 / x2;
                break;
            default:
                error = 1;
                break;
            }
        }
    }
    if (error == 1)
    {
        printf("ERROR");
    }
    else
    {
        printf("%d", x1);
    }

    return 0;
}