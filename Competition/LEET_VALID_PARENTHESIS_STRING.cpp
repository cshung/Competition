#include "stdafx.h"

// https://leetcode.com/problems/valid-parenthesis-string

#include "LEET_VALID_PARENTHESIS_STRING.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_VALID_PARENTHESIS_STRING
{
    class Solution
    {
    public:
        bool checkValidString(string s)
        {
            int u = 0;
            int l = 0;
            for (int i = 0; i < s.length(); i++)
            {
                char c = s[i];
                switch (c)
                {
                case '(':
                    u++;
                    l++;
                    break;
                case ')':
                    u--;
                    l--;
                    if (u < 0) { return false; }
                    if (l < 0) { l = 0; }
                    break;
                case '*':
                    u++;
                    l--;
                    if (l < 0) { l = 0; }
                    break;
                }
            }
            return u >= 0 && l <= 0;
        }
    };
};

using namespace _LEET_VALID_PARENTHESIS_STRING;

int LEET_VALID_PARENTHESIS_STRING()
{
    Solution solution;
    cout << solution.checkValidString("()") << endl;
    cout << solution.checkValidString("(*)") << endl;
    cout << solution.checkValidString("((*)") << endl;
    return 0;
}