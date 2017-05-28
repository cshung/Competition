#include "stdafx.h"

// https://leetcode.com/problems/longest-harmonious-subsequence

#include "LEET_LONGEST_HARMONIOUS_SUBSEQUENCE.h"
#include <map>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

namespace _LEET_LONGEST_HARMONIOUS_SUBSEQUENCE
{
    class Solution
    {
    public:
        int findLHS(vector<int>& nums)
        {
            map<int, int> m;
            for (auto&& n : nums)
            {
                auto probe = m.find(n);
                if (probe == m.end())
                {
                    m.insert(make_pair(n, 1));
                }
                else
                {
                    probe->second++;
                }
            }
            vector<pair<int, int>> freq;
            for (auto&& p : m)
            {
                freq.push_back(p);
            }
            if (freq.size() < 2)
            {
                return 0;
            }
            else
            {
                int result = 0;
                for (size_t i = 1; i < freq.size(); i++)
                {
                    if (freq[i - 1].first + 1 == freq[i].first)
                    {
                        result = max(result, freq[i - 1].second + freq[i].second);
                    }
                }
                return result;
            }
        }
    };
};

using namespace _LEET_LONGEST_HARMONIOUS_SUBSEQUENCE;

int LEET_LONGEST_HARMONIOUS_SUBSEQUENCE()
{
    Solution s;
    int input_array[] = { 1,3,2,2,5,2,3,7 };
    vector<int> input(input_array, input_array + _countof(input_array));
    cout << s.findLHS(input) << endl;
    return 0;
}
