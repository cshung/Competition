#include "stdafx.h"

// https://leetcode.com/problems/find-right-interval/

#include "LEET_FIND_RIGHT_INTERVAL.h"
#include <map>
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_FIND_RIGHT_INTERVAL
{
    class Solution
    {
    public:
        vector<int> findRightInterval(vector<vector<int>>& intervals)
        {
            for (int i = 0; i < intervals.size(); i++)
            {
                intervals[i].push_back(i);
            }
            sort(intervals.begin(), intervals.end(), [](vector<int> x, vector<int> y)
            {
                return x[0] < y[0];
            });
            vector<int> answer(intervals.size(), -1);
            for (auto interval : intervals)
            {
                vector<vector<int>> x;
                vector<int> fake;
                fake.push_back(interval[1]);
                auto probe = lower_bound(intervals.begin(), intervals.end(), fake, [](vector<int> x, vector<int> y) {
                    return x[0] < y[0];
                });
                answer[interval[2]] = (probe == intervals.end()) ? -1 : (*probe)[2];
            }
            return answer;
        }
    };
};

using namespace _LEET_FIND_RIGHT_INTERVAL;

int LEET_FIND_RIGHT_INTERVAL()
{
    vector<vector<int>> problem(1);
    problem[0].push_back(1);
    problem[0].push_back(2);
    Solution s;
    auto answers = s.findRightInterval(problem);
    for (auto answer : answers)
    {
        cout << answer << " ";
    }
    cout << endl;
    return 0;
}