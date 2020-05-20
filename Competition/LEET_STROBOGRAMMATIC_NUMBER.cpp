#include "stdafx.h"

// https://leetcode.com/problems/strobogrammatic-number/

#include "LEET_STROBOGRAMMATIC_NUMBER.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_STROBOGRAMMATIC_NUMBER
{
    class Solution
    {
    public:
        bool isStrobogrammatic(string num)
        {
            int map[] = { 0, 1, -1, -1, -1, -1, 9, -1, 8, 6 };
            int i = 0;
            int j = num.size() - 1;
            while (i <= j)
            {
                int di = num[i] - '0';
                int dj = num[j] - '0';
                if (map[di] != dj)
                {
                    return false;
                }
                i++;
                j--;
            }
            return true;
        }
    };
};

using namespace _LEET_STROBOGRAMMATIC_NUMBER;

int LEET_STROBOGRAMMATIC_NUMBER()
{
    Solution solution;
    cout << solution.isStrobogrammatic("69") << endl;
    cout << solution.isStrobogrammatic("88") << endl;
    cout << solution.isStrobogrammatic("962") << endl;
    return 0;
}