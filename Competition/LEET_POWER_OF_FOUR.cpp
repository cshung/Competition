#include "stdafx.h"

// https://leetcode.com/problems/power-of-four/

#include "LEET_POWER_OF_FOUR.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_POWER_OF_FOUR
{
	class Solution
	{
	public:
		bool isPowerOfFour(int n)
		{
			if (n == 1) return true;
			if (n == 4) return true;
			if (n == 16) return true;
			if (n == 64) return true;
			if (n == 256) return true;
			if (n == 1024) return true;
			if (n == 4096) return true;
			if (n == 16384) return true;
			if (n == 65536) return true;
			if (n == 262144) return true;
			if (n == 1048576) return true;
			if (n == 4194304) return true;
			if (n == 16777216) return true;
			if (n == 67108864) return true;
			if (n == 268435456) return true;
			if (n == 1073741824) return true;
			return false;
		}
	};
};

using namespace _LEET_POWER_OF_FOUR;

int LEET_POWER_OF_FOUR()
{
	Solution solution;
	for (int i = 0; i <= 9; i++)
	{
		cout << solution.isPowerOfFour(i) << endl;
	}
	return 0;
}