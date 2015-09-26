#include "stdafx.h"

// https://leetcode.com/problems/powx-n/

#include "LEET_POW_X_N.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

namespace _LEET_POW_X_N
{
    class Solution
    {
    public:
        double myPow(double x, int n)
        {
            if (n == 0)
            {
                return 1;
            }
            else if (n < 0)
            {
                // -intMax cannot take negative
                return 1.0 / myPow(x, -(n + 1)) / x;
            }
            else
            {
                bool odd = (n % 2 == 1);
                double halfPower = myPow(x, n / 2);
                double halfPowerSquared = halfPower * halfPower;
                return odd ? halfPowerSquared * x : halfPowerSquared;
            }
        }
    };
};

using namespace _LEET_POW_X_N;

int LEET_POW_X_N()
{
    Solution s;
    cout << s.myPow(0.5, -2) << endl;
    cout << s.myPow(0.5, -1) << endl;
    cout << s.myPow(0.5, 0) << endl;
    cout << s.myPow(0.5, 1) << endl;
    cout << s.myPow(0.5, 2) << endl;
    return 0;
}