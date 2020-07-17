#include "stdafx.h"

// https://leetcode.com/problems/top-k-frequent-elements/

#include "LEET_TOP_K_FREQUENT_ELEMENTS.h"
#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_TOP_K_FREQUENT_ELEMENTS
{
    class Solution
    {
    public:
        vector<int> topKFrequent(vector<int>& nums, int k)
        {
            unordered_map<int, int> freq;
            for (auto num : nums)
            {
                auto probe = freq.find(num);
                if (probe == freq.end())
                {
                    freq.insert(make_pair(num, -1));
                }
                else
                {
                    probe->second--;
                }
            }
            vector<int> freqs;
            for (auto pair : freq)
            {
                freqs.push_back(pair.second);
            }
            nth_element(freqs.begin(), freqs.begin() + k - 1, freqs.end());
            vector<int> answer;
            for (auto pair : freq)
            {
                if (pair.second <= freqs[k - 1])
                {
                    answer.push_back(pair.first);
                }
            }
            return answer;
        }
    };
};

using namespace _LEET_TOP_K_FREQUENT_ELEMENTS;

int LEET_TOP_K_FREQUENT_ELEMENTS()
{
    Solution solution;
    int nums_array[] = { 1,1,1,2,2,3 };
    vector<int> nums(nums_array, nums_array + _countof(nums_array));
    for (auto s : solution.topKFrequent(nums, 2))
    {
        cout << s << " ";
    }
    cout << endl;
    return 0;
}