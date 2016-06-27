#include "stdafx.h"

// https://leetcode.com/problems/water-and-jug-problem/

#include "LEET_WATER_AND_JUG_PROBLEM.h"
#include <map>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <set>
#include <queue>
#include <string>

using namespace std;

namespace _LEET_WATER_AND_JUG_PROBLEM
{
    class Solution
    {
    public:
        int gcd(int x, int y)
        {
            if (y > x)
            {
                return gcd(y, x);
            } 
            else if (y == 0)
            {
                return x;
            }
            else
            {
                return gcd(y, x % y);
            }
        }
        bool canMeasureWater(int x, int y, int z)
        {
            if (x == 0)
            {
                return z == 0 || z == y;
            } 
            else if (y == 0)
            {
                return z == 0 || z == x;
            }
            else if (z > x + y)
            {
                return false;
            }
            else
            {
                return (z % gcd(x, y)) == 0;
            }
        }
    };
};

using namespace _LEET_WATER_AND_JUG_PROBLEM;

int LEET_WATER_AND_JUG_PROBLEM()
{
    Solution solution;
    cout << solution.canMeasureWater(104579, 104593, 12444) << endl;
    return 0;
}