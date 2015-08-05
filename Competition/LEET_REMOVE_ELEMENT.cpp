#include "stdafx.h"

// https://leetcode.com/problems/remove-element/

#include "LEET_REMOVE_ELEMENT.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_REMOVE_ELEMENT
{
    class Solution
    {
    public:
        int removeElement(vector<int>& nums, int val)
        {
            unsigned int i = 0;
            unsigned int j = 0;
            while (i < nums.size())
            {
                if (nums[i] != val)
                {
                    nums[j++] = nums[i];
                }
                i++;
            }
            return j;
        }
    };
};

using namespace _LEET_REMOVE_ELEMENT;

int LEET_REMOVE_ELEMENT()
{
    Solution solution;
    int case1[] = { 3, 2, 3, 3, 1, 2, 3 };
    vector<int> v1 = vector<int>(case1, case1 + _countof(case1));
    int newLength = solution.removeElement(v1, 2);
    for (int i = 0; i < newLength; i++)
    {
        cout << v1[i] << endl;
    }

    return 0;
}