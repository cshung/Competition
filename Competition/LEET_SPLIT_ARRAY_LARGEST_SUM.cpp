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
			int n = nums.size();

			// Running sum (j) = sum[0 .. j) nums
			vector<int> runningSums;
			runningSums.resize(n + 1);
			runningSums[0] = 0;
			int sum = 0;
			for (int i = 0; i < n; i++)
			{
				sum += nums[i];
				runningSums[i + 1] = sum;
			}

			// Let S(p, q) be the minimum largest sum that we can obtain by splitting nums[p..n) into q parts
			// Base case:
			// S(p, 1) = sum(num[p..n))
			// 
			// S(p, k) = min_r(sum(num[p,r)),S(r,k-1))
			//
			// [n - k + 0, n - k + 1, ..., n - k + k) has k elements
			//
			// Therefore the range of p is
			// [0 <= p <= (n - k)]
			// [p < r <= (n - k + 1)]

			int k = 1;
			vector<int> buffer1; 
			vector<int> buffer2; 
			buffer1.resize(n);
			buffer2.resize(n);

			vector<int>& initial_solution = buffer1;

			// Initialization
			for (int p = 0; p < n; p++)
			{
				initial_solution[p] = runningSums[n] - runningSums[p];
			}

			vector<int>* prev_solution_ptr = &buffer1;
			vector<int>* next_solution_ptr = &buffer1;

			// Iteration
			for (int k = 2; k <= m; k++)
			{
				vector<int>& prev_solution = *prev_solution_ptr;
				vector<int>& next_solution = *next_solution_ptr;
				for (int p = 0; p <= (n - k); p++)
				{
					int current_min = ~(1 << 31);
					for (int r = p + 1; r <= (n - k + 1); r++)
					{
						int head = runningSums[r] - runningSums[p];
						int tail = prev_solution[r];
						int largestSum = max(head, tail);
						// cout << "[" << p << ", " << r << ") = " << head << ", [" << r << "..." << n << ") = " << tail << endl;
						current_min = min(current_min, largestSum);
					}
					next_solution[p] = current_min;
					// cout << "[" << p << "..." << n << ") = " << next_solution[p] << endl << endl;
				}
				vector<int>* temp = prev_solution_ptr;
				prev_solution_ptr = next_solution_ptr;
				next_solution_ptr = temp;
				// cout << "================================================" << endl;
			}
			return (*prev_solution_ptr)[0];
		}
	};
};

using namespace _LEET_SPLIT_ARRAY_LARGEST_SUM;

int LEET_SPLIT_ARRAY_LARGEST_SUM()
{
	Solution solution;
	vector<int> input;
	input.push_back(1);
	input.push_back(2);
	input.push_back(3);
	input.push_back(4);
	input.push_back(5);

	cout << solution.splitArray(input, 3) << endl;
	return 0;
}