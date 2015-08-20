#include "stdafx.h"

// https://leetcode.com/problems/single-number-iii/

#include "LEET_SINGLE_NUMBER_III.h"
#include <map>
#include <iostream>
#include <vector>

using namespace std;

namespace _LEET_SINGLE_NUMBER_III
{
    class Solution
    {
    public:
        vector<int> singleNumber(vector<int>& nums)
        {
            int xorOfAll = 0;
            for (unsigned int i = 0; i < nums.size(); i++)
            {
                xorOfAll = xorOfAll ^ nums[i];
            }
            int mask = 1;
            while ((mask & xorOfAll) == 0)
            {
                mask = mask << 1;
            }

            int xorOfMasked = 0;
            for (unsigned int i = 0; i < nums.size(); i++)
            {
                if ((nums[i] & mask) != 0)
                {
                    xorOfMasked = xorOfMasked ^ nums[i];
                }
            }

            int result[] = { xorOfMasked, xorOfAll ^ xorOfMasked };
            return vector<int>(result, result + _countof(result));
        }
    };
};

using namespace _LEET_SINGLE_NUMBER_III;

int LEET_SINGLE_NUMBER_III()
{
    int case1[] = { 1, 2, 3, 2, 1, 5 };
    Solution s;
    vector<int> result = s.singleNumber(vector<int>(case1, case1+_countof(case1)));
    cout << result[0] << ", " << result[1] << endl;
    return 0;
}
