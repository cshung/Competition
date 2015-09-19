#include "stdafx.h"

// https://leetcode.com/problems/3sum/

#include "LEET_SEARCH_INSERT_POSITION.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

namespace _LEET_SEARCH_INSERT_POSITION
{
    class Solution
    {
    public:
        int searchInsert(vector<int>& nums, int target)
        {
            int size = nums.size();
            int start = 0;
            int end = size;
            while (end > start)
            {
                int mid = (start + end) / 2;
                if (nums[mid] >= target)
                {
                    if (mid > 0)
                    {
                        if (nums[mid - 1] < target)
                        {
                            // nums[mid] >= target && nums[mid - 1] < target => mid is the answer
                            return mid;
                        }
                        else
                        {
                            // nums[mid] >= target && nums[mid - 1] >= target => mid or above cannot be the answer
                            end = mid;
                        }
                    }
                    else
                    {
                        // nums[0] >= target => 0 is the answer
                        return 0;
                    }
                }
                else
                {
                    // nums[mid] < target, mid or below cannot be the answer
                    start = mid + 1;
                }
            }

            // If we do not find anything, this must be the case the number is larger than all elements.
            return size;
        }
    };
};

using namespace _LEET_SEARCH_INSERT_POSITION;

int LEET_SEARCH_INSERT_POSITION()
{
    int case1_array[] = { 1, 3, 5, 6 };
    vector<int> case1(case1_array, case1_array + _countof(case1_array));
    Solution s;
    cout << s.searchInsert(case1, 5) << endl;
    cout << s.searchInsert(case1, 2) << endl;
    cout << s.searchInsert(case1, 7) << endl;
    cout << s.searchInsert(case1, 0) << endl;
    return 0;
}