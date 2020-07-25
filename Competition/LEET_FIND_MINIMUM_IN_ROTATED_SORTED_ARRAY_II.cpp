#include "stdafx.h"

// https://leetcode.com/problems/find-minimum-in-rotated-sorted-array-ii/

#include "LEET_FIND_MINIMUM_IN_ROTATED_SORTED_ARRAY_II.h"
#include <map>
#include <iostream>
#include <cassert>
#include <vector>
#include <algorithm>

using namespace std;

namespace _LEET_FIND_MINIMUM_IN_ROTATED_SORTED_ARRAY_II
{
    class Solution
    {
    public:
        int findMin(vector<int>& nums)
        {
            int size = nums.size();
            if (size == 0)
            {
                // minimum is not defined for this case
                return -1;
            }
            else if (size == 1)
            {
                return nums[0];
            }
            else
            {
                int start = 0;
                int end = size;
                while (end > start)
                {
                    int length = end - start;
                    if (length == 2)
                    {
                        return min(nums[start], nums[end - 1]);
                    }
                    if (nums[start] < nums[end - 1])
                    {
                        return nums[start];
                    }
                    else if (nums[start] > nums[end - 1])
                    {
                        int mid = (start + end) / 2;
                        if (nums[start] > nums[mid])
                        {
                            end = mid + 1;
                        }
                        else if (nums[start] < nums[mid])
                        {
                            start = mid;
                        }
                        else if (nums[mid] > nums[end - 1])
                        {
                            start = mid;
                        }
                        else if (nums[mid] < nums[end - 1])
                        {
                            end = mid + 1;
                        }
                        else
                        {
                            assert(false);
                        }
                    }
                    else
                    {
                        while (nums[start] == nums[end - 1] && (end - start) > 2)
                        {
                            start++;
                        }
                        while (nums[start] == nums[end - 1] && (end - start) > 2)
                        {
                            end--;
                        }
                    }
                }
            }

            return -1;
        }
    };
};

using namespace _LEET_FIND_MINIMUM_IN_ROTATED_SORTED_ARRAY_II;

int LEET_FIND_MINIMUM_IN_ROTATED_SORTED_ARRAY_II()
{
    Solution solution;
    int case1_array[] = { 1, 3, 5 };
    int case2_array[] = { 2, 2, 2, 0, 1 };
    vector<int> case1(case1_array, case1_array + _countof(case1_array));
    vector<int> case2(case2_array, case2_array + _countof(case2_array));
    cout << solution.findMin(case1) << endl;
    cout << solution.findMin(case2) << endl;
    return 0;
}