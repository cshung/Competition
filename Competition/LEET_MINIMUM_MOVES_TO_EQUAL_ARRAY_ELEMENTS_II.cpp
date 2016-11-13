#include "stdafx.h"

// https://leetcode.com/problems/minimum-moves-to-equal-array-elements-ii/

#include "LEET_MINIMUM_MOVES_TO_EQUAL_ARRAY_ELEMENTS_II.h"
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

namespace _LEET_MINIMUM_MOVES_TO_EQUAL_ARRAY_ELEMENTS_II
{
    class Solution
    {
    private:
        int findKthSmallest(vector<int>& nums, int start, int end, int k)
        {
            if (nums.size() == 1)
            {
                return nums[0];
            }
            int pivotIndex = rand() % (end - start) + start;
            swap(nums[start], nums[pivotIndex]);

            int pivot = nums[start];
            int left = start;
            int right = end;

            // Maintain these variables
            int smallerEnd = left;             // [left, smallerEnd) are strictly smaller than the pivot
            int smallerOrEqualEnd = left + 1;  // [smallerEnd, smallerOrEqualEnd) are smaller or equal to the pivot
            int largerBegin = right;           // [largerBegin, right) are strictly larger than the pivot

            while (true)
            {
                while (smallerOrEqualEnd < nums.size() && nums[smallerOrEqualEnd] <= pivot)
                {
                    if (nums[smallerOrEqualEnd] < pivot)
                    {
                        swap(nums[smallerEnd], nums[smallerOrEqualEnd]);
                        smallerEnd++;
                    }

                    smallerOrEqualEnd++;
                }

                while (largerBegin > 0 && nums[largerBegin - 1] > pivot)
                {
                    largerBegin--;
                }
                if (smallerOrEqualEnd == largerBegin)
                {
                    break;
                }

                // [left, smallerEnd) are strictly smaller than the pivot
                // [smallerEnd, smallerOrEqualEnd) are equal to the pivot
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
            }

            int smallPortionLength = smallerEnd - left;
            if (k < smallPortionLength)
            {
                return this->findKthSmallest(nums, left, smallerEnd, k);
            }
            else
            {
                k -= smallPortionLength;
                int pivotPortionLength = smallerOrEqualEnd - smallerEnd;
                if (k < pivotPortionLength)
                {
                    return pivot;
                }
                else
                {
                    k -= pivotPortionLength;
                    return this->findKthSmallest(nums, smallerOrEqualEnd, right, k);
                }
            }
        }

    public:
        int minMoves2(vector<int>& nums)
        {
            // This could be the larger one of the two center elements if the array length is even.
            int median = findKthSmallest(nums, 0, nums.size(), nums.size() / 2);
            int move = 0;
            for (int i = 0; i < nums.size(); i++)
            {
                move += abs(nums[i] - median);
            }
            return move;
        }
    };
};

using namespace _LEET_MINIMUM_MOVES_TO_EQUAL_ARRAY_ELEMENTS_II;

int LEET_MINIMUM_MOVES_TO_EQUAL_ARRAY_ELEMENTS_II()
{
    Solution solution;
    int input_array[] = { 1, 2, 3 };
    vector<int> input(input_array, input_array + _countof(input_array));
    cout << solution.minMoves2(input) << endl;
    return 0;
}