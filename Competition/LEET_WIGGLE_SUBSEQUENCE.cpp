#include "stdafx.h"

// https://leetcode.com/problems/wiggle-subsequence/

#include "LEET_WIGGLE_SUBSEQUENCE.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_WIGGLE_SUBSEQUENCE
{
    class Solution
    {
    public:
        int wiggleMaxLength(vector<int>& nums)
        {
            if (nums.size() == 0)
            {
                return 0;
            }
            if (nums.size() == 1)
            {
                return 1;
            }
            bool initial = true;
            bool is_max = true;
            int last = 0;
            int counter = 1;
            for (int i = 1; i < nums.size(); i++)
            {
                if (initial)
                {
                    if (nums[i] != nums[i - 1])
                    {
                        is_max = nums[i - 1] < nums[i];
                    }
                    initial = false;
                }
                else
                {
                    if (is_max)
                    {
                        if (nums[i - 1] > nums[i])
                        {
                            last = nums[i - 1];
                            counter++;
                            is_max = false;
                        }
                    }
                    else
                    {
                        if (nums[i - 1] < nums[i])
                        {
                            last = nums[i - 1];
                            counter++;
                            is_max = true;
                        }
                    }
                }
            }
            if (nums[nums.size() - 1] != last)
            {
                counter++;
            }

            return counter;
        }
    };
};

using namespace _LEET_WIGGLE_SUBSEQUENCE;

int LEET_WIGGLE_SUBSEQUENCE()
{
    Solution solution;
    int case1_array[] = { 1,7,4,9,2,5 };
    int case2_array[] = { 1,17,5,10,13,15,10,5,16,8 };
    int case3_array[] = { 1,2,3,4,5,6,7,8,9 };
    vector<int> case1_vector(case1_array, case1_array + _countof(case1_array));
    vector<int> case2_vector(case2_array, case2_array + _countof(case2_array));
    vector<int> case3_vector(case3_array, case3_array + _countof(case3_array));
    cout << solution.wiggleMaxLength(case1_vector) << endl;
    cout << solution.wiggleMaxLength(case2_vector) << endl;
    cout << solution.wiggleMaxLength(case3_vector) << endl;
    return 0;
}