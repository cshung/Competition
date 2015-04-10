#include "stdafx.h"

// https://leetcode.com/problems/unique-binary-search-trees/

#include "LEET_UNIQUE_BINARY_SEARCH_TREES.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_UNIQUE_BINARY_SEARCH_TREES
{
    class Solution
    {
    public:
        int numTrees(int n)
        {
            long long result = 1;
            int u = 2 * n;
            for (int v = 1; v <= n; v++, u--)
            {
                result *= u;
                result /= v;
            }
            return result / (n + 1);
        }
    };
};

using namespace _LEET_UNIQUE_BINARY_SEARCH_TREES;

int LEET_UNIQUE_BINARY_SEARCH_TREES()
{
    Solution solution;
    cout << solution.numTrees(19) << endl;
    return 0;
}