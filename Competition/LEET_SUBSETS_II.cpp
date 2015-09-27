#include "stdafx.h"

// https://leetcode.com/problems/subsets-ii/

#include "LEET_SUBSETS_II.h"
#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_SUBSETS_II
{
    class Solution
    {
    public:
        vector<vector<int>> subsetsWithDup(vector<int>& nums)
        {
            vector<vector<int>> result;
            if (nums.size() == 0)
            {
                return result;
            }

            sort(nums.begin(), nums.end());
            vector<int> distinct_nums;
            vector<int> distinct_nums_count;
            distinct_nums.push_back(nums[0]);
            distinct_nums_count.push_back(1);
            for (unsigned int i = 1; i < nums.size(); i++)
            {
                if (nums[i] == nums[i - 1])
                {
                    distinct_nums_count[distinct_nums_count.size() - 1]++;
                }
                else
                {
                    distinct_nums.push_back(nums[i]);
                    distinct_nums_count.push_back(1);
                }
            }

            int size = distinct_nums.size();
            vector<int> bits;
            bits.resize(size);
            for (int i = 0; i < size; i++)
            {
                bits[i] = 0;
            }
            while (true)
            {
                vector<int> subset;
                for (int i = 0; i < size; i++)
                {
                    for (int j = 0; j < bits[i]; j++)
                    {
                        subset.push_back(distinct_nums[i]);
                    }
                }
                result.push_back(subset);
                int digit = 0;
                while (true)
                {
                    if (bits[digit] == distinct_nums_count[digit])
                    {
                        bits[digit] = 0;
                        digit++;
                    }
                    else
                    {
                        bits[digit]++;
                        break;
                    }
                    if (digit == size)
                    {
                        return result;
                    }
                }
            }
        }
    };
};

using namespace _LEET_SUBSETS_II;

int LEET_SUBSETS_II()
{
    Solution solution;
    vector<int> nums;
    nums.push_back(1);
    nums.push_back(2);
    nums.push_back(2);
    vector<vector<int>> subsets = solution.subsetsWithDup(nums);
    for (unsigned int i = 0; i < subsets.size(); i++)
    {
        for (unsigned int j = 0; j < subsets[i].size(); j++)
        {
            cout << subsets[i][j];
        }
        cout << endl;
    }
    return 0;
}