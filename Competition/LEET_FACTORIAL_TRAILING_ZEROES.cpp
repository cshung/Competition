#include "stdafx.h"

// https://leetcode.com/problems/factorial-trailing-zeroes/

#include "LEET_FACTORIAL_TRAILING_ZEROES.h"
#include <map>
#include <iostream>
#include <vector>

using namespace std;

namespace _LEET_FACTORIAL_TRAILING_ZEROES
{
    class Solution
    {
    public:
        int trailingZeroes(int n)
        {
            int numZeros = 0;
            long long p = 5;
            while (p <= n)
            {
                numZeros += n / p;
                p *= 5;
            }
            return numZeros;
        }
    };
};

using namespace _LEET_FACTORIAL_TRAILING_ZEROES;

int LEET_FACTORIAL_TRAILING_ZEROES()
{
    Solution solution;
    cout << solution.trailingZeroes(2147483647) << endl;
    return 0;
}
