#include "stdafx.h"

// https://leetcode.com/problems/reverse-bits/

#include "LEET_REVERSE_BITS.h"

#include <vector>
#include <set>
#include <map>
#include <iostream>
#include <stdint.h>

using namespace std;

namespace _LEET_REVERSE_BITS
{
    class Solution
    {
    public:
        uint32_t reverseBits(uint32_t n)
        {
            uint32_t result = 0;
            for (int i = 0; i < 32; i++)
            {
                result = result << 1;
                result = result | (n & 1);
                n = n >> 1;
            }
            return result;
        }
    };
};

using namespace _LEET_REVERSE_BITS;

int LEET_REVERSE_BITS()
{
    Solution solution;
    cout << solution.reverseBits(43261596) << endl;
    return 0;
}