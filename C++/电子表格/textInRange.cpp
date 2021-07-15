#include <vector>
#include <iostream>
// #include <QtGui>

using namespace std;

vector<double> textInRange(string Range)
{
    int leftColume, rightColume, topRow, bottomRow;
    char temp1[5],temp2[5];
    sscanf(Range.c_str(),"%[A-Z]%d:%[A-Z]%d",temp1,&topRow,temp2,&bottomRow);
    leftColume = atoi(temp1);
    rightColume = atoi(temp2);
    // Range 的格式 A1:B1
    vector<double> ret;
    return ret;
}
int main()
{
    textInRange("A1:B1");
}