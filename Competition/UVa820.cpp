#include "stdafx.h"

// http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=761

#include "UVa820.h"

#include <iostream>
#include <vector>
#include <set>
#include <queue>
#include <algorithm>

using namespace std;

int UVa820_Edmonds_Karps(vector<vector<int>>& capacities, vector<set<int>>& adjacency_list, int src, int dst);

int UVa820()
{
    int test_case = 0;
    while (true)
    {
        test_case++;

        // Step 1: Read input
        int number_of_nodes;
        cin >> number_of_nodes;
        if (number_of_nodes == 0)
        {
            break;
        }
        int src;
        int dst;
        int number_of_edges;
        cin >> src;
        cin >> dst;
        cin >> number_of_edges;

        // Input is 1 based index
        src--;
        dst--;

        vector<vector<int>> capacities;
        vector<set<int>> adjacency_list;
        adjacency_list.resize(number_of_nodes);
        capacities.resize(number_of_nodes);
        for (int src = 0; src < number_of_nodes; src++)
        {
            capacities[src].resize(number_of_nodes);
            for (int dst = 0; dst < number_of_nodes; dst++)
            {
                capacities[src][dst] = 0;
            }
        }

        for (int e = 0; e < number_of_edges; e++)
        {
            int src;
            int dst;
            int cost;
            cin >> src;
            cin >> dst;
            cin >> cost;

            // Input is 1 based index
            src--;
            dst--;

            adjacency_list[src].insert(dst);
            adjacency_list[dst].insert(src);
            capacities[src][dst] += cost;
            capacities[dst][src] += cost;
        }

        int total_flow = UVa820_Edmonds_Karps(capacities, adjacency_list, src, dst);

        cout << "Network " << test_case << endl;
        cout << "The bandwidth is " << total_flow << "." << endl;
        cout << endl;
    }

    return 0;
}

int UVa820_Edmonds_Karps(vector<vector<int>>& capacities, vector<set<int>>& adjacency_list, int src, int dst)
{
    int total_flow = 0;
    // Step 2: Edmonds Karp's
    vector<int> parents; // Allow back-tracking the path found from bfs
    int number_of_nodes = capacities.size();
    parents.resize(number_of_nodes); // avoid reallocation
    while (true)
    {
        // Step 2.1: Use BFS to find an augmenting flow
        queue<int> bfs_queue;
        for (int n = 0; n < number_of_nodes; n++)
        {
            parents[n] = -1; // indicating the node is not enqueued
        }

        parents[src] = -2; // indicating the node is enqueued but no actual parent because this is the root
        bfs_queue.push(src);
        while (bfs_queue.size() > 0)
        {
            int current = bfs_queue.front();
            bfs_queue.pop();
            for (set<int>::iterator ni = adjacency_list[current].begin(); ni != adjacency_list[current].end(); ni++)
            {
                int neighbor = *ni;
                if (parents[neighbor] == -1 && capacities[current][neighbor] > 0)
                {
                    parents[neighbor] = current;
                    bfs_queue.push(neighbor);

                    if (neighbor == dst)
                    {
                        break;
                    }
                }
            }
            if (parents[dst] != -1)
            {
                break;
            }
        }

        if (parents[dst] == -1)
        {
            break;
        }
        else
        {
            // We have found an augmenting path, go through the path and find the max flow through this path
            int cur = dst;
            bool first = true;
            int max_flow_through_path = 0;
            while (true)
            {
                int src = parents[cur];
                if (src != -2)
                {
                    int dst = cur;
                    int available = capacities[src][dst];
#ifdef LOG
                    cout << src << "--" << available << "->" << dst << endl;
#endif
                    cur = parents[cur];
                    if (first)
                    {
                        max_flow_through_path = available;
                        first = false;
                    }
                    else
                    {
                        max_flow_through_path = min(max_flow_through_path, available);
                    }
                }
                else
                {
                    break;
                }
            }
#ifdef LOG
            cout << "flowing " << max_flow_through_path << endl << endl;
#endif
            total_flow += max_flow_through_path;
            // Flow the max flow through the augmenting path
            cur = dst;
            while (true)
            {
                int src = parents[cur];
                if (src != -2)
                {
                    capacities[src][cur] -= max_flow_through_path;
                    capacities[cur][src] += max_flow_through_path;
                    cur = parents[cur];
                }
                else
                {
                    break;
                }
            }
        }
    }

    return total_flow;
}