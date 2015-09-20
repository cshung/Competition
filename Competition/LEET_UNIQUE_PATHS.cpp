#include "stdafx.h"

// https://leetcode.com/problems/unique-paths/

#include "LEET_UNIQUE_PATHS.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

namespace _LEET_UNIQUE_PATHS
{
    class Solution
    {
    public:
        int uniquePaths(int m, int n)
        {
            if (m == 1 || n == 1)
            {
                return 1;
            }
            long long result = 1;
            m--;
            n--;
            int u = m + n;
            n = min(m, n); // be careful with the loop below - this minimum is required
            for (int v = 1; v <= n; v++, u--)
            {
                result *= u;
                result /= v;
            }
            return (int)result;
        }
    };
};

using namespace _LEET_UNIQUE_PATHS;

int LEET_UNIQUE_PATHS()
{
    Solution s;
    cout << s.uniquePaths(2, 100) << endl;
    return 0;
}