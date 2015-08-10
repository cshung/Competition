#include "stdafx.h"

// https://leetcode.com/problems/contains-duplicate-ii/

#include "LEET_CONTAINS_DUPLICATE_II.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

namespace _LEET_CONTAINS_DUPLICATE_II
{
    class Solution
    {
    public:
        bool containsNearbyDuplicate(vector<int>& nums, int k)
        {
            vector<pair<int, unsigned int>> nums_with_position;
            nums_with_position.resize(nums.size());
            for (unsigned int i = 0; i < nums.size(); i++)
            {
                nums_with_position[i] = pair<int, unsigned >(nums[i], i);
            }
            sort(nums_with_position.begin(), nums_with_position.end());
            for (unsigned int i = 1; i < nums.size(); i++)
            {
                if (nums_with_position[i - 1].first == nums_with_position[i].first)
                {
                    if (nums_with_position[i].second - nums_with_position[i - 1].second <= k)
                    {
                        return true;
                    }
                }
            }
            return false;
        }
    };
};

using namespace _LEET_CONTAINS_DUPLICATE_II;

int LEET_CONTAINS_DUPLICATE_II()
{
    Solution solution;
    int case1[] = { 3, 2, 3 };
    cout << !solution.containsNearbyDuplicate(vector<int>(case1, case1 + _countof(case1)), 1) << endl;
    cout << solution.containsNearbyDuplicate(vector<int>(case1, case1 + _countof(case1)), 2) << endl;
    return 0;
}
