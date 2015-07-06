#include "stdafx.h"

// https://leetcode.com/problems/string-to-integer-atoi/

#include "LEET_STRING_TO_INTEGER_ATOI.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_STRING_TO_INTEGER_ATOI
{
    class Solution
    {
    public:
        int myAtoi(string str)
        {
            int state = 0;
            int current_number = 0;
            bool negative = false;
            for (unsigned int i = 0; i < str.length(); i++)
            {
                char current_character = str[i];
                if (state == 0)
                {
                    if (' ' == current_character)
                    {
                        // no-op, state is still 0
                    }
                    else if ('0' <= current_character && current_character <= '9')
                    {
                        state = 2;
                        current_number = current_character - '0';
                    }
                    else if ('+' == current_character)
                    {
                        state = 1;
                    }
                    else if ('-' == current_character)
                    {
                        state = 1;
                        negative = true;
                    }
                    else
                    {
                        // parse error
                        return 0;
                    }
                }
                else if (state == 1)
                {
                    if ('0' <= current_character && current_character <= '9')
                    {
                        current_number = current_character - '0';
                        state = 2;
                    }
                    else
                    {
                        // parse error;
                        return 0;
                    }
                }
                else if (state == 2)
                {
                    if ('0' <= current_character && current_character <= '9')
                    {
                        if (current_number > 214748364)
                        {
                            if (negative)
                            {
                                return (1 << 31);
                            }
                            else
                            {
                                return ~(1 << 31);
                            }
                        }
                        else if (current_number == 214748364)
                        {
                            if (negative)
                            {
                                if (current_character <= '7')
                                {
                                    current_number = current_number * 10 + (current_character - '0');
                                }
                                else
                                {
                                    // Suppose we see '8', this is right answer (with or without anymore trailing digits)
                                    // and so it for '9'
                                    return (1 << 31);
                                }
                            }
                            else
                            {
                                if (current_character <= '7')
                                {
                                    current_number = current_number * 10 + (current_character - '0');
                                }
                                else
                                {
                                    return ~(1 << 31);
                                }
                            }
                        }
                        else
                        {
                            current_number = current_number * 10 + (current_character - '0');
                        }                    
                    }
                    else
                    {
                        break;
                    }
                }
            }

            if (negative)
            {
                return -current_number;
            }
            else
            {
                return current_number;
            }
        }
    };
};

using namespace _LEET_STRING_TO_INTEGER_ATOI;

int LEET_STRING_TO_INTEGER_ATOI()
{
    Solution solution;
    cout << solution.myAtoi("123") << endl;
    cout << solution.myAtoi("+123") << endl;
    cout << solution.myAtoi("-123") << endl;
    cout << solution.myAtoi(" 123") << endl;
    cout << solution.myAtoi(" +123") << endl;
    cout << solution.myAtoi(" -123") << endl;
    cout << solution.myAtoi(" -0") << endl;
    cout << solution.myAtoi(" +0") << endl;
    cout << solution.myAtoi("") << endl;
    cout << solution.myAtoi("x") << endl;
    cout << solution.myAtoi("2147483646") << endl;
    cout << solution.myAtoi("2147483647") << endl;
    cout << solution.myAtoi("2147483648") << endl;
    cout << solution.myAtoi("-2147483647") << endl;
    cout << solution.myAtoi("-2147483648") << endl;
    cout << solution.myAtoi("-2147483649") << endl;
    return 0;
}