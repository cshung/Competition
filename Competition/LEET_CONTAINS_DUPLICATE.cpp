#include "stdafx.h"

// https://leetcode.com/problems/contains-duplicate/

#include "LEET_CONTAINS_DUPLICATE.h"
#include <set>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_CONTAINS_DUPLICATE
{
    class Solution
    {
    public:
        bool containsDuplicate(vector<int>& nums)
        {
            set<int> num_set;
            for (unsigned int i = 0; i < nums.size(); i++)
            {
                set<int>::iterator probe = num_set.find(nums[i]);
                if (probe == num_set.end())
                {
                    num_set.insert(nums[i]);
                }
                else
                {
                    return true;
                }
            }

            return false;
        }
    };
};

using namespace _LEET_CONTAINS_DUPLICATE;

int LEET_CONTAINS_DUPLICATE()
{
    Solution solution;
    int case1[] = { 1, 2, 3 };
    int case2[] = { 3, 1, 3 };
    cout << !solution.containsDuplicate(vector<int>(case1, case1 + _countof(case1))) << endl;
    cout << solution.containsDuplicate(vector<int>(case2, case2 + _countof(case2))) << endl;
    return 0;
}