#include "stdafx.h"

// https://leetcode.com/problems/minimum-path-sum/

#include "LEET_MINIMUM_PATH_SUM.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

namespace _LEET_MINIMUM_PATH_SUM
{
    class Solution
    {
    public:
        int minPathSum(vector<vector<int>>& grid)
        {
            int height = grid.size();
            if (height > 0)
            {
                int width = grid[0].size();
                if (width > 0)
                {
                    vector<vector<int>> solution;
                    solution.resize(height);
                    for (int i = 0; i < height; i++)
                    {
                        solution[i].resize(width);
                    }
                    for (int h = 0; h < height; h++)
                    {
                        for (int w = 0; w < width; w++)
                        {
                            bool hasPrev = false;
                            int prev = 0;
                            if (h != 0)
                            {
                                if (hasPrev)
                                {
                                    prev = min(prev, solution[h - 1][w]);
                                }
                                else
                                {
                                    hasPrev = true;
                                    prev = solution[h - 1][w];
                                }
                            }
                            if (w != 0)
                            {
                                if (hasPrev)
                                {
                                    prev = min(prev, solution[h][w - 1]);
                                }
                                else
                                {
                                    hasPrev = true;
                                    prev = solution[h][w - 1];
                                }
                            }
                            solution[h][w] = prev + grid[h][w];
                        }
                    }

                    return solution[height - 1][width - 1];
                }
            }
            return 0;
        }
    };
};

using namespace _LEET_MINIMUM_PATH_SUM;

int LEET_MINIMUM_PATH_SUM()
{
    Solution s;
    vector<vector<int>> grid;
    vector<int> row1;
    vector<int> row2;
    row1.push_back(1);    row1.push_back(2);
    row2.push_back(3);    row2.push_back(4);
    grid.push_back(row1);
    grid.push_back(row2);
    cout << s.minPathSum(grid) << endl;
    return 0;
}