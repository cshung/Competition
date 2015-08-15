#include "stdafx.h"

// https://leetcode.com/problems/add-binary/

#include "LEET_ADD_BINARY.h"
#include <stack>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_ADD_BINARY
{
    class Solution {
    public:
        string addBinary(string a, string b)
        {
            int base = 2;
            int carry = 0;
            unsigned int i = 0;
            stack<int> digits;
            while (i < a.length() || i < b.length() || carry != 0)
            {
                int ad = 0;
                int bd = 0;
                if (i < a.length())
                {
                    ad = a[a.length() - i - 1] - '0';
                }
                if (i < b.length())
                {
                    bd = b[b.length() - i - 1] - '0';
                }
                int sum = (ad + bd + carry);
                int digit = sum % base;
                carry = sum / base;
                digits.push(digit);
                i++;
            }
            ostringstream result;
            while (digits.size() > 0)
            {
                result << digits.top();
                digits.pop();
            }

            return result.str();
        }
    };
};

using namespace _LEET_ADD_BINARY;

int LEET_ADD_BINARY()
{
    Solution solution;
    cout << solution.addBinary("11", "10") << endl;
    return 0;
}
