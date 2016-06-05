#include "stdafx.h"

// https://leetcode.com/problems/intersection-of-two-arrays-ii/

#include "LEET_INTERSECTION_OF_TWO_ARRAYS_II.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_INTERSECTION_OF_TWO_ARRAYS_II
{
    class Solution
    {
    public:
        vector<int> intersect(vector<int>& nums1, vector<int>& nums2)
        {
            vector<int> result;
            map<int, int> nums1_summary;
            for (size_t i = 0; i < nums1.size(); i++)
            {
                map<int, int>::iterator probe = nums1_summary.find(nums1[i]);
                if (probe == nums1_summary.end())
                {
                    nums1_summary.insert(pair<int, int>(nums1[i], 1));
                }
                else
                {
                    probe->second++;
                }
            }
            for (size_t j = 0; j < nums2.size(); j++)
            {
                map<int, int>::iterator probe = nums1_summary.find(nums2[j]);
                if (probe != nums1_summary.end())
                {
                    if (probe->second > 0)
                    {
                        result.push_back(nums2[j]);
                        probe->second--;
                    }
                }
            }
            return result;
        }
    };
};

using namespace _LEET_INTERSECTION_OF_TWO_ARRAYS_II;

int LEET_INTERSECTION_OF_TWO_ARRAYS_II()
{
    Solution solution;
    vector<int> nums1; nums1.push_back(1); nums1.push_back(2); nums1.push_back(2); nums1.push_back(1);
    vector<int> nums2; nums2.push_back(2); nums2.push_back(2); 
    vector<int> soln = solution.intersect(nums1, nums2);
    for (size_t i = 0; i < soln.size(); i++)
    {
        cout << soln[i] << endl;
    }
    return 0;
}