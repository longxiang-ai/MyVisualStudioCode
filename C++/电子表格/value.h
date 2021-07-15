#ifndef FREETRY_H
#define FREETRY_H

#include <iostream>
#include <vector>
#include <stack>
#include <string>
#include <stdlib.h>
#include <cmath>
#include <iomanip>
using namespace std;

class value
{
private:
    /* -------------------------split part----------------------------*/
    string simplified(const string &str);
    bool isPreOfSci(const string &str, int i);
    vector<string> split(string &str);
    /* -------------------value-check & transform part ---------------- */
    void stringSegCpy(string &des, const string &src, int begin, int end);
    int countChar(const string &str, char ch);
    bool allNum(const string &str);
    bool isLegalInt(const string &str);
    bool allAlpha(const string &str);
    bool isAlphaNumFormat(const string &str);
    bool isLegalRange(const string &str);
    bool isLegalFloat(const string &str);
    bool isLegalPercentage(const string &str);
    bool isLegalFraction(const string &str);
    bool isLegalScientific(const string &str);
    bool isLegalValue(const string &str);
    vector<double> transform(const string &str);
    /* ---------------------fomula part-----------------------*/
    bool isFunc(const string &str);
    double SUM(vector<double> parameter);
    double AVERAGE(vector<double> parameter);
    double COUNT(vector<double> parameter);
    double MAX(vector<double> parameter);
    double MIN(vector<double> parameter);
    double ABS(vector<double> parameter);
    double FACT(vector<double> parameter);
    double LN(vector<double> parameter);
    double LOG(vector<double> parameter);
    double SQRT(vector<double> parameter);
    double SIN(vector<double> parameter);
    double COS(vector<double> parameter);
    double TAN(vector<double> parameter);
    double ASIN(vector<double> parameter);
    double ACOS(vector<double> parameter);
    double ATAN(vector<double> parameter);
    /* ---------------------calculation part-----------------------*/
    void pushLegalValue(stack<double> &valStack, stack<double> &paraStack,
                        const string &str, bool funMode);
    bool isLegalOp(const string &str);
    bool isFuncMode(int FuncCnt);
    void processUniOp(stack<double> &s, char op);
    double callFunc(stack<string> &funStack, stack<double> &paraStack, int paraNum);
    void conductBiOp(stack<double> &vStack, stack<string> &opStack);
    void processBiOp(stack<double> &vStack, stack<string> &opStack, const string &op);
    double calSplitedExp(vector<string> tokens);

public:
    value();
    ~value();
    double calValue(string &input) ;
};

#endif