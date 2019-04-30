#include "stdafx.h"

// https://leetcode.com/problems/reach-a-number

#include "LEET_REACH_A_NUMBER.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_REACH_A_NUMBER
{
    class Solution
    {
    public:
        int reachNumber(int target)
        {
            if (target < 0)
            {
                target = -target;
            }
            int64_t l = 0;
            int64_t r = target;
            while (true)
            {
                int64_t m = (l + r) / 2;
                int64_t probe = m * (m + 1) / 2;
                if (probe >= target)
                {
                    r = m;
                }
                else
                {
                    l = m;
                }
                if (r - l == 1)
                {
                    do
                    {
                        probe = r * (r + 1) / 2;
                        if (probe % 2 == target % 2)
                        {
                            return (int)r;
                        }
                        else
                        {
                            r++;
                        }
                    } while (true);
                }
            }

        }
    };
};

using namespace _LEET_REACH_A_NUMBER;

int LEET_REACH_A_NUMBER()
{
    Solution solution;
    cout << solution.reachNumber(3) << endl;
    cout << solution.reachNumber(2) << endl;
    return 0;
}