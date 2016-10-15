#include "stdafx.h"

// https://leetcode.com/problems/patching-array/

#include "LEET_PATCHING_ARRAY.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

// #define LOG

using namespace std;

namespace _LEET_PATCHING_ARRAY
{
    class Solution
    {
    public:
        int minPatches(vector<int>& nums, int n)
        {
            long long minInfeasibleValue = 1;
            int patch = 0;
            int s = nums.size();
            int i = 0;
            bool moved = false;
            int v = 0;
            int f = 0;
            while (true)
            {
                if (moved || i < s)
                {
                    if (!moved)
                    {
                        v = nums[i];
                        f = 1;
                        while (true)
                        {
                            i++;
                            if (i == s)
                            {
                                break;
                            }
                            if (nums[i] != v)
                            {
                                break;
                            }
                            f++;
                        }
                        moved = true;
                    }
                    if (minInfeasibleValue >= v)
                    {
#ifdef LOG
                        cout << v << " is feasible while seeing it" << endl;
#endif
                        minInfeasibleValue += v * f;
#ifdef LOG
                        cout << minInfeasibleValue << " = minInfeasibleValue" << endl;
#endif
                        moved = false;
                    }
                    else
                    {
#ifdef LOG
                        cout << minInfeasibleValue << " is infeasible while seeing it" << endl;
#endif
                        patch++;
                        minInfeasibleValue *= 2;
#ifdef LOG
                        cout << minInfeasibleValue << " = minInfeasibleValue" << endl;
#endif
                    }
                }
                else
                {
#ifdef LOG
                    cout << minInfeasibleValue << " is infeasible while seeing it" << endl;
#endif
                    patch++;
                    minInfeasibleValue *= 2;
#ifdef LOG
                    cout << minInfeasibleValue << " = minInfeasibleValue" << endl;
#endif
                }
                if (minInfeasibleValue > n)
                {
                    break;
                }
            }
            return patch;
        }
    };
};

using namespace _LEET_PATCHING_ARRAY;

int LEET_PATCHING_ARRAY()
{
    Solution solution;
    vector<int> nums;
    nums.push_back(1);
    nums.push_back(2);
    nums.push_back(31);
    nums.push_back(33);
    cout << solution.minPatches(nums, ~(1 << 31)) << endl;
    return 0;
}