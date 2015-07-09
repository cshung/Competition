#include "stdafx.h"

// https://leetcode.com/problems/jump-game/

#include "LEET_JUMP_GAME.h"
#include <map>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

namespace _LEET_JUMP_GAME
{
    class Solution {
    public:
        bool canJump(vector<int>& nums)
        {
            unsigned int horizon = 0;
            for (unsigned int i = 0; i <= horizon; i++)
            {
                if (horizon >= nums.size() - 1)
                {
                    return true;
                }
                horizon = max(i + nums[i], horizon);
            }

            return false;
        }
    };
}

using namespace _LEET_JUMP_GAME;

int LEET_JUMP_GAME()
{
    Solution solution;
    int case1Array[] = { 2, 3, 1, 1, 4 };
    int case2Array[] = { 3, 2, 1, 0, 4 };
    vector<int> case1 = vector<int>(case1Array, case1Array + 5);
    vector<int> case2 = vector<int>(case2Array, case2Array + 5);
    cout << solution.canJump(case1) << endl;
    cout << solution.canJump(case2) << endl;
    return 0;
}