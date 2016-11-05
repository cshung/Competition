#include "stdafx.h"

// https://leetcode.com/problems/arranging-coins/

#include "LEET_ARRANGING_COINS.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_ARRANGING_COINS
{
    class Solution {
    public:
        int arrangeCoins(int n)
        {
            if (n == 0)
            {
                return 0;
            }
            if (n == 1)
            {
                return 1;
            }
            long long l = 0;
            long long u = n;
            while (u - l > 1)
            {
                long long m = (l + u) / 2;
                long long d = 0;
                if (m % 2 == 0)
                {
                    d = (m + 1) * (m / 2);
                }
                else
                {
                    d = ((m + 1) / 2) * m;
                }
                if (d > n)
                {
                    u = m;
                }
                else
                {
                    l = m;
                }
            }
            return l;
        }
    };
};

using namespace _LEET_ARRANGING_COINS;

int LEET_ARRANGING_COINS()
{
    Solution solution;
    for (int i = 0; i <= 10; i++)
    {
        cout << i << " " << solution.arrangeCoins(i) << endl;
    }
    cout << solution.arrangeCoins(119) << endl;
    cout << solution.arrangeCoins(120) << endl;
    cout << solution.arrangeCoins(121) << endl;
    cout << solution.arrangeCoins(~(1<<31)) << endl;
    return 0;
}