#include "stdafx.h"

// http://uva.onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=2501

// #define LOG

#include "UVa11506.h"

#include <iostream>
#include <vector>
#include <queue>
#include <set>

using namespace std;

int UVa11506_get_computer_source_node_id(int computer_id, int number_of_computers, int number_of_nodes);
int UVa11506_get_computer_target_node_id(int computer_id, int number_of_computers, int number_of_nodes);
int UVa11506_Edmonds_Karps(vector<vector<int>>& capacities, vector<vector<int>>& adjacency_list, int src, int dst);

int UVa11506()
{
    int test_case = 0;
    while (true)
    {
        test_case++;
        int number_of_computers;
        int number_of_wires;
        cin >> number_of_computers;
        cin >> number_of_wires;

        if (number_of_computers == 0 && number_of_wires == 0)
        {
            break;
        }

        // For each node (other than boss computer and the central server) are split
        // so let the boss machine's node be 0
        // so let each other machines be (1, 2), (3, 4), ...
        // and therefore the central server is 2k + 3, where k is the number of other computers

        int number_of_nodes = 1 + (number_of_computers - 2) * 2 + 1;

        vector<vector<int>> capacities;
        vector<vector<int>> adjacency_list;
        capacities.resize(number_of_nodes);
        adjacency_list.resize(number_of_nodes);
        for (int src = 0; src < number_of_nodes; src++)
        {
            capacities[src].resize(number_of_nodes);
            for (int dst = 0; dst < number_of_nodes; dst++)
            {
                capacities[src][dst] = 0;
            }
        }

        for (int c = 0; c < number_of_computers - 2; c++)
        {
            int computer_id;
            int computer_cost;
            cin >> computer_id;
            cin >> computer_cost;

            int computer_source_node = UVa11506_get_computer_source_node_id(computer_id, number_of_computers, number_of_nodes);
            int computer_target_node = UVa11506_get_computer_target_node_id(computer_id, number_of_computers, number_of_nodes);

            capacities[computer_source_node][computer_target_node] = computer_cost;
            capacities[computer_target_node][computer_source_node] = computer_cost;
            adjacency_list[computer_source_node].push_back(computer_target_node);
            adjacency_list[computer_target_node].push_back(computer_source_node);
        }

        for (int w = 0; w < number_of_wires; w++)
        {
            int src_computer_id;
            int dst_computer_id;
            int cost;
            cin >> src_computer_id;
            cin >> dst_computer_id;
            cin >> cost;

            int src_computer_source_node = UVa11506_get_computer_source_node_id(src_computer_id, number_of_computers, number_of_nodes);
            int src_computer_target_node = UVa11506_get_computer_target_node_id(src_computer_id, number_of_computers, number_of_nodes);
            int dst_computer_source_node = UVa11506_get_computer_source_node_id(dst_computer_id, number_of_computers, number_of_nodes);
            int dst_computer_target_node = UVa11506_get_computer_target_node_id(dst_computer_id, number_of_computers, number_of_nodes);

            capacities[src_computer_target_node][dst_computer_source_node] = cost;
            capacities[dst_computer_target_node][src_computer_source_node] = cost;
            
            adjacency_list[src_computer_target_node].push_back(dst_computer_source_node);
            adjacency_list[dst_computer_source_node].push_back(src_computer_target_node);

            adjacency_list[dst_computer_target_node].push_back(src_computer_source_node);
            adjacency_list[src_computer_source_node].push_back(dst_computer_target_node);
        }

#ifdef LOG
        cout << "digraph {" << endl;
        for (int src = 0; src < number_of_nodes; src++)
        {
            for (vector<int>::iterator di = adjacency_list[src].begin(); di != adjacency_list[src].end(); di++)
            {
                int dst = *di;
                cout << src << "->" << dst << " [label=\"" << capacities[src][dst] << "\"];" << endl;
            }
        }
        cout << "}" << endl;
#endif

        cout << UVa11506_Edmonds_Karps(capacities, adjacency_list, 0, number_of_nodes - 1) << endl;
    }
    return 0;
}

int UVa11506_get_computer_source_node_id(int computer_id, int number_of_computers, int number_of_nodes)
{
    if (computer_id == 1)
    {
        return 0;
    }
    else if (computer_id == number_of_computers)
    {
        return number_of_nodes - 1;
    }
    else
    {
        return (computer_id - 2) * 2 + 1;
    }
}

int UVa11506_get_computer_target_node_id(int computer_id, int number_of_computers, int number_of_nodes)
{
    if (computer_id == 1)
    {
        return 0;
    }
    else if (computer_id == number_of_computers)
    {
        return number_of_nodes - 1;
    }
    else
    {
        return (computer_id - 2) * 2 + 2;
    }
}

int UVa11506_Edmonds_Karps(vector<vector<int>>& capacities, vector<vector<int>>& adjacency_list, int src, int dst)
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