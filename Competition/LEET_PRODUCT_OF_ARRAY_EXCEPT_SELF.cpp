#include "stdafx.h"

// https://leetcode.com/problems/product-of-array-except-self/

#include "LEET_PRODUCT_OF_ARRAY_EXCEPT_SELF.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_PRODUCT_OF_ARRAY_EXCEPT_SELF
{
    class Solution
    {
    public:
        vector<int> productExceptSelf(vector<int>& nums)
        {
            vector<int> left;
            vector<int> right;
            vector<int> result;
            left.resize(nums.size());
            right.resize(nums.size());
            result.resize(nums.size());
            int p = 1;
            for (unsigned int i = 0; i < nums.size(); i++)
            {
                p *= nums[i];
                left[i] = p;
            }
            p = 1;
            for (unsigned int i = nums.size(); i > 0; i--)
            {
                p *= nums[i - 1];
                right[i - 1] = p;
            }
            for (unsigned int i = 0; i < nums.size(); i++)
            {
                int l = i == 0 ? 1 : left[i - 1];
                int r = i == (nums.size() - 1) ? 1 : right[i + 1];
                result[i] = l * r;
            }
            return result;
        }
    };
};

using namespace _LEET_PRODUCT_OF_ARRAY_EXCEPT_SELF;

int LEET_PRODUCT_OF_ARRAY_EXCEPT_SELF()
{
    Solution solution;
    int case1[] = { 1, 2, 3, 4};
    vector<int> result1 = solution.productExceptSelf(vector<int>(case1, case1 + _countof(case1)));
    for (unsigned int i = 0; i < result1.size(); i++) { cout << result1[i] << ','; } cout << endl;
    solution.productExceptSelf(vector<int>());
    return 0;
}