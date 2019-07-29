#include "stdafx.h"

// https://leetcode.com/problems/minimum-area-rectangle/

#include "LEET_MINIMUM_AREA_RECTANGLE.h"
#include <map>
#include <set>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_MINIMUM_AREA_RECTANGLE
{
    class Solution
    {
    public:
        int minAreaRect(vector<vector<int>>& points)
        {
            set<pair<int, int>> map;
            for (int i = 0; i < points.size(); i++)
            {
                map.insert(make_pair(points[i][0], points[i][1]));
            }
            int answer = -1;
            for (int i = 0; i < points.size(); i++)
            {
                for (int j = i + 1; j < points.size(); j++)
                {
                    int x1 = points[i][0];
                    int y1 = points[i][1];
                    int x2 = points[j][0];
                    int y2 = points[j][1];

                    if (x1 != x2 && y1 != y2 && (map.find(make_pair(x1, y2)) != map.end()) && (map.find(make_pair(x2, y1)) != map.end()))
                    {
                        int w = x1 - x2;
                        int h = y1 - y2;
                        int area = w * h;
                        if (area < 0)
                        {
                            area = -area;
                        }
                        if (answer == -1 || area < answer)
                        {
                            answer = area;
                        }
                    }
                }
            }
            if (answer == -1)
            {
                return 0;
            }
            else
            {
                return answer;
            }
        }
    };
};

using namespace _LEET_MINIMUM_AREA_RECTANGLE;

int LEET_MINIMUM_AREA_RECTANGLE()
{
    Solution solution;
    vector<vector<int>> points;
    points.resize(5);
    points[0].push_back(1);
    points[0].push_back(1);
    points[1].push_back(1);
    points[1].push_back(3);
    points[2].push_back(3);
    points[2].push_back(1);
    points[3].push_back(3);
    points[3].push_back(3);
    points[4].push_back(2);
    points[4].push_back(2);
    cout << solution.minAreaRect(points) << endl;
    return 0;
}