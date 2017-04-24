#include "stdafx.h"

// https://leetcode.com/problems/array-partition-i/

#include "LEET_ARRAY_PARTITION_I.h"
#include <map>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_ARRAY_PARTITION_I
{
    class Solution {
    public:
        int arrayPairSum(vector<int>& nums)
        {
            int result = 0;
            sort(nums.begin(), nums.end());
            for (size_t i = 0; i < nums.size(); i += 2)
            {
                result += nums[i];
            }
            return result;
        }
    };
};

using namespace _LEET_ARRAY_PARTITION_I;

int LEET_ARRAY_PARTITION_I()
{
    Solution solution;
    vector<int> nums;
    nums.push_back(1);
    nums.push_back(2);
    nums.push_back(3);
    nums.push_back(4);
    cout << solution.arrayPairSum(nums) << endl;
    return 0;
}
