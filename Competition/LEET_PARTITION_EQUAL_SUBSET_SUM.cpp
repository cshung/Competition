#include "stdafx.h"

// https://leetcode.com/problems/partition-equal-subset-sum/

#include "LEET_PARTITION_EQUAL_SUBSET_SUM.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_PARTITION_EQUAL_SUBSET_SUM
{
    class Solution {
    public:
        bool canPartition(vector<int>& nums)
        {
            int sum = 0;
            for (int i = 0; i < nums.size(); i++)
            {
                sum += nums[i];
            }
            if (sum % 2 == 0)
            {
                sum /= 2;
                vector<bool> can_reach;
                can_reach.resize(sum + 1, false);
                can_reach[0] = true;
                for (int i = 0; i < nums.size(); i++)
                {
                    for (int j = sum - nums[i]; j >=0 ; j--)
                    {
                        if (can_reach[j])
                        {
                            can_reach[j + nums[i]] = true;
                            if (j + nums[i] == sum)
                            {
                                return true;
                            }
                        }
                    }
                }
            }
            return false;
        }
    };
};

using namespace _LEET_PARTITION_EQUAL_SUBSET_SUM;

int LEET_PARTITION_EQUAL_SUBSET_SUM()
{
    Solution solution;
    int input_array[] = { 1, 11, 5 ,5};
    vector<int> input(input_array, input_array + _countof(input_array));
    cout << solution.canPartition(input) << endl;
    return 0;
}