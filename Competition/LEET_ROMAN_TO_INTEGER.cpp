#include "stdafx.h"

// https://leetcode.com/problems/roman-to-integer/

#include "LEET_ROMAN_TO_INTEGER.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_ROMAN_TO_INTEGER
{
    class Solution
    {
    public:
        int romanToInt(string s)
        {
            int value = 0;
            for (unsigned int i = 0; i < s.size(); i++)
            {
                char currentCharacter = s[i];
                char nextCharacter = '\0';
                if (i != s.size() - 1)
                {
                    nextCharacter = s[i + 1];
                }
                if (currentCharacter == 'M')
                {
                    value += 1000;
                }
                else if (currentCharacter == 'D')
                {
                    value += 500;
                }
                else if (currentCharacter == 'C')
                {
                    if (nextCharacter == 'M')
                    {
                        i++;
                        value += 900;
                    }
                    else if (nextCharacter == 'D')
                    {
                        i++;
                        value += 400;
                    }
                    else
                    {
                        value += 100;
                    }
                }
                else if (currentCharacter == 'L')
                {
                    value += 50;
                }
                else if (currentCharacter == 'X')
                {
                    if (nextCharacter == 'C')
                    {
                        i++;
                        value += 90;
                    }
                    else if (nextCharacter == 'L')
                    {
                        i++;
                        value += 40;
                    }
                    else
                    {
                        value += 10;
                    }
                }
                else if (currentCharacter == 'V')
                {
                    value += 5;
                }
                else if (currentCharacter == 'I')
                {
                    if (nextCharacter == 'X')
                    {
                        i++;
                        value += 9;
                    }
                    else if (nextCharacter == 'V')
                    {
                        i++;
                        value += 4;
                    }
                    else
                    {
                        value += 1;
                    }
                }
            }
            return value;
        }
    };
};

#include "LEET_INTEGER_TO_ROMAN.h"

using namespace _LEET_ROMAN_TO_INTEGER;
using namespace _LEET_INTEGER_TO_ROMAN;

int LEET_ROMAN_TO_INTEGER()
{
    Solution s;
    for (int i = 1; i < 4000; i++)
    {
        cout << (s.romanToInt(intToRoman(i)) == i) << endl;
    }

    return 0;
}