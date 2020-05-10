#include "stdafx.h"

// https://leetcode.com/problems/find-the-town-judge/

#include "LEET_FIND_THE_TOWN_JUDGE.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_FIND_THE_TOWN_JUDGE
{
    class Solution
    {
    public:
        int findJudge(int N, vector<vector<int>>& trust)
        {
            vector<int> indegree;
            vector<int> outdegree;
            indegree.resize(N);
            outdegree.resize(N);
            for (int i = 0; i < N; i++)
            {
                indegree[i] = outdegree[i] = 0;
            }
            for (auto pair : trust)
            {
                outdegree[pair[0] - 1]++;
                indegree[pair[1] - 1]++;
            }
            int candidate = -1;
            for (int i = 0; i < N; i++)
            {
                if (indegree[i] == N - 1 && outdegree[i] == 0)
                {
                    if (candidate == -1)
                    {
                        candidate = i + 1;
                    }
                    else
                    {
                        return -1;
                    }
                }
            }
            return candidate;
        }
    };
};

using namespace _LEET_FIND_THE_TOWN_JUDGE;

int LEET_FIND_THE_TOWN_JUDGE()
{
    Solution solution;
    vector<vector<int>> trust;
    vector<int> pair;
    pair.push_back(1);
    pair.push_back(2);
    trust.push_back(pair);
    cout << solution.findJudge(2, trust) << endl;
    return 0;
}