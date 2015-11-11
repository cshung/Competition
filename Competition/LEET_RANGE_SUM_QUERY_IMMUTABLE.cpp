#include "stdafx.h"

// https://leetcode.com/problems/range-sum-query-immutable/

#include "LEET_RANGE_SUM_QUERY_IMMUTABLE.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_RANGE_SUM_QUERY_IMMUTABLE
{
    class NumArray
    {
    public:
        NumArray(vector<int> &nums)
        {
            int sum = 0;
            runningSums.push_back(0);
            for (unsigned int i = 0; i < nums.size(); i++)
            {
                sum += nums[i];
                runningSums.push_back(sum);
            }
        }

        int sumRange(int i, int j)
        {
            return runningSums[j + 1] - runningSums[i];
        }
    private:
        vector<int> runningSums;
    };
};

using namespace _LEET_RANGE_SUM_QUERY_IMMUTABLE;

int LEET_RANGE_SUM_QUERY_IMMUTABLE()
{
    int case1[] = { -2, 0, 3, -5, 2, -1 };
    vector<int> nums(case1, case1 + _countof(case1));
    NumArray n(nums);
    cout << n.sumRange(0, 2) << endl;
    cout << n.sumRange(2, 5) << endl;
    cout << n.sumRange(0, 5) << endl;
    return 0;
}