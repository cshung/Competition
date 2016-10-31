#include "stdafx.h"

// https://leetcode.com/problems/next-permutation/

#include "LEET_NEXT_PERMUTATION.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_NEXT_PERMUTATION
{
    class Solution {
    public:
        void nextPermutation(vector<int>& nums)
        {
            if (nums.size() < 2)
            {
                return;
            }
            int i = nums.size() - 2;
            while (i >= 0 && nums[i] >= nums[i + 1])
            {
                i--;
            }
            int s;
            if (i == -1)
            {
                // This is a monotonically decreasing sequence!
                s = 0;
            }
            else
            {
                s = i + 1;
                // nums[i] < nums[i + 1]
                for (int j = i + 2; j < nums.size(); j++)
                {
                    // Finding the last occurrence of the least number larger than nums[i]
                    // and swap with it to ensure the suffix is still monotonically decreasing
                    if (nums[j] > nums[i] && nums[j] <= nums[s])
                    {
                        s = j;
                    }
                }
                int temp = nums[s];
                nums[s] = nums[i];
                nums[i] = temp;
                s = i + 1;
            }
            int t = nums.size() - 1;
            while (s < t)
            {
                int temp = nums[s];
                nums[s] = nums[t];
                nums[t] = temp;
                s++;
                t--;
            }
        }
    };
};

using namespace _LEET_NEXT_PERMUTATION;

int LEET_NEXT_PERMUTATION()
{
    Solution solution;
    int input_array[5] = { 2, 3, 1, 3, 3 };
    vector<int> input(input_array, input_array + 5);
    solution.nextPermutation(input);
    for (int i = 0; i < 5; i++)
    {
        cout << input[i] << ", ";
    }
    return 0;
}