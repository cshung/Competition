#include "stdafx.h"

// https://leetcode.com/problems/max-area-of-island

#include "LEET_MAX_AREA_OF_ISLAND.h"
#include <iostream>
#include <queue>
#include <map>
#include <string>

using namespace std;

namespace _LEET_MAX_AREA_OF_ISLAND
{
    class Solution
    {
    public:
        int maxAreaOfIsland(vector<vector<int>>& grid)
        {
            if (grid.size() == 0)
            {
                return 0;
            }
            int height = grid.size();
            int width = grid[0].size();
            int max_size = 0;
            for (int row = 0; row < height; row++)
            {
                if (grid[row].size() != width)
                {
                    throw 1;
                }
                for (int col = 0; col < width; col++)
                {
                    if (grid[row][col] == 1)
                    {
                        int size = 0;
                        queue<pair<int, int>> bfs;
                        bfs.push(make_pair(row, col));
                        grid[row][col] = -1;
                        while (bfs.size() > 0)
                        {
                            auto current = bfs.front();
                            int current_row = current.first;
                            int current_col = current.second;

                            size++;
                            bfs.pop();
                            if (current_row + 1 < height && grid[current_row + 1][current_col] == 1)
                            {
                                bfs.push(make_pair(current_row + 1, current_col));
                                grid[current_row + 1][current_col] = -1;
                            }
                            if (current_col + 1 < width && grid[current_row][current_col + 1] == 1)
                            {
                                bfs.push(make_pair(current_row, current_col + 1));
                                grid[current_row][current_col + 1] = -1;
                            }
                            if (current_row - 1 >= 0 && grid[current_row - 1][current_col] == 1)
                            {
                                bfs.push(make_pair(current_row - 1, current_col));
                                grid[current_row - 1][current_col] = -1;
                            }
                            if (current_col - 1 >= 0 && grid[current_row][current_col - 1] == 1)
                            {
                                bfs.push(make_pair(current_row, current_col - 1));
                                grid[current_row][current_col - 1] = -1;
                            }
                        }
                        max_size = max(size, max_size);
                    }
                }
            }
            return max_size;
        }
    };
};

using namespace _LEET_MAX_AREA_OF_ISLAND;

int LEET_MAX_AREA_OF_ISLAND()
{
    Solution solution;
    int row0[] = { 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0 };
    int row1[] = { 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0 };
    int row2[] = { 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0 };
    int row3[] = { 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 0, 0 };
    int row4[] = { 0, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0 };
    int row5[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0 };
    int row6[] = { 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0 };
    int row7[] = { 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0 };
    vector<vector<int>> grid;
    grid.push_back(vector<int>(row0, row0 + _countof(row0)));
    grid.push_back(vector<int>(row1, row1 + _countof(row1)));
    grid.push_back(vector<int>(row2, row2 + _countof(row2)));
    grid.push_back(vector<int>(row3, row3 + _countof(row3)));
    grid.push_back(vector<int>(row4, row4 + _countof(row4)));
    grid.push_back(vector<int>(row5, row5 + _countof(row5)));
    grid.push_back(vector<int>(row6, row6 + _countof(row6)));
    grid.push_back(vector<int>(row7, row7 + _countof(row7)));
    cout << solution.maxAreaOfIsland(grid) << endl;
    return 0;
}