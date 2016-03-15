#include "stdafx.h"

// https://leetcode.com/problems/search-for-a-range/

#include "LEET_SEARCH_FOR_A_RANGE.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_SEARCH_FOR_A_RANGE
{
    class Solution
    {
    public:
        vector<int> searchRange(vector<int>& nums, int target)
        {
            int size = nums.size();

            // A binary search on the gaps in the array, an index of 0 means the gap between [-1] = -infinity and [0]
            int begin = 0;
            int end = size + 1;

            int range_start = -1;
            int range_end = -1;
            while (begin < end)
            {
                int mid = (begin + end) / 2;
                bool prevLessThanTarget = (mid == 0) ? true : nums[mid - 1] < target;
                bool nextHitTargetOrAbove = (mid == size) ? true : nums[mid] >= target;

                if (prevLessThanTarget && nextHitTargetOrAbove)
                {
                    range_start = mid;
                    break;
                }
                else if (!prevLessThanTarget)
                {
                    end = mid;
                }
                else 
                {
                    begin = mid;
                }
            }
            if (nums[range_start] == target)
            {
                begin = 0;
                end = size + 1;
                while (begin < end)
                {
                    int mid = (begin + end) / 2;
                    bool prevHitTargetOrBelow = (mid == 0) ? true : nums[mid - 1] <= target;
                    bool nextLargerThanTarget = (mid == size) ? true : nums[mid] > target;

                    if (prevHitTargetOrBelow && nextLargerThanTarget)
                    {                       
                        range_end = mid - 1;
                        break;
                    }
                    else if (!nextLargerThanTarget)
                    {
                        begin = mid;
                    }
                    else
                    {
                        end = mid;
                    }
                }
            }
            else
            {
                range_start = -1;
            }


            vector<int> result;
            result.push_back(range_start);
            result.push_back(range_end);
            return result;
        }
    };
};

using namespace _LEET_SEARCH_FOR_A_RANGE;

int LEET_SEARCH_FOR_A_RANGE()
{
    int case1_array[] = { 5, 7, 7, 8, 8, 10 };
    vector<int> case1(case1_array, case1_array + _countof(case1_array));
    Solution s;
    vector<int> result = s.searchRange(case1, 8);
    cout << result[0] << ", " << result[1] << endl;
    return 0;
}