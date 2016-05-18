#include "stdafx.h"

// https://leetcode.com/problems/intersection-of-two-arrays/

#include "LEET_INTERSECTION_OF_TWO_ARRAYS.h"
#include <map>
#include <unordered_set>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_INTERSECTION_OF_TWO_ARRAYS
{
    class Solution
    {
    public:
        vector<int> intersection(vector<int>& nums1, vector<int>& nums2)
        {
            unordered_set<int> nums1_set;
            unordered_set<int> result_set;
            vector<int> result;
            for (size_t i = 0; i < nums1.size(); i++)
            {
                nums1_set.insert(nums1[i]);
            }
            for (size_t i = 0; i < nums2.size(); i++)
            {
                int num = nums2[i];
                if (nums1_set.find(num) != nums1_set.end())
                {
                    result_set.insert(num);
                }
            }
            for (unordered_set<int>::iterator ri = result_set.begin(); ri != result_set.end(); ri++)
            {
                result.push_back(*ri);
            }

            return result;
        }
        
    };
};

using namespace _LEET_INTERSECTION_OF_TWO_ARRAYS;

int LEET_INTERSECTION_OF_TWO_ARRAYS()
{
    Solution solution;
    vector<int> nums1;
    vector<int> nums2;
    nums1.push_back(1);
    nums1.push_back(2);
    nums1.push_back(2);
    nums1.push_back(1);
    nums2.push_back(2);
    nums2.push_back(2);
    vector<int> soln = solution.intersection(nums1, nums2);
    for (size_t i = 0; i < soln.size(); i++)
    {
        cout << soln[i] << endl;
    }
    return 0;
}