#include "stdafx.h"

// https://leetcode.com/problems/number-of-connected-components-in-an-undirected-graph/

#include "LEET_NUMBER_OF_CONNECTED_COMPONENTS_IN_AN_UNDIRECTED_GRAPH.h"
#include <map>
#include <iostream>
#include <set>
#include <queue>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_NUMBER_OF_CONNECTED_COMPONENTS_IN_AN_UNDIRECTED_GRAPH
{
    class Solution
    {
    public:
        int countComponents(int n, vector<vector<int>>& edges)
        {
            vector<int>* adjacencyList = new vector<int>[n];
            for (auto edge : edges)
            {
                int from = edge[0];
                int to = edge[1];
                adjacencyList[from].push_back(to);
                adjacencyList[to].push_back(from);
            }
            int answer = 0;
            set<int> enqueued;
            queue<int> queue;
            for (int i = 0; i < n; i++)
            {
                if (enqueued.find(i) == enqueued.end())
                {
                    answer++;
                    queue.push(i);
                    enqueued.insert(i);
                    while (queue.size() > 0)
                    {
                        int visit = queue.front();
                        queue.pop();
                        for (auto neighbor : adjacencyList[visit])
                        {
                            if (enqueued.find(neighbor) == enqueued.end())
                            {
                                enqueued.insert(neighbor);
                                queue.push(neighbor);
                            }
                        }
                    }
                }
            }
            delete[] adjacencyList;
            return answer;
        }
    };
};

using namespace _LEET_NUMBER_OF_CONNECTED_COMPONENTS_IN_AN_UNDIRECTED_GRAPH;

int LEET_NUMBER_OF_CONNECTED_COMPONENTS_IN_AN_UNDIRECTED_GRAPH()
{
    Solution solution;
    // [[0, 1], [1, 2], [3, 4]]
    vector<vector<int>> test;
    test.resize(3);
    test[0].push_back(0);
    test[0].push_back(1);
    test[1].push_back(1);
    test[1].push_back(2);
    test[2].push_back(3);
    test[2].push_back(4);
    cout << solution.countComponents(5, test) << endl;
    return 0;
}