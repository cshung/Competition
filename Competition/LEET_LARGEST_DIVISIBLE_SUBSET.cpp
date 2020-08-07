#include "stdafx.h"

// https://leetcode.com/problems/largest-divisible-subset/

#include "LEET_LARGEST_DIVISIBLE_SUBSET.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

namespace _LEET_LARGEST_DIVISIBLE_SUBSET
{
    class Solution
    {
    public:
        vector<int> largestDivisibleSubset(vector<int>& nums)
        {
            vector<int> result;
            if (nums.size() == 0)
            {
                return result;
            }

            sort(nums.begin(), nums.end());
            vector<int> chain_lengths(nums.size());
            vector<int> parents(nums.size());
            int max_chain_length = 1;
            int max_chain_length_index = 0;
            chain_lengths[0] = 1;
            parents[0] = -1;
            for (size_t i = 1; i < nums.size(); i++)
            {
                int chain_length = 1;
                parents[i] = -1;
                for (size_t j = 0; j < i; j++)
                {
                    if (nums[i] % nums[j] == 0)
                    {
                        int candidate_chain_length = chain_lengths[j] + 1;
                        if (candidate_chain_length > chain_length)
                        {
                            chain_length = candidate_chain_length;
                            parents[i] = j;
                        }
                    }
                }
                chain_lengths[i] = chain_length;
                if (chain_length > max_chain_length)
                {
                    max_chain_length = chain_length;
                    max_chain_length_index = i;
                }
            }
            int result_index = max_chain_length_index;
            while (result_index != -1)
            {
                result.push_back(nums[result_index]);
                result_index = parents[result_index];
            }
            return result;            
        }
    };
};

using namespace _LEET_LARGEST_DIVISIBLE_SUBSET;

int LEET_LARGEST_DIVISIBLE_SUBSET()
{
    Solution solution;
    vector<int> nums;
    nums.push_back(1);
    nums.push_back(4);
    nums.push_back(2);
    nums.push_back(8);
    vector<int> divisible_subset = solution.largestDivisibleSubset(nums);
    for (size_t i = 0; i < divisible_subset.size(); i++)
    {
        cout << divisible_subset[i] << ", ";
    }
    cout << endl;
    return 0;
}