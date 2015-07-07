#include "stdafx.h"

// https://leetcode.com/problems/merge-sorted-array/

#include "LEET_MERGE_SORTED_ARRAY.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_MERGE_SORTED_ARRAY
{
    class Solution
    {
    public:
        void merge(vector<int>& nums1, int m, vector<int>& nums2, int n)
        {
            int f = m - 1;
            int s = n - 1;
            int t = m + n - 1;
            while (f >= 0 || s >= 0)
            {
                if (f == -1)
                {
                    nums1[t--] = nums2[s--];
                }
                else if (s == -1)
                {
                    nums1[t--] = nums1[f--];
                }
                else if (nums1[f] > nums2[s])
                {
                    nums1[t--] = nums1[f--];
                }
                else
                {
                    nums1[t--] = nums2[s--];
                }
            }
        }
    };
};

using namespace _LEET_MERGE_SORTED_ARRAY;

int LEET_MERGE_SORTED_ARRAY()
{
    Solution s;
    int first[6] = { 1, 3, 5, 0, 0, 0 };
    int second[3] = { 2, 4, 6 };
    vector<int> firstVector(first, first + 6);
    vector<int> secondVector(second, second + 3);
    s.merge(firstVector, 3, secondVector, 3);
    for (int i =0 ; i < 6; i++)
    {
        cout << firstVector[i];
    }
    return 0;
}