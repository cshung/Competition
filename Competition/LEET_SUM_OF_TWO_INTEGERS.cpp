#include "stdafx.h"

// https://leetcode.com/problems/sum-of-two-integers/

#include "LEET_SUM_OF_TWO_INTEGERS.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_SUM_OF_TWO_INTEGERS
{
    class Solution {
    public:
        int getSum(int a, int b)
        {
            int result = 0;
            int carry = 0;
            int mask = 1;
            int bit1;
            int bit2;

#define LINE \
            bit1 = a & mask;                                                                                                          \
            bit2 = b & mask;                                                                                                          \
            if (bit1 != 0 && bit2 == 0 && carry == 0 || bit1 == 0 && bit2 != 0 && carry == 0 || bit1 == 0 && bit2 == 0 && carry != 0) \
            {                                                                                                                         \
                result |= mask; carry = 0;                                                                                            \
            }                                                                                                                         \
            else if (bit1 != 0 && bit2 != 0 && carry == 0 || bit1 != 0 && bit2 == 0 && carry == bit1 == 0 && bit2 != 0 && carry != 0) \
            {                                                                                                                         \
                carry = 1;                                                                                                            \
            }                                                                                                                         \
            else if (bit1 != 0 && bit2 != 0 && carry != 0)                                                                            \
            {                                                                                                                         \
                result |= mask; carry = 1;                                                                                            \
            }                                                                                                                         \
            mask = mask << 1;                                                                                                         \

            LINE LINE LINE LINE LINE LINE LINE LINE
            LINE LINE LINE LINE LINE LINE LINE LINE
            LINE LINE LINE LINE LINE LINE LINE LINE
            LINE LINE LINE LINE LINE LINE LINE LINE

            return result;
        }
    };
};

using namespace _LEET_SUM_OF_TWO_INTEGERS;

int LEET_SUM_OF_TWO_INTEGERS()
{
    Solution solution;
    cout << solution.getSum(32032, 2132) << " " << 32032 + 2132 << endl;

    return 0;
}