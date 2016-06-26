#include "stdafx.h"

// https://leetcode.com/problems/valid-perfect-square/

#include "LEET_VALID_PERFECT_SQUARE.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_VALID_PERFECT_SQUARE
{
    class Solution
    {
    public:
        bool isPerfectSquare(int num)
        {
            if (num == 0) { return true; }
            if (num == 1) { return true; }
            int exclusiveLowerBound = 0;
            int exclusiveUpperBound = num;
            while (exclusiveUpperBound - exclusiveLowerBound > 1)
            {
                // Note: this will never overflow
                // This will also always return a value strictly between the two bounds
                int mid = (exclusiveLowerBound + exclusiveUpperBound) / 2;

                // Squaring could overflow, so using 64 bit arithmetic here
                long long midl = (long long)mid;
                long long square = midl * midl;
                if (square < num)
                {
                    exclusiveLowerBound = mid;
                }
                else if (square > num)
                {
                    exclusiveUpperBound = mid;
                }
                else 
                {
                    return true;
                }
            }

            return false;
        }
    };
};

using namespace _LEET_VALID_PERFECT_SQUARE;

int LEET_VALID_PERFECT_SQUARE()
{
    Solution s;
    cout << s.isPerfectSquare(899 * 899) << endl;
    return 0;
}