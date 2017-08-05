#include "stdafx.h"

// https://leetcode.com/problems/set-mismatch/description/

#include "LEET_SET_MISMATCH.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_SET_MISMATCH
{
    class Solution
    {
    public:
        vector<int> findErrorNums(vector<int>& nums)
        {
            vector<int> result;
            int n = (int)nums.size();
            int duplicated = -1;
            int sum = 0;
            int correct_sum = (n + 1) * n / 2;
            for (int i = 0; i < n; i++)
            {
                sum += nums[i];
            }
            for (int i = 1; i <= n; i++)
            {
                int value = i;
                int index = value - 1;

                if (nums[index] == value)
                {
                    continue;
                }

                value = nums[index];
                nums[index] = -1;
                index = value - 1;

                while (true)
                {
                    if (nums[index] == value)
                    {
                        duplicated = value;
                        break;
                    }
                    else if (nums[index] == -1)
                    {
                        nums[index] = value;
                        break;
                    }
                    else
                    {
                        int next_value = nums[index];
                        nums[index] = value;
                        value = next_value;
                        index = value - 1;
                    }
                }

                if (duplicated != -1)
                {
                    break;
                }
            }
            result.push_back(duplicated);
            result.push_back(correct_sum - sum + duplicated);
            return result;
        }
    };
};

using namespace _LEET_SET_MISMATCH;

int LEET_SET_MISMATCH()
{
    Solution solution;
    int test_array[] = { 2, 4, 1, 2 };
    vector<int> test(test_array, test_array + _countof(test_array));
    vector<int> result = solution.findErrorNums(test);
    cout << result[0] << " " << result[1] << endl;
    return 0;
}