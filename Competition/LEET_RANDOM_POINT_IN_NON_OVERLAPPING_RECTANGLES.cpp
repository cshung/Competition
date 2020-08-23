#include "stdafx.h"

// https://leetcode.com/problems/random-point-in-non-overlapping-rectangles/

#include "LEET_RANDOM_POINT_IN_NON_OVERLAPPING_RECTANGLES.h"
#include <map>
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_RANDOM_POINT_IN_NON_OVERLAPPING_RECTANGLES
{
    class Solution
    {
    private:
        vector<vector<int>> rects;
        vector<int> total_sizes;
    public:
        Solution(vector<vector<int>>& rects)
        {
            this->rects = rects;
            int total_size = 0;
            total_sizes.push_back(total_size);
            for (auto rect : rects)
            {
                int x1 = rect[0];
                int y1 = rect[1];
                int x2 = rect[2];
                int y2 = rect[3];
                int width = x2 - x1 + 1;
                int height = y2 - y1 + 1;
                int size = width * height;
                total_size += size;
                total_sizes.push_back(total_size);
            }
        }

        vector<int> pick()
        {
            int which_point = rand() % total_sizes[total_sizes.size() - 1];
            int which_rect = upper_bound(total_sizes.begin(), total_sizes.end(), which_point) - total_sizes.begin() - 1;
            int which_point_within_rect = which_point - total_sizes[which_rect];
            int x1 = rects[which_rect][0];
            int y1 = rects[which_rect][1];
            int x2 = rects[which_rect][2];
            int y2 = rects[which_rect][3];
            int width = x2 - x1 + 1;
            int height = y2 - y1 + 1;
            int which_row = which_point_within_rect / width;
            int which_col = which_point_within_rect % width;
            vector<int> s;
            s.push_back(x1 + which_col);
            s.push_back(y1 + which_row);
            return s;
        }
    };
};

using namespace _LEET_RANDOM_POINT_IN_NON_OVERLAPPING_RECTANGLES;

int LEET_RANDOM_POINT_IN_NON_OVERLAPPING_RECTANGLES()
{
    vector<vector<int>> rects(1, vector<int>(4));
    rects[0][0] = 1;
    rects[0][1] = 1;
    rects[0][2] = 5;
    rects[0][3] = 5;
    Solution s(rects);
    for (int i = 0; i < 3; i++)
    {
        vector<int> point = s.pick();
        cout << point[0] << ", " << point[1] << endl;
    }
    
    return 0;
}