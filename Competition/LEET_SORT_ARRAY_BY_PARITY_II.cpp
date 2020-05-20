#include "stdafx.h"

// https://leetcode.com/problems/sort-array-by-parity-ii

#include "LEET_SORT_ARRAY_BY_PARITY_II.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_SORT_ARRAY_BY_PARITY_II
{
    class Solution
    {
    public:
        vector<int> sortArrayByParityII(vector<int>& A)
        {
            vector<int> r;
            int e = 0;
            int o = 1;
            r.resize(A.size());
            for (int i = 0; i < A.size(); i++)
            {
                if (A[i] % 2 == 0)
                {
                    r[e] = A[i];
                    e += 2;
                }
                else
                {
                    r[o] = A[i];
                    o += 2;
                }
            }
            return r;
        }
    };
};

using namespace _LEET_SORT_ARRAY_BY_PARITY_II;

int LEET_SORT_ARRAY_BY_PARITY_II()
{
    Solution solution;
    int test[] = { 4, 2, 5, 7 };
    vector<int> result = solution.sortArrayByParityII(vector<int>(test, test + _countof(test)));
    for (int i = 0; i < result.size(); i++)
    {
        cout << result[i] << ",";
    }
    cout << endl;
    return 0;
}