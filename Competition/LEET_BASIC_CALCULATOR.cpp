#include "stdafx.h"

// https://leetcode.com/problems/basic-calculator/

#include "LEET_BASIC_CALCULATOR.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_BASIC_CALCULATOR
{
    class Solution
    {
    public:
        // Scanner states
        int position;
        char token;
        string* expression;

        // Expression = Value
        // Expression = Expression + Value
        // Expression = Expression - Value
        // Value = Number
        // Value = ( Expression )

        // The key innovation in this solution is parsing backward and thus eliminate the left recursion problem of the left associative grammar
        void scan()
        {
            while (true)
            {
                if (position >= 0)
                {
                    token = (*expression)[position--];
                }
                else
                {
                    token = '\0';
                }
                if (token != ' ')
                {
                    break;
                }
            }
        }

        bool ParseValue(int* result)
        {
            if (token >= '0' && token <= '9')
            {
                return ParseNumber(result);
            }
            else if (token == ')')
            {
                scan();
                int bracketedExpression;
                if (ParseExpression(&bracketedExpression))
                {
                    *result = bracketedExpression;
                    if (token == '(')
                    {   
                        scan();
                        return true;
                    }
                    else
                    {
                        return false;
                    }
                }
                else
                {
                    return false;
                }
            }
            else
            {
                return false;
            }
        }

        bool ParseNumber(int* result)
        {
            int base = 1;
            *result = 0;
            while (true)
            {
                if (token >= '0' && token <= '9')
                {
                    int digit = token - '0';
                    *result = *result + base * digit;
                    base *= 10;
                    scan();
                }
                else
                {
                    return true;
                }
            }
            return false;
        }

        bool ParseExpression(int* result)
        {
            if ((token >= '0' && token <= '9') || token == ')')
            {
                int tail;
                if (ParseValue(&tail))
                {
                    if (token == '+')
                    {
                        scan();
                        int head;
                        if (ParseExpression(&head))
                        {
                            *result = head + tail;
                            return true;
                        }
                    }
                    else if (token == '-')
                    {
                        scan();
                        int head;
                        if (ParseExpression(&head))
                        {
                            *result = head - tail;
                            return true;
                        }
                    }
                    else if (token == '\0' || token == '(')
                    {
                        *result = tail;
                        return true;
                    }
                    else
                    {
                        return false;
                    }
                }
                else
                {
                    return false;
                }
            }

            return false;
        }

        int calculate(string s)
        {
            position = s.size() - 1;
            expression = &s;
            scan();
            int result;
            if (ParseExpression(&result))
            {
                return result;
            }
            cout << "Parse error!" << endl;
            return 0;
        }
    };
};

using namespace _LEET_BASIC_CALCULATOR;

int LEET_BASIC_CALCULATOR()
{
    Solution solution;
    cout << (solution.calculate("1 + 1") == 2) << endl;
    cout << (solution.calculate(" 2-1 + 2 ") == 3) << endl;
    cout << (solution.calculate("(1+(4+5+2)-3)+(6+8)") == 23) << endl;
    return 0;
}