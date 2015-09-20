#include "stdafx.h"

// https://leetcode.com/problems/find-minimum-in-rotated-sorted-array/

#include "LEET_FIND_MINIMUM_IN_ROTATED_SORTED_ARRAY.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

namespace _LEET_FIND_MINIMUM_IN_ROTATED_SORTED_ARRAY
{
    class Solution {
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
                    if (nums[start] < nums[end - 1])
                    {
                        return nums[start];
                    }
                    else
                    {
                        int length = end - start;
                        if (length == 2)
                        {
                            return nums[start + 1];
                        }
                        else
                        {
                            int mid = (start + end) / 2;
                            if (nums[start] > nums[mid])
                            {
                                end = mid + 1;
                            }
                            else
                            {
                                // nums[start] > nums[end - 1]
                                // nums[start] < nums[mid]
                                // => nums[end - 1] < nums[start] < nums[mid]
                                start = mid;
                            }
                        }
                    }
                }
            }
            
            return -1;
        }
    };
};

using namespace _LEET_FIND_MINIMUM_IN_ROTATED_SORTED_ARRAY;

int LEET_FIND_MINIMUM_IN_ROTATED_SORTED_ARRAY()
{
    int case1[] = { 4, 5, 6, 7, 0, 1, 2 };
    Solution s;
    cout << s.findMin(vector<int>(case1, case1 + _countof(case1))) << endl;
    return 0;
}