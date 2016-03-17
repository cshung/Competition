#include "stdafx.h"

// https://leetcode.com/problems/max-points-on-a-line/

#include "LEET_MAX_POINTS_ON_A_LINE.h"
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_MAX_POINTS_ON_A_LINE
{
    struct Point
    {
        int x;
        int y;
        Point() : x(0), y(0) {}
        Point(int a, int b) : x(a), y(b) {}
    };

    struct SlantedLine
    {
    public:
        int slope_numerator;
        int slope_denominator;
        int intercept_numerator;
        int intercept_denominator;
    };

    struct SlantedLineHash
    {
        size_t operator()(const SlantedLine& k) const
        {
            return k.slope_numerator ^ k.slope_denominator ^ k.intercept_numerator ^ k.intercept_denominator;
        }
    };

    struct SlantedLineEqual
    {
        size_t operator()(const SlantedLine& line1, const SlantedLine& line2) const
        {
            return (line1.slope_numerator == line2.slope_numerator) && (line1.slope_denominator == line2.slope_denominator) && (line1.intercept_numerator == line2.intercept_numerator) && (line1.intercept_denominator == line2.intercept_denominator);
        }
    };

    class Solution
    {
    public:
        int maxPoints(vector<Point>& points)
        {
            if (points.size() == 0)
            {
                return 0;
            }

            unordered_map<SlantedLine, unordered_set<int>, SlantedLineHash, SlantedLineEqual> slantedLineToPointsMap;
            unordered_map<int, unordered_set<int>> verticalLineToPointsMap;
            for (size_t i = 0; i < points.size(); i++)
            {
                for (size_t j = i + 1; j < points.size(); j++)
                {
                    int x1 = points[i].x;
                    int y1 = points[i].y;
                    int x2 = points[j].x;
                    int y2 = points[j].y;
                    
                    if (x1 == x2)
                    {
                        unordered_map<int, unordered_set<int>>::iterator probe = verticalLineToPointsMap.find(x1);
                        if (probe == verticalLineToPointsMap.end())
                        {
                            unordered_set<int> points;
                            points.insert(i);
                            points.insert(j);
                            verticalLineToPointsMap.insert(pair<int, unordered_set<int>>(x1, points));
                        }
                        else
                        {
                            probe->second.insert(i);
                            probe->second.insert(j);
                        }
                    }
                    else
                    {
                        int slope_numerator = y2 - y1;
                        int slope_denominator = x2 - x1;
                        int intercept_numerator = y1 * x2 - x1 * y2;
                        int intercept_denominator = x2 - x1;
                        simplify_fraction(&slope_numerator, &slope_denominator);
                        simplify_fraction(&intercept_numerator, &intercept_denominator);
                        SlantedLine line;
                        line.slope_numerator = slope_numerator;
                        line.slope_denominator = slope_denominator;
                        line.intercept_numerator = intercept_numerator;
                        line.intercept_denominator = intercept_denominator;
                        unordered_map<SlantedLine, unordered_set<int>, SlantedLine, SlantedLineEqual>::iterator probe = slantedLineToPointsMap.find(line);
                        if (probe == slantedLineToPointsMap.end())
                        {
                            unordered_set<int> points;
                            points.insert(i);
                            points.insert(j);
                            slantedLineToPointsMap.insert(pair<SlantedLine, unordered_set<int>>(line, points));
                        }
                        else
                        {
                            probe->second.insert(i);
                            probe->second.insert(j);
                        }
                    }
                }
            }

            size_t maxPoints = 0;
            for (unordered_map<int, unordered_set<int>>::iterator i = verticalLineToPointsMap.begin(); i != verticalLineToPointsMap.end(); i++)
            {
                maxPoints = max(maxPoints, i->second.size());
            }
            for (unordered_map<SlantedLine, unordered_set<int>, SlantedLine, SlantedLineEqual>::iterator i = slantedLineToPointsMap.begin(); i != slantedLineToPointsMap.end(); i++)
            {
                maxPoints = max(maxPoints, i->second.size());
            }

            return maxPoints;
        }
    private:
        void simplify_fraction(int* numerator, int* denominator)
        {
            int common_factor = gcd(*numerator, *denominator);
            *numerator /= common_factor;
            *denominator /= common_factor;
            if (*denominator < 0)
            {
                *numerator *= -1;
                *denominator *= -1;
            }
        }

        int gcd(int a, int b)
        {
            if (a < 0)
            {
                return gcd(-a, b);
            }
            else if (b < 0)
            {
                return gcd(a, -b);
            }
            else if (b > a)
            {
                return gcd(b, a);
            }
            else
            {
                if (b == 0)
                {
                    return a;
                }
                else
                {
                    return gcd(b, a % b);
                }
            }
        }
    };
};

using namespace _LEET_MAX_POINTS_ON_A_LINE;

int LEET_MAX_POINTS_ON_A_LINE()
{
    Solution solution;
    return 0;
}