#include "stdafx.h"

// https://leetcode.com/problems/missing-ranges/

#include "LEET_MISSING_RANGES.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_MISSING_RANGES
{
    class Solution
    {
    public:
        vector<string> findMissingRanges(vector<int>& nums, int lower, int upper)
        {
            vector<string> result;
            int64_t needed = lower;
            for (auto num : nums)
            {
                if (num == needed)
                {
                    needed++;
                }
                else if (num > needed)
                {
                    emit(needed, num - 1, result);
                    needed = (int64_t)num + 1;
                }
            }
            if (needed <= upper)
            {
                emit(needed, upper, result);
            }
            return result;
        }

        void emit(int64_t from, int to, vector<string>& result)
        {
            ostringstream oss;
            if (from == to)
            {
                oss << from;
            }
            else
            {
                oss << from;
                oss << "->";
                oss << to;
            }
            result.push_back(oss.str());
        }
    };
};

using namespace _LEET_MISSING_RANGES;

int LEET_MISSING_RANGES()
{
    Solution solution;
    int test_array[] = { 0, 1, 3, 50, 75 };
    vector<int> test(test_array, test_array + _countof(test_array));
    vector<string> answers = solution.findMissingRanges(test, 0, 99);
    for (auto answer : answers)
    {
        cout << answer << endl;
    }
    return 0;
}