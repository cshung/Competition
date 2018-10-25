#include "stdafx.h"

// https://leetcode.com/problems/is-graph-bipartite

#include "LEET_IS_GRAPH_BIPARTITE.h"
#include <map>
#include <iostream>
#include <vector>

using namespace std;

namespace _LEET_IS_GRAPH_BIPARTITE
{
    class Solution
    {
    public:
        bool isBipartite(vector<vector<int>>& graph)
        {
            vector<int> colors;
            colors.resize(graph.size());
            for (int i = 0; i < graph.size(); i++)
            {
                colors[i] = 0;
            }
            for (int i = 0; i < graph.size(); i++)
            {
                if (colors[i] == 0)
                {
                    if (!dfs(i, 1, graph, colors))
                    {
                        return false;
                    }
                }
            }
            return true;
        }

        bool dfs(int visiting, int color, vector<vector<int>>& graph, vector<int>& colors)
        {
            colors[visiting] = color;
            for (int n : graph[visiting])
            {
                if (colors[n] == color)
                {
                    return false;
                }
                else if (colors[n] == 0)
                {
                    if (!dfs(n, -color, graph, colors))
                    {
                        return false;
                    }
                }
            }
            return true;
        }
    };
};

using namespace _LEET_IS_GRAPH_BIPARTITE;

int LEET_IS_GRAPH_BIPARTITE()
{
    int row1[] = { 1, 3 };
    int row2[] = { 0, 2 };
    int row3[] = { 1, 3 };
    int row4[] = { 0, 2 };
    vector<vector<int>> graph;
    graph.push_back(vector<int>(row1, row1 + _countof(row1)));
    graph.push_back(vector<int>(row2, row2 + _countof(row2)));
    graph.push_back(vector<int>(row3, row3 + _countof(row3)));
    graph.push_back(vector<int>(row4, row4 + _countof(row4)));
    Solution solution;
    cout << solution.isBipartite(graph) << endl;
    return 0;
}
