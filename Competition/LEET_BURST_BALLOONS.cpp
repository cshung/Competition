#include "stdafx.h"

// https://leetcode.com/problems/burst-balloons/

#include "LEET_BURST_BALLOONS.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

namespace _LEET_BURST_BALLOONS
{
    class Solution
    {
    public:
		int maxCoins(vector<int>& nums)
		{
			if (nums.size() == 0)
			{
				return 0;
			}

			// interval_solution[i][j] represents the maximum number of coins one can collect 
			// in the range [i, j] subject to the constraint that the (i-1)th and the (j+1)th 
			// balloon is not bursted until all balloons in [i, j] are bursted.
			vector<vector<int>> interval_solution;
			unsigned int n = nums.size();
			interval_solution.resize(n);
			for (unsigned int i = 0; i < n; i++)
			{
				interval_solution[i].resize(n);
			}

			// We build the solution from short interval to long ones
			for (int interval_length = 1; interval_length <= n; interval_length++)
			{
				int interval_src = 0;
				while (true)
				{
					int interval_dst = interval_src + interval_length - 1; // the inclusive end index
					if (interval_dst == n)
					{
						break;
					}

					int best = -1;
					for (int last_balloon = interval_src; last_balloon <= interval_dst; last_balloon++)
					{	
						// Since this is the last balloon to burst, all other balloons within the interval are bursted
						// So at the time the last balloon is bursted, the last balloon is between the boundary of the interval
						int last_balloon_prev_value = interval_src == 0     ? 1 : nums[interval_src - 1];
						int last_balloon_next_value = interval_dst == n - 1 ? 1 : nums[interval_dst + 1];
						int burst_value = last_balloon_prev_value * nums[last_balloon] * last_balloon_next_value;

						// The total value of bursting all balloon is divided into three parts, the 
						// portion before the last balloon, the last balloon itself, and the portion after the last balloon.
						// In actual bursting, one could interleave bursting balloon is the left hand side or right hand side.
						// The optimal bursting value is unchanged
						int prev_value = last_balloon == interval_src ? 0 : interval_solution[interval_src][last_balloon - 1];
						int next_value = last_balloon == interval_dst ? 0 : interval_solution[last_balloon + 1][interval_dst];

						int total_value = prev_value + burst_value + next_value;

						best = max(best, total_value);						
					}
					interval_solution[interval_src][interval_dst] = best;

					interval_src++;
				}
			}
			return interval_solution[0][n - 1];
        }
    };
};

using namespace _LEET_BURST_BALLOONS;

int LEET_BURST_BALLOONS()
{
    int case1[] = { 3, 1, 5, 8 };
    Solution solution;
    cout << solution.maxCoins(vector<int>(case1, case1 + _countof(case1))) << endl;
    return 0;
}