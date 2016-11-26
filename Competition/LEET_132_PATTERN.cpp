#include "stdafx.h"

// https://leetcode.com/problems/132-pattern/

#include "LEET_132_PATTERN.h"
#include <stack>
#include <map>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_132_PATTERN
{
    class Solution
    {
    public:
        bool find132pattern(vector<int>& nums)
        {
            if (nums.size() < 3)
            {
                return false;
            }
            stack<pair<int, int>> increasing_ranges;
            int range_begin = -1;
            int state = 1;
            for (int i = 0; i < nums.size(); i++)
            {
                while (increasing_ranges.size() > 0)
                {
                    pair<int, int> top = increasing_ranges.top();
                    if (nums[i] > top.first && nums[i] < top.second)
                    {
                        return true;
                    }
                    else if (nums[i] >= top.second)
                    {
                        increasing_ranges.pop();
                    }
                    else
                    {
                        break;
                    }
                }
                if (i < nums.size() - 1)
                {
                    if (state == 1)
                    {
                        if (nums[i] < nums[i + 1])
                        {
                            range_begin = nums[i];
                            state = 2;
                        }
                        // otherwise stay in state 1
                    }
                    else
                    {
                        // state == 2
                        if (nums[i] > nums[i + 1])
                        {
                            // we have found an increasing range
                            increasing_ranges.push(pair<int, int>(range_begin, nums[i]));
                            state = 1;
                        }
                        // otherwise stay in state 2
                    }
                }
            }
            return false;
        }
    };
};

using namespace _LEET_132_PATTERN;

int LEET_132_PATTERN()
{
    Solution solution;
    int input1[] = { 1, 2, 3, 4 };
    int input2[] = { 3, 1, 4, 2 };
    int input3[] = { -1, 3, 2, 0 };
    int input4[] = { 1,0,1,-4,-3 };
    int input5[] = { 8, 10, 4, 6, 5 };
    cout << solution.find132pattern(vector<int>(input1, input1 + _countof(input1))) << endl;
    cout << solution.find132pattern(vector<int>(input2, input2 + _countof(input2))) << endl;
    cout << solution.find132pattern(vector<int>(input3, input3 + _countof(input3))) << endl;
    cout << solution.find132pattern(vector<int>(input4, input4 + _countof(input4))) << endl;
    cout << solution.find132pattern(vector<int>(input5, input5 + _countof(input5))) << endl;
    return 0;
}