#include "stdafx.h"

// https://leetcode.com/problems/total-hamming-distance

#include "LEET_TOTAL_HAMMING_DISTANCE.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_TOTAL_HAMMING_DISTANCE
{
    class Solution
    {
    public:
        int totalHammingDistance(vector<int>& nums)
        {
            int dist = 0;
            int mask = 1;
            for (int i = 0; i < 32; i++)
            {
                int zero = 0;
                int ones = 0;
                for (size_t j = 0; j < nums.size(); j++)
                {
                    bool is_zero = (nums[j] & mask) == 0;
                    if (is_zero) { zero++; } else { ones++; }
                }
                dist += zero * ones;
                mask = mask << 1;
            }
            return dist;
        }
    };
};

using namespace _LEET_TOTAL_HAMMING_DISTANCE;

int LEET_TOTAL_HAMMING_DISTANCE()
{
    Solution solution;
    int input_array[] = { 4, 14, 2 };
    vector<int> input(input_array, input_array + _countof(input_array));
    cout << solution.totalHammingDistance(input) << endl;
    return 0;
}