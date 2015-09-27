#include "stdafx.h"

// https://leetcode.com/problems/subsets/

#include "LEET_SUBSETS.h"
#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_SUBSETS
{
    class Solution
    {
    public:
        vector<vector<int>> subsets(vector<int>& nums)
        {
            int size = nums.size();
            sort(nums.begin(), nums.end());
            vector<bool> bits;
            bits.resize(size);
            for (int i = 0; i < size; i++)
            {
                bits[i] = false;
            }
            vector<vector<int>> result;
            while (true)
            {
                vector<int> subset;
                for (int i = 0; i < size; i++)
                {
                    if (bits[i])
                    {
                        subset.push_back(nums[i]);
                    }
                }
                result.push_back(subset);
                int digit = 0;
                while (true)
                {
                    if (bits[digit])
                    {
                        bits[digit] = false;
                        digit++;
                    }
                    else
                    {
                        bits[digit] = true;
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

using namespace _LEET_SUBSETS;

int LEET_SUBSETS()
{
    Solution solution;
    vector<int> nums;
    nums.push_back(1);
    nums.push_back(2);
    nums.push_back(3);
    vector<vector<int>> subsets = solution.subsets(nums);
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