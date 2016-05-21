#include "stdafx.h"

// https://leetcode.com/problems/reverse-string/

#include "LEET_REVERSE_STRING.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_REVERSE_STRING
{
    class Solution
    {
    public:
        string reverseString(string s)
        {
            size_t length = s.length();
            char* y = new char[length + 1];
            for (size_t i = 0; i < length; i++)
            {
                y[length - i - 1] = s[i];
            }
            y[length] = '\0';
            string result = y;
            delete[] y;
            return result;
        }
    };
};

using namespace _LEET_REVERSE_STRING;

int LEET_REVERSE_STRING()
{
    Solution solution;
    cout << solution.reverseString("Hello") << endl;
    return 0;
}