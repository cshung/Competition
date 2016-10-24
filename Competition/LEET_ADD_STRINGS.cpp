#include "stdafx.h"

// https://leetcode.com/problems/add-strings/

#include "LEET_ADD_STRINGS.h"
#include <stack>
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_ADD_STRINGS
{
    class Solution
    {
    public:
        string addStrings(string num1, string num2)
        {
            stack<char> digits;
            size_t maxLength = max(num1.length(), num2.length());
            int carry = 0;
            for (size_t i = 0; i < maxLength + 1; i++)
            {
                int digit1, digit2;
                if (i < num1.length())
                {
                    digit1 = num1[num1.length() - 1 - i] - '0';
                }
                else
                {
                    digit1 = 0;
                }
                if (i < num2.length())
                {
                    digit2 = num2[num2.length() - 1 - i] - '0';
                }
                else
                {
                    digit2 = 0;
                }
                int result = digit1 + digit2 + carry;
                carry = result / 10;
                result = result % 10;
                digits.push(result + '0');
            }
            size_t j = 0;
            char* buffer = new char[digits.size() + 1];
            while (digits.size() > 0 && digits.top() == '0')
            {
                digits.pop();
            }
            if (digits.size() == 0)
            {
                return "0";
            }
            while (digits.size() > 0)
            {
                buffer[j++] = digits.top();
                digits.pop();
            }
            buffer[j] = '\0';
            string answer(buffer);
            delete[] buffer;
            return answer;
        }
    };
};

using namespace _LEET_ADD_STRINGS;

int LEET_ADD_STRINGS()
{
    Solution solution;
    cout << solution.addStrings("10086", "12580") << endl;
    return 0;
}