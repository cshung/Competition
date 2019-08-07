#include "stdafx.h"

// https://leetcode.com/problems/meeting-rooms-ii/

#include "LEET_MEETING_ROOMS_II.h"
#include <map>
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_MEETING_ROOMS_II
{
    class Solution
    {
    public:
        int minMeetingRooms(vector<vector<int>>& intervals)
        {
            vector<int> events;
            for (auto interval : intervals)
            {
                events.push_back(interval[0]);
                events.push_back(-interval[1]);
            }
            sort(events.begin(), events.end(), [](const int a, const int b)
                {
                    int A = a > 0 ? a : -a;
                    int B = b > 0 ? b : -b;
                    if (A < B)
                    {
                        return true;
                    }
                    else if (A > B)
                    {
                        return false;
                    }
                    else if (a < 0 && b > 0)
                    {
                        return true;
                    }
                    else if (b < 0 && a > 0)
                    {
                        return false;
                    }
                    else
                    {
                        return true;
                    }
                });
            int room = 0;
            int answer = 0;
            for (auto event : events)
            {
                if (event >= 0)
                {
                    room++;
                    if (room > answer)
                    {
                        answer = room;
                    }
                }
                else
                {
                    room--;
                }
            }
            return answer;
        }
    };
};

using namespace _LEET_MEETING_ROOMS_II;

int LEET_MEETING_ROOMS_II()
{
    Solution solution;
    vector<vector<int>> test;
    test.resize(3);
    test[0].push_back(0);
    test[0].push_back(30);
    test[1].push_back(5);
    test[1].push_back(10);
    test[2].push_back(15);
    test[2].push_back(20);
    cout << solution.minMeetingRooms(test) << endl;
    return 0;
}