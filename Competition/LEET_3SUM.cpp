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
            }
            
            for (unsigned int i = 0; i < nums.size(); i++)
            {
                if (i != 0 && nums[i] == nums[i - 1])
                {
                    continue;
                }
                for (unsigned int j = (i + 1); j < nums.size(); j++)
                {
                    if ((j - 1) != i && nums[j] == nums[j - 1])
                    {
                        continue;
                    }
                    int sum = nums[i] + nums[j];
                    int target = -sum;
                    map<int, int>::iterator probe = count.find(target);
                    if (probe != count.end())
                    {
                        int requiredCount = 1;
                        if (target == nums[i])
                        {
                            requiredCount++;
                        }
                        if (target == nums[j])
                        {
                            requiredCount++;
                        }
                        if (probe->second >= requiredCount)
                        {
                            if (target >= nums[j])
                            {
#ifdef LOG
                                cout << nums[i] << " " << nums[j] << " " << target << endl;
#endif
                                int tuple[] = { nums[i], nums[j], target };
                                result.push_back(vector<int>(tuple, tuple + 3));
                            }
                        }
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
    int case5[] = { 3, 0, -2, -1, 1, 2 };
    int case6[] = { -1, 0, 1 };

    Solution s;
    s.threeSum(vector<int>(case1, case1 + _countof(case1)));
    cout << "-------------------------------------------------" << endl;
    s.threeSum(vector<int>(case2, case2 + _countof(case2)));
    cout << "-------------------------------------------------" << endl;
    s.threeSum(vector<int>(case3, case3 + _countof(case3)));
    cout << "-------------------------------------------------" << endl;
    s.threeSum(vector<int>(case4, case4 + _countof(case4)));
    cout << "-------------------------------------------------" << endl;
    s.threeSum(vector<int>(case5, case5 + _countof(case5)));
    cout << "-------------------------------------------------" << endl;
    s.threeSum(vector<int>(case6, case6 + _countof(case6)));
    return 0;
}