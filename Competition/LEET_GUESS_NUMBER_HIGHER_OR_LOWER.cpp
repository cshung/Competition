#include "stdafx.h"

// https://leetcode.com/problems/guess-number-higher-or-lower/

#include "LEET_GUESS_NUMBER_HIGHER_OR_LOWER.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_GUESS_NUMBER_HIGHER_OR_LOWER
{
    int guess(int num)
    {
        if (num == 6)
        {
            return 0;
        }
        else if (num > 6)
        {
            return 1;
        }
        else
        {
            return -1;
        }
    }

    class Solution {
    public:
        int guessNumber(int n) {
            int low = 1;
            int high = n;
            while (low <= high)
            {
                int mid = low + (high - low) / 2;
                int g = guess(mid);
                if (g == 0)
                {
                    return mid;
                }
                else if (g == -1) {
                    high = mid - 1;
                }
                else {
                    low = mid + 1;
                }
            }

            // Unless the guess API is not stable.
            return -1;
        }
    };
};

using namespace _LEET_GUESS_NUMBER_HIGHER_OR_LOWER;

int LEET_GUESS_NUMBER_HIGHER_OR_LOWER()
{
    Solution solution;
    cout << solution.guessNumber(10) << endl;
    return 0;
}