#include "stdafx.h"

// https://leetcode.com/problems/gas-station/

#include "LEET_GAS_STATION.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

namespace _LEET_GAS_STATION
{
    class Solution
    {
    public:
        int canCompleteCircuit(vector<int>& gas, vector<int>& cost)
        {
            int size = gas.size();

            int tank = 0;
            int loop = 0;
            int start = 0;
            int position = 0;
            while (true)
            {
                tank += gas[position];
                tank -= cost[position];
                position++;
                if (position == size)
                {
                    loop++;
                    position = 0;
                }
                if (loop == 2)
                {
                    return -1;
                }
                if (tank < 0)
                {
                    start = position;
                    tank = 0;
                }
                else
                {
                    if (position == start)
                    {
                        return start;
                    }
                }
            }
        }
    };
};

using namespace _LEET_GAS_STATION;

int LEET_GAS_STATION()
{
    int gas[] =  { 2, 4 };
    int cost[] = { 3, 4 };
    Solution s;
    cout << s.canCompleteCircuit(vector<int>(gas, gas + _countof(gas)), vector<int>(cost, cost + _countof(cost))) << endl;
    return 0;
}