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
            int left = start;
            int right = end;

            // Maintain these variables
            int smallerEnd = left;             // [left, smallerEnd) are strictly smaller than the pivot
            int smallerOrEqualEnd = left + 1;  // [smallerEnd, smallerOrEqualEnd) are smaller or equal to the pivot
            int largerBegin = right;           // [largerBegin, right) are strictly larger than the pivot
            
            while (smallerOrEqualEnd < largerBegin - 1)
            {
                // TODO: Update smallerEnd here and swap as needed
                while (nums[smallerOrEqualEnd] <= pivot)
                {
                    smallerOrEqualEnd++;
                }

                while (nums[largerBegin - 1] > pivot)
                {
                    largerBegin--;
                }

                // [left, smallerEnd) are strictly smaller than the pivot
                // [smallerEnd, smallerOrEqualEnd) are smaller or equal to the pivot
                // [largerBegin, right) are strictly larger than the pivot

                // nums[smallerEnd] = pivot
                // nums[smallerOrEqualEnd] > pivot
                // nums[largerBegin - 1] <= pivot
                if (nums[largerBegin - 1] == pivot)
                {
                    swap(nums[smallerOrEqualEnd], nums[largerBegin - 1]);
                    smallerOrEqualEnd++;
                    largerBegin--;
                }
                else
                {
                    nums[smallerEnd] = nums[largerBegin - 1];
                    nums[largerBegin - 1] = nums[smallerOrEqualEnd];
                    nums[smallerOrEqualEnd] = pivot;
                    smallerEnd++;
                    smallerOrEqualEnd++;
                    largerBegin--;
                }
                // This is not the right way to update smaller end
                while (nums[smallerEnd] < pivot)
                {
                    smallerEnd++;
                }


                for (int i = left; i < right; i++)
                {
                    cout << nums[i] << " ";
                }
                cout << endl;

                cout << "[";
                for (int i = left; i < smallerEnd; i++)
                {
                    cout << nums[i] << " ";
                }
                cout << "][";
                for (int i = smallerEnd; i < smallerOrEqualEnd; i++)
                {
                    cout << nums[i] << " ";
                }
                cout << "][";
                for (int i = largerBegin; i < right; i++)
                {
                    cout << nums[i] << " ";
                }
                cout << "]" << endl;
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
    int data[] = { 3, 0, 6, 3, 2, 4, 3, 7, 0, 0 };
    vector<int> case1 = vector<int>(data, data + _countof(data));
    Solution solution;
    cout << solution.findKthLargest(case1, 3) << endl;
    return 0;
}