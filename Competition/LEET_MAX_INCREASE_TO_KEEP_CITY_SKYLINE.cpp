#include "stdafx.h"

// https://leetcode.com/problems/max-increase-to-keep-city-skyline

#include "LEET_MAX_INCREASE_TO_KEEP_CITY_SKYLINE.h"
#include <map>
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_MAX_INCREASE_TO_KEEP_CITY_SKYLINE
{
    class Solution
    {
    public:
        int maxIncreaseKeepingSkyline(vector<vector<int>>& grid)
        {
            if (grid.size() == 0 || grid[0].size() == 0)
            {
                return 0;
            }
            size_t height = grid.size();
            size_t width = grid[0].size();
            vector<int> skyline_h;
            vector<int> skyline_v;
            skyline_h.resize(width);
            skyline_v.resize(height);
            for (size_t col = 0; col < width; col++)
            {
                skyline_h[col] = 0;
            }
            for (size_t row = 0; row < height; row++)
            {
                skyline_v[row] = 0;
            }
            for (size_t row = 0; row < height; row++)
            {
                for (size_t col = 0; col < width; col++)
                {
                    skyline_v[row] = max(skyline_v[row], grid[row][col]);
                    skyline_h[col] = max(skyline_h[col], grid[row][col]);
                }
            }
            int answer = 0;
            for (size_t row = 0; row < height; row++)
            {
                for (size_t col = 0; col < width; col++)
                {
                    int allowed = min(skyline_v[row], skyline_h[col]);
                    answer += (allowed - grid[row][col]);
                }
            }
            return answer;
        }
    };
};

using namespace _LEET_MAX_INCREASE_TO_KEEP_CITY_SKYLINE;

int LEET_MAX_INCREASE_TO_KEEP_CITY_SKYLINE()
{
    Solution solution;

    int row1[] = { 3, 0, 8, 4 };
    int row2[] = { 2, 4, 5, 7 };
    int row3[] = { 9, 2, 6, 3 };
    int row4[] = { 0, 3, 1, 0 };

    vector<vector<int>> grid;
    grid.push_back(vector<int>(row1, row1 + _countof(row1)));
    grid.push_back(vector<int>(row2, row2 + _countof(row2)));
    grid.push_back(vector<int>(row3, row3 + _countof(row3)));
    grid.push_back(vector<int>(row4, row4 + _countof(row4)));
    cout << solution.maxIncreaseKeepingSkyline(grid) << endl;
    return 0;
}