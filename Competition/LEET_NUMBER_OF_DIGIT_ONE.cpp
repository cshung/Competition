#include "stdafx.h"

// https://leetcode.com/problems/number-of-digit-one/

#include "LEET_NUMBER_OF_DIGIT_ONE.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_NUMBER_OF_DIGIT_ONE
{
    class Solution
    {
    public:
        int countDigitOne(int n)
        {
            if (n < 10)
            {
                return n >= 1 ? 1 : 0;
            }
            else
            {
                // 324  ++\
                // 323  ++\
                // 322  ++\
                // 321  ++\
                // 320  ++\
                //      **.
                //      **.
                int lsbRepeatingPart = 1 * (n / 10);                                                      // This is the '.' part, 0-9   repeated 32 times
                int lsbResidue = countDigitOne(n % 10);                                                   // This is the '\' part, 0-4   repeated 1  times
                int msbsRepeatingPart = countDigitOne(n / 10 - 1) * 10;                                   // This is the '*' part, 00-31 repeated 10 times
                int msbsResidue = (countDigitOne(n / 10) - countDigitOne(n / 10 - 1)) * ((n % 10) + 1);   // This is the '+' part, 32    repeated 5  times

                return lsbRepeatingPart + lsbResidue + msbsRepeatingPart + msbsResidue;
            }
        }
    };
};

using namespace _LEET_NUMBER_OF_DIGIT_ONE;

int LEET_NUMBER_OF_DIGIT_ONE()
{
    Solution solution;
    for (int i = 21; i <= 21; i++)
    {
        cout << i << "\t" << solution.countDigitOne(i) << endl;
    }
    return 0;
}