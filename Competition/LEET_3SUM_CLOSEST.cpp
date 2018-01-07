#include "stdafx.h"

// https://leetcode.com/problems/3sum-closest

#include "LEET_3SUM_CLOSEST.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

namespace _LEET_3SUM_CLOSEST
{
    class Solution
    {
    public:
        int threeSumClosest(vector<int>& nums, int target)
        {
            sort(nums.begin(), nums.end());

            size_t n = nums.size();
            bool first = true;
            int best_diff = 0;
            for (size_t p = 0; p < n; p++)
            {
                int b = 0;
                int e = n - 1;
                while (true)
                {
                    if (b == p) { b++; }
                    if (e == p) { e--; }
                    if (b >= e)
                    {
                        break;
                    }
                    int candidate = nums[b] + nums[p] + nums[e];
                    if (first)
                    {
                        best_diff = candidate - target;
                        first = false;
                    }
                    else
                    {
                        int diff = candidate - target;
                        int abs_diff = diff > 0 ? diff : -diff;
                        int abs_best_diff = best_diff > 0 ? best_diff : -best_diff;
                        if (abs_diff < abs_best_diff)
                        {
                            best_diff = diff;
                        }
                    }
                    if (candidate > target)
                    {
                        e--;
                    }
                    else if (candidate == target)
                    {
                        return target;
                    }
                    else
                    {
                        b++;
                    }
                }
            }

            return target + best_diff;
        }
    };
};

using namespace _LEET_3SUM_CLOSEST;

int LEET_3SUM_CLOSEST()
{
    Solution s;
    int case1_array[] = { 0, 1, 2 };
    vector<int> case1(case1_array, case1_array + _countof(case1_array));
    cout << s.threeSumClosest(case1, 0) << endl;
    return 0;
}