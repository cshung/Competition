#include "stdafx.h"

// https://leetcode.com/problems/subarray-sum-equals-k

#include "LEET_SUBARRAY_SUM_EQUALS_K.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_SUBARRAY_SUM_EQUALS_K
{
	class Solution
	{
	public:
		int subarraySum(vector<int>& nums, int k)
		{
			int n = (int)nums.size();
			vector<int> running_sums;
			running_sums.resize(n + 1);
			running_sums[0] = 0;
			for (int i = 0; i < n; i++)
			{
				running_sums[i + 1] = nums[i] + running_sums[i];
			}
			map<int, int> wanted_count;
			int result = 0;
			for (int i = 0; i < (n + 1); i++)
			{
				auto probe1 = wanted_count.find(running_sums[i]);
				if (probe1 != wanted_count.end())
				{
					result += probe1->second;
				}
				int wanted = k + running_sums[i];
				auto probe2 = wanted_count.find(wanted);
				if (probe2 == wanted_count.end())
				{
					wanted_count.insert(make_pair(wanted, 1));
				}
				else
				{
					probe2->second++;
				}
			}
			return result;
		}
	};
};

using namespace _LEET_SUBARRAY_SUM_EQUALS_K;

int LEET_SUBARRAY_SUM_EQUALS_K()
{
	Solution s;
	int input_array[] = { 1, 1, 1 };
	vector<int> input(input_array, input_array + _countof(input_array));
	cout << s.subarraySum(input, 2) << endl;
	return 0;
}