#include "stdafx.h"

// https://leetcode.com/problems/redundant-connection

#include "LEET_REDUNDANT_CONNECTION.h"
#include <map>
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_REDUNDANT_CONNECTION
{
    class Solution
    {
    public:
        void add_edge(map<int, map<int, int>>& adjacency_list, int from, int to, int edge_index)
        {
            auto probe = adjacency_list.find(from);
            if (probe == adjacency_list.end())
            {
                adjacency_list.insert(make_pair(from, map<int, int>()));
            }
            adjacency_list[from].insert(make_pair(to, edge_index));
        }

        // best_edge_so_far, bad_node
        pair<int, int> findRedundantConnection(int edge, int parent, int current, map<int, map<int, int>>& adjacency_list, map<int, int>& associated_edge)
        {
            associated_edge[current] = edge;
            for (auto&& neighbor_node_edge_pair : adjacency_list[current])
            {
                int neighbor = neighbor_node_edge_pair.first;
                if (neighbor != parent)
                {
                    int edge = neighbor_node_edge_pair.second;
                    auto check = associated_edge.find(neighbor);
                    if (check == associated_edge.end())
                    {
                        pair<int, int> result = findRedundantConnection(edge, current, neighbor, adjacency_list, associated_edge);
                        int best_edge_so_far = result.first;
                        int bad_node = result.second;
                        if (best_edge_so_far != -1)
                        {
                            if (bad_node == -1)
                            {
                                return make_pair(best_edge_so_far, bad_node);
                            }
                            else if (neighbor == bad_node)
                            {
                                return make_pair(best_edge_so_far, -1);
                            }
                            else
                            {
                                return make_pair(max(edge, best_edge_so_far), bad_node);
                            }
                        }
                    }
                    else
                    {
                        return make_pair(edge, neighbor);
                    }
                }
            }
            return make_pair(-1, 0);
        }

        vector<int> findRedundantConnection(vector<vector<int>>& edges)
        {
            map<int, map<int, int>> adjacency_list;

            for (size_t i = 0; i < edges.size(); i++)
            {
                add_edge(adjacency_list, edges[i][0], edges[i][1], i);
                add_edge(adjacency_list, edges[i][1], edges[i][0], i);
            }

            map<int, int> associated_edge;
            return edges[findRedundantConnection(-1, 0, 1, adjacency_list, associated_edge).first];
        }
    };
};

using namespace _LEET_REDUNDANT_CONNECTION;

int LEET_REDUNDANT_CONNECTION()
{
    Solution solution;
    vector<vector<int>> graph;
    graph.resize(10);
    for (int i = 0; i < 10; i++)
    {
        graph[i].resize(2);
    }
    // [[2,7],[7,8],[3,6],[2,5],[6,8],[4,8],[2,8],[1,8],[7,10],[3,9]]
    graph[0][0] = 2;    graph[0][1] = 7;
    graph[1][0] = 7;    graph[1][1] = 8;
    graph[2][0] = 3;    graph[2][1] = 6;
    graph[3][0] = 2;    graph[3][1] = 5;
    graph[4][0] = 6;    graph[4][1] = 8;
    graph[5][0] = 4;    graph[5][1] = 8;
    graph[6][0] = 2;    graph[6][1] = 8;
    graph[7][0] = 1;    graph[7][1] = 8;
    graph[8][0] = 7;    graph[8][1] = 10;
    graph[9][0] = 3;    graph[9][1] = 9;
    
    vector<int> answer = solution.findRedundantConnection(graph);
    cout << answer[0] << "," << answer[1] << endl;
    return 0;
}