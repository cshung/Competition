#include "stdafx.h"

// https://leetcode.com/problems/missing-number/

#include "LEET_MISSING_NUMBER.h"
#include <stack>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_MISSING_NUMBER
{
    class Solution
    {
    public:
        int missingNumber(vector<int>& nums)
        {
            int expected_sum = (nums.size()) * (nums.size() + 1 ) / 2;
            int actual_sum = 0;
            for (int i = 0; i < nums.size(); i++)
            {
                actual_sum += nums[i];
            }
            return expected_sum - actual_sum;
        }
    };
};

using namespace _LEET_MISSING_NUMBER;

int LEET_MISSING_NUMBER()
{
    Solution solution;
    int case1[] = { 0, 1, 3 };
    cout << (solution.missingNumber(vector<int>(case1, case1 + _countof(case1))) == 2) << endl;
    return 0;
}
