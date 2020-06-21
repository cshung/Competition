#include "stdafx.h"

// https://leetcode.com/problems/dungeon-game/

#include "LEET_DUNGEON_GAME.h"
#include <map>
#include <iostream>
#include <cassert>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_DUNGEON_GAME
{
    class Solution
    {
    public:
        int calculateMinimumHP(vector<vector<int>>& dungeon)
        {
            vector<vector<int>> require = dungeon;
            int height = dungeon.size();
            int width = dungeon[0].size();
            require[height - 1][width - 1] = max(-dungeon[height - 1][width - 1], 0) + 1;
            for (int s = height + width - 3; s >= 0; s--)
            {
                int row = 0;
                int col = s;
                if (col >= width)
                {
                    col = width - 1;
                    row = s - col;
                }
                while (col >= 0 && row < height)
                {
                    int post_require;
                    if (row < height - 1 && col < width - 1)
                    {
                        post_require = min(require[row + 1][col], require[row][col + 1]);
                    }
                    else if (row < height - 1)
                    {
                        post_require = require[row + 1][col];
                    }
                    else if (col < width - 1)
                    {
                        post_require = require[row][col + 1];
                    }
                    else
                    {
                        assert(false);
                    }
                    require[row][col] = max(1, post_require - dungeon[row][col]);
                    row++;
                    col--;
                }
            }
            return require[0][0];
        }
    };
};

using namespace _LEET_DUNGEON_GAME;

int LEET_DUNGEON_GAME()
{
    vector<vector<int>> dungeon;
    int row1_array[] = { -2,-3,3 };
    int row2_array[] = { -5,-10,1 };
    int row3_array[] = { 10,30,-5 };
    vector<int> row1(row1_array, row1_array + _countof(row1_array));
    vector<int> row2(row2_array, row2_array + _countof(row2_array));
    vector<int> row3(row3_array, row3_array + _countof(row3_array));
    dungeon.push_back(row1);
    dungeon.push_back(row2);
    dungeon.push_back(row3);
    Solution s;
    cout << s.calculateMinimumHP(dungeon) << endl;
    return 0;
}