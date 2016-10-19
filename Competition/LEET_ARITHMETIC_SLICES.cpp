#include "stdafx.h"

// 

#include "LEET_ARITHMETIC_SLICES.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_ARITHMETIC_SLICES
{
    class Solution
    {
    public:
        int numberOfArithmeticSlices(vector<int>& A)
        {
            if (A.size() < 2)
            {
                return 0;
            }
            int s = 0;
            for (size_t i = 0; i < A.size() - 2; i++)
            {
                int d = A[i + 1] - A[i];
                size_t j = i + 2;
                while (j < A.size() && A[j] - A[j - 1] == d)
                {
                    j++;
                }
                int l = j - i;
                s += (l - 2) * (l - 1) / 2;
                i = j - 1;
            }
            return s;
        }
    };
};

using namespace _LEET_ARITHMETIC_SLICES;

int LEET_ARITHMETIC_SLICES()
{
    Solution solution;
    int case1Array[] = { 1, 2, 3, 4, 1, 2, 3 };
    vector<int> case1(case1Array, case1Array + _countof(case1Array));
    cout << solution.numberOfArithmeticSlices(case1) << endl;
    return 0;
}