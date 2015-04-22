#include "stdafx.h"

// https://leetcode.com/problems/median-of-two-sorted-arrays/

#include "LEET_MEDIAN_OF_TWO_SORTED_ARRAYS.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_MEDIAN_OF_TWO_SORTED_ARRAYS
{
    class Solution
    {
    public:
        double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2)
        {
            int size1 = nums1.size();
            int size2 = nums2.size();
            int size = size1 + size2;
            int mid = size / 2;
            if (size % 2 == 0)
            {
                // a[10] => (a[4] + a[5]) * 0.5
                return (select(nums1, nums2, 0, size1, 0, size2, mid) + select(nums1, nums2, 0, size1, 0, size2, mid + 1)) * 0.5;
            }
            else
            {
                // a[9] => a[4]
                return select(nums1, nums2, 0, size1, 0, size2, mid);
            }
        }
    private:
        int select(vector<int>& nums1, vector<int>& nums2, int s1, int e1, int s2, int e2, int k)
        {
            int size1 = e1 - s1;
            int size2 = e2 - s2;
            int size = size1 + size2;
            if (size1 == 0)
            {
                return nums2[s2 + k];
            }
            else if (size2 == 0)
            {
                return nums1[s1 + k];
            }
            else
            {
                // First, all elements n[i] = n[i] + epsilon * i with sufficiently small epsilon, which means all elements are unique (i measured from the two vectors concatenated)
                int probe1 = size1 / 2; // To be determined
                int probe2 = size2 / 2; // To be determined
                int probe1_value = nums1[s1 + probe1];
                int probe2_value = nums2[s2 + probe2];

                // Denote all the numbers smaller than probe1 in nums1 be the set A with size a
                // Denote all the numbers greater than probe1 in nums1 be the set B with size b
                // Denote all the numbers smaller than probe2 in nums2 be the set C with size c
                // Denote all the numbers greater than probe2 in nums2 be the set D with size d
                
                int a = probe1;
                int b = size1 - probe1 - 1;
                int c = probe2;
                int d = size2 - probe2 - 1;

                // Just an algebraic identity, we have
                // a + b + c + d = size1 + size2 - 2
                //               = size - 2
                //     a + c + 1 = size - b - d - 1

                if (probe1_value <= probe2_value) // Note the assumption above, it is the same as saying probe1_value epsilon modified is less than as probe2_value
                {
                    if (a + c + 1 >= k + 1)
                    {
                        // The number of elements smaller than probe2_value is at least a + c + 1
                        // so we can safely discard any values known to be larger than or equal to probe2_value
                        return select(nums1, nums2, s1, e1, s2, probe2, k);
                    }
                    else if (a + c + 1 <= k)
                    {                        
                        // The number of elements greater than probe1_value is at least b + d + 1
                        // The number of elements smaller than probe1_value is at most size - b - d - 1 = a + c + 1
                        // so we can safely discard any values known to be smaller than probe1_value
                        return select(nums1, nums2, s1 + probe1 + 1, e1, s2, e2, k - probe1 - 1);
                    }
                }
                else if (probe1_value > probe2_value)
                {
                    if (a + c + 1 >= k + 1)
                    {                        
                        // The number of elements smaller than probe1_value is at least a + c + 1
                        // so we can safely discard any values known to be larger than or equal to probe1_value
                        return select(nums1, nums2, s1, probe1, s2, e2, k);
                    }
                    else if (a + c + 1 <= k)
                    {
                        // The number of elements greater than probe2_value is at least b + d + 1
                        // The number of elements smaller than probe2_value is at most size - b - d - 1 = a + c + 1
                        // so we can safely discard any values known to be smaller than probe2_value
                        return select(nums1, nums2, s1, e1, s2 + probe2 + 1, e2, k - probe2 - 1);
                    }
                }

                return 0;
            }
        }
    };
};

using namespace _LEET_MEDIAN_OF_TWO_SORTED_ARRAYS;

int LEET_MEDIAN_OF_TWO_SORTED_ARRAYS()
{
    Solution solution;
    int nums2[] = { 1, 2, 3 };
    int nums1[] = { 4, 5 };
    vector<int> nums1v(nums1, nums1 + sizeof(nums1) / sizeof(nums1[0]));
    vector<int> nums2v(nums2, nums2 + sizeof(nums2) / sizeof(nums2[0]));
    cout << solution.findMedianSortedArrays(nums1v, nums2v) << endl;
    return 0;
}