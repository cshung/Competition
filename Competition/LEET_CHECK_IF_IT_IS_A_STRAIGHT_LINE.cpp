#include "stdafx.h"

// https://leetcode.com/problems/check-if-it-is-a-straight-line/

#include "LEET_CHECK_IF_IT_IS_A_STRAIGHT_LINE.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_CHECK_IF_IT_IS_A_STRAIGHT_LINE
{
    class Solution
    {
    private:
        int gcd(int x, int y)
        {
            if (x < 0)
            {
                return gcd(-x, y);
            }
            if (y < 0)
            {
                return gcd(x, -y);
            }
            if (y > x)
            {
                return gcd(y, x);
            }
            if (x == y)
            {
                return x;
            }
            if (x % y == 0)
            {
                return y;
            }
            return gcd(y, x % y);
        }
    public:
        bool checkStraightLine(vector<vector<int>>& coordinates)
        {
            if (coordinates.size() < 3)
            {
                return true;
            }
            int dx = coordinates[1][0] - coordinates[0][0];
            int dy = coordinates[1][1] - coordinates[0][1];
            if (dx == 0)
            {
                for (int i = 0; i < coordinates.size(); i++)
                {
                    if (coordinates[i][0] != coordinates[0][0])
                    {
                        return false;
                    }
                }
                return true;
            }
            else if (dy == 0)
            {
                for (int i = 0; i < coordinates.size(); i++)
                {
                    if (coordinates[i][1] != coordinates[0][1])
                    {
                        return false;
                    }
                }
                return true;
            }
            else
            {
                int d = gcd(dx, dy);
                dx = dx / d;
                dy = dy / d;
                for (int i = 2; i < coordinates.size(); i++)
                {
                    int mdx = coordinates[i][0] - coordinates[0][0];
                    int mdy = coordinates[i][1] - coordinates[0][1];
                    if (mdx % dx != 0)
                    {
                        return false;
                    }
                    if (mdy % dy != 0)
                    {
                        return false;
                    }
                    if (mdx / dx != mdy / dy)
                    {
                        return false;
                    }
                }
                return true;
            }
        }
    };
};

using namespace _LEET_CHECK_IF_IT_IS_A_STRAIGHT_LINE;

int LEET_CHECK_IF_IT_IS_A_STRAIGHT_LINE()
{
    Solution solution;
    vector<vector<int>> coordinates;
    vector<int> one;
    one.push_back(1);
    one.push_back(2);
    vector<int> two;
    two.push_back(2);
    two.push_back(3);
    vector<int> three;
    three.push_back(3);
    three.push_back(4);
    vector<int> four;
    four.push_back(4);
    four.push_back(5);
    vector<int> five;
    five.push_back(5);
    five.push_back(6);
    vector<int> six;
    six.push_back(6);
    six.push_back(7);
    coordinates.push_back(one);
    coordinates.push_back(two);
    coordinates.push_back(three);
    coordinates.push_back(four);
    coordinates.push_back(five);
    coordinates.push_back(six);
    cout << solution.checkStraightLine(coordinates) << endl;
    return 0;
}