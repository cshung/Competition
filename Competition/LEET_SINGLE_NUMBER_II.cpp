#include "stdafx.h"

// https://leetcode.com/problems/single-number-ii/

#include "LEET_SINGLE_NUMBER_II.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_SINGLE_NUMBER_II
{
    typedef long long int64;

    class Solution
    {
    public:
        int singleNumber(int A[], int n)
        {
            int64 accumulator = 0;
            for (int i = 0; i < n; i++)
            {
                int64 lo_mask = 1;
                int64 hi_mask = (int64)1 << 32;
                for (int d = 0; d < 32; d++)
                {
                    int64 ac_lo = accumulator & lo_mask;
                    int64 ac_hi = accumulator & hi_mask;
                    int64 ar_lo = (unsigned int)A[i] & lo_mask;
                    int64 ar_hi = (unsigned int)A[i] & hi_mask;

                    int ac_digit = ((ac_hi == 0) ? 0 : 2) + ((ac_lo == 0) ? 0 : 1);
                    int ar_digit = ((ar_hi == 0) ? 0 : 2) + ((ar_lo == 0) ? 0 : 1);

                    int sum = (ac_digit + ar_digit) % 3;

                    accumulator = accumulator & ~lo_mask;
                    accumulator = accumulator & ~hi_mask;

                    switch (sum)
                    {
                    case 0:
                        // The digit is already reset
                        break;
                    case 1:
                        accumulator = accumulator | lo_mask;
                        break;
                    case 2:
                        accumulator = accumulator | hi_mask;
                        break;
                    }

                    lo_mask = lo_mask << 1;
                    hi_mask = hi_mask << 1;
                }
            }

            if (n % 3 == 2)
            {
                int64 lo_mask = 1;
                int64 hi_mask = (int64)1 << 32;
                for (int d = 0; d < 32; d++)
                {
                    int64 ac_lo = accumulator & lo_mask;
                    int64 ac_hi = accumulator & hi_mask;

                    int ac_digit = ((ac_hi == 0) ? 0 : 2) + ((ac_lo == 0) ? 0 : 1);

                    int quoient = (ac_digit * 2) % 3;

                    accumulator = accumulator & ~lo_mask;
                    accumulator = accumulator & ~hi_mask;
                    accumulator = accumulator & ~lo_mask;
                    accumulator = accumulator & ~hi_mask;

                    switch (quoient)
                    {
                    case 0:
                        // The digit is already reset
                        break;
                    case 1:
                        accumulator = accumulator | lo_mask;
                        break;
                    case 2:
                        accumulator = accumulator | hi_mask;
                        break;
                    }

                    lo_mask = lo_mask << 1;
                    hi_mask = hi_mask << 1;
                }
            }

            return (accumulator << 32) >> 32;
        }
    };
};

using namespace _LEET_SINGLE_NUMBER_II;

int LEET_SINGLE_NUMBER_II()
{
    int A[] = { -2, -2, 1, 1, -3, 1, -3, -3, -4, -2 };
    Solution solution;
    cout << solution.singleNumber(A, 10) << endl;
    return 0;
}