#include <iostream>
#include <string>
using namespace std;

int main()
{
   string Range = "C1";
   char temp[5];
   int num;
   sscanf(Range.c_str(),"%[A-Z]%d",&temp,&num);
   int a = atoi(temp);
   cout << a << num;

}