#include "stdafx.h"

// https://leetcode.com/problems/rectangle-area-ii

#include "LEET_RECTANGLE_AREA_II.h"
#include <map>
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_RECTANGLE_AREA_II
{
    class Solution
    {
    public:
        int rectangleArea(vector<vector<int>>& rectangles)
        {
            int n = rectangles.size();
            long long result = 0;
            vector<int> x_events;
            vector<int> y_events;
            vector<bool> active;
            x_events.resize(n * 2);
            y_events.resize(n * 2);
            active.resize(n);
            for (int i = 0; i < rectangles.size(); i++)
            {
                // +ve means starting edge, -ve means ending edge
                // rectangle index offset by 1
                x_events[i * 2 + 0] = (i + 1);
                x_events[i * 2 + 1] = -(i + 1);
                y_events[i * 2 + 0] = (i + 1);
                y_events[i * 2 + 1] = -(i + 1);
                active[i] = false;
            }
            sort(x_events.begin(), x_events.end(), [&](int a, int b)
            {
                int a_x = a > 0 ? rectangles[a - 1][0] : rectangles[-a - 1][2];
                int b_x = b > 0 ? rectangles[b - 1][0] : rectangles[-b - 1][2];
                return a_x < b_x;
            });
            sort(y_events.begin(), y_events.end(), [&](int a, int b)
            {
                int a_y = a > 0 ? rectangles[a - 1][1] : rectangles[-a - 1][3];
                int b_y = b > 0 ? rectangles[b - 1][1] : rectangles[-b - 1][3];
                return a_y < b_y;
            });

            bool first = true;
            int last_x = -10000;
            for (int i = 0; i < n * 2; i++)
            {
                int ex = x_events[i];
                int rx = ex > 0 ? ex - 1 : -ex - 1;
                int x = ex > 0 ? rectangles[rx][0] : rectangles[rx][2];
                if (!first)
                {
                    if (x != last_x)
                    {
                        long long width = x - last_x;
                        long long height = 0;
                        int active_count = 0;
                        int last_y = -10000;
                        for (int j = 0; j < n * 2; j++)
                        {
                            int ey = y_events[j];
                            int ry = ey > 0 ? ey - 1 : -ey - 1;
                            int y = ey > 0 ? rectangles[ry][1] : rectangles[ry][3];
                            if (ey > 0 && active[ry])
                            {
                                if (active_count == 0)
                                {
                                    last_y = y;
                                }
                                active_count++;
                            }
                            else if (ey < 0 && active[ry])
                            {
                                active_count--;
                                if (active_count == 0)
                                {
                                    height += (y - last_y);
                                }
                            }
                        }
                        result += width * height;
                    }
                }
                active[rx] = ex > 0;
                first = false;
                last_x = x;
            }
            return (int)(result % (1000000007));
        }
    };
};

using namespace _LEET_RECTANGLE_AREA_II;

int LEET_RECTANGLE_AREA_II()
{
    Solution solution;
    int rect1_array[] = { 0, 0, 2, 2 };
    int rect2_array[] = { 1, 0, 2, 3 };
    int rect3_array[] = { 1, 0, 3, 1 };
    vector<int> rect1(rect1_array, rect1_array + _countof(rect1_array));
    vector<int> rect2(rect2_array, rect2_array + _countof(rect2_array));
    vector<int> rect3(rect3_array, rect3_array + _countof(rect3_array));
    vector<vector<int>> rectangles;
    rectangles.push_back(rect1);
    rectangles.push_back(rect2);
    rectangles.push_back(rect3);
    cout << solution.rectangleArea(rectangles) << endl;
    return 0;
}