#include "stdafx.h"

// https://leetcode.com/problems/3sum/

#include "LEET_3SUM.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

namespace _LEET_3SUM
{
#define LOG
    class Solution
    {
    public:
        vector<vector<int>> threeSum(vector<int>& nums)
        {
            vector<vector<int>> result;
            sort(nums.begin(), nums.end());
            vector<int> dedup;
            vector<int> dup;
            map<int, int> count;
            bool seen = false;
            for (unsigned int i = 0; i < nums.size(); i++)
            {
                map<int, int>::iterator probe = count.find(nums[i]);
                if (probe == count.end())
                {
                    count.insert(pair<int, int>(nums[i], 1));
                }
                else
                {
                    probe->second++;
                }
                if (i != 0)
                {
                    if (nums[i] == nums[i - 1])
                    {
                        if (seen)
                        {
                            continue;
                        }
                        else
                        {
                            dup.push_back(nums[i]);
                            seen = true;
                        }
                    }
                    else
                    {
                        dedup.push_back(nums[i]);
                        seen = false;
                    }
                }
                else
                {
                    dedup.push_back(nums[i]);
                }
            }

            int minTargetFound = ~(1 << 31);
            for (unsigned int i = 0; i < dedup.size(); i++)
            {
                for (unsigned int j = (i + 1); j < dedup.size(); j++)
                {
                    if (dedup[j] >= minTargetFound)
                    {
                        goto next;
                    }
                    int sum = dedup[i] + dedup[j];
                    int target = -sum;
                    map<int, int>::iterator probe = count.find(target);
                    if (probe != count.end())
                    {
                        int requiredCount = 1;
                        if (target == dedup[i])
                        {
                            requiredCount++;
                        }
                        if (target == dedup[j])
                        {
                            requiredCount++;
                        }
                        if (probe->second >= requiredCount)
                        {
                            if (target < minTargetFound)
                            {
                                minTargetFound = target;
                            }
#ifdef LOG
                            cout << dedup[i] << " " << dedup[j] << " " << target << endl;
#endif
                            int tuple[] = { dedup[i], dedup[j], target };
                            result.push_back(vector<int>(tuple, tuple + 3));
                        }
                    }
                }
            }
next:
            minTargetFound = ~(1 << 31);
            for (unsigned int i = 0; i < dup.size(); i++)
            {
                if (dup[i] >= minTargetFound)
                {
                    break;
                }
                int sum = dup[i] * 2;
                int target = -sum;
                map<int, int>::iterator probe = count.find(target);
                if (probe != count.end())
                {
                    int requiredCount = 1;
                    if (target == dup[i])
                    {
                        requiredCount += 2;
                    }
                    if (probe->second >= requiredCount)
                    {
                        if (target < minTargetFound)
                        {
                            minTargetFound = target;
                        }
#ifdef LOG
                        cout << dup[i] << " " << dup[i] << " " << target << endl;
#endif
                        int tuple[] = { dup[i], dup[i], target };
                        result.push_back(vector<int>(tuple, tuple + 3));
                    }
                }
            }

            return result;
        }
    };
};

using namespace _LEET_3SUM;

int LEET_3SUM()
{
    int case1[] = {-1, 0, 1, 2, -1, -4};
    int case2[] = {1, 0, 1, 0, 1, 0};
    int case3[] = {-1,0,1,0};
    int case4[] = {-2, 1, 1};

    Solution s;
    s.threeSum(vector<int>(case1, case1 + _countof(case1)));
    cout << "-------------------------------------------------" << endl;
    s.threeSum(vector<int>(case2, case2 + _countof(case2)));
    cout << "-------------------------------------------------" << endl;
    s.threeSum(vector<int>(case3, case3 + _countof(case3)));
    cout << "-------------------------------------------------" << endl;
    s.threeSum(vector<int>(case4, case4 + _countof(case4)));
    return 0;
}