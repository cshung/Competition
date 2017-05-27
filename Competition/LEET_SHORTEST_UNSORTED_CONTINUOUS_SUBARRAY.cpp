#include "stdafx.h"

// https://leetcode.com/problems/shortest-unsorted-continuous-subarray

#include "LEET_SHORTEST_UNSORTED_CONTINUOUS_SUBARRAY.h"
#include <map>
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_SHORTEST_UNSORTED_CONTINUOUS_SUBARRAY
{
	class Solution
	{
	public:
		int findUnsortedSubarray(vector<int>& nums)
		{
			vector<int> sorted(nums.begin(), nums.end());
			sort(sorted.begin(), sorted.end());
			int result = (int)nums.size();
			int s = 0;
			while (s < nums.size() && nums[s] == sorted[s])
			{
				s++;
				result--;
			}
			int e = (int)(nums.size() - 1);
			while (e >= s && nums[e] == sorted[e])
			{
				e--;
				result--;
			}
			return result;
		}
	};
};

using namespace _LEET_SHORTEST_UNSORTED_CONTINUOUS_SUBARRAY;

int LEET_SHORTEST_UNSORTED_CONTINUOUS_SUBARRAY()
{
	Solution s;
	int input_array[] = { 2, 6, 4, 8, 10, 9, 15 };
	vector<int> input(input_array, input_array + _countof(input_array));
	cout << s.findUnsortedSubarray(input) << endl;
	return 0;
}
