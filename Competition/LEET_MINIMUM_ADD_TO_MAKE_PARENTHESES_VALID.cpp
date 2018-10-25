#include "stdafx.h"

// https://leetcode.com/problems/minimum-add-to-make-parentheses-valid/

#include "LEET_MINIMUM_ADD_TO_MAKE_PARENTHESES_VALID.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_MINIMUM_ADD_TO_MAKE_PARENTHESES_VALID
{
    class Solution
    {
    public:
        int minAddToMakeValid(string S)
        {
            int c = 0;
            int r = 0;
            for (int i = 0; i < S.length(); i++)
            {
                if (S[i] == '(')
                {
                    c++;
                }
                else
                {
                    c--;
                }
                if (c < 0)
                {
                    c++;
                    r++;
                }
            }
            return r + c;
        }
    };
};

using namespace _LEET_MINIMUM_ADD_TO_MAKE_PARENTHESES_VALID;

int LEET_MINIMUM_ADD_TO_MAKE_PARENTHESES_VALID()
{
    Solution solution;
    cout << solution.minAddToMakeValid("())") << endl;
    cout << solution.minAddToMakeValid("(((") << endl;
    cout << solution.minAddToMakeValid("()") << endl;
    cout << solution.minAddToMakeValid("()))((") << endl;
    return 0;
}