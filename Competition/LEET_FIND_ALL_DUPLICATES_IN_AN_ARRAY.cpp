#include "stdafx.h"

// https://leetcode.com/case1s/find-all-duplicates-in-an-array/

#include "LEET_FIND_ALL_DUPLICATES_IN_AN_ARRAY.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_FIND_ALL_DUPLICATES_IN_AN_ARRAY
{
    class Solution
    {
    public:
        vector<int> findDuplicates(vector<int>& nums)
        {
            vector<int> answer;

            for (size_t i = 0; i < nums.size(); i++)
            {
                while (true)
                {
                    int current = nums[i];
                    int target = nums[current - 1];
                    if (current == target)
                    {
                        break;
                    }
                    else
                    {
                        nums[i] = target;
                        nums[current - 1] = current;
                    }
                }
            }
            for (size_t i = 0; i < nums.size(); i++)
            {
                if (nums[i] != i + 1)
                {
                    answer.push_back(nums[i]);
                }
            }
            return answer;
        }
    };
};

using namespace _LEET_FIND_ALL_DUPLICATES_IN_AN_ARRAY;

int LEET_FIND_ALL_DUPLICATES_IN_AN_ARRAY()
{
    int case1_array[] = { 4,3,2,7,8,2,3,1 };
    vector<int> case1(case1_array, case1_array + _countof(case1_array));
    Solution s;
    for (auto v : s.findDuplicates(case1))
    {
        cout << v << " ";
    }
    cout << endl;
    return 0;
}