#include "stdafx.h"

// https://leetcode.com/problems/binary-number-with-alternating-bits

#include "LEET_BINARY_NUMBER_WITH_ALTERNATING_BITS.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_BINARY_NUMBER_WITH_ALTERNATING_BITS
{
    class Solution
    {
    public:
        bool hasAlternatingBits(int n)
        {
            switch (n)
            {
            case 0x00:
            case 0x01:
            case 0x02:
            case 0x05:
            case 0x0A:
            case 0x15:
            case 0x2A:
            case 0x55:
            case 0xAA:
            case 0x155:
            case 0x2AA:
            case 0x555:
            case 0xAAA:
            case 0x1555:
            case 0x2AAA:
            case 0x5555:
            case 0xAAAA:
            case 0x15555:
            case 0x2AAAA:
            case 0x55555:
            case 0xAAAAA:
            case 0x155555:
            case 0x2AAAAA:
            case 0x555555:
            case 0xAAAAAA:
            case 0x1555555:
            case 0x2AAAAAA:
            case 0x5555555:
            case 0xAAAAAAA:
            case 0x15555555:
            case 0x2AAAAAAA:
            case 0x55555555:
            case 0xAAAAAAAA:
                return true;
            default:
                return false;
            }
        }
    };
};

using namespace _LEET_BINARY_NUMBER_WITH_ALTERNATING_BITS;

int LEET_BINARY_NUMBER_WITH_ALTERNATING_BITS()
{
    Solution solution;
    cout << solution.hasAlternatingBits(5) << endl;
    return 0;
}