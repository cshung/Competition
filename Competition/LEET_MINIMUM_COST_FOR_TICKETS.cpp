#include "stdafx.h"

// https://leetcode.com/problems/minimum-cost-for-tickets/

#include "LEET_MINIMUM_COST_FOR_TICKETS.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_MINIMUM_COST_FOR_TICKETS
{
    class Solution
    {
    public:
        int mincostTickets(vector<int>& days, vector<int>& costs)
        {
            vector<int> mincosts(366, 0);
            vector<bool> travel(366, false);
            for (auto day : days)
            {
                travel[day] = true;
            }
            for (int day = 1; day <= 365; day++)
            {
                int cost = costs[0] + mincosts[day - 1];
                cost = min(cost, costs[1] + mincosts[day - 1]);
                cost = min(cost, costs[2] + mincosts[day - 1]);
                if (day - 7 >= 0)
                {
                    cost = min(cost, costs[1] + mincosts[day - 7]);
                    cost = min(cost, costs[2] + mincosts[day - 7]);
                }
                if (day - 30 >= 0)
                {
                    cost = min(cost, costs[2] + mincosts[day - 30]);
                }
                if (!travel[day])
                {
                    cost = min(cost, mincosts[day - 1]);
                }
                mincosts[day] = cost;
            }
            return mincosts[365];
        }
    };
};

using namespace _LEET_MINIMUM_COST_FOR_TICKETS;

int LEET_MINIMUM_COST_FOR_TICKETS()
{
    Solution solution;
    int days_array[] = { 1, 4, 6, 7, 8, 20 };
    int costs_array[] = { 2, 7, 15 };
    vector<int> days(days_array, days_array + _countof(days_array));
    vector<int> costs(costs_array, costs_array + _countof(costs_array));
    cout << solution.mincostTickets(days, costs) << endl;
    return 0;
}