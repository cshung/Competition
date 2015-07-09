#include "stdafx.h"

// https://leetcode.com/problems/jump-game-ii/

#include "LEET_JUMP_GAME_II.h"
#include <map>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

namespace _LEET_JUMP_GAME_II
{
    class Solution {
    public:
        int jump(vector<int>& nums)
        {
            int horizon = 0;
            vector<unsigned int> requiredStepsBeyond;
            requiredStepsBeyond.resize(nums.size());
            for (unsigned int i = 0; i < nums.size(); i++)
            {
                requiredStepsBeyond[i] = 0;
            }
            requiredStepsBeyond[0] = 1;

            for (unsigned int i = 0; i < nums.size(); i++)
            {
                if (i != 0)
                {

                }
                if (i > horizon)
                {
                    return -1;
                }
                if (i + nums[i] > horizon)
                {
                    if (i + nums[i] < requiredStepsBeyond.size())
                    {
                        requiredStepsBeyond[i + nums[i]] = steps + 1;
                    }
                    horizon = i + nums[i];
                }
                if (requiredStepsBeyond[i] > steps)
                {
                    steps = requiredStepsBeyond[i];
                }
            }

            return steps;
        }
    };
}

/*
[0, 1, 2, 3, 4, 5, 6, 7, 8, 9, A, B]
[7, 8, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0]
    x  x  x  x  x  x  x
       y  y  y  y  y  y  y  y
          z  z  z  z  z  z  z  z  z
 0  1  1  1  1  1  1  1  2  2  2  2 [STEP VALUE]
 1  x  x  x  x  x  x  2  x  x  x  3
 */
using namespace _LEET_JUMP_GAME_II;

int LEET_JUMP_GAME_II()
{
    Solution solution;
    // need quick way to find out if an index is reachable with n step
    int case1Array[] = { 1 };
    vector<int> case1 = vector<int>(case1Array, case1Array + 1);
    cout << solution.jump(case1) << endl;
    return 0;
}