#include "stdafx.h"

// https://leetcode.com/problems/summary-ranges/

#include "LEET_SUMMARY_RANGES.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_SUMMARY_RANGES
{
    class Solution {
    private:
        void summaryRanges(vector<int>& nums, unsigned int i, vector<string>& append_to)
        {
            while (i < nums.size())
            {
                ostringstream os;
                unsigned int j = i;
                while (j < nums.size() - 1 && (nums[j + 1] == nums[j] + 1))
                {
                    j++;
                }
                if (i == j)
                {
                    os << nums[i];
                }
                else
                {
                    os << nums[i] << "->" << nums[j];
                }
                append_to.push_back(os.str());
                i = j + 1;
            }
        }
    public:
        vector<string> summaryRanges(vector<int>& nums)
        {
            vector<string> result;
            summaryRanges(nums, 0, result);
            return result;
        }
    };
};

using namespace _LEET_SUMMARY_RANGES;

int LEET_SUMMARY_RANGES()
{
    Solution solution;
    int case1[] = {0,1,2,4,5,7};
    vector<string> case1_solution = solution.summaryRanges(vector<int>(case1, case1 + _countof(case1)));
    for (unsigned int i = 0; i < case1_solution.size(); i++)
    {
        cout << case1_solution[i] << ",";
    }
    cout << endl;
    return 0;
}