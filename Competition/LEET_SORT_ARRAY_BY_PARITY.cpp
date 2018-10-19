#include "stdafx.h"

// https://leetcode.com/problems/sort-array-by-parity

#include "LEET_SORT_ARRAY_BY_PARITY.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_SORT_ARRAY_BY_PARITY
{
    class Solution
    {
    public:
        vector<int> sortArrayByParity(vector<int>& A)
        {
            vector<int> r;
            r.resize(A.size());
            int e = 0;
            int o = A.size();
            for (int i = 0; i < A.size(); i++)
            {
                if (A[i] % 2 == 0)
                {
                    r[e++] = A[i];
                }
                else
                {
                    r[--o] = A[i];
                }
            }
            return r;
        }
    };
};

using namespace _LEET_SORT_ARRAY_BY_PARITY;

int LEET_SORT_ARRAY_BY_PARITY()
{
    Solution solution;
    int test[] = { 3,1,2,4 };
    vector<int> result = solution.sortArrayByParity(vector<int>(test, test + _countof(test)));
    for (int i = 0; i < result.size(); i++)
    {
        cout << result[i] << ",";
    }
    cout << endl;
    return 0;
}