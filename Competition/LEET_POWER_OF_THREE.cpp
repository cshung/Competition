#include "stdafx.h"

// https://leetcode.com/problems/power-of-three/

#include "LEET_POWER_OF_THREE.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_POWER_OF_THREE
{
    class Solution {
    public:
        bool isPowerOfThree(int n) {
            if (n == 1) return true;
            if (n == 3) return true;
            if (n == 9) return true;
            if (n == 27) return true;
            if (n == 81) return true;
            if (n == 243) return true;
            if (n == 729) return true;
            if (n == 2187) return true;
            if (n == 6561) return true;
            if (n == 19683) return true;
            if (n == 59049) return true;
            if (n == 177147) return true;
            if (n == 531441) return true;
            if (n == 1594323) return true;
            if (n == 4782969) return true;
            if (n == 14348907) return true;
            if (n == 43046721) return true;
            if (n == 129140163) return true;
            if (n == 387420489) return true;
            if (n == 1162261467) return true;
            return false;
        }
    };
};

using namespace _LEET_POWER_OF_THREE;

int LEET_POWER_OF_THREE()
{
    Solution solution;
    for (int i = 0; i <= 9; i++)
    {
        cout << solution.isPowerOfThree(i) << endl;
    }
    return 0;
}