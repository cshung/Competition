#include "stdafx.h"

// https://leetcode.com/problems/sqrtx/

#include "LEET_SQRTX.h"
#include <stack>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_SQRTX
{
    class Solution
    {
    public:
        
        int mySqrt(int x)
        {
            if (x == 0)
            {
                return 0;
            }
            else if (x < 0)
            {
                throw 1;
            }
            double estimate = 1;
            for (int i = 0; i < 20; i++)
            {
                estimate = (estimate + x / estimate) / 2;
            }
            return (int)estimate;
        }
    };
};

using namespace _LEET_SQRTX;

int LEET_SQRTX()
{
    Solution s;
    cout << s.mySqrt(289) << endl;
    return 0;
}
