#include "stdafx.h"

// http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=504

#include "UVa563.h"

#include <iostream>
#include <vector>
#include <map>
#include <queue>

using namespace std;

// #define LOG

int UVa563_get_incoming_node_id(int row, int col, int number_of_rows, int number_of_cols, int number_of_nodes);
int UVa563_get_outgoing_node_id(int row, int col, int number_of_rows, int number_of_cols, int number_of_nodes);
int UVa563_Edmonds_Karps(vector<vector<int>>& capacities, vector<vector<int>>& adjacency_list, int src, int dst);

int UVa563()
{
    int number_of_test_case;
    cin >> number_of_test_case;
    for (int test_case = 1; test_case <= number_of_test_case; test_case++)
    {
        // Step 1: Read input
        int number_of_rows;
        int number_of_cols;
        int number_of_robs;
        cin >> number_of_rows;
        cin >> number_of_cols;
        cin >> number_of_robs;
        vector<pair<int, int>> robs;
        robs.resize(number_of_robs);
        for (int r = 0; r < number_of_robs; r++)
        {
            int rob_row;
            int rob_col;
            cin >> rob_row;
            cin >> rob_col;
            rob_row--;
            rob_col--;
            robs[r] = pair<int, int>(rob_row, rob_col);
        }

        // Step 2: Graph modeling
        // for each crossing, model as a splitted vertex (row * num_col + col) * 2 and (row * num_col + col) * 2 + 1
        // one master source, one master sink (number_of_node - 2, number_of_nodes - 1)
        // all cost is 1, cost does not matter really
        int number_of_nodes = number_of_rows * number_of_cols * 2 + 2;

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

        for (int row = 0; row < number_of_rows; row++)
        {
            for (int col = 0; col < number_of_cols; col++)
            {
                int source_node_1 = UVa563_get_incoming_node_id(row, col, number_of_rows, number_of_cols, number_of_nodes);
                int source_node_2 = UVa563_get_outgoing_node_id(row, col, number_of_rows, number_of_cols, number_of_nodes);
                int target_node_1 = UVa563_get_incoming_node_id(row - 1, col, number_of_rows, number_of_cols, number_of_nodes);
                int target_node_2 = UVa563_get_incoming_node_id(row + 1, col, number_of_rows, number_of_cols, number_of_nodes);
                int target_node_3 = UVa563_get_incoming_node_id(row, col - 1, number_of_rows, number_of_cols, number_of_nodes);
                int target_node_4 = UVa563_get_incoming_node_id(row, col + 1, number_of_rows, number_of_cols, number_of_nodes);

                capacities[source_node_1][source_node_2] = 1;
                capacities[source_node_2][target_node_1] = 1;
                capacities[source_node_2][target_node_2] = 1;
                capacities[source_node_2][target_node_3] = 1;
                capacities[source_node_2][target_node_4] = 1;

                adjacency_list[source_node_1].push_back(source_node_2);
                adjacency_list[source_node_2].push_back(source_node_1);
                adjacency_list[source_node_2].push_back(target_node_1);
                adjacency_list[source_node_2].push_back(target_node_2);
                adjacency_list[source_node_2].push_back(target_node_3);
                adjacency_list[source_node_2].push_back(target_node_4);
            }
        }

        int master_source = number_of_nodes - 2;
        int master_sink = number_of_nodes - 1;
        for (vector<pair<int, int>>::iterator ri = robs.begin(); ri != robs.end(); ri++)
        {
            int rob_row = ri->first;
            int rob_col = ri->second;

            int rob_target = UVa563_get_incoming_node_id(rob_row, rob_col, number_of_rows, number_of_cols, number_of_nodes);
            capacities[master_source][rob_target] = 1;
            adjacency_list[master_source].push_back(rob_target);
        }

        int total_flow = UVa563_Edmonds_Karps(capacities, adjacency_list, master_source, master_sink);
        if (total_flow == robs.size())
        {
            cout << "possible" << endl;
        }
        else
        {
            cout << "not possible" << endl;
        }
    }
    return 0;
}

int UVa563_get_incoming_node_id(int row, int col, int number_of_rows, int number_of_cols, int number_of_nodes)
{
    if (row < 0 || row >= number_of_rows || col < 0 || col >= number_of_cols)
    {
        return number_of_nodes - 1;
    }
    else
    {
        return (row * number_of_cols + col) * 2;
    }
}

int UVa563_get_outgoing_node_id(int row, int col, int number_of_rows, int number_of_cols, int number_of_nodes)
{
    if (row < 0 || row >= number_of_rows || col < 0 || col >= number_of_cols)
    {
        return number_of_nodes - 1;
    }
    else
    {
        return (row * number_of_cols + col) * 2 + 1;
    }
}

int UVa563_Edmonds_Karps(vector<vector<int>>& capacities, vector<vector<int>>& adjacency_list, int src, int dst)
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