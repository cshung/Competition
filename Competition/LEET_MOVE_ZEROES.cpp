#include "stdafx.h"

// https://leetcode.com/problems/move-zeroes/

#include "LEET_MOVE_ZEROES.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

namespace _LEET_MOVE_ZEROES
{
    class Solution
    {
    public:
        void moveZeroes(vector<int>& nums)
        {
            int n = nums.size();
            int write = 0;
            int read = 0;
            while (read < n)
            {
                if (nums[read] != 0)
                {
                    nums[write] = nums[read];
                    write++;
                }
                read++;
            }
            while (write < n)
            {
                nums[write] = 0;
                write++;
            }
        }
    };
};

using namespace _LEET_MOVE_ZEROES;

int LEET_MOVE_ZEROES()
{
    int case1_array[] = { 0, 1, 0, 3, 12 };
    vector<int> case1(case1_array, case1_array + _countof(case1_array));
    Solution s;
    s.moveZeroes(case1);
    for (int i = 0; i < 5; i++)
    {
        cout << case1[i] << " ";
    }
    cout << endl;
    return 0;
}