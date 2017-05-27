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
			vector<int> freq;
			for (auto&& p : m)
			{
				freq.push_back(p.second);
			}
			if (freq.size() == 1)
			{
				return freq[0];
			}
			else
			{
				int result = freq[0] + freq[1];
				for (size_t i = 2; i < freq.size(); i++)
				{
					result = max(result, freq[i - 1] + freq[i]);
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
