#include "stdafx.h"

// https://leetcode.com/contest/2/problems/perfect-rectangle/

#include "LEET_PERFECT_RECTANGLE.h"
#include <map>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_PERFECT_RECTANGLE
{
    class Solution
    {
    public:
        int area(vector<int>& rectangle)
        {
            return (rectangle[2] - rectangle[0]) * (rectangle[3] - rectangle[1]);
        }

        bool overlap(vector<int>& rectangle1, vector<int>& rectangle2)
        {
            if (rectangle1[2] <= rectangle2[0])
            {
                return false;
            }
            if (rectangle2[2] <= rectangle1[0])
            {
                return false;
            }
            if (rectangle1[3] <= rectangle2[1])
            {
                return false;
            }
            if (rectangle2[3] <= rectangle1[1])
            {
                return false;
            }
            return true;
        }

        bool isRectangleCover(vector<vector<int>>& rectangles)
        {
            int total_area = 0;
            int min_x = rectangles[0][0];
            int min_y = rectangles[0][1];
            int max_x = rectangles[0][2];
            int max_y = rectangles[0][3];
            for (size_t i = 0; i < rectangles.size(); i++)
            {
                total_area += area(rectangles[i]);
                min_x = min(min_x, rectangles[i][0]);
                min_y = min(min_y, rectangles[i][1]);
                max_x = max(max_x, rectangles[i][2]);
                max_y = max(max_y, rectangles[i][3]);
            }
            int expected_area = (max_x - min_x) * (max_y - min_y);
            if (total_area != expected_area)
            {
                return false;
            }
            for (size_t i = 0; i < rectangles.size(); i++)
            {
                for (size_t j = i + 1; j < rectangles.size(); j++)
                {
                    if (overlap(rectangles[i], rectangles[j]))
                    {
                        return false;
                    }
                }
            }

            return true;
        }
    };
};

using namespace _LEET_PERFECT_RECTANGLE;

int LEET_PERFECT_RECTANGLE()
{
    // Not a great approach, quadratic time is not allowed
    Solution solution;
    int r[5][4] = { {1, 1, 3, 3},{3, 1, 4, 2},{3, 2, 4, 4},{1, 3, 2, 4},{2, 3, 3, 4} };
    vector<vector<int>> rectangles;
    rectangles.push_back(vector<int>(r[0], r[0] + 4));
    rectangles.push_back(vector<int>(r[1], r[1] + 4));
    rectangles.push_back(vector<int>(r[2], r[2] + 4));
    rectangles.push_back(vector<int>(r[3], r[3] + 4));
    rectangles.push_back(vector<int>(r[4], r[4] + 4));
    cout << solution.isRectangleCover(rectangles) << endl;
    return 0;
}
