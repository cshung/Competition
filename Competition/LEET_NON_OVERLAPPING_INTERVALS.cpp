#include "stdafx.h"

// https://leetcode.com/problems/non-overlapping-intervals/

#include "LEET_NON_OVERLAPPING_INTERVALS.h"
#include <map>
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_NON_OVERLAPPING_INTERVALS
{

    class Solution
    {
    public:
        int eraseOverlapIntervals(vector<vector<int>>& intervals)
        {
            sort(intervals.begin(), intervals.end(), [](vector<int> left, vector<int> right)
            {
                return left[1] < right[1];
            });

            bool first = true;
            int last = 0;
            int drop = 0;
            for (int i = 0; i < intervals.size(); i++)
            {
                int begin = intervals[i][0];
                int end = intervals[i][1];
                if (first)
                {
                    last = end;
                    first = false;
                }
                else
                {
                    if (begin >= last)
                    {
                        last = end;
                    }
                    else
                    {
                        drop++;
                    }
                }
            }

            return drop;
        }
    };
};

using namespace _LEET_NON_OVERLAPPING_INTERVALS;

int LEET_NON_OVERLAPPING_INTERVALS()
{
    vector<vector<int>> case1(4, vector<int>(2));
    case1[0][0] = 1; case1[0][1] = 2;
    case1[1][0] = 2; case1[1][1] = 3;
    case1[2][0] = 3; case1[2][1] = 4;
    case1[3][0] = 1; case1[3][1] = 3;
    Solution s;
    cout << s.eraseOverlapIntervals(case1) << endl;
    return 0;
}