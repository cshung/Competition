#include "stdafx.h"

// https://leetcode.com/problems/sum-of-subsequence-widths

#include "LEET_SUM_OF_SUBSEQUENCE_WIDTHS.h"
#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_SUM_OF_SUBSEQUENCE_WIDTHS
{
    typedef long long int64;

    class Solution
    {
    public:
        int sumSubseqWidths(vector<int>& A)
        {
            sort(A.begin(), A.end());
            int N = A.size();
            int result = 0;

            vector<int64> powers;
            powers.resize(N);

            powers[0] = 1;
            for (int i = 1; i < N; i++)
            {
                int64 last = powers[i - 1];
                last = (last * 2) % 1000000007;
                powers[i] = last;
            }

            for (int j = 1; j < N - 1; j++)
            {
                result = (result + A[j] * (powers[j] - 1)) % 1000000007;
                result = (result - A[j] * (powers[N - 1 - j] - 1)) % 1000000007;
            }

            result = (result + A[N - 1] * (powers[N - 1] - 1)) % 1000000007;
            result = (result - A[0] * (powers[N - 1] - 1)) % 1000000007;

            return (result + 1000000007) % 1000000007;
        }
    };
};

using namespace _LEET_SUM_OF_SUBSEQUENCE_WIDTHS;

int LEET_SUM_OF_SUBSEQUENCE_WIDTHS()
{
    Solution solution;
    int test_array[] = { 2, 1, 3 };
    vector<int> test(test_array, test_array + _countof(test_array));
    cout << solution.sumSubseqWidths(test) << endl;
    return 0;
}