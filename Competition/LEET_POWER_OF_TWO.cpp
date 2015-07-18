#include "stdafx.h"

// https://leetcode.com/problems/power-of-two/

#include "LEET_POWER_OF_TWO.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_POWER_OF_TWO
{
    class Solution
    {
    public:
        bool isPowerOfTwo(int n)
        {
            return (n > 0) && ((n & ((~n)+1)) == n);
        }
    };
};

using namespace _LEET_POWER_OF_TWO;

int LEET_POWER_OF_TWO()
{
    Solution solution;
    cout << (solution.isPowerOfTwo(0) == false) << endl;
    cout << (solution.isPowerOfTwo(1) == true) << endl;
    cout << (solution.isPowerOfTwo(2) == true) << endl;
    cout << (solution.isPowerOfTwo(3) == false) << endl;
    cout << (solution.isPowerOfTwo(4) == true) << endl;
    cout << (solution.isPowerOfTwo((1 << 30) + 1) == false) << endl;
    cout << (solution.isPowerOfTwo(1 << 30) == true) << endl;
    cout << (solution.isPowerOfTwo((1 << 30) - 1) == false) << endl;
    cout << (solution.isPowerOfTwo(1 << 31) == true) << endl;
    return 0;
}