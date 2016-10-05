#include "stdafx.h"

// https://leetcode.com/problems/split-array-largest-sum/

#include "LEET_SPLIT_ARRAY_LARGEST_SUM.h"
#include <map>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_SPLIT_ARRAY_LARGEST_SUM
{
	class Solution
	{
	public:
		int splitArray(vector<int>& nums, int m)
		{
			long long total = 0;
			for (size_t i = 0; i < nums.size(); i++)
			{
				total += nums[i];
			}
			
			// lo is always infeasible
			// hi is always feasible
			long long lo = -1;
			long long hi = total;
			while (lo + 1 < hi)
			{
				long long mid = lo + (hi - lo) / 2;
				long long run = 0;
				int seg = 1;
				for (size_t i = 0; i < nums.size(); i++)
				{
					if (run + nums[i] <= mid)
					{
						run += nums[i];
					}
					else
					{
						if (nums[i] > mid)
						{
							seg = m + 1;
							break;
						}
						i--;
						seg++;
						run = 0;
					}
				}
				if (seg <= m)
				{
					hi = mid;
				}
				else
				{
					lo = mid;
				}
			}

			return hi;
		}
	};
};

using namespace _LEET_SPLIT_ARRAY_LARGEST_SUM;

int LEET_SPLIT_ARRAY_LARGEST_SUM()
{
	Solution solution;
	vector<int> input;
	input.push_back(1);
	input.push_back(2147483646);
	cout << solution.splitArray(input, 2) << endl;
	return 0;
}