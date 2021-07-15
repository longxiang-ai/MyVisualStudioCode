#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>

#define LEN 40
typedef struct book
{
    double price;
    char* name;
} Book;

int main()
{
    int N = 2;
    scanf("%d", &N);
    getchar();
    Book booklist[N];
    for (int i = 0; i < N; i++)
    {
        booklist[i].name = (char*)malloc(sizeof(char)*LEN);
        gets(booklist[i].name);
        
        printf("THiS LEN IS %s",booklist[i].name);
        scanf("%lf", &booklist[i].price);
    }
    int index_cheap = 0;
    double cheap = 0;
    int index_exp = 0;
    double exp = 0;

    for (int i = 0; i < N; i++)
    {
        if (booklist[i].price > exp)
        {
            exp = booklist[i].price;
            index_exp = i;
        }
        if (booklist[i].price < cheap)
        {
            cheap = booklist[i].price;
            index_cheap = i;
        }
    }
    printf("%.2f,%s\n", booklist[index_exp].price, booklist[index_exp].name);
}