#include "stdafx.h"

// https://leetcode.com/problems/maximum-subarray/

#include "LEET_MAXIMUM_SUBARRAY.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

namespace _LEET_MAXIMUM_SUBARRAY
{
    class Solution
    {
    public:
        int maxSubArray(vector<int>& nums)
        {
            int size = nums.size();
            if (size == 0)
            {
                return 0;
            }
            int best_sum = nums[0];
            int best_sum_ends = nums[0];
            for (int i = 1; i < size; i++)
            {
                if (best_sum_ends < 0)
                {
                    best_sum_ends = nums[i];
                }
                else
                {
                    best_sum_ends = best_sum_ends + nums[i];
                }
                best_sum = max(best_sum, best_sum_ends);
            }

            return best_sum;
        }
    };
};

using namespace _LEET_MAXIMUM_SUBARRAY;

int LEET_MAXIMUM_SUBARRAY()
{
    int case1[] = { -2, 1, -3, 4, -1, 2, 1, -5, 4 };

    Solution s;
    cout << s.maxSubArray(vector<int>(case1, case1 + _countof(case1))) << endl;
    return 0;
}