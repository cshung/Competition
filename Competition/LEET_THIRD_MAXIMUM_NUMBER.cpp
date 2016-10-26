#include "stdafx.h"

// https://leetcode.com/problems/third-maximum-number/

#include "LEET_THIRD_MAXIMUM_NUMBER.h"
#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_THIRD_MAXIMUM_NUMBER
{
    class Solution
    {
    public:
        int thirdMax(vector<int>& nums)
        {
            bool as = false;
            bool bs = false;
            bool cs = false;
            int a;
            int b;
            int c;
            for (size_t i = 0; i < nums.size(); i++)
            {
                int n = nums[i];

                if (as && n == a)
                {
                    continue;
                }

                if (bs && n == b)
                {
                    continue;
                }

                if (cs && n == c)
                {
                    continue;
                }

                if (!as)
                {
                    as = true;
                    a = n;
                }
                else if (n > a)
                {
                    if (bs)
                    {
                        c = b;
                        cs = true;
                    }
                    b = a;
                    bs = true;
                    a = n;
                }
                else if (!bs)
                {
                    b = n;
                    bs = true;
                }
                else if (n > b)
                {
                    c = b;
                    cs = true;
                    b = n;
                }
                else if (!cs)
                {
                    c = n;
                    cs = true;
                }
                else if (n > c)
                {
                    c = n;
                    cs = true;
                }
            }
            if (cs)
            {
                return c;
            }
            else
            {
                return a;
            }
        }
    };
};

using namespace _LEET_THIRD_MAXIMUM_NUMBER;

int LEET_THIRD_MAXIMUM_NUMBER()
{
    Solution solution;
    vector<int> x;
    x.push_back(2);
    x.push_back(2);
    x.push_back(3);
    x.push_back(1);
    cout << solution.thirdMax(x) << endl;
    return 0;
}