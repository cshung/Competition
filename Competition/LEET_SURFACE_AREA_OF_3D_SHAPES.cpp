#include "stdafx.h"

// https://leetcode.com/problems/surface-area-of-3d-shapes

#include "LEET_SURFACE_AREA_OF_3D_SHAPES.h"
#include <map>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_SURFACE_AREA_OF_3D_SHAPES
{
    class Solution
    {
    public:
        int surfaceArea(vector<vector<int>>& grid)
        {
            int height = grid.size();
            if (height == 0)
            {
                return 0;
            }
            int width = grid[0].size();
            int result = 0;
            for (int row = 0; row < height; row++)
            {
                for (int col = 0; col < width; col++)
                {
                    int current = grid[row][col];
                    result += (current == 0) ? 0 : 2;
                    result += current * 4;
                    if (row > 0)
                    {
                        result -= min(current, grid[row - 1][col]);
                    }
                    if (row + 1 < height)
                    {
                        result -= min(current, grid[row + 1][col]);
                    }
                    if (col > 0)
                    {
                        result -= min(current, grid[row][col - 1]);
                    }
                    if (col + 1 < width)
                    {
                        result -= min(current, grid[row][col + 1]);
                    }
                }
            }
            return result;
        }
    };
};

using namespace _LEET_SURFACE_AREA_OF_3D_SHAPES;

int LEET_SURFACE_AREA_OF_3D_SHAPES()
{
    Solution solution;
    vector<vector<int>> grid;
    grid.resize(2);
    for (int i = 0; i < 2; i++) { grid[i].resize(2); }
    grid[0][0] = 1; grid[0][1] = 2;
    grid[1][0] = 3; grid[1][1] = 4;
    cout << solution.surfaceArea(grid) << endl;
    return 0;
}