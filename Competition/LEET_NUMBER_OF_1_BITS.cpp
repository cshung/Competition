#include "stdafx.h"

// https://leetcode.com/problems/number-of-1-bits/

#include "LEET_NUMBER_OF_1_BITS.h"

#include <vector>
#include <set>
#include <map>
#include <iostream>
#include <stdint.h>

using namespace std;

namespace _LEET_NUMBER_OF_1_BITS
{
    class Solution {
    public:
        int hammingWeight(uint32_t n) {
            int weight = 0;
            for (int b = 0; b < 32; b++)
            {
                weight += n & 1;
                n = n >> 1;
            }

            return weight;
        }
    };
};

using namespace _LEET_NUMBER_OF_1_BITS;

int LEET_NUMBER_OF_1_BITS()
{
    Solution solution;
    cout << solution.hammingWeight(0) << endl;
    cout << solution.hammingWeight(1) << endl;
    cout << solution.hammingWeight(3) << endl;
    uint32_t data = 0;
    data--;
    cout << solution.hammingWeight(data) << endl;
    return 0;
}