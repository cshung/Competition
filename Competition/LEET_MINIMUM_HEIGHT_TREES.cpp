#include "stdafx.h"

// https://leetcode.com/problems/minimum-height-trees/

#include "LEET_MINIMUM_HEIGHT_TREES.h"
#include <list>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

namespace _LEET_MINIMUM_HEIGHT_TREES
{
    class Solution {
    private:
        class summary
        {
        public:
            int max;
            int max_id;
            int second_max;
            summary()
            {
                max = second_max = 0;
                max_id = -1;
            }

            void add(int id, int cost)
            {
                if (cost > max)
                {
                    second_max = max;
                    max = cost;
                    max_id = id;
                }
                else if (cost > second_max)
                {
                    second_max = cost;
                }
            }

            int get_max()
            {
                return this->max;
            }

            int get_max_but_id(int id)
            {
                if (id == this->max_id)
                {
                    return this->second_max;
                }
                else
                {
                    return this->max;
                }
            }
        };
    public:
        void first_pass(int parent, int node, vector<vector<int>>& adjacency_list, vector<summary>& summaries)
        {
            for (size_t i = 0; i < adjacency_list[node].size(); i++)
            {
                int neighbor = adjacency_list[node][i];
                if (neighbor != parent)
                {
                    first_pass(node, neighbor, adjacency_list, summaries);
                    summaries[node].add(neighbor, 1 + summaries[neighbor].get_max());
                }
            }
        }

        void second_pass(int parent, int node, int parent_cost, vector<vector<int>>& adjacency_list, vector<summary>& summaries)
        {
            summaries[node].add(parent, parent_cost);
            for (size_t i = 0; i < adjacency_list[node].size(); i++)
            {
                int neighbor = adjacency_list[node][i];
                if (neighbor != parent)
                {
                    second_pass(node, neighbor, 1 + summaries[node].get_max_but_id(neighbor), adjacency_list, summaries);
                }
            }
        }

        vector<int> findMinHeightTrees(int n, vector<pair<int, int>>& edges)
        {
            vector<vector<int>> adjacency_list(n);
            vector<summary> summaries(n);
            for (size_t e = 0; e < edges.size(); e++)
            {
                adjacency_list[edges[e].first].push_back(edges[e].second);
                adjacency_list[edges[e].second].push_back(edges[e].first);
            }

            first_pass(-1, 0, adjacency_list, summaries);
            second_pass(-1, 0, 0, adjacency_list, summaries);

            vector<int> result;
            int min_max = 100000;
            for (int i = 0; i < n; i++)
            {
                min_max = min(min_max, summaries[i].get_max());
            }
            for (int i = 0; i < n; i++)
            {
                if (summaries[i].get_max() == min_max)
                {
                    result.push_back(i);
                }
            }
            return result;
        }
    };
};

using namespace _LEET_MINIMUM_HEIGHT_TREES;

int LEET_MINIMUM_HEIGHT_TREES()
{
    Solution solution;
    vector<pair<int, int>> edges;

    edges.push_back(pair<int, int>(0, 1));
    edges.push_back(pair<int, int>(1, 3));
    edges.push_back(pair<int, int>(1, 4));
    edges.push_back(pair<int, int>(0, 2));
    edges.push_back(pair<int, int>(4, 5));

    solution.findMinHeightTrees(6, edges);
    return 0;
}