#include "stdafx.h"

// https://leetcode.com/problems/bomb-enemy

#include "LEET_BOMB_ENEMY.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

namespace _LEET_BOMB_ENEMY
{
    class Solution
    {
    public:
        int maxKilledEnemies(vector<vector<char>>& grid)
        {
            if (grid.size() == 0 || grid[0].size() == 0)
            {
                return 0;
            }
            int height = grid.size();
            int width = grid[0].size();

            vector<vector<int>> left;
            vector<vector<int>> right;
            vector<vector<int>> top;
            vector<vector<int>> bottom;
            
            left.resize(height);
            right.resize(height);
            top.resize(height);
            bottom.resize(height);
            for (int i = 0; i < height; i++)
            {
                left[i].resize(width);
                right[i].resize(width);
                top[i].resize(width);
                bottom[i].resize(width);
                for (int j = 0; j < width; j++)
                {
                    left[i][j] = 0;
                    right[i][j] = 0;
                    top[i][j] = 0;
                    bottom[i][j] = 0;
                }
            }
            int count;
            for (int row = 0; row < height; row++)
            {
                count = 0;
                for (int col = 0; col < width; col++)
                {
                    if (grid[row][col] == 'W') { count = 0; } else if (grid[row][col] == 'E') { count++; }
                    else { left[row][col] = count; }
                }
                count = 0;
                for (int col = width - 1; col >= 0; col--)
                {
                    if (grid[row][col] == 'W') { count = 0; } else if (grid[row][col] == 'E') { count++; }
                    else { right[row][col] = count; }
                }
            }

            for (int col = 0; col < width; col++)
            {
                count = 0;
                for (int row = 0; row < height; row++)
                {
                    if (grid[row][col] == 'W') { count = 0; }
                    else if (grid[row][col] == 'E') { count++; }
                    else { top[row][col] = count; }
                }
                count = 0;
                for (int row = height - 1; row >= 0; row--)
                {
                    if (grid[row][col] == 'W') { count = 0; }
                    else if (grid[row][col] == 'E') { count++; }
                    else { bottom[row][col] = count; }
                }
            }
            int kill = 0;
            for (int row = 0; row < height; row++)
            {
                for (int col = 0; col < width; col++)
                {
                    kill = max(kill, left[row][col] + right[row][col] + top[row][col] + bottom[row][col]);
                }
            }
            return kill;
        }
    };
};

using namespace _LEET_BOMB_ENEMY;

int LEET_BOMB_ENEMY()
{
    Solution solution;
    vector<vector<char>> grid;
    grid.resize(3);
    grid[0].resize(4);
    grid[1].resize(4);
    grid[2].resize(4);
    grid[0][0] = '0'; grid[0][1] = 'E'; grid[0][2] = '0'; grid[0][3] = '0';
    grid[1][0] = 'E'; grid[1][1] = '0'; grid[1][2] = 'W'; grid[1][3] = 'E';
    grid[2][0] = '0'; grid[2][1] = 'E'; grid[2][2] = '0'; grid[2][3] = '0';
    cout << solution.maxKilledEnemies(grid) << endl;
    return 0;
}