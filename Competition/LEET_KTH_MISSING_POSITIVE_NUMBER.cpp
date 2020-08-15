#include "stdafx.h"

// https://leetcode.com/problems/kth-missing-positive-number/

#include "LEET_KTH_MISSING_POSITIVE_NUMBER.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_KTH_MISSING_POSITIVE_NUMBER
{
    class Solution
    {
    public:
        int findKthPositive(vector<int>& arr, int k)
        {
            vector<bool> data(1000, true);
            for (int i = 0; i < arr.size(); i++)
            {
                data[arr[i] - 1] = false;
            }
            for (int i = 0; i < 1000; i++)
            {
                if (data[i])
                {
                    k--;
                }
                if (k == 0)
                {
                    return i + 1;
                }
            }
            return 1000 + k;
        }
    };
};

using namespace _LEET_KTH_MISSING_POSITIVE_NUMBER;

int LEET_KTH_MISSING_POSITIVE_NUMBER()
{
    Solution solution;
    int case1_array[] = { 2,3,4,7,11 };
    vector<int> case1(case1_array, case1_array + _countof(case1_array));
    cout << solution.findKthPositive(case1, 5) << endl;
    return 0;
}