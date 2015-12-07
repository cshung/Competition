#include "stdafx.h"

// https://leetcode.com/problems/burst-balloons/

#include "LEET_BURST_BALLOONS.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_BURST_BALLOONS
{
    class Solution
    {
    public:

        int maxCoins(vector<int>& nums)
        {
            // Do something
            return -1;
        }
    };
};

using namespace _LEET_BURST_BALLOONS;

int LEET_BURST_BALLOONS()
{
    int case1[] = { 3, 1, 5, 8 };
    Solution solution;
    cout << solution.maxCoins(vector<int>(case1, case1 + _countof(case1))) << endl;
    return 0;
}