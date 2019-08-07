#include "stdafx.h"

// https://leetcode.com/problems/minimum-number-of-arrows-to-burst-balloons/

#include "LEET_MINIMUM_NUMBER_OF_ARROWS_TO_BURST_BALLOONS.h"
#include <map>
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_MINIMUM_NUMBER_OF_ARROWS_TO_BURST_BALLOONS
{
    struct event
    {
        int x;
        bool enter;
        int index;
    };

    class Solution
    {
    public:
        int findMinArrowShots(vector<vector<int>>& points)
        {
            vector<event> events;
            vector<bool> bursted;
            for (int i = 0; i < points.size(); i++)
            {
                event e;
                e.x = points[i][0];
                e.enter = true;
                e.index = i;
                events.push_back(e);
                e.x = points[i][1];
                e.enter = false;
                e.index = i;
                events.push_back(e);
                bursted.push_back(false);
            }
            sort(events.begin(), events.end(), [](const event& left, const event& right)
                {
                    if (left.x < right.x)
                    {
                        return true;
                    }
                    else if (left.x == right.x && left.enter && !right.enter)
                    {
                        return true;
                    }
                    else
                    {
                        return false;
                    }
                }
            );
            vector<int> seen;
            int count = 0;
            for (auto event : events)
            {
                if (!bursted[event.index])
                {
                    if (event.enter)
                    {
                        seen.push_back(event.index);
                    }
                    else
                    {
                        count++;
                        for (auto s : seen)
                        {
                            bursted[s] = true;
                        }
                        seen.clear();
                    }
                }
            }
            return count;
        }
    };

};

using namespace _LEET_MINIMUM_NUMBER_OF_ARROWS_TO_BURST_BALLOONS;

int LEET_MINIMUM_NUMBER_OF_ARROWS_TO_BURST_BALLOONS()
{
    Solution solution;
    vector<vector<int>> test;
    test.resize(4);
    test[0].push_back(10);
    test[0].push_back(16);
    test[1].push_back(2);
    test[1].push_back(8);
    test[2].push_back(1);
    test[2].push_back(6);
    test[3].push_back(7);
    test[3].push_back(12);
    cout << solution.findMinArrowShots(test) << endl;
    return 0;
}