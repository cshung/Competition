#include "stdafx.h"

// https://leetcode.com/problems/perfect-number

#include "LEET_PERFECT_NUMBER.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_PERFECT_NUMBER
{
    class Solution
    {
    public:
        bool checkPerfectNumber(int num)
        {
            switch (num)
            {
            case 6:
            case 28:
            case 496:
            case 8128:
            case 33550336:
                return true;
            default:
                return false;
            }
        }
    };
};

using namespace _LEET_PERFECT_NUMBER;

int LEET_PERFECT_NUMBER()
{
    Solution solution;
    cout << solution.checkPerfectNumber(28) << endl;
    return 0;
}