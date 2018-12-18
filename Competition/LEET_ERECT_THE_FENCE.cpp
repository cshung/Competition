#include "stdafx.h"

// https://leetcode.com/problems/erect-the-fence/

#include "LEET_ERECT_THE_FENCE.h"
#include <stack>
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_ERECT_THE_FENCE
{
    struct Point
    {
        int x;
        int y;
        Point() : x(0), y(0) {}
        Point(int a, int b) : x(a), y(b) {}
    };
    
    class Solution
    {
    public:
        vector<Point> outerTrees(vector<Point>& points)
        {
            if (points.size() < 4)
            {
                return points;
            }            
            for (int i = 1; i < points.size(); i++)
            {
                if (points[i].x < points[0].x || (points[i].x == points[0].x) && (points[i].y < points[0].y)) {
                    swap(points[i], points[0]);
                }
            }

            vector<Point> answer;
            answer.push_back(points[0]);
            while (true)
            {
                Point& basePoint = answer[answer.size() - 1];
                // In the first iteration, we know that it is impossible for the hull to end, so we pick index 1 as the candidate and start the loop from 2
                // In any other iterations, it is possible that the convex hull ends, so we use 0 as the nextIndex and loop through all the points that are not on the hull
                int nextIndex = (answer.size() == 1) ? 1 : 0;
                int start = answer.size() + nextIndex;

                for (int testIndex = start; testIndex < points.size(); testIndex++)
                {
                    Point& nextPoint = points[nextIndex];
                    Point& testPoint = points[testIndex];
                    bool take = false;
                    int cross = (nextPoint.x - basePoint.x) * (testPoint.y - basePoint.y) - (nextPoint.y - basePoint.y) * (testPoint.x - basePoint.x);
                    if (cross > 0)
                    {
                        take = true;
                    }
                    else if (cross == 0)
                    {
                        // If we found collinear points in the set of points that are not added to the hull, they are either all added to the hull or not at all.
                        // so we picked the one with least distance to keep it in the hull order.
                        //
                        // The statement above is always true, but the colinear points we just found might not all come from the points not added to the hull.
                        // The only special case when nextIndex = 0. In that case, we should always set take = true to ensure this point (and any other points 
                        // also colinear with points[0]) to be chosen in the hull.
                        int next_base_squared_dist = (nextPoint.x - basePoint.x) * (nextPoint.x - basePoint.x) + (nextPoint.y - basePoint.y) * (nextPoint.y - basePoint.y);
                        int test_base_squared_dist = (testPoint.x - basePoint.x) * (testPoint.x - basePoint.x) + (testPoint.y - basePoint.y) * (testPoint.y - basePoint.y);
                        if (nextIndex == 0 || next_base_squared_dist > test_base_squared_dist)
                        {
                            take = true;
                        }
                    }
                    if (take)
                    {
                        nextIndex = testIndex;
                    }
                }
                if (nextIndex == 0)
                {
                    break;
                }
                answer.push_back(points[nextIndex]);
                swap(points[answer.size() - 1], points[nextIndex]);
            }

            return answer;
        }
    };
};

using namespace _LEET_ERECT_THE_FENCE;

int LEET_ERECT_THE_FENCE()
{
    Solution solution;
    vector<Point> points;
    points.resize(9);
    points[0].x = 0; points[0].y = 0;
    points[1].x = 0; points[1].y = 1;
    points[2].x = 0; points[2].y = 2;
    points[3].x = 1; points[3].y = 2;
    points[4].x = 2; points[4].y = 2;
    points[5].x = 3; points[5].y = 2;
    points[6].x = 3; points[6].y = 1;
    points[7].x = 3; points[7].y = 0;
    points[8].x = 2; points[8].y = 0;
    vector<Point> answer = solution.outerTrees(points);
    for (Point p : answer)
    {
        cout << p.x << "," << p.y << endl;
    }

    return 0;
}