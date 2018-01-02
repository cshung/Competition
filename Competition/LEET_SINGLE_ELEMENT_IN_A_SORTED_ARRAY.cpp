#include "stdafx.h"

// https://leetcode.com/problems/single-element-in-a-sorted-array

#include "LEET_SINGLE_ELEMENT_IN_A_SORTED_ARRAY.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_SINGLE_ELEMENT_IN_A_SORTED_ARRAY
{
    class Solution
    {
    public:
        int singleNonDuplicate(vector<int>& nums)
        {
            return singleNonDuplicate(nums, 0, nums.size());
        }

        int singleNonDuplicate(vector<int>& nums, int begin, int end)
        {
            int length = end - begin;
            int middle = (begin + end) / 2;
            
            if (length == 1)
            {
                return nums[begin];
            }
            else
            {
                int val_c = nums[middle];
                int val_l = nums[middle - 1];
                int val_r = nums[middle + 1];
                int idx_l;
                int idx_r;
                if (val_l == val_c)
                {
                    idx_l = middle - 1;
                    idx_r = middle + 1;
                }
                else if (val_c == val_r)
                {
                    idx_l = middle;
                    idx_r = middle + 2;
                }
                else
                {
                    return val_c;
                }
                int len_l = idx_l - begin;
                int len_r = end - idx_r;
                if (len_l % 2 == 1)
                {
                    return singleNonDuplicate(nums, begin, idx_l);
                }
                else
                {
                    return singleNonDuplicate(nums, idx_r, end);
                }
            }
        }
    };
};

using namespace _LEET_SINGLE_ELEMENT_IN_A_SORTED_ARRAY;

int LEET_SINGLE_ELEMENT_IN_A_SORTED_ARRAY()
{
    Solution solution;
    int input_array[] = { 1, 1, 2, 3, 3, 4, 4, 5, 5 };
    vector<int> input(input_array, input_array + _countof(input_array));
    cout << solution.singleNonDuplicate(input) << endl;
    return 0;
}