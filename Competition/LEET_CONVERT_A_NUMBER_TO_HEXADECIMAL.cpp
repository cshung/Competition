#include "stdafx.h"

// https://leetcode.com/problems/convert-a-number-to-hexadecimal/

#include "LEET_CONVERT_A_NUMBER_TO_HEXADECIMAL.h"
#include <stack>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_CONVERT_A_NUMBER_TO_HEXADECIMAL
{
    class Solution
    {
    public:
        string toHex(int num)
        {
            stack<char> digits;
            unsigned int n = (unsigned int)num;
            while (n > 0)
            {
                int d = n % 16;
                n = n / 16;
                if (d < 10)
                {
                    digits.push(d + '0');
                }
                else
                {
                    digits.push(d - 10 + 'a');
                }
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

using namespace _LEET_CONVERT_A_NUMBER_TO_HEXADECIMAL;

int LEET_CONVERT_A_NUMBER_TO_HEXADECIMAL()
{
    Solution solution;
    cout << solution.toHex(-1) << endl;
    return 0;
}