#include "stdafx.h"

// https://leetcode.com/problems/minimum-swaps-to-make-sequences-increasing

#include "LEET_MINIMUM_SWAPS_TO_MAKE_SEQUENCES_INCREASING.h"
#include <map>
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_MINIMUM_SWAPS_TO_MAKE_SEQUENCES_INCREASING
{
    class Solution
    {
    public:
        int minSwap(vector<int>& A, vector<int>& B) {
            int n = A.size();
            int curr_count = 0;
            int swap_count = 1;
            for (int p = 1; p < n; p++)
            {
                // a b 
                // c d
                int a = A[p - 1];
                int b = A[p];
                int c = B[p - 1];
                int d = B[p];
                bool curr_work = a < b && c < d;
                bool swap_work = a < d && c < b;
                if (curr_work && swap_work)
                {
                    curr_count = min(curr_count, swap_count);
                    swap_count = curr_count + 1;
                }
                else if (curr_work)
                {
                    curr_count = curr_count;
                    swap_count = swap_count + 1;
                }
                else if (swap_work)
                {
                    // new_curr_count = swap_count
                    // new_swap_count = curr_count + 1
                    swap(curr_count, swap_count);
                    swap_count++;
                }
            }

            return min(curr_count, swap_count);
        }
    };
};

using namespace _LEET_MINIMUM_SWAPS_TO_MAKE_SEQUENCES_INCREASING;

int LEET_MINIMUM_SWAPS_TO_MAKE_SEQUENCES_INCREASING()
{
    Solution s;
    int a_array[] = { 1, 3, 5, 4 };
    int b_array[] = { 1, 2, 3, 7 };
    vector<int> a(a_array, a_array + _countof(a_array));
    vector<int> b(b_array, b_array + _countof(b_array));
    cout << s.minSwap(a, b) << endl;
    return 0;
}