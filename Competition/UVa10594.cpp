#include "stdafx.h"

// http://uva.onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=1535

#define LOG

#include "UVa10594.h"

#include <iostream>
#include <vector>
#include <queue>

typedef long long int64;

using namespace std;

int64 UVa10594_Edmonds_Karps(vector<vector<int64>>& capacities, vector<vector<int>>& adjacency_list, int src, int dst);

int UVa10594()
{
    while (true)
    {
        int number_of_nodes;
        int number_of_edges;
        cin >> number_of_nodes;
        if (cin.eof())
        {
            break;
        }
        cin >> number_of_edges;

        // Read edges and build data structures for 1st phase maximum flow
        vector<vector<int>> adjacency_list;
        vector<vector<int64>> capacities;
        vector<vector<int64>> cost;

        number_of_nodes++; // create a virtual sink
        adjacency_list.resize(number_of_nodes);
        capacities.resize(number_of_nodes);
        cost.resize(number_of_nodes);
        for (int src = 0; src < number_of_nodes; src++)
        {
            capacities[src].resize(number_of_nodes);
            cost[src].resize(number_of_nodes);
            for (int dst = 0; dst < number_of_nodes; dst++)
            {
                cost[src][dst] = 0;
                capacities[src][dst] = 0;
            }
        }

        for (int e = 0; e < number_of_edges; e++)
        {
            int src;
            int dst;
            int64 time;
            cin >> src;
            cin >> dst;
            cin >> time;
            src--;
            dst--;
            adjacency_list[src].push_back(dst);
            adjacency_list[dst].push_back(src);
            cost[src][dst] = time;
            cost[dst][src] = time;
        }

        int64 total_volume;
        int64 link_capacity;
        cin >> total_volume;
        cin >> link_capacity;

        // Virtual sink
        int target = number_of_nodes - 2;
        int virtual_sink = number_of_nodes - 1;
        adjacency_list[target].push_back(virtual_sink);
        adjacency_list[virtual_sink].push_back(target);
        capacities[target][virtual_sink] = total_volume;
        capacities[virtual_sink][target] = total_volume;

        for (int src = 0; src < number_of_nodes; src++)
        {
            for (int dst = 0; dst < number_of_nodes; dst++)
            {
                if (cost[src][dst] > 0)
                {
                    capacities[src][dst] = link_capacity;
                }
            }
        }

        int64 maximum_flow = UVa10594_Edmonds_Karps(capacities, adjacency_list, 0, virtual_sink);
#ifdef LOG
        cout << "First phase maximum flow gives " << maximum_flow << endl;
#endif
        if (maximum_flow == total_volume)
        {
            // Next thing next - we will use the minimum mean weight cycle cancellation algorithm to find the minimum cost flow 
        }
        else
        {
            // TODO: Be careful with output format
            cout << "Impossible." << endl;
        }
        
    }

    return 0;
}

int64 UVa10594_Edmonds_Karps(vector<vector<int64>>& capacities, vector<vector<int>>& adjacency_list, int src, int dst)
{
    int64 total_flow = 0;
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
            for (vector<int>::iterator ni = adjacency_list[current].begin(); ni != adjacency_list[current].end(); ni++)
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
            int64 max_flow_through_path = 0;
            while (true)
            {
                int src = parents[cur];
                if (src != -2)
                {
                    int dst = cur;
                    int64 available = capacities[src][dst];
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