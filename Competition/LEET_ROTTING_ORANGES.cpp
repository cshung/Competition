#include "stdafx.h"

// https://leetcode.com/problems/rotting-oranges/

#include "LEET_ROTTING_ORANGES.h"
#include <map>
#include <iostream>
#include <queue>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_ROTTING_ORANGES
{
    class Solution
    {
    public:
        int orangesRotting(vector<vector<int>>& grid)
        {
            int height = grid.size();
            if (height == 0)
            {
                return 0;
            }
            int width = grid[0].size();
            if (width == 0)
            {
                return 0;
            }
            queue<int> parent_rows;
            queue<int> parent_cols;
            queue<int> bfs_rows;
            queue<int> bfs_cols;
            int count = 0;
            for (int row = 0; row < height; row++)
            {
                for (int col = 0; col < width; col++)
                {
                    if (grid[row][col] == 2)
                    {
                        parent_rows.push(-1);
                        parent_cols.push(-1);
                        bfs_rows.push(row);
                        bfs_cols.push(col);
                        grid[row][col] = -1;
                    }
                    else if (grid[row][col] == 1)
                    {
                        count++;
                    }
                }
            }
            int answer = 0;
            while (!bfs_rows.empty())
            {
                int parent_row = parent_rows.front();
                parent_rows.pop();
                int parent_col = parent_cols.front();
                parent_cols.pop();
                int row = bfs_rows.front();
                bfs_rows.pop();
                int col = bfs_cols.front();
                bfs_cols.pop();
                int distance = -1 - grid[row][col];
                if (row > 0 && grid[row - 1][col + 0] == 1)
                {
                    parent_rows.push(row);
                    parent_cols.push(col);
                    bfs_rows.push(row - 1);
                    bfs_cols.push(col + 0);
                    answer = distance + 1;
                    count--;
                    grid[row - 1][col + 0] = -1 - answer;
                }
                if (row < (height - 1) && grid[row + 1][col + 0] == 1)
                {
                    parent_rows.push(row);
                    parent_cols.push(col);
                    bfs_rows.push(row + 1);
                    bfs_cols.push(col + 0);
                    answer = distance + 1;
                    count--;
                    grid[row + 1][col + 0] = -1 - answer;
                }
                if (col > 0 && grid[row + 0][col - 1] == 1)
                {
                    parent_rows.push(row);
                    parent_cols.push(col);
                    bfs_rows.push(row + 0);
                    bfs_cols.push(col - 1);
                    answer = distance + 1;
                    count--;
                    grid[row + 0][col - 1] = -1 - answer;
                }
                if (col < (width - 1) && grid[row + 0][col + 1] == 1)
                {
                    parent_rows.push(row);
                    parent_cols.push(col);
                    bfs_rows.push(row + 0);
                    bfs_cols.push(col + 1);
                    answer = distance + 1;
                    count--;
                    grid[row + 0][col + 1] = -1 - answer;
                }
            }
            return count == 0 ? answer : -1;
        }
    };
};

using namespace _LEET_ROTTING_ORANGES;

int LEET_ROTTING_ORANGES()
{
    vector<vector<int>> grid(3, vector<int>(3));
    grid[0][0] = 2; grid[0][1] = 1; grid[0][2] = 1;
    grid[1][0] = 1; grid[1][1] = 1; grid[1][2] = 0;
    grid[2][0] = 0; grid[2][1] = 1; grid[2][2] = 1;
    Solution s;
    cout << s.orangesRotting(grid) << endl;
    return 0;
}