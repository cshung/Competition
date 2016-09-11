#include "stdafx.h"

// https://leetcode.com/contest/4/problems/rotate-function/

#include "LEET_ROTATE_FUNCTION.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_ROTATE_FUNCTION
{
    class Solution {
    public:
        int maxRotateFunction(vector<int>& A) {
            vector<int>& nums = A;

            int n = (int)nums.size();
            int sum = 0;

            for (int i = 0; i < n; i++)
            {
                sum += nums[i];
            }

            int r = 0;
            for (int i = 0; i < n; i++)
            {
                r += i * nums[i];
            }

            int max_r = r;

            for (int move = 0; move < n - 1; move++)
            {
                r = r - sum + nums[move] * nums.size();
                if (r > max_r)
                {
                    max_r = r;
                }
            }

            return max_r;
        }
    };
};

using namespace _LEET_ROTATE_FUNCTION;

int LEET_ROTATE_FUNCTION()
{
    Solution solution;
    vector<int> v;
    v.push_back(4);
    v.push_back(3);
    v.push_back(2);
    v.push_back(6);
    cout << solution.maxRotateFunction(v) << endl;
    return 0;
}