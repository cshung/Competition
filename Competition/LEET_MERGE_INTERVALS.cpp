#include "stdafx.h"

// https://leetcode.com/problems/merge-intervals/

#include "LEET_MERGE_INTERVALS.h"
#include <map>
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_MERGE_INTERVALS
{
    class Solution
    {
    public:
        vector<vector<int>> merge(vector<vector<int>>& intervals)
        {
            int n = intervals.size();
            vector<vector<int>> endpoints(n * 2, vector<int>(2));

            for (int i = 0; i < n; i++)
            {
                endpoints[2 * i + 0][0] = intervals[i][0];
                endpoints[2 * i + 0][1] = 1;
                endpoints[2 * i + 1][0] = intervals[i][1];
                endpoints[2 * i + 1][1] = 0;
            }
            sort(endpoints.begin(), endpoints.end(), [](vector<int> left, vector<int> right)
            {
                return left[0] < right[0] || left[0] == right[0] && left[1] && !right[1];
            });

            int open = 0;
            int start = -1;
            int end = -1;
            vector<vector<int>> answer;
            bool continuing = false;
            for (int i = 0; i < 2 * n; i++)
            {
                if (endpoints[i][1])
                {
                    if (open == 0 && !continuing)
                    {
                        start = endpoints[i][0];
                    }
                    open++;
                }
                else
                {
                    open--;
                    if (open == 0)
                    {
                        if (i < 2 * n - 1 && endpoints[i][0] == endpoints[i + 1][0])
                        {
                            continuing = true;
                        }
                        else
                        {
                            end = endpoints[i][0];
                            vector<int> interval(2);
                            interval[0] = start;
                            interval[1] = end;
                            answer.push_back(interval);
                        }
                    }
                }
            }
            return answer;
        }
    };
};

using namespace _LEET_MERGE_INTERVALS;

int LEET_MERGE_INTERVALS()
{
    Solution solution;
    vector<vector<int>> case1(4, vector<int>(2));
    case1[0][0] = 1;
    case1[0][1] = 3;
    case1[1][0] = 2;
    case1[1][1] = 6;
    case1[2][0] = 8;
    case1[2][1] = 10;
    case1[3][0] = 15;
    case1[3][1] = 18;
    vector<vector<int>> answers = solution.merge(case1);
    for (vector<int> answer : answers)
    {
        cout << answer[0] << "," << answer[1] << endl;
    }
    return 0;
}