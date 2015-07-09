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
            if (nums.size() == 1)
            {
                return 0;
            }

            unsigned int horizon = 0;
            unsigned int steps = 0;
            vector<unsigned int> walls;
            vector<unsigned int> walls_positions;
            walls.resize(nums.size());
            walls_positions.resize(nums.size());
            for (unsigned int i = 0; i < nums.size(); i++)
            {
                walls[i] = -1;
                walls_positions[i] = -1; // int.max is a good value for not exist
            }
            walls[0] = 0;
            walls_positions[0] = 0;

            for (unsigned int i = 0; i < nums.size(); i++)
            {
                if (i != 0)
                {
                    if (walls[i - 1] != -1)
                    {
                        steps = walls[i - 1] + 1;
                    }
                }
                if (i > horizon)
                {
                    return -1;
                }
                if (i + nums[i] > horizon)
                {
                    unsigned int proposed_wall_position = i + nums[i];
                    if (proposed_wall_position >=  walls.size())
                    {
                        proposed_wall_position = walls.size() - 1;
                    }
                    if (walls_positions[steps + 1] != -1)
                    {
                        walls[walls_positions[steps + 1]] = -1;
                    }
                    walls[proposed_wall_position] = steps + 1;
                    walls_positions[steps + 1] = proposed_wall_position;
                    horizon = proposed_wall_position;
                }
            }

            return steps;
        }
    };
}

using namespace _LEET_JUMP_GAME_II;

int LEET_JUMP_GAME_II()
{
    Solution solution;
    int case1Array[] = { 7, 8, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    //                  0,1,2,3,4,5,6,7,8,9,A,B,C,D,E
    int case2Array[] = {9,7,9,4,8,1,6,1,5,6,2,1,7,9,0};
    vector<int> case1 = vector<int>(case1Array, case1Array + _countof(case1Array));
    vector<int> case2 = vector<int>(case2Array, case2Array + _countof(case2Array));
    // cout << solution.jump(case1) << endl;
    cout << solution.jump(case2) << endl;
    return 0;
}