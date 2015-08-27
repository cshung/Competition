#include "stdafx.h"

// https://leetcode.com/problems/divide-two-integers/

#include "LEET_DIVIDE_TWO_INTEGERS.h"
#include <map>
#include <iostream>
#include <vector>

using namespace std;

namespace _LEET_DIVIDE_TWO_INTEGERS
{
    typedef long long int64;

    class Solution {
    public:
        int64 divideHelper(int64 dividend, int64 divisor)
        {
            if (dividend < divisor)
            {
                // dividend is the remainder, if wished
                return 0;
            }
            else
            {
                int64 subtractor = divisor;
                int64 quotient = 1;
                while ((subtractor << 1) > 0 && dividend >(subtractor << 1))
                {
                    subtractor = (subtractor << 1);
                    quotient = (quotient << 1);
                }

                // At this point, we know dividend < divisor * 2
                // But in the previous iteration, we have dividend > (divisor / 2) * 2 
                // Overall, we have  divisor <= dividend < divisor * 2
                return quotient + divideHelper(dividend - subtractor, divisor);
            }
        }

        int divide(int dividend, int divisor)
        {
            int64 dividendLong = dividend;
            int64 divisorLong = divisor;

            int sign = 1;
            if (dividendLong < 0)
            { 
                sign = -sign;
                dividendLong = -dividendLong;
            }
            if (divisorLong < 0)
            {
                sign = -sign;
                divisorLong = -divisorLong;
            }
            int64 result = sign * this->divideHelper(dividendLong, divisorLong);

            int64 intMax64 = 1;
            intMax64 = intMax64 << 31;
            intMax64--;
            int intMax = (int)intMax64;

            int64 intMin64 = 1;
            intMin64 = intMin64 << 31;
            intMin64 = -intMin64;
            int intMin = (int)intMin64;

            if (result > 0)
            {
                if (result > intMax64)
                {
                    return intMax;
                }
                else
                {
                    return (int)result;
                }
            }
            else
            {
                if (result < intMin64)
                {
                    return intMin;
                }
                else
                {
                    return (int)result;
                }
            }
        }
    };
};

using namespace _LEET_DIVIDE_TWO_INTEGERS;

int LEET_DIVIDE_TWO_INTEGERS()
{
    Solution s;
    // Bug: cannot take negative of int.min
    cout << s.divide(2147483647, 1) << endl;
    cout << s.divide(2147483647, 2) << endl;
    cout << s.divide(-1010369383, (1 << 31)) << endl;
    cout << s.divide((1 << 31), -1) << endl;
    return 0;
}
