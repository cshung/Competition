#include "stdafx.h"

// http://uva.onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=1720

// #define LOG

#include "UVa10779.h"

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

int UVa10779_Edmonds_Karps(vector<vector<int>>& capacities, vector<vector<int>>& adjacency_list, int src, int dst);

int UVa10779()
{
    int number_of_test_cases;
    cin >> number_of_test_cases;
    for (int test_case = 1; test_case <= number_of_test_cases; test_case++)
    {
        vector<vector<int>> input;
        int number_of_people;
        int number_of_stickers_types;
        cin >> number_of_people;
        cin >> number_of_stickers_types;
        input.resize(number_of_people);
        for (int p = 0; p < number_of_people; p++)
        {
            int number_of_stickers_i_have;
            cin >> number_of_stickers_i_have;
            input[p].resize(number_of_stickers_i_have);
            for (int s = 0; s < number_of_stickers_i_have; s++)
            {
                int sticker_i_have;
                cin >> sticker_i_have;
                input[p][s] = sticker_i_have - 1; // make sticker id goes from [0, number_of_stickers_types)
            }
        }

        // Step 2.1: Formulate the graph
        // First, there is a super sink node [0]
        // For each sticker, there is a source node for bob [1 ... ns]
        // For each sticker, there is a trace  node for bob [1 ... ns]
        // For each sticker, there is a sink   node for bob [1 ... ns]
        // For each other user, there is a node
        //   For each missing item from other user, there is a link from the bob trade node to the other user with capacity 1
        //   For each duplicated item from other user, this is a link from the other user node to bob trade node with quantity - 1
        
        // Step 2.2: Allocate the graph
        int number_of_nodes = /* master source */ 1 +
                              /* master sink   */ 1 +
                              /* bob source    */ number_of_stickers_types +
                              /* bob trade     */ number_of_stickers_types +
                              /* bob sink      */ number_of_stickers_types +
                              /* other users   */ (number_of_people - 1);

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

        // Step 2.3: Count how many sticker per type bob have
        vector<int> bob_counts;
        bob_counts.resize(number_of_stickers_types);
        for (int i = 0; i < number_of_stickers_types; i++)
        {
            bob_counts[i] = 0;
        }
        for (vector<int>::iterator bs = input[0].begin(); bs != input[0].end(); bs++)
        {
            bob_counts[*bs]++;
        }

        // Step 2.3: Bob sticker links
        int master_source = 0;
        int master_sink   = 1 + number_of_stickers_types * 3;
        for (int st = 0; st < number_of_stickers_types; st++)
        {
            int bob_source    = st + 1; 
            int bob_trade     = bob_source + number_of_stickers_types;
            int bob_sink      = bob_trade + number_of_stickers_types;

            capacities[master_source][bob_source] = bob_counts[st];
            capacities[bob_source][bob_trade] = bob_counts[st];
            capacities[bob_trade][bob_sink] = 1;
            capacities[bob_sink][master_sink] = 1;

            adjacency_list[master_source].push_back(bob_source);
            adjacency_list[bob_source].push_back(bob_trade);
            adjacency_list[bob_trade].push_back(bob_sink);
            adjacency_list[bob_sink].push_back(master_sink);

            // reverse connection could happen in residual graph
            // instead of maintaining the list at that time, might as well just put 
            // it here now for simplicity
            adjacency_list[bob_source].push_back(master_source);
            adjacency_list[bob_trade].push_back(bob_source);
            adjacency_list[bob_sink].push_back(bob_trade);
            adjacency_list[master_sink].push_back(bob_sink);
        }

        // Step 2.1: Formulate the trades
        for (int p = 1; p < number_of_people; p++)
        {
            int people_node = master_sink + p;
            vector<int> counts;
            counts.resize(number_of_stickers_types);
            for (int st = 0; st < number_of_stickers_types; st++)
            {
                counts[st] = 0;
            }
            for (unsigned int i = 0; i < input[p].size(); i++)
            {
                counts[input[p][i]]++;
            }

            vector<int> gives;
            vector<int> takes;

            for (int st = 0; st < number_of_stickers_types; st++)
            {
                if (counts[st] > 1)
                {
                    gives.push_back(st);
                }
                else if (counts[st] == 0)
                {
                    takes.push_back(st);
                }
            }

            for (vector<int>::iterator ti = takes.begin(); ti != takes.end(); ti++)
            {
                int take = *ti;
                int bob_give_node = 1 + take + number_of_stickers_types;
                capacities[bob_give_node][people_node] = 1;
                adjacency_list[bob_give_node].push_back(people_node);

                // reverse connection could happen in residual graph
                // instead of maintaining the list at that time, might as well just put 
                // it here now for simplicity
                adjacency_list[people_node].push_back(bob_give_node);
            }

            for (vector<int>::iterator gi = gives.begin(); gi != gives.end(); gi++)
            {
                int give = *gi;

                int give_volume = counts[give] - 1;

                int bob_take_node = 1 + give + number_of_stickers_types;
                capacities[people_node][bob_take_node] = give_volume;
                adjacency_list[people_node].push_back(bob_take_node);

                // reverse connection could happen in residual graph
                // instead of maintaining the list at that time, might as well just put 
                // it here now for simplicity
                adjacency_list[bob_take_node].push_back(people_node);
            }
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

        

        cout << "Case #" << test_case << ": " << UVa10779_Edmonds_Karps(capacities, adjacency_list, master_source, master_sink) << endl;
    }
    
    return 0;
}

int UVa10779_Edmonds_Karps(vector<vector<int>>& capacities, vector<vector<int>>& adjacency_list, int src, int dst)
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
                    cout << src << "-" << available << "->" << dst << endl;
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