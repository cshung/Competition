#include "stdafx.h"

// https://leetcode.com/problems/minimum-moves-to-equal-array-elements/

#include "LEET_MINIMUM_MOVES_TO_EQUAL_ARRAY_ELEMENTS.h"
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

namespace _LEET_MINIMUM_MOVES_TO_EQUAL_ARRAY_ELEMENTS
{
    class Solution
    {
    public:
        int minMoves(vector<int>& nums)
        {
            int m = ~(1 << 31);
            int s = 0;
            for (int i = 0; i < nums.size(); i++)
            {
                m = min(nums[i], m);
                s += nums[i];
            }
            return s - m * nums.size();
        }
    };
};

using namespace _LEET_MINIMUM_MOVES_TO_EQUAL_ARRAY_ELEMENTS;

int LEET_MINIMUM_MOVES_TO_EQUAL_ARRAY_ELEMENTS()
{
    Solution solution;
    int input_array[] = { 1, 2, 3 };
    vector<int> input(input_array, input_array + _countof(input_array));
    cout << solution.minMoves(input) << endl;
    return 0;
}