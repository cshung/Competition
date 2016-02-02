#include "stdafx.h"

// https://leetcode.com/problems/kth-largest-element-in-an-array/

#include "LEET_KTH_LARGEST_ELEMENT_IN_AN_ARRAY.h"
#include <algorithm>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_KTH_LARGEST_ELEMENT_IN_AN_ARRAY
{
    class Solution
    {
    private:
        int findKthLargest(vector<int>& nums, int start, int end, int k)
        {
            int pivot = nums[start];
            int left = start + 1;
            int right = end - 1;

            // Let's properly implement 3 way partitioning
            int left_filled = start;    // [start, left_filled) < pivot
            int right_filled = end;     // [right_filled, right) > pivot

            while (left < right)
            {
                while (nums[left] < pivot)
                {
                    left++;
                }
                while (nums[right] > pivot)
                {
                    right--;
                }
                swap(nums[left], nums[right]);
            }

            
            return 0;
        }
    public:
        int findKthLargest(vector<int>& nums, int k)
        {
            return this->findKthLargest(nums, 0, nums.size(), k);
        }
    };
};

using namespace _LEET_KTH_LARGEST_ELEMENT_IN_AN_ARRAY;

int LEET_KTH_LARGEST_ELEMENT_IN_AN_ARRAY()
{
    int data[] = { 3, 0, 6, 2, 4, 7, 0, 0 };
    vector<int> case1 = vector<int>(data, data + _countof(data));
    Solution solution;
    cout << solution.findKthLargest(case1, 3) << endl;
    return 0;
}