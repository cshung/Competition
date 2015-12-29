#include "stdafx.h"

// https://leetcode.com/problems/bulb-switcher/

#include "LEET_BULB_SWITCHER.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_BULB_SWITCHER
{
    /*
     * Analysis:
     * For the general mth bulb, it is toggled in the nth round if n is a factor of m
     * For example, the 3 bulb is on after round 1 and off after round 3 and will never turn on again (no matter what n is)
     * That applies for all prime
     * That actually also apply for all composite with even number of factors
     * What number has odd number of factors? Squares
     * So it is really just asking how many squares are there
     */
    class Solution {
    public:
        int bulbSwitch(int n)
        {
            int count = 0;
            int k = 3;
            int s = 1;
            while (n >= s)
            {
                count++;
                s += k;
                k += 2;
            }

            return count;
        }
    };
};

using namespace _LEET_BULB_SWITCHER;

int LEET_BULB_SWITCHER()
{
    Solution solution;
    for (int i = 1; i <= 10; i++)
    {
        cout << solution.bulbSwitch(i) << endl;
    }
    return 0;
}