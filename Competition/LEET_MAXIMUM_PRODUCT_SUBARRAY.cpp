#include "stdafx.h"

// https://leetcode.com/problems/maximum-product-subarray/

#include "LEET_MAXIMUM_PRODUCT_SUBARRAY.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

namespace _LEET_MAXIMUM_PRODUCT_SUBARRAY
{
    class Solution
    {
    public:
        int maxProduct(vector<int>& nums)
        {
            int size = nums.size();
            if (size == 0)
            {
                return 1;
            }
            int best_product = nums[0];
            int best_positive_ends = nums[0];
            int best_negative_ends = nums[0];
            if (nums[0] > 0)
            {
                best_negative_ends = 0;
            }
            if (nums[0] < 0)
            {
                best_positive_ends = 0;
            }
            for (int i = 1; i < size; i++)
            {
                int new_best_positive_ends = 0;
                int new_best_negative_ends = 0;
                if (nums[i] == 0)
                {
                    best_positive_ends = best_negative_ends = 0;
                }
                else if (nums[i] > 0)
                {
                    if (best_positive_ends != 0)
                    {
                        new_best_positive_ends = best_positive_ends * nums[i];
                    }
                    else
                    {
                        new_best_positive_ends = nums[i];
                    }
                    if (best_negative_ends != 0)
                    {
                        new_best_negative_ends = best_negative_ends * nums[i];
                    }
                    else
                    {
                        new_best_negative_ends = 0;
                    }
                }
                else if (nums[i] < 0)
                {
                    if (best_positive_ends != 0)
                    {
                        new_best_negative_ends = best_positive_ends * nums[i];
                    }
                    else
                    {
                        new_best_negative_ends = nums[i];
                    }
                    if (best_negative_ends != 0)
                    {
                        new_best_positive_ends = best_negative_ends * nums[i];
                    }
                    else
                    {
                        new_best_positive_ends = 0;
                    }
                }

                best_positive_ends = new_best_positive_ends;
                best_negative_ends = new_best_negative_ends;
                best_product = max(best_product, best_positive_ends);
            }

            return best_product;
        }
    };
};

using namespace _LEET_MAXIMUM_PRODUCT_SUBARRAY;

int LEET_MAXIMUM_PRODUCT_SUBARRAY()
{
    int case1[] = { -1 };
    Solution s;
    cout << s.maxProduct(vector<int>(case1, case1 + _countof(case1))) << endl;
    return 0;
}