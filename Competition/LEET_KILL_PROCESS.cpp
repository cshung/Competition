#include "stdafx.h"

// https://leetcode.com/problems/kill-process

#include "LEET_KILL_PROCESS.h"
#include <map>
#include <iostream>
#include <queue>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_KILL_PROCESS
{
	struct Node
	{
		int data;
		Node* child;
		Node* sibling;
	};
	class Solution {
	public:
		vector<int> killProcess(vector<int>& pid, vector<int>& ppid, int kill)
		{
			map<int, Node*> nodes;
			Node* root = nullptr;
			size_t n = pid.size();
			for (size_t i = 0; i < n; i++)
			{
				Node* newNode = new Node();
				newNode->data = pid[i];
				newNode->child = newNode->sibling = nullptr;
				nodes.insert(make_pair(pid[i], newNode));
			}

			for (size_t i = 0; i < n; i++)
			{
				if (ppid[i] == 0)
				{
					root = nodes[pid[i]];
				}
				else
				{
					Node* curr = nodes[pid[i]];
					Node* prev = nodes[ppid[i]];
					curr->sibling = prev->child;
					prev->child = curr;
				}
			}

			vector<int> result;
			queue<Node*> bfs;
			bfs.push(nodes[kill]);
			while (!bfs.empty())
			{
				Node* current = bfs.front();
				bfs.pop();
				result.push_back(current->data);
				Node* child = current->child;
				while (child != nullptr)
				{
					bfs.push(child);
					child = child->sibling;
				}
			}
			return result;
		}
	};
};

using namespace _LEET_KILL_PROCESS;

int LEET_KILL_PROCESS()
{
	Solution s;
	int pid_array[] = { 1,3,10,5 };
	int ppid_array[] = { 3,0,5,3 };
	vector<int> pid(pid_array, pid_array + _countof(pid_array));
	vector<int> ppid(ppid_array, ppid_array + _countof(ppid_array));
	vector<int> result = s.killProcess(pid, ppid, 5);
	for (size_t i = 0; i < result.size(); i++)
	{
		cout << result[i] << " ";
	}
	cout << endl;
	return 0;
}
