// LEET_ISLAND_PERIMETER
#include "stdafx.h"

// https://leetcode.com/problems/island-perimeter/

#include "LEET_ISLAND_PERIMETER.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_ISLAND_PERIMETER
{
    class Solution
    {
    public:
        int islandPerimeter(vector<vector<int>>& grid)
        {
            int result = 0;
            int height = grid.size();
            if (height == 0)
            {
                return 0;
            }
            int width = grid[0].size();
            for (int i = 0; i < height; i++)
            {
                for (int j = 0; j < width; j++)
                {
                    if (grid[i][j] == 1)
                    {
                        if (i == 0 || grid[i - 1][j] == 0)
                        {
                            result++;
                        }
                        if (i == (height - 1) || grid[i + 1][j] == 0)
                        {
                            result++;
                        }
                        if (j == 0 || grid[i][j - 1] == 0)
                        {
                            result++;
                        }
                        if (j == (width - 1) || grid[i][j + 1] == 0)
                        {
                            result++;
                        }
                    }
                }
            }
            return result;
        }
    };
};

using namespace _LEET_ISLAND_PERIMETER;

int LEET_ISLAND_PERIMETER()
{
    Solution solution;
    vector<vector<int>> input;
    //int row1_array[] = { 0, 1, 0, 0 };
    //int row2_array[] = { 1, 1, 1, 0 };
    //int row3_array[] = { 0, 1, 0, 0 };
    //int row4_array[] = { 1, 1, 0, 0 };
    //input.push_back(vector<int>(row1_array, row1_array + _countof(row1_array)));
    //input.push_back(vector<int>(row2_array, row2_array + _countof(row2_array)));
    //input.push_back(vector<int>(row3_array, row3_array + _countof(row3_array)));
    //input.push_back(vector<int>(row4_array, row4_array + _countof(row4_array)));
    int row1_array[] = { 1, 0 };
    input.push_back(vector<int>(row1_array, row1_array + _countof(row1_array)));
    cout << solution.islandPerimeter(input) << endl;
    return 0;
}