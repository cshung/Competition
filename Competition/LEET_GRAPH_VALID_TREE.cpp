#include "stdafx.h"

// https://leetcode.com/problems/graph-valid-tree/

#include "LEET_GRAPH_VALID_TREE.h"
#include <map>
#include <iostream>
#include <queue>
#include <vector>
#include <set>

using namespace std;

namespace _LEET_GRAPH_VALID_TREE
{
	class Solution
	{
	public:
		bool validTree(int n, vector<vector<int>>& edges) {
			if (edges.size() != n - 1)
			{
				return false;
			}
			vector<vector<int>> adjacency_list(n);
			for (auto edge : edges)
			{
				int n1 = edge[0];
				int n2 = edge[1];
				adjacency_list[n1].push_back(n2);
				adjacency_list[n2].push_back(n1);
			}
			queue<int> bfs;
			set<int> enqueued;
			bfs.push(0);
			enqueued.insert(0);
			while (bfs.size() > 0)
			{
				int visiting = bfs.front();
				bfs.pop();
				for (auto neighbor : adjacency_list[visiting])
				{
					auto probe = enqueued.find(neighbor);
					if (probe == enqueued.end())
					{
						bfs.push(neighbor);
						enqueued.insert(neighbor);
					}
				}
			}
			return enqueued.size() == n;
		}
	};
};

using namespace _LEET_GRAPH_VALID_TREE;

int LEET_GRAPH_VALID_TREE()
{
	Solution solution;
	vector<vector<int>> edges;
	edges.resize(4);
	edges[0].push_back(0);
	edges[0].push_back(1);
	edges[1].push_back(0);
	edges[1].push_back(2);
	edges[2].push_back(0);
	edges[2].push_back(3);
	edges[3].push_back(1);
	edges[3].push_back(4);
	cout << solution.validTree(5, edges) << endl;
	return 0;
}