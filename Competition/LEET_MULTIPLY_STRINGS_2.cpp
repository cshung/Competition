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
    class Solution {
    private:
        void mulDigit(vector<int>& num, int digit, vector<int>& result)
        {
            int carry = 0;
            for (unsigned int i = 0; i < num.size(); i++)
            {
                int p = num[i] * digit + carry;
                result.push_back(p % 10);
                carry = p / 10;
            }
            if (carry != 0)
            {
                result.push_back(carry);
            }
        }

        vector<int> toDigits(string num)
        {
            vector<int> result;
            for (unsigned int i = num.size(); i > 0; i--)
            {
                result.push_back(num[i - 1] - '0');
            }
            return result;
        }
        string toString(vector<int> result)
        {
            string s;
            s.resize(result.size());
            unsigned int j = 0;
            for (unsigned int i = result.size(); i > 0; i--)
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
            for (unsigned int i = 0; i < num1v.size(); i++)
            {
                vector<int> product;
                for (unsigned int j = 0; j < i; j++)
                {
                    product.push_back(0);
                }
                mulDigit(num2v, num1v[i], product);
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