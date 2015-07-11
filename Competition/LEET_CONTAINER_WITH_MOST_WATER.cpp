#include "stdafx.h"

// https://leetcode.com/problems/container-with-most-water/

#include "LEET_CONTAINER_WITH_MOST_WATER.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_CONTAINER_WITH_MOST_WATER
{
    class Solution
    {
    public:
        int maxArea(vector<int>& height)
        {
            if (height.size() < 2)
            {
                // There is no container!
                return - 1;
            }

            int bestAreaSoFar = -1;
            for (unsigned int i = 0; i < height.size(); i++)
            {
                for (unsigned int j = i + 1; j < height.size(); j++)
                {
                    int area = (j - i) * min(height[j], height[i]);
                    if (area > bestAreaSoFar) 
                    {
                        bestAreaSoFar = area;
                    }
                }
            }

            return bestAreaSoFar;
        }
    };
};

using namespace _LEET_CONTAINER_WITH_MOST_WATER;

int LEET_CONTAINER_WITH_MOST_WATER()
{
    Solution solution;
    int case1[] = { 1, 2, 3, 4, 5, 6 };
    int case2[] = { 6, 5, 4, 3, 2, 1 };
    int case3[] = { 4, 3, 2, 4 };
    int case4[] = { 4, 3, 2, 5 };
    int case5[] = { 4, 3, 2, 4, 4, 3, 2, 5 };
    int case6[] = { 4, 3, 2, 5, 4, 3, 2, 4 };
    int case7[] = { 1, 2, 1 };
    cout << (solution.maxArea(vector<int>(case1, case1 + _countof(case1))) == 5) << endl;
    cout << (solution.maxArea(vector<int>(case2, case2 + _countof(case2))) == 5) << endl;
    cout << (solution.maxArea(vector<int>(case3, case3 + _countof(case3))) == 12) << endl;
    cout << (solution.maxArea(vector<int>(case4, case4 + _countof(case4))) == 12) << endl;
    cout << (solution.maxArea(vector<int>(case5, case5 + _countof(case5))) == 12) << endl;
    cout << (solution.maxArea(vector<int>(case6, case6 + _countof(case6))) == 12) << endl;
    cout << (solution.maxArea(vector<int>(case7, case7 + _countof(case7))) == 1) << endl;
    return 0;
}
