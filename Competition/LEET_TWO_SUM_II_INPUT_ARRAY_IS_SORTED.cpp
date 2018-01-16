#include "stdafx.h"

// https://leetcode.com/problems/two-sum-ii-input-array-is-sorted

#include "LEET_TWO_SUM_II_INPUT_ARRAY_IS_SORTED.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_TWO_SUM_II_INPUT_ARRAY_IS_SORTED
{
    class Solution
    {
    public:
        vector<int> twoSum(vector<int>& numbers, int target) {
            vector<int> result;
            size_t s = 0;
            size_t e = numbers.size() - 1;
            while (true)
            {
                if (s >= e)
                {
                    break;
                }
                int sum = numbers[s] + numbers[e];
                if (sum < target)
                {
                    s++;
                }
                else if (sum > target)
                {
                    e--;
                }
                else
                {
                    result.push_back(s + 1);
                    result.push_back(e + 1);
                    break;
                }
            }
            return result;
        }
    };
};

using namespace _LEET_TWO_SUM_II_INPUT_ARRAY_IS_SORTED;

int LEET_TWO_SUM_II_INPUT_ARRAY_IS_SORTED()
{
    int case1[] = { 2, 7, 11, 15 };
    Solution solution;
    vector<int> result = solution.twoSum(vector<int>(case1, case1 + _countof(case1)), 9);
    cout << result[0] << ", " << result[1] << endl;
    return 0;
}