#include "stdafx.h"

// https://leetcode.com/problems/two-city-scheduling/

#include "LEET_TWO_CITY_SCHEDULING.h"
#include <map>
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_TWO_CITY_SCHEDULING
{

    class Solution {
    public:
        int twoCitySchedCost(vector<vector<int>>& costs) {
            sort(costs.begin(), costs.end(), [](vector<int> left, vector<int> right)
            {
                return (left[1] - left[0]) > (right[1] - right[0]);
            });
            int answer = 0;
            int n = costs.size() / 2;
            for (int i = 0; i < n; i++)
            {
                answer += costs[i][0] + costs[i + n][1];
            }
            return answer;
        }
    };

};

using namespace _LEET_TWO_CITY_SCHEDULING;

int LEET_TWO_CITY_SCHEDULING()
{
    vector<int> a;
    vector<int> b;
    vector<int> c;
    vector<int> d;
    vector<vector<int>> costs;
    a.push_back(10); a.push_back(20);
    b.push_back(30); b.push_back(200);
    c.push_back(400); c.push_back(50);
    d.push_back(30); d.push_back(20);
    costs.push_back(a);
    costs.push_back(b);
    costs.push_back(c);
    costs.push_back(d);
    Solution s;
    cout << s.twoCitySchedCost(costs) << endl;
    return 0;
}