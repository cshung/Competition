#include "stdafx.h"

// https://leetcode.com/problems/remove-9

#include "LEET_REMOVE_9.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_REMOVE_9
{
    class Solution
    {
    public:
        int newInteger(int n)
        {
            if (n < 9)
            {
                return n;
            }
            else
            {
                return newInteger(n / 9) * 10 + n % 9;
            }
        }
    };
};

using namespace _LEET_REMOVE_9;

int LEET_REMOVE_9()
{
    Solution solution;
    for (int i = 1; i <= 80; i++)
    {
        cout << solution.newInteger(i) << endl;
    }
    return 0;
}