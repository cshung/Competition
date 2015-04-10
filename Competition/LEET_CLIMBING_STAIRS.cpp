#include "stdafx.h"

// https://leetcode.com/problems/climbing-stairs/

#include "LEET_CLIMBING_STAIRS.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_CLIMBING_STAIRS
{
    class Solution
    {
    public:
        int climbStairs(int n)
        {
            if (n == 0 || n == 1)
            {
                return 1;
            }
            else
            {
                int a = 1;
                int b = 1;
                int c = 0;
                for (int i = 2; i <= n; i++)
                {
                    c = a + b;
                    a = b;
                    b = c;
                }

                return c;
            }
        }
    };
};

using namespace _LEET_CLIMBING_STAIRS;

int LEET_CLIMBING_STAIRS()
{
    Solution solution;
    for (int i = 1; i <= 10; i++)
    {
        cout << solution.climbStairs(i) << endl;
    }
    return 0;
}