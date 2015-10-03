#include "stdafx.h"

// https://leetcode.com/problems/find-the-duplicate-number/

#include "LEET_FIND_THE_DUPLICATE_NUMBER.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_FIND_THE_DUPLICATE_NUMBER
{
    class Solution
    {
    public:
        int findDuplicate(vector<int>& nums)
        {
            int size = nums.size();
            int begin = 1;
            int end = size;
            while (begin < end)
            {
#ifdef LOG
                cout << "Answer should be in [" << begin << ", " << end << ")" << endl;
#endif
                if ((end - begin) == 1)
                {
                    return begin;
                }
                int mid = (begin + end) / 2;
                int lCount = 0;
                int rCount = 0;
                for (int i = 0; i < size; i++)
                {
                    if (begin <= nums[i] && nums[i] < mid)
                    {
                        lCount++;
                    }
                    else if (mid <= nums[i] && nums[i] < end)
                    {
                        rCount++;
                    }
                }
#ifdef LOG
                cout << "Count in [" << begin << ", " << mid << ") is " << lCount << endl;
                cout << "Count in [" << mid << ", " << end << ") is " << rCount << endl;
#endif
                int lCountExpected = mid - begin;
                int rCountExpected = end - mid;
                if (lCount > lCountExpected)
                {
                    end = mid;
                }
                else if (rCount > rCountExpected)
                {
                    begin = mid;
                }
                else
                {
                    throw 1;
                }
            }
        }
    };
};

using namespace _LEET_FIND_THE_DUPLICATE_NUMBER;

int LEET_FIND_THE_DUPLICATE_NUMBER()
{
    int case1[] = { 2, 2, 2, 2, 2 };
    int case2[] = { 1, 2, 3, 4, 5, 6, 7, 7 };
    int case3[] = { 4, 4, 16, 3, 12, 18, 11, 19, 10, 17, 4, 15, 4, 9, 4, 13, 4, 4, 1, 4 };
    Solution solution;
    cout << solution.findDuplicate(vector<int>(case1, case1 + _countof(case1))) << endl;
    cout << solution.findDuplicate(vector<int>(case2, case2 + _countof(case2))) << endl;
    cout << solution.findDuplicate(vector<int>(case3, case3 + _countof(case3))) << endl;
    return 0;
}