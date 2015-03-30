#include "stdafx.h"

// https://leetcode.com/problems/rotate-array/

#include "LEET_ROTATE_ARRAY.h"
#include <map>
#include <iostream>
#include <vector>

using namespace std;

namespace _LEET_ROTATE_ARRAY
{
    class Solution
    {
    public:
        void rotate(int nums[], int n, int k)
        {
            int moved_element = 0;
            for (int start_index = 0; moved_element < n; start_index++)
            {
                int current_index = start_index;
                int next_index;
                int value_to_put = nums[start_index];
                do
                {
                    next_index = (current_index + k) % n;
                    int next_value = nums[next_index];
                    nums[next_index] = value_to_put;
                    value_to_put = next_value;
                    current_index = next_index;
                    moved_element++;
                } while (next_index != start_index);
            }
        }
    };
};

using namespace _LEET_ROTATE_ARRAY;

int LEET_ROTATE_ARRAY()
{
    int A[] = { 1, 2, 3, 4, 5 };
    Solution solution;
    solution.rotate(A, 4, 2);
    for (int i = 0; i < 5; i++)
    {
        cout << A[i] << " ";
    }
    cout << endl;
    return 0;
}
