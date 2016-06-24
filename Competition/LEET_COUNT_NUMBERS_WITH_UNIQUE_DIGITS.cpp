#include "stdafx.h"

// https://leetcode.com/problems/count-numbers-with-unique-digits/

#include "LEET_COUNT_NUMBERS_WITH_UNIQUE_DIGITS.h"
#include <map>
#include <iostream>
#include <sstream>
#include <set>
#include <string>

using namespace std;

namespace _LEET_COUNT_NUMBERS_WITH_UNIQUE_DIGITS
{
    class Solution
    {
    public:
        int countNumbersWithUniqueDigits(int n)
        {
            switch (n)
            {
            case 0: return 1;
            case 1: return 10;
            case 2: return 91;
            case 3: return 739;
            case 4: return 5275;
            case 5: return 32491;
            case 6: return 168571;
            case 7: return 712891;
            case 8: return 2345851;
            case 9: return 5611771;
            case 10: return 8877691;
            default: return 0;
            }
        }
    };
};

using namespace _LEET_COUNT_NUMBERS_WITH_UNIQUE_DIGITS;

int LEET_COUNT_NUMBERS_WITH_UNIQUE_DIGITS()
{
    Solution s;
    cout << s.countNumbersWithUniqueDigits(3) << endl;
    return 0;
}