#include "stdafx.h"

// https://leetcode.com/problems/multiply-strings/

#include "LEET_MULTIPLY_STRINGS_2.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_MULTIPLY_STRINGS_2
{
    class Solution
    {
    private:
        void mulDigit(vector<int>& num, int digit, vector<int>& accumulateTo, size_t offset)
        {
            if (digit == 0)
            {
                // Pointless to do anything here - optimize
                return;
            }

            size_t j = offset;
            int carry = 0;
            for (size_t i = 0; i < num.size(); i++)
            {
                int original_digit = 0;
                if (j < accumulateTo.size())
                {
                    original_digit = accumulateTo[j];
                }
                int p = num[i] * digit + carry + original_digit;
                if (j < accumulateTo.size())
                {
                    accumulateTo[j] = p % 10;
                }
                else
                {
                    while (accumulateTo.size() < j)
                    {
                        accumulateTo.push_back(0);
                    }
                    accumulateTo.push_back(p % 10);
                }

                carry = p / 10;
                j++;
            }
            if (carry != 0)
            {
                if (j < accumulateTo.size())
                {
                    accumulateTo[j] = carry;
                }
                else
                {
                    while (accumulateTo.size() < j)
                    {
                        accumulateTo.push_back(0);
                    }
                    accumulateTo.push_back(carry);
                }
            }
        }

        vector<int> toDigits(string num)
        {
            vector<int> result;
            for (size_t i = num.size(); i > 0; i--)
            {
                result.push_back(num[i - 1] - '0');
            }
            return result;
        }

        string toString(vector<int> result)
        {
            int length = 0;
            bool non_zero_found = false;
            size_t start_index = 1;
            for (size_t i = result.size(); i > 0; i--)
            {
                if (non_zero_found)
                {
                    length++;
                }
                else
                {
                    if (result[i - 1] != 0)
                    {
                        start_index = i;
                        non_zero_found = true;
                        length++;
                    }
                }
            }
            length = length == 0 ? 1 : length;
            string s;
            s.resize(length);
            size_t j = 0;
            for (size_t i = start_index; i > 0; i--)
            {
                s[j++] = result[i - 1] + '0';
            }
            return s;
        }
    public:
        string multiply(string num1, string num2)
        {
            vector<int> num1v = toDigits(num1);
            vector<int> num2v = toDigits(num2);

            vector<int> result;

            // Make sure we have a single digit 0 when the result is actually 0
            result.push_back(0);

            for (size_t i = 0; i < num1v.size(); i++)
            {
                mulDigit(num2v, num1v[i], result, i);
            }

            return toString(result);
        }
    };
};

using namespace _LEET_MULTIPLY_STRINGS_2;

int LEET_MULTIPLY_STRINGS_2()
{
    Solution s;
    cout << (s.multiply("3284324385937593", "579837574598437") == "1904374686136554873066717342141") << endl;
    return 0;
}