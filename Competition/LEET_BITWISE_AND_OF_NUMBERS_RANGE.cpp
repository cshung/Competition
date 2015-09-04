#include "stdafx.h"

// https://leetcode.com/problems/bitwise-and-of-numbers-range/

#include "LEET_BITWISE_AND_OF_NUMBERS_RANGE.h"
#include <stack>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_BITWISE_AND_OF_NUMBERS_RANGE
{
    class Solution {
    private:
        bool oneOnly(int m, int n, int d, int mask)
        {
            if ((n - m + 1) > mask)
            {
                return false;
            }
            else
            {
                int m_masked = m & mask;
                int n_masked = n & mask;
                return (m_masked != 0 && n_masked != 0);
            }
        }
    public:
        int rangeBitwiseAnd(int m, int n)
        {
            int result = 0;
            int mask = 1;
            for (int d = 0; d < 32; d++)
            {
                if (oneOnly(m, n, d, mask))
                {
                    result += mask;
                }
                mask = mask << 1;
            }
            return result;
        }
    };
};

using namespace _LEET_BITWISE_AND_OF_NUMBERS_RANGE;

int LEET_BITWISE_AND_OF_NUMBERS_RANGE()
{
    Solution solution;
    cout << (solution.rangeBitwiseAnd(0, 0) == 0) << endl;
    cout << (solution.rangeBitwiseAnd(1, 1) == 1) << endl;
    cout << (solution.rangeBitwiseAnd(5, 7) == 4) << endl;
    return 0;
}

