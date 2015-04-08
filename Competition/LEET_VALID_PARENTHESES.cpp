#include "stdafx.h"

// https://leetcode.com/problems/valid-parentheses/

#include "LEET_VALID_PARENTHESES.h"
#include <map>
#include <iostream>
#include <stack>

using namespace std;

namespace _LEET_VALID_PARENTHESES
{
    class Solution
    {
    public:
        bool isValid(string s)
        {
            stack<char> opened;
            for (unsigned int i = 0; i < s.length(); i++)
            {
                char cur = s[i];
                if (cur == '(')
                {
                    opened.push(')');
                }
                else if (cur == '[')
                {
                    opened.push(']');
                }
                else if (cur == '{')
                {
                    opened.push('}');
                }
                else
                {
                    if (opened.size() == 0)
                    {
                        return false;
                    }
                    else if (cur == opened.top())
                    {
                        opened.pop();
                    }
                    else
                    {
                        return false;
                    }
                }
            }

            return opened.size() == 0;
        }
    };
};

using namespace _LEET_VALID_PARENTHESES;

int LEET_VALID_PARENTHESES()
{
    Solution solution;
    cout << (solution.isValid("([{}])") ? "Yes" : "No") << endl;
    cout << (solution.isValid("([{}]")  ? "Yes" : "No") << endl;
    cout << (solution.isValid("([{]})") ? "Yes" : "No") << endl;
    return 0;
}
