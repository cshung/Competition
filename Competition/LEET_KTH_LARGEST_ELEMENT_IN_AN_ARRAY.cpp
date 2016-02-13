#include "stdafx.h"

// https://leetcode.com/problems/kth-largest-element-in-an-array/

#include "LEET_KTH_LARGEST_ELEMENT_IN_AN_ARRAY.h"
#include <algorithm>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

#define LOG

namespace _LEET_KTH_LARGEST_ELEMENT_IN_AN_ARRAY
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
#ifdef LOG
            cout << "Starting a call" << endl;
#endif
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
#ifdef LOG
                cout << "Before swap" << endl;
                PrintState(nums, left, smallerEnd, smallerOrEqualEnd, largerBegin, right);
                cout << endl;
#endif
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
#ifdef LOG
                cout << "After swap" << endl;
                PrintState(nums, left, smallerEnd, smallerOrEqualEnd, largerBegin, right);
                cout << endl;
                cout << endl;
#endif
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

        void PrintState(vector<int>& nums, int left, int smallerEnd, int smallerOrEqualEnd, int largerBegin, int right)
        {
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
            cout << "]";
            for (int i = smallerOrEqualEnd; i < largerBegin; i++)
            {
                cout << nums[i] << " ";
            }
            cout << "[";
            for (int i = largerBegin; i < right; i++)
            {
                cout << nums[i] << " ";
            }
            cout << "]" << endl;
        }
    public:
        int findKthLargest(vector<int>& nums, int k)
        {
            return this->findKthSmallest(nums, 0, nums.size(), nums.size() - k);
        }
    };
};

using namespace _LEET_KTH_LARGEST_ELEMENT_IN_AN_ARRAY;

int LEET_KTH_LARGEST_ELEMENT_IN_AN_ARRAY()
{
    int data[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20 };
    vector<int> case1 = vector<int>(data, data + _countof(data));
    Solution solution;
    cout << solution.findKthLargest(case1, 1) << endl;
    return 0;
}