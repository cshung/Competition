#include "stdafx.h"

// https://leetcode.com/problems/plus-one/

#include "LEET_PLUS_ONE.h"
#include <map>
#include <iostream>
#include <vector>

using namespace std;

namespace _LEET_PLUS_ONE
{
    class Solution
    {
    public:
        vector<int> plusOne(vector<int> &digits)
        {
            vector<int> result;
            int i = digits.size() - 1;
            int carry = 1;
            while (i >= 0 || carry == 1)
            {
                int digit = i < 0 ? 0 : digits[i];
                if (carry == 1)
                {
                    digit++;
                    if (digit == 10)
                    {
                        digit = 0;
                        carry =  1;
                    }
                    else
                    {
                        carry = 0;
                    }
                }
                result.push_back(digit);
                i--;
            }

            reverse(result.begin(), result.end());
            return result;
        }
    };
};

using namespace _LEET_PLUS_ONE;

int LEET_PLUS_ONE()
{
    vector<int> input;
    // input.push_back(1);
    input.push_back(9);
    input.push_back(9);
    Solution solution;
    vector<int> answer = solution.plusOne(input);
    for (unsigned int i = 0; i < answer.size(); i++)
    {
        cout << answer[i];
    }
    cout << endl;
    return 0;
}