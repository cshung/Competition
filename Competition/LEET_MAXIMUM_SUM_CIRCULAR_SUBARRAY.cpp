#include "stdafx.h"

// https://leetcode.com/problems/maximum-sum-circular-subarray

#include "LEET_MAXIMUM_SUM_CIRCULAR_SUBARRAY.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_MAXIMUM_SUM_CIRCULAR_SUBARRAY
{
    class Solution
    {
    public:
        int maxSubarraySumCircular(vector<int>& A)
        {
            if (A.size() == 0)
            {
                return 0;
            }
            int sum = A[0];
            int maxStart = 0;
            int maxEnd = 1;
            int max = A[0];
            int minStart = 0;
            int minEnd = 1;
            int min = A[0];
            int maxAtEnd = A[0];
            int minAtEnd = A[0];
            for (int i = 1; i < A.size(); i++)
            {
                sum += A[i];
                int newMaxStart = maxStart;
                if (maxAtEnd > 0)
                {
                    maxAtEnd += A[i];
                }
                else
                {
                    newMaxStart = i;
                    maxAtEnd = A[i];
                }
                if (maxAtEnd > max)
                {
                    maxStart = newMaxStart;
                    maxEnd = i + 1;
                    max = maxAtEnd;
                }
                int newMinStart = minStart;
                if (minAtEnd < 0)
                {
                    minAtEnd += A[i];
                }
                else
                {
                    minStart = i;
                    minAtEnd = A[i];
                }
                if (minAtEnd < min)
                {
                    minStart = newMinStart;
                    minEnd = i + 1;
                    min = minAtEnd;
                }
            }
            int wrap = sum - min;
            if (wrap > max && (minEnd - minStart) != A.size())
            {
                max = wrap;
            }

            return max;
        }
    };
};

using namespace _LEET_MAXIMUM_SUM_CIRCULAR_SUBARRAY;

int LEET_MAXIMUM_SUM_CIRCULAR_SUBARRAY()
{
    Solution solution;
    int test_array1[] = { 1,-2,3,-2 };
    int test_array2[] = { 5,-3,5 };
    int test_array3[] = { 3,-1,2,-1 };
    int test_array4[] = { 3,-2,2,-3 };
    int test_array5[] = { -2,-3,-1 };
    int test_array6[] = { -2 };
    
    vector<int> test1(test_array1, test_array1 + _countof(test_array1));
    vector<int> test2(test_array2, test_array2 + _countof(test_array2));
    vector<int> test3(test_array3, test_array3 + _countof(test_array3));
    vector<int> test4(test_array4, test_array4 + _countof(test_array4));
    vector<int> test5(test_array5, test_array5 + _countof(test_array5));
    vector<int> test6(test_array6, test_array6 + _countof(test_array6));

    cout << solution.maxSubarraySumCircular(test1) << endl;
    cout << solution.maxSubarraySumCircular(test2) << endl;
    cout << solution.maxSubarraySumCircular(test3) << endl;
    cout << solution.maxSubarraySumCircular(test4) << endl;
    cout << solution.maxSubarraySumCircular(test5) << endl;
    cout << solution.maxSubarraySumCircular(test6) << endl;

    return 0;
}