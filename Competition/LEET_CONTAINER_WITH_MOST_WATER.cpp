#include "stdafx.h"

// https://leetcode.com/problems/container-with-most-water/

#include "LEET_CONTAINER_WITH_MOST_WATER.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>

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

            unsigned int l = 0; 
            unsigned int r = height.size() - 1;
            int currentHeight = min(height[r], height[l]);
            int bestAreaSoFar = currentHeight * ( r - l );
            while (l < r)
            {
                unsigned int lSearch = l;
                unsigned int rSearch = r;
                while (lSearch < height.size() && height[lSearch] <= currentHeight)
                {
                    lSearch++;
                }
                while (rSearch > 0 && height[rSearch] <= currentHeight)
                {
                    rSearch--;
                }
                if (lSearch < rSearch)
                {
                    l = lSearch;
                    r = rSearch;
                    currentHeight = min(height[r], height[l]);
                    int areaSoFar = currentHeight * ( r - l );
                    if (areaSoFar > bestAreaSoFar)
                    {
                        bestAreaSoFar = areaSoFar;
                    }
                }
                else
                {
                    break;
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
    cout << (solution.maxArea(vector<int>(case1, case1 + _countof(case1))) == 9) << endl;
    cout << (solution.maxArea(vector<int>(case2, case2 + _countof(case2))) == 9) << endl;
    cout << (solution.maxArea(vector<int>(case3, case3 + _countof(case3))) == 12) << endl;
    cout << (solution.maxArea(vector<int>(case4, case4 + _countof(case4))) == 12) << endl;
    cout << (solution.maxArea(vector<int>(case5, case5 + _countof(case5))) == 28) << endl;
    cout << (solution.maxArea(vector<int>(case6, case6 + _countof(case6))) == 28) << endl;
    cout << (solution.maxArea(vector<int>(case7, case7 + _countof(case7))) == 2) << endl;
    return 0;
}
