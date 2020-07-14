#include "stdafx.h"

// https://leetcode.com/problems/angle-between-hands-of-a-clock/

#include "LEET_ANGLE_BETWEEN_HANDS_OF_A_CLOCK.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_ANGLE_BETWEEN_HANDS_OF_A_CLOCK
{
    class Solution
    {
    public:
        double angleClock(int hour, int minutes)
        {
            hour = hour % 12;
            int h = hour * 60 + minutes;
            int m = minutes * 12;
            int d = abs(h - m);
            if (d > 360)
            {
                d = 720 - d;
            }
            return d / 2.0;
        }
    };
};

using namespace _LEET_ANGLE_BETWEEN_HANDS_OF_A_CLOCK;

int LEET_ANGLE_BETWEEN_HANDS_OF_A_CLOCK()
{
    Solution solution;
    cout << solution.angleClock(12, 30) << endl;
    return 0;
}