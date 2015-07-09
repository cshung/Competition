#include "stdafx.h"

// https://leetcode.com/problems/remove-duplicates-from-sorted-array/

#include "LEET_REMOVE_DUPLICATES_FROM_SORTED_ARRAY.h"
#include <map>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

namespace _LEET_REMOVE_DUPLICATES_FROM_SORTED_ARRAY
{
    class Solution
    {
    public:
        int removeDuplicates(vector<int>& nums)
        {
            if (nums.size() == 0)
            {
                return 0;
            }

            unsigned int c = 1;
            unsigned int w = 1;
            for (unsigned int r = 1; r < nums.size(); r++)
            {
                if (nums[r] != nums[r - 1])
                {
                    c++;
                    nums[w++] = nums[r];
                }
            }
            return c;
        }
    };
};

using namespace _LEET_REMOVE_DUPLICATES_FROM_SORTED_ARRAY;

int LEET_REMOVE_DUPLICATES_FROM_SORTED_ARRAY()
{
    Solution solution;
    vector<int> data;
    data.push_back(1);
    data.push_back(1);
    data.push_back(2);

    cout << solution.removeDuplicates(data) << endl;
    for (int i = 0; i < 2; i++)
    {
        cout << data[i] << endl;
    }
    return 0;
}
