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
                if ((end - begin) == 1)
                {
                    return begin;
                }
                int mid = (begin + end) / 2;
                int sum = 0;
                for (int i = 0; i < size; i++)
                {
                    if (nums[i] < mid)
                    {
                        sum += nums[i];
                    }
                }
                int noDupSum = (mid - 1) * mid / 2;
                if (sum == noDupSum)
                {
                    begin = mid;
                }
                else
                {
                    end = mid;
                }
            }
        }
    };
};

using namespace _LEET_FIND_THE_DUPLICATE_NUMBER;

int LEET_FIND_THE_DUPLICATE_NUMBER()
{
    int case1[] = { 2, 1, 2 };
    int case2[] = { 1, 2, 3, 4, 5, 6, 7, 7 };
    Solution solution;
    cout << solution.findDuplicate(vector<int>(case1, case1 + _countof(case1))) << endl;
    cout << solution.findDuplicate(vector<int>(case2, case2 + _countof(case2))) << endl;
    return 0;
}