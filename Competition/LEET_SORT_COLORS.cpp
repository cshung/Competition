#include "stdafx.h"

// https://leetcode.com/problems/sort-colors/

#include "LEET_SORT_COLORS.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

namespace _LEET_SORT_COLORS
{
#define LOG
    class Solution
    {
    public:
        void sortColors(vector<int>& nums)
        {
            int size = nums.size();
            int left = 0;
            int right = size - 1;
            int red = 0;
            int blue = size - 1;
            while (true)
            {
                while (left < size && nums[left] != 2)
                {
                    if (nums[left] == 0)
                    {
                        swap(nums[red], nums[left]);
                        red++;
                    }
                    left++;
                }
                // After this loop, we are certain either left == size || nums[left] == 2
                // nums[0, red) is red
                // nums[red, left) is green

                while (right >= 0 && nums[right] != 0)
                {
                    if (nums[right] == 2)
                    {
                        swap(nums[blue], nums[right]);
                        blue--;
                    }
                    right--;
                }
                // Similarly, after this loop, we are certain that either right == -1 || nums[right] == 0
                // nums(blue, size) is blue
                // nums(right, blue] is green

#ifdef LOG
                for (int i = 0; i < size; i++)
                {
                    cout << nums[i] << " ";
                }
                cout << endl;

                for (int i = 0; i < size; i++)
                {
                    if (i == left) { cout << 'L'; }
                    else if (i == right) { cout << 'R'; }
                    else { cout << ' '; }
                    cout << ' ';
                }
                cout << endl;
                for (int i = 0; i < size; i++)
                {
                    if (i == red) { cout << 'r'; }
                    else if (i == blue) { cout << 'b'; }
                    else { cout << ' '; }
                    cout << ' ';
                }
                cout << endl;
                cout << endl;
#endif

                if (left == size || right == -1)
                {
                    // The iteration above have arranged the order correctly
                    // this is the case when the array do not need a swap at all
                    break;
                }
                if (left > right)
                {
                    // We have reach the point where the pointer crosses, no point doing any more swaps
                    break;
                }
                
                swap(nums[red], nums[left]);
                swap(nums[blue], nums[right]);
                swap(nums[red], nums[blue]);
                left++;
                right--;
                red++;
                blue--;
            }
        }
    };
};

using namespace _LEET_SORT_COLORS;

int LEET_SORT_COLORS()
{
    int case1_array[] = { 0, 1, 2, 0, 2, 1, 1, 0, 2, 1, 2, 0, 2, 0, 1, 2, 1, 0 };
    int case2_array[] = { 1, 2, 0, 0 };
    vector<int> case1_vector(case1_array, case1_array + _countof(case1_array));
    vector<int> case2_vector(case2_array, case2_array + _countof(case2_array));
    Solution s;
    s.sortColors(case1_vector);
    s.sortColors(case1_vector);
    s.sortColors(case2_vector);
    for (int i = 0; i < _countof(case1_array); i++)
    {
        cout << case1_vector[i] << " ";
    }
    cout << endl;
    for (int i = 0; i < _countof(case2_array); i++)
    {
        cout << case2_vector[i] << " ";
    }
    cout << endl;
    return 0;
}