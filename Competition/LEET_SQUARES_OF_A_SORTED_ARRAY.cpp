#include "stdafx.h"

// https://leetcode.com/problems/squares-of-a-sorted-array/

#include "LEET_SQUARES_OF_A_SORTED_ARRAY.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_SQUARES_OF_A_SORTED_ARRAY
{
    class Solution
    {
    public:
        vector<int> sortedSquares(vector<int>& nums)
        {
            int n = nums.size();
            vector<int> tomerge(n);
            vector<int> answer(n);
            int left = 0;
            int right = n;
            for (int num : nums)
            {
                int square = num * num;
                if (num < 0)
                {
                    tomerge[--right] = square;
                }
                else
                {
                    tomerge[left++] = square;
                }
            }
            
            int p = 0;
            int q = right;
            int r = 0;
            while (p < right || q < n)
            {
                if (p == right)
                {
                    answer[r++] = tomerge[q++];
                }
                else if (q == n)
                {
                    answer[r++] = tomerge[p++];
                }
                else
                {
                    int c = tomerge[p];
                    int d = tomerge[q];
                    if (c < d)
                    {
                        answer[r++] = tomerge[p++];
                    }
                    else
                    {
                        answer[r++] = tomerge[q++];
                    }
                }
            }
            return answer;
        }
    };
};

using namespace _LEET_SQUARES_OF_A_SORTED_ARRAY;

int LEET_SQUARES_OF_A_SORTED_ARRAY()
{
    Solution solution;
    int case1_array[] = { -4, -1, 0, 3, 10 };
    int case2_array[] = { -7, -3, 2, 3, 11 };
    vector<int> case1(case1_array, case1_array + _countof(case1_array));
    vector<int> case2(case2_array, case2_array + _countof(case2_array));
    vector<int> answer1 = solution.sortedSquares(case1);
    vector<int> answer2 = solution.sortedSquares(case2);
    for (auto element : answer1)
    {
        cout << element << " ";
    }
    cout << endl;
    for (auto element : answer2)
    {
        cout << element << " ";
    }
    cout << endl;
    return 0;
}
