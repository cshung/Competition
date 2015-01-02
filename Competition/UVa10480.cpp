#include "stdafx.h"

// http://uva.onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=1421

// #define LOG

#include "UVa10480.h"

#include <iostream>
#include <vector>
#include <set>
#include <queue>

using namespace std;

int UVa10480()
{
    while (true)
    {
        int number_of_nodes;
        int number_of_edges;
        cin >> number_of_nodes;
        cin >> number_of_edges;
        
        if (number_of_nodes == 0 && number_of_edges == 0)
        {
            break;
        }

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
            capacities[src][dst] += cost;

            adjacency_list[dst].insert(src);
            capacities[dst][src] += cost;
        }

        int total_flow = 0;
        // Step 2: Edmonds Karp's
        vector<int> parents; // Allow back-tracking the path found from bfs
        parents.resize(number_of_nodes); // avoid reallocation
        while (true)
        {
            // Step 2.1: Use BFS to find an augmenting flow
            queue<int> bfs_queue;
            for (int n = 0; n < number_of_nodes; n++)
            {
                parents[n] = -1; // indicating the node is not enqueued
            }

            parents[0] = -2; // indicating the node is enqueued but no actual parent because this is the root
            bfs_queue.push(0);
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

                        if (neighbor == 1)
                        {
                            break;
                        }
                    }
                }
                if (parents[1] != -1)
                {
                    break;
                }
            }

            if (parents[1] == -1)
            {
                set<int> source_side;
                for (int i = 0; i < number_of_nodes; i++)
                {
                    if (parents[i] == -2 || parents[i] >= 0)
                    {
                        source_side.insert(i);
                        // These are reachable nodes, belongs to left hand side of the edge.
                    }
                }
#ifdef LOG
                cout << "Source side of the cut" << endl;
                for (set<int>::iterator si = source_side.begin(); si != source_side.end(); si++)
                {
                    cout << *si << " ";
                }
                cout << endl;
#endif
                for (set<int>::iterator si = source_side.begin(); si != source_side.end(); si++)
                {
                    int s = *si;
                    for (set<int>::iterator ni = adjacency_list[s].begin(); ni != adjacency_list[s].end(); ni++)
                    {
                        int n = *ni;
                        if (source_side.find(n) == source_side.end())
                        {
                            cout << (s + 1) << " " << (n + 1) << endl;
                        }
                    }
                }
                cout << endl;

                break;
            }
            else
            {
                // We have found an augmenting path, go through the path and find the max flow through this path
                int cur = 1;
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
                cur = 1;
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
#ifdef LOG
        cout << "The total flow is " << total_flow << endl;
#endif
    }

    return 0;
}