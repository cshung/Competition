#include "stdafx.h"

// https://leetcode.com/problems/find-peak-element/

#include "LEET_FIND_PEAK_ELEMENT.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_FIND_PEAK_ELEMENT
{
    class Solution
    {
    public:
        int findPeakElement(vector<int>& nums)
        {
            int size = nums.size();
            if (size == 0)
            {
                // There is no valid peak index for an empty array
                return -1;
            }
            else if (size == 1)
            {
                // The only index is also a peak index
                return 0;
            }

            int begin = 0;   // This must point to an index where the element before it is smaller than it
            int end = size;  // This must point to an index where the elemebe before it is larger  than it
            while (begin < end)
            {
                // cout << "Considering [" << begin << ", " << end << ")" << endl;
                if ((end - begin) == 1)
                {
                    return begin;
                }

                int mid = (begin + end) / 2;
                if (mid == 0)
                {
                    // We have begin < end
                    // So this happen only if end == 1
                    // But we already returned above if that is the case, so this should not happen at all
                    throw 1;
                }
                else
                {
                    if (nums[mid - 1] < nums[mid])
                    {
                        // There must be a peak index in [mid, end) because [mid - 1] -> [mid] is increasing and end side is decreasing
                        begin = mid;
                    }
                    else if (nums[mid - 1] > nums[mid])
                    {
                        // There must be a peak index in [begin, mid) because [mid - 1] -> [mid] is decreasing and begin side is increasing
                        end = mid;
                    }
                    else
                    {
                        // This should not happen given problem description
                        throw 1;
                    }
                }

            }
            return -1;
        }
    };
};

using namespace _LEET_FIND_PEAK_ELEMENT;

int LEET_FIND_PEAK_ELEMENT()
{
    int case1[] = { 1, 2, 3, 1 };
    int case2[] = { 1, 2, 3, 4 };
    int case3[] = { 5, 4, 3, 2, 1 };
    Solution solution;
    cout << (solution.findPeakElement(vector<int>(case1, case1 + _countof(case1))) == 2) << endl;
    cout << (solution.findPeakElement(vector<int>(case2, case2 + _countof(case2))) == 3) << endl;
    cout << (solution.findPeakElement(vector<int>(case3, case3 + _countof(case3))) == 0) << endl;
    return 0;
}