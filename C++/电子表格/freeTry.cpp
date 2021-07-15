#include <iostream>
#include <vector>
#include <stack>
#include <string>
#include <stdlib.h>
#include <cmath>
#include <iomanip>

using namespace std;

/* -------------------------split part----------------------------*/

// remove ' ' at start/end of a string
// replace consecutive ' ' with only one ' '
// also turn 'a'~'z' into 'A'~'Z'
string simplified(const string &str)
{
    string ret;
    bool spaceForward = false;
    bool contentForward = false;
    for (int i = 0; i < str.size(); i++)
    {
        if (str[i] == ' ')
        {
            // '  ' or no forward content
            if (spaceForward || !contentForward)
            {
                contentForward = false;
                continue;
            }
            else
            {
                contentForward = false;
                ret.push_back(str[i]);
            }
        }
        else
        {
            contentForward = true;
            if ('a' <= str[i] && str[i] <= 'z')
                ret.push_back(str[i] - 32);
            else
                ret.push_back(str[i]);
        }
    }
    if (ret.size() > 0 && ret[ret.size() - 1] == ' ')
        ret.erase(ret.end() - 1);

    return ret;
}

// check 1.E+2 / 1.1E-1 / .1E+3
// assume str[i] is "+" or "-"
// here split has not been done
// return true if "+""-" is prefix of scientifc num
bool isPreOfSci(const string &str, int i)
{
    // at least of the form "XXE+2" / "XXE-1"
    if (i <= 2)
        return false;
    else if (i == str.size() - 1)
        return false;
    else
    {
        if (str[i - 1] == 'E' && '0' <= str[i + 1] && str[i + 1] <= '9')
        {
            if ('0' <= str[i - 2] && str[i - 2] <= '9')
                return true;
            else if (str[i - 2] == '.')
            {
                if ('0' <= str[i - 3] && str[i - 3] <= '9')
                    return true;
                else
                    return false;
            }
            else
                return false;
        }
        else
            return false;
    }
    return false;
}

// NOTE: some Errors in expression will be dealed with in next part
// NOTE: 1B / B1 is not distinguished in this part
// NOTE: ".1" and "1." is not dealed with in this part
// NOTE: lack of ')' in the end is always regarded as illegal
// NOTE: '&'-string is not processed
vector<string> split(string &str)
{
    if (str[0] != '=' && str[0] != '-' && str[0] != '+')
    {
        string NotAExp("Not a expression!!!");
        throw NotAExp;
    }

    str = simplified(str); // remove space in before/after content,
                           // replace consecutive space with only one

    vector<string> tokens;
    string temp;
    bool opForward = true; // at start "=+11" or "-11", here '+'/'-' is prefix
    // '=' at start is omitted in reading tokens
    for (int i = 0; i < str.size(); i++)
    {
        if (str[i] != ' ')
        {
            // ':' is specially dealed with
            if (str[i] == '(' || str[i] == ')' || str[i] == '*' ||
                str[i] == '/' || str[i] == '^' || str[i] == '>' ||
                str[i] == '<')
            {
                if (temp.length() > 0)
                    tokens.push_back(temp); // add tokens before
                temp.clear();               // rest temp
                string op;
                op.append(1, str[i]);
                tokens.push_back(op); // add operator
                opForward = true;
            }
            // '+' or '-'
            else if (str[i] == '+' || str[i] == '-')
            {
                // prefix of number
                // regard +1 / +(1) as +1*1 / +1*(1)
                if (opForward)
                {
                    temp.push_back(str[i]); // construct +1 or -1
                    temp.push_back('1');
                    tokens.push_back(temp);
                    temp.clear();
                    tokens.push_back("*");
                    opForward = true;
                }
                // operator with exception(scientific num)
                else
                {
                    // exception: 1.1E+2 / 1.E-1
                    if (isPreOfSci(str, i))
                    {
                        temp.push_back(str[i]); // add op into string as prefix
                        opForward = true;
                    }
                    else
                    {
                        if (temp.length() > 0)
                            tokens.push_back(temp); // add tokens before
                        temp.clear();
                        string op;
                        op.append(1, str[i]);
                        tokens.push_back(op); // add operator
                        opForward = true;
                    }
                }
            }
            else if (str[i] == '%')
            {
                if (temp.length() > 0)
                    tokens.push_back(temp); // add tokens before
                temp.clear();
                string op;
                op.append(1, str[i]);
                tokens.push_back(op); // add operator
                opForward = false;    // % is a uniOP
            }
            else if (str[i] == ',')
            {
                if (temp.length() > 0)
                    tokens.push_back(temp); // add tokens before
                temp.clear();
                string op;
                op.append(1, str[i]);
                tokens.push_back(op);
                opForward = true;
            }
            // B11:D15 as a token
            else if (str[i] == ':')
            {
                temp.push_back(str[i]); // just add ':'
                opForward = true;       // ':' is regarded as an op
            }
            // float
            else if (str[i] == '.')
            {
                temp.push_back(str[i]);
                opForward = false; // '.' is not regarded as an op
            }
            // alpha
            else if (isalpha(str[i]))
            {
                temp.push_back(str[i]);
                opForward = false;
            }
            // number
            else if ('0' <= str[i] && str[i] <= '9')
            {
                temp.push_back(str[i]);
                opForward = false;
            }
            // other cases
            else
            {
                if (str[i] == '=')
                {
                    // "<=" or ">="
                    if (i > 0 && (str[i - 1] == '>' || str[i - 1] == '<'))
                    {
                        string totOp;
                        totOp.push_back(str[i - 1]);
                        totOp.push_back(str[i]);
                        tokens.back() = totOp;
                        continue;
                    }
                    else if (i == 0)
                        continue;
                }
                string ErrInExp("Error In Expression!!!");
                throw ErrInExp;
            }
        }
        // ' '
        else
        {
            // distinguish and cut "1 A", "A 1", "1 1", "A A"
            if (!opForward && i > 0 && i < str.size() - 1 &&
                isalnum(str[i - 1]) && isalnum(str[i + 1]))
            {
                string consecALNUM("Consecutive ALNUM!!!");
                throw consecALNUM;
            }
        }
    }
    if (temp.length() > 0)
        tokens.push_back(temp);

    return tokens;
}

/* -------------------value-check & transform part ---------------- */

// Cases to consider:
//***********************************************************
// case for each possible parameter:
// case1: 1
// case2: 1.1
// case3: .1 / 1. // at most 1 point is allowed
// case4: 1%
// case5: 5/6
// case6: B11
// case7: B11:H14
// case8: 2.1E3   // no point after 'E'/'e'
// case9: .1E1
// illegal(***maybe cases othen than those above are)
// so cases below can be neglected
// case1: 1B1
// case2: 1..1 / 1...1
// case3: B.11 / .B11
// case4: 2.1E1. / 2.1E2.1
//************************************************************/

// copy a segment of char from src to des
void stringSegCpy(string &des, const string &src, int begin, int end)
{
    des.clear();
    for (int i = begin; i <= end; i++)
    {
        des.push_back(src[i]);
    }
}

// count times of one char in a string
int countChar(const string &str, char ch)
{
    int ret = 0;
    for (int i = 0; i < str.size(); i++)
    {
        if (str[i] == ch)
            ret++;
    }
    return ret;
}

// check whether is all num
bool allNum(const string &str)
{
    if (str.size() == 0)
        return false;
    bool AllNum = true;
    for (int i = 0; i < str.size(); i++)
    {
        if ('0' <= str[i] && str[i] <= '9')
        {
            continue;
        }
        else
        {
            AllNum = false;
            break;
        }
    }

    return AllNum;
}

// check if is an legal integer
bool isLegalInt(const string &str)
{
    if (allNum(str))
        return true;
    else
    {
        if (str[0] == '+' || str[0] == '-')
        {
            string temp;
            stringSegCpy(temp, str, 1, str.size() - 1);
            if (allNum(temp))
                return true;
            else
                return false;
        }
        else
            return false;
    }
    return false;
}

// assist check of legal range
bool allAlpha(const string &str)
{
    bool AllAlpha = true;
    for (int i = 0; i < str.size(); i++)
    {
        if (!isalpha(str[i]))
        {
            AllAlpha = false;
            break;
        }
    }

    return AllAlpha;
}

// check whether a string is in form of
// "AAA111"(all alpha is before all num)
bool isAlphaNumFormat(const string &str)
{
    bool startNum = false;
    bool NumExist = false;
    bool AlphaExist = false;
    for (int i = 0; i < str.size(); i++)
    {
        // other ch
        if (!isalnum(str[i]))
            return false;
        // alpha
        else if (isalpha(str[i]))
        {
            AlphaExist = true;
            if (startNum)
                return false;
            else
                continue;
        }
        // num
        else
        {
            NumExist = true;
            startNum = true; // part of num starts
        }
    }

    return NumExist & AlphaExist;
}

// in a legal format, "X:X" is required
// to be specific, "1:2", "B:C", "B1:C2"
// also just one colon should be found
bool isLegalRange(const string &str)
{
    bool OneColon = false;
    int colonPos = str.find(':');
    if (countChar(str, ':') != 1)
        return false;
    else if (colonPos == 0)
        return false;
    else if (colonPos == str.size() - 1)
        return false;
    // only one ':' exists and is not at start/end
    else
    {
        string beforeColon;
        stringSegCpy(beforeColon, str, 0, colonPos - 1);
        string afterColon;
        stringSegCpy(afterColon, str, colonPos + 1, str.size() - 1);
        // "B11:C11"
        if (isAlphaNumFormat(beforeColon) && isAlphaNumFormat(afterColon))
        {
            return true;
        }
        // "B:C"
        else if (allAlpha(beforeColon) && allAlpha(afterColon))
        {
            return true;
        }
        // "1:2"
        else if (allNum(beforeColon) && allNum(afterColon))
        {
            return true;
        }
        else
            return false;
    }
    return false; // redundant here
}

// consider sign at pos[0]
bool isLegalFloat(const string &str)
{
    if (countChar(str, '.') != 1)
        return false;
    // string is composed of only one '.'
    else if (str.size() == 1)
        return false;
    // with just one '.' and length > 1
    else
    {
        int pointPos = str.find('.');
        // "+/-.XXX"
        if (pointPos == 0)
        {
            string temp;
            stringSegCpy(temp, str, 1, str.size() - 1);
            if (allNum(temp))
                return true;
            else if (str[0] == '+' || str[0] == '-')
            {
                string temp2;
                stringSegCpy(temp2, str, 2, str.size() - 1);
                if (allNum(temp2))
                    return true;
            }
            else
                return false;
        }
        // "(+/-)XXX."
        else if (pointPos == str.size() - 1)
        {
            string temp;
            stringSegCpy(temp, str, 0, str.size() - 2);
            if (isLegalInt(temp))
                return true;
            else
                return false;
        }
        // "(+/-)X.X"
        else
        {
            string beforePoint;
            stringSegCpy(beforePoint, str, 0, pointPos - 1);
            string afterPoint;
            stringSegCpy(afterPoint, str, pointPos + 1, str.size() - 1);
            if (isLegalInt(beforePoint) && allNum(afterPoint))
            {
                return true;
            }
            else
                return false;
        }
    }

    return false; // redundant here
}

bool isLegalPercentage(const string &str)
{
    if (countChar(str, '%') != 1)
        return false;
    // only a '%'
    else if (str.size() == 1)
        return false;
    // not ends with '%'
    else if (str[str.size() - 1] != '%')
        return false;
    // "X%"
    else
    {
        string temp;
        stringSegCpy(temp, str, 0, str.size() - 2);
        if (isLegalFloat(temp) || isLegalInt(temp))
            return true;
        else
            return false;
    }
    return false;
}

bool isLegalFraction(const string &str)
{
    if (countChar(str, '/') != 1)
        return false;
    // string is composed of only a '/'
    else if (str.size() == 1)
        return false;
    // '+' or '-' is expression mode
    else if (str[0] == '+' || str[0] == '-')
        return false;
    else
    {
        int divisionPos = str.find('/');
        string beforedivi;
        stringSegCpy(beforedivi, str, 0, divisionPos - 1);
        string afterdivi;
        stringSegCpy(afterdivi, str, divisionPos + 1, str.size() - 1);
        if ((isLegalFloat(beforedivi) || isLegalInt(beforedivi)) &&
            (isLegalFloat(afterdivi) || isLegalInt(afterdivi)))
            return true;
        else
            return false;
    }

    return false;
}

// assume 'e' is turned into 'E' before
bool isLegalScientific(const string &str)
{
    if (countChar(str, 'E') != 1)
        return false;
    else
    {
        int EPos = str.find('E');
        if (EPos == 0 || EPos == str.size() - 1)
            return false;
        else
        {
            string beforeE;
            stringSegCpy(beforeE, str, 0, EPos - 1);
            string afterE;
            stringSegCpy(afterE, str, EPos + 1, str.size() - 1);
            if (!isLegalInt(afterE))
                return false;
            else
            {
                if (isLegalInt(afterE) || isLegalFloat(beforeE))
                    return true;
                else
                    return false;
            }
        }
    }
    return false;
}

bool isLegalValue(const string &str)
{
    if (isLegalInt(str) || isLegalFloat(str) ||
        isLegalPercentage(str) || isLegalFraction(str) ||
        isLegalRange(str) || isLegalScientific(str) ||
        isAlphaNumFormat(str))
        return true;
    else
        return false;
}

// transform legal data in string form into value
// also assume 'e' has been turned into 'E' before
vector<double> transform(const string &str)
{
    vector<double> ret;
    // integer
    if (isLegalInt(str))
    {
        ret.push_back((double)atoi(str.c_str()));
    }
    // float
    else if (isLegalFloat(str))
    {
        ret.push_back(atof(str.c_str()));
    }
    // percentage
    else if (isLegalPercentage(str))
    {
        ret.push_back(atof(str.c_str()) / 100);
    }
    // fraction
    else if (isLegalFraction(str))
    {
        int divisionPos = str.find('/');
        string beforedivi;
        stringSegCpy(beforedivi, str, 0, divisionPos - 1);
        string afterdivi;
        stringSegCpy(afterdivi, str, divisionPos + 1, str.size() - 1);
        double numerator = atof(beforedivi.c_str());
        double denominator = atof(afterdivi.c_str());
        ret.push_back(numerator / denominator);
    }
    // TODO: complete this part combined with Qt part
    // part1: Legal unit
    else if (isAlphaNumFormat(str))
    {
        // read data in unit
        double dataInUnit = 1.2345;
        // process that data
        // here assume data in unit is 1.2345
        ret.push_back(dataInUnit);
    }
    // part2: Legal range
    else if (isLegalRange(str))
    {
        int colonPos = str.find(':');
        string beforeColon;
        stringSegCpy(beforeColon, str, 0, colonPos - 1);
        // read and process data in range, if just B:C

        // ***just read edited unit, no content is regarded as 0

        // here assume it's {10.1,10.1,10.1,10.1,10.1,10.1}
        for (int i = 0; i < 6; i++)
        {
            ret.push_back(10.1);
        }
        return ret;
    }
    // scientific format
    else if (isLegalScientific(str))
    {
        int EPos = str.find('E');
        string beforeE;
        stringSegCpy(beforeE, str, 0, EPos - 1);
        string afterE;
        stringSegCpy(afterE, str, EPos + 1, str.size() - 1);
        double coe = atof(beforeE.c_str());
        int exp = atoi(afterE.c_str());
        double res = coe * pow(10, exp);
        ret.push_back(res);
    }
    else
    {
        string IllExp("Illegal Expression!!!");
        throw IllExp;
    }

    return ret;
}

/* ---------------------fomula part-----------------------*/

// check if a string represents a function
// more functions can be added later
bool isFunc(const string &str)
{
    if (str == "SUM")
        return true;
    else if (str == "AVERAGE")
        return true;
    else if (str == "COUNT")
        return true;
    else if (str == "MAX")
        return true;
    else if (str == "MIN")
        return true;
    else if (str == "ABS")
        return true;
    else if (str == "FACT")
        return true;
    else if (str == "LN")
        return true;
    else if (str == "LOG")
        return true;
    else if (str == "SQRT")
        return true;
    else if (str == "SIN")
        return true;
    else if (str == "COS")
        return true;
    else if (str == "TAN")
        return true;
    else if (str == "ASIN")
        return true;
    else if (str == "ACOS")
        return true;
    else if (str == "ATAN")
        return true;
    else
        return false;
}

// assume ',' is dealed with before
// here we can assume this function just
// need to deal with simple cases, since
// complex cases such as nested func is
// processed to avoid in split function
// NOTE: all parameter is not NULL
// NOTE: parameters are of double type
double SUM(vector<double> parameter)
{
    if (parameter.size() == 0)
    {
        string NoPara("No Parameter for SUM!!!");
        throw NoPara;
    }

    double sum = 0.0;
    for (int i = 0; i < parameter.size(); i++)
    {
        sum += parameter[i];
    }

    return sum;
}

double AVERAGE(vector<double> parameter)
{
    if (parameter.size() == 0)
    {
        string NoPara("No Parameter for AVERAGE!!!");
        throw NoPara;
    }

    double sum = 0.0;
    for (int i = 0; i < parameter.size(); i++)
    {
        sum += parameter[i];
    }

    return sum / parameter.size();
}

double COUNT(vector<double> parameter)
{
    return parameter.size();
}

double MAX(vector<double> parameter)
{
    if (parameter.size() == 0)
    {
        string NoPara("No Parameter for MAX!!!");
        throw NoPara;
    }

    double max = parameter[0];
    for (int i = 1; i < parameter.size(); i++)
    {
        if (parameter[i] > max)
            max = parameter[i];
    }

    return max;
}

double MIN(vector<double> parameter)
{
    if (parameter.size() == 0)
    {
        string NoPara("No Parameter for MAX!!!");
        throw NoPara;
    }

    double min = parameter[0];
    for (int i = 1; i < parameter.size(); i++)
    {
        if (parameter[i] < min)
            min = parameter[i];
    }

    return min;
}

double ABS(vector<double> parameter)
{
    if (parameter.size() == 0)
    {
        string NoPara("No Parameter for ABS!!!");
        throw NoPara;
    }
    else if (parameter.size() > 1)
    {
        string TooManyPara("Too Many Parameters for ABS!!!");
        throw TooManyPara;
    }
    else
        return fabs(parameter[0]);
}

double FACT(vector<double> parameter)
{
    if (parameter.size() == 0)
    {
        string NoPara("No Parameter for FACT!!!");
        throw NoPara;
    }
    else if (parameter.size() > 1)
    {
        string TooManyPara("Too Many Parameters for FACT!!!");
        throw TooManyPara;
    }
    else
    {
        if (parameter[0] < 0)
        {
            string IllPara("Illegal Parameter!!!");
            throw IllPara;
        }
        else if (parameter[0] == 0)
            return 1;
        else
        {
            double ret = 1;
            for (int i = 1; i <= parameter[0]; i++)
            {
                ret *= i;
            }
            return ret;
        }
    }
}

double LN(vector<double> parameter)
{
    if (parameter.size() == 0)
    {
        string NoPara("No Parameter for LN!!!");
        throw NoPara;
    }
    else if (parameter.size() > 1)
    {
        string TooManyPara("Too Many Parameters for LN!!!");
        throw TooManyPara;
    }
    else if (parameter[0] <= 0)
    {
        string IllNum("Illegal Number for LN!!!");
        throw IllNum;
    }
    else
        return log(parameter[0]);
}

// first para: number; second para: base
double LOG(vector<double> parameter)
{
    if (parameter.size() <= 1)
    {
        string NoPara("Not Enough Parameters for LOG!!!");
        throw NoPara;
    }
    else if (parameter.size() > 2)
    {
        string TooManyPara("Too Many Parameters for LOG!!!");
        throw TooManyPara;
    }
    else if (parameter[1] == 1)
    {
        string Divide0("Divide 0!!!");
        throw Divide0;
    }
    else if (parameter[1] <= 0 || parameter[0] <= 0)
    {
        string IllNum("Illegal Number for LOG!!!");
        throw IllNum;
    }
    else
        return log(parameter[0]) / log(parameter[1]);
}

double SQRT(vector<double> parameter)
{
    if (parameter.size() == 0)
    {
        string NoPara("No Parameter for SQRT!!!");
        throw NoPara;
    }
    else if (parameter.size() > 1)
    {
        string TooManyPara("Too Many Parameters for SQRT!!!");
        throw TooManyPara;
    }
    else
        return sqrt(parameter[0]);
}

double SIN(vector<double> parameter)
{
    if (parameter.size() == 0)
    {
        string NoPara("No Parameter for SIN!!!");
        throw NoPara;
    }
    else if (parameter.size() > 1)
    {
        string TooManyPara("Too Many Parameters for SIN!!!");
        throw TooManyPara;
    }
    else
        return sin(parameter[0]);
}

double COS(vector<double> parameter)
{
    if (parameter.size() == 0)
    {
        string NoPara("No Parameter for COS!!!");
        throw NoPara;
    }
    else if (parameter.size() > 1)
    {
        string TooManyPara("Too Many Parameters for COS!!!");
        throw TooManyPara;
    }
    else
        return cos(parameter[0]);
}

// assume no number can be exactly k * PI/ 2(k!=0)
double TAN(vector<double> parameter)
{
    if (parameter.size() == 0)
    {
        string NoPara("No Parameter for TAN!!!");
        throw NoPara;
    }
    else if (parameter.size() > 1)
    {
        string TooManyPara("Too Many Parameters for TAN!!!");
        throw TooManyPara;
    }
    else
        return tan(parameter[0]);
}

double ASIN(vector<double> parameter)
{
    if (parameter.size() == 0)
    {
        string NoPara("No Parameter for ASIN!!!");
        throw NoPara;
    }
    else if (parameter.size() > 1)
    {
        string TooManyPara("Too Many Parameters for ASIN!!!");
        throw TooManyPara;
    }
    else if (parameter[0] < -1 || parameter[0] > 1)
    {
        string IllPara("Illegal Parameter!!!");
        throw IllPara;
    }
    else
        return asin(parameter[0]);
}

double ACOS(vector<double> parameter)
{
    if (parameter.size() == 0)
    {
        string NoPara("No Parameter for ACOS!!!");
        throw NoPara;
    }
    else if (parameter.size() > 1)
    {
        string TooManyPara("Too Many Parameters for ACOS!!!");
        throw TooManyPara;
    }
    else if (parameter[0] < -1 || parameter[0] > 1)
    {
        string IllPara("Illegal Parameter!!!");
        throw IllPara;
    }
    else
        return acos(parameter[0]);
}

double ATAN(vector<double> parameter)
{
    if (parameter.size() == 0)
    {
        string NoPara("No Parameter for ATAN!!!");
        throw NoPara;
    }
    else if (parameter.size() > 1)
    {
        string TooManyPara("Too Many Parameters for ATAN!!!");
        throw TooManyPara;
    }
    else
        return atan(parameter[0]);
}

/* ---------------------calculation part-----------------------*/

/* -------val cases:------- */
// case1: 1
// case2: 1.1 / .1 / 1.
// case3: 1%
// case4: 1/1
// case5: 1.1E1
// case6: A1 / A1:F11
/* -------func cases:------ */
// case1: SUM
// case2: AVERAGE
// case3: COUNT
// case4: MAX
// case5: MIN
// caseX: ...
/* -------op cases:-------- */
// case1: + -
// case2: * /
// case3: ^
// case4: %
// case5: > < >= <=
// case6: (
// case7: )
// ***priority: '('; '^'; '*''/'; '+''-'; '>' series; ')'
// once read '%', process immediately

// push vector of legal values that a string represents
// ensure it must be legal value(s)
// mode = 1: fun mode: size-1 into paraStack and last 1 into valStack
// mode = 0; normal mode: 1 into valStack
// only 1 case will produce more than 1 parameters: A1:B2
// and values[size-1] will also be pushed into valStack
void pushLegalValue(stack<double> &valStack, stack<double> &paraStack,
                    const string &str, bool funMode)
{
    vector<double> values;
    values = transform(str);
    for (int j = 0; j < values.size() - 1; j++)
    {
        paraStack.push(values[j]);
    }
    valStack.push(values[values.size() - 1]);
}

// check if is a legal operator
bool isLegalOp(const string &str)
{
    if (str == "+" || str == "-")
        return true;
    else if (str == "*" || str == "/")
        return true;
    else if (str == "(" || str == ")")
        return true;
    else if (str == "^" || str == "%")
        return true;
    else if (str == ">" || str == "<")
        return true;
    else if (str == ">=" || str == "<=")
        return true;
    else if (str == ",")
        return true;
    else
        return false;
}

// check stack mode: value / parameter
bool isFuncMode(int FuncCnt)
{
    return FuncCnt > 0;
}

// since there is only one uniOp '%'
// here just consider this case
void processUniOp(stack<double> &s, char op)
{
    if (s.size() == 0)
    {
        string illExp("Illegal Expression!!!");
        throw illExp;
    }
    else
    {
        double operand = s.top();
        operand /= 100;
        s.pop();
        s.push(operand);
    }
}

// get passed parameters and
// pass parameters to corresponding func
// return the res of the func
// other fun can be added later
double callFunc(stack<string> &funStack, stack<double> &paraStack, int paraNum)
{
    vector<double> para;
    string IllFunExp("Illegal Fun Expression!!!");
    for (int i = 0; i < paraNum; i++)
    {
        if (paraStack.empty())
        {
            throw IllFunExp;
        }
        para.push_back(paraStack.top());
        paraStack.pop();
    }
    if (funStack.empty())
        throw IllFunExp;
    string Fun = funStack.top();
    funStack.pop();

    double ret;
    if (Fun == "SUM")
        ret = SUM(para);
    else if (Fun == "AVERAGE")
        ret = AVERAGE(para);
    else if (Fun == "COUNT")
        ret = COUNT(para);
    else if (Fun == "MAX")
        ret = MAX(para);
    else if (Fun == "MIN")
        ret = MIN(para);
    else if (Fun == "ABS")
        ret = ABS(para);
    else if (Fun == "FACT")
        ret = FACT(para);
    else if (Fun == "LN")
        ret = LN(para);
    else if (Fun == "LOG")
        ret = LOG(para);
    else if (Fun == "SQRT")
        ret = SQRT(para);
    else if (Fun == "SIN")
        ret = SIN(para);
    else if (Fun == "COS")
        ret = COS(para);
    else if (Fun == "TAN")
        ret = TAN(para);
    else if (Fun == "ASIN")
        ret = ASIN(para);
    else if (Fun == "ACOS")
        ret = ACOS(para);
    else if (Fun == "ATAN")
        ret = ATAN(para);
    else
    {
        string noSuchFun("No Such Function!!!");
        throw noSuchFun;
    }

    return ret;
}

void conductBiOp(stack<double> &vStack, stack<string> &opStack)
{
    string IllFunExp("Illegal Fun Expression!!!");
    if (vStack.size() < 2 || opStack.size() < 1)
    {
        throw IllFunExp;
    }
    string op = opStack.top();
    opStack.pop();
    double oprand2 = vStack.top();
    vStack.pop();
    double oprand1 = vStack.top();
    vStack.pop();

    if (op == "+")
        vStack.push(oprand1 + oprand2);
    else if (op == "-")
        vStack.push(oprand1 - oprand2);
    else if (op == "*")
        vStack.push(oprand1 * oprand2);
    else if (op == "/")
    {
        if (oprand2 == 0)
        {
            string Divide0("Divide 0!!!");
            throw Divide0;
        }
        else
            vStack.push(oprand1 / oprand2);
    }
    else if (op == "^")
    {
        if (oprand1 == 0 && oprand2 == 0)
        {
            string NaN("Not A Number(0^0)!!!");
            throw NaN;
        }
        else
            vStack.push(pow(oprand1, oprand2));
    }
    else if (op == ">")
        vStack.push(oprand1 > oprand2);
    else if (op == "<")
        vStack.push(oprand1 < oprand2);
    else if (op == ">=")
        vStack.push(oprand1 >= oprand2);
    else if (op == "<=")
        vStack.push(oprand1 <= oprand2);
    else
    {
        throw IllFunExp;
    }
}

// according to priority, process Binary Operator
// manage stack: push and pop
// deal with those of equal or higher priority
void processBiOp(stack<double> &vStack, stack<string> &opStack, const string &op)
{
    // step 1: pop equal/higher op before
    if (op == "^")
    {
        while (!opStack.empty() && opStack.top() == "^")
        {
            conductBiOp(vStack, opStack);
        }
    }
    else if (op == "*" || op == "/")
    {
        while (!opStack.empty() &&
               (opStack.top() == "^" || opStack.top() == "*" ||
                opStack.top() == "/"))
        {
            conductBiOp(vStack, opStack);
        }
    }
    else if (op == "+" || op == "-")
    {
        while (!opStack.empty() &&
               (opStack.top() == "^" || opStack.top() == "*" ||
                opStack.top() == "/" || opStack.top() == "+" ||
                opStack.top() == "-"))
        {
            conductBiOp(vStack, opStack);
        }
    }
    else if (op == ">" || op == "<" ||
             op == ">=" || op == "<=")
    {
        while (!opStack.empty() &&
               (opStack.top() == "^" || opStack.top() == "*" ||
                opStack.top() == "/" || opStack.top() == "+" ||
                opStack.top() == "-" || opStack.top() == ">" ||
                opStack.top() == "<" || opStack.top() == ">=" ||
                opStack.top() == "<="))
        {
            conductBiOp(vStack, opStack);
        }
    }
    else
    {
        string IllExp("Illegal Expression!!!");
        throw IllExp;
    }
    // step 2: push the op
    opStack.push(op);
}

// calculate result in double version
// from input tokens
// throw exception if illegal Expression
double calSplitedExp(vector<string> tokens)
{
    stack<double> valStack;
    stack<string> funcStack;
    stack<string> opStack;
    stack<double> paraStack;
    stack<int> paraSepStack; // store the border of parameters
    int funcCnt = 0;         // process nested case
    int frontBracCnt = 0;
    int backBracCnt = 0;
    for (int i = 0; i < tokens.size(); i++)
    {
        /* value */
        if (isLegalValue(tokens[i]))
        {
            // fun mode: push size-1 values into paraStack
            //           1 value into valStack
            // normal mode: push 1 values into valStack
            int mode = isFuncMode(funcCnt) && funcCnt == frontBracCnt;
            pushLegalValue(valStack, paraStack, tokens[i], mode);
        }
        /* func */
        else if (isFunc(tokens[i]))
        {
            // '(' must be next to the FUN name
            if (i < tokens.size() - 1 && tokens[i + 1] == "(")
            {
                funcCnt++;
                funcStack.push(tokens[i]);
                paraSepStack.push(paraStack.size()); // start pos of parameters in paraS
            }
            // illegal FUN call
            else
            {
                string funcError("Function Call Error!!!");
                throw funcError;
            }
        }
        /* op */
        else if (isLegalOp(tokens[i]))
        {
            if (tokens[i] == "(")
            {
                frontBracCnt++;
                opStack.push("(");
            }
            else if (tokens[i] == ")")
            {
                backBracCnt++;
                string illExp("Illegal Expression!!!");
                // process(since '%' is considered specially,
                // here only need to consider Binary Op)
                if (opStack.empty())
                    throw illExp; // empty stack
                while (opStack.top() != "(")
                {
                    // no '(' in opStack or '%' exists, error
                    if (opStack.size() <= 1 || opStack.top() == "%")
                    {
                        throw illExp;
                    }
                    // opStack.size() > 1 below
                    // all binary ops but '(' will be processed
                    else
                    {
                        if (isLegalOp(opStack.top()))
                        {
                            if (valStack.size() >= 2)
                                conductBiOp(valStack, opStack);
                            else
                                throw illExp;
                        }
                        else
                            throw illExp;
                    }
                }
                // process '('
                opStack.pop(); // remove '('
                // call function and push result
                if (isFuncMode(funcCnt) && funcCnt == frontBracCnt)
                {
                    funcCnt--; // upgrade mode status
                    if (valStack.empty())
                        throw illExp;
                    paraStack.push(valStack.top());
                    if (paraSepStack.empty())
                        throw illExp;
                    int startPos = paraSepStack.top();
                    int paraNum = paraStack.size() - startPos;
                    paraSepStack.pop();
                    // call function
                    valStack.push(callFunc(funcStack, paraStack, paraNum));
                }
                frontBracCnt--;
                backBracCnt--;
            }
            // once read '%', process it immediately
            // so pop is not needed
            else if (tokens[i] == "%")
            {
                processUniOp(valStack, '%');
            }
            // separator ',' for function mode
            // no ',' before and stop when meet '('
            // assume it has the second highest priority
            else if (tokens[i] == ",")
            {
                string illFunExp("illegal Fun Expression!!!");
                // ',' after op or normal mode
                if (i == 0 || (isLegalOp(tokens[i - 1]) && tokens[i - 1] != ")" && tokens[i - 1] != "%") || !isFuncMode(funcCnt))
                {
                    throw illFunExp;
                }
                // function mode: separate
                // pop opStack and process until meet '('
                // last step: pop top in valStack and push into paraStack
                // do nothing to the '(' in the stack
                else
                {
                    // no operator in opStack: error
                    // at least '(' is in for a legal expression
                    if (opStack.empty())
                        throw illFunExp;
                    while (opStack.top() != "(")
                    {
                        // just a op which is not '(' remains
                        if (opStack.size() <= 1)
                            throw illFunExp;
                        conductBiOp(valStack, opStack);
                    }
                    // last step
                    paraStack.push(valStack.top());
                    valStack.pop();
                }
            }
            // Binary Operator
            else
            {
                processBiOp(valStack, opStack, tokens[i]);
            }
        }
        else
        {
            string illExp("Illegal Expression!!!");
            throw illExp;
        }
    }

    // Last process: deal with rest elements in stacks
    // only Binary Operator to consider
    while (!opStack.empty())
    {
        if (opStack.top() == "(" || opStack.top() == ")" || opStack.top() == "%")
        {
            string IllExp("Illegal Expression!!!");
            throw IllExp;
        }
        else
        {
            conductBiOp(valStack, opStack);
        }
    }

    if (valStack.empty() || !paraStack.empty())
    {
        string IllExp("Illegal Expression!!!");
        throw IllExp;
    }
    double ret = valStack.top();
    valStack.pop();
    return ret;
}

/* ------check the correctness of functions above------ */
int main(void)
{
    string input;
    getline(cin, input, '\n');

    try
    {
        vector<string> tokens = split(input);
        double res = calSplitedExp(tokens);

        cout << res << endl;
    }
    catch (const string &exp)
    {
        cout << exp << endl;
    }
    catch (...)
    {
        cout << "Some Errors happen!!!" << endl;
    }
}
