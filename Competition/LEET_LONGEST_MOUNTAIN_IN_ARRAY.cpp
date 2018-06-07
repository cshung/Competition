#include "stdafx.h"

// https://leetcode.com/problems/longest-mountain-in-array

#include "LEET_LONGEST_MOUNTAIN_IN_ARRAY.h"
#include <map>
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_LONGEST_MOUNTAIN_IN_ARRAY
{
    class Solution
    {
    public:
        int longestMountain(vector<int>& A)
        {
            int n = A.size();
            if (n < 3)
            {
                return 0;
            }
            int best = 0;
            int state = 0;
            int start = 0;
            int table[3][3]
            {
                { 1, 0, 0 },
                { 1, 0, 2 },
                { 1, 0, 2 }
            };
            for (int i = 1; i < n; i++)
            {
                int c = 2;
                if (A[i - 1] < A[i])
                {
                    c = 0;
                }
                else if (A[i - 1] == A[i])
                {
                    c = 1;
                }
                else
                {
                    c = 2;
                }
                int newState = table[state][c];
                if (state == 2 && newState != 2)
                {
                    best = max(best, i - start);
                }
                if (newState == 1 && state != 1)
                {
                    start = i - 1;
                }
                state = newState;
            }
            if (state == 2)
            {
                best = max(best, n - start);
            }
            return best;
        }
    };
};

using namespace _LEET_LONGEST_MOUNTAIN_IN_ARRAY;

int LEET_LONGEST_MOUNTAIN_IN_ARRAY()
{
    Solution solution;
    int test_array[] = { 2, 1, 4, 7, 3, 2, 5 };
    vector<int> test(test_array, test_array + _countof(test_array));
    cout << solution.longestMountain(test) << endl;
    return 0;
}