#include "stdafx.h"

// https://leetcode.com/problems/all-paths-from-source-to-target/

#include "LEET_ALL_PATHS_FROM_SOURCE_TO_TARGET.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_ALL_PATHS_FROM_SOURCE_TO_TARGET
{
    class Solution
    {
    public:
        vector<vector<int>> allPathsSourceTarget(vector<vector<int>>& graph)
        {
            vector<vector<int>> solution;
            vector<int> prefix;
            allPaths(graph, prefix, 0, solution);
            return solution;
        }
    private:
        void allPaths(vector<vector<int>>& graph, vector<int>& prefix, int current, vector<vector<int>>& solution)
        {
            prefix.push_back(current);
            if (current == graph.size() - 1)
            {
                solution.push_back(prefix);
            }
            for (auto neighbor : graph[current])
            {
                allPaths(graph, prefix, neighbor, solution);
            }
            prefix.pop_back();
        }
    };
};

using namespace _LEET_ALL_PATHS_FROM_SOURCE_TO_TARGET;

int LEET_ALL_PATHS_FROM_SOURCE_TO_TARGET()
{
    vector<vector<int>> graph(4);
    graph[0].push_back(1);
    graph[0].push_back(2);
    graph[1].push_back(3);
    graph[2].push_back(3);
    Solution s;
    for (auto path : s.allPathsSourceTarget(graph))
    {
        for (auto node : path)
        {
            cout << node << " ";
        }
        cout << endl;
    }
    return 0;
}