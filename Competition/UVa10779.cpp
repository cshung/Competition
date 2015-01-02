#include "stdafx.h"

// http://uva.onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=1720

// #define LOG

#include "UVa10779.h"

#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>
#include <queue>

using namespace std;

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
        // For each possible trade, there is a node 
        // For each trade node, there is a link from bob trade node to the trade node, 
        // and there is a link from the trade node back to the bob trade node 

        // Step 2.1: Formulate the trades
        vector<tuple<int, int, int>> trades;
        for (int p = 1; p < number_of_people; p++)
        {
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

            for (vector<int>::iterator gi = gives.begin(); gi != gives.end(); gi++)
            {
                for (vector<int>::iterator ti = takes.begin(); ti != takes.end(); ti++)
                {
                    int give = *gi;
                    int give_volume = counts[give] - 1;
                    int take = *ti;
                    trades.push_back(std::make_tuple(give, take, give_volume));
#ifdef LOG
                    cout << "People " << p << " is willing to trade " << (1 + give) << " for " << (1 + take) << endl;
#endif
                }
            }
        }
        
        // Step 2.2: Allocate the graph
        int number_of_nodes = /* master source */ 1 +
                              /* master sink   */ 1 +
                              /* bob source    */ number_of_stickers_types +
                              /* bob trade     */ number_of_stickers_types +
                              /* bob sink      */ number_of_stickers_types +
                              /* trades        */ trades.size();

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
        }

        // Step 2.4: Trade links
        int trade_node = master_sink + 1;

#ifdef LOG
        cout << "Trade links" << endl;
#endif
        for (vector<tuple<int, int, int>>::iterator ti = trades.begin(); ti != trades.end(); ti++)
        {
            int give = get<0>(*ti);
            int take = get<1>(*ti);
            int give_volume = get<2>(*ti);
            
            int give_trade_node = 1 + number_of_stickers_types + give;
            int take_trade_node = 1 + number_of_stickers_types + take;
#ifdef LOG
            cout << take_trade_node << "--" << give_volume << "-->" << trade_node << endl;
            cout << trade_node << "--" << 1 << "-->" << give_trade_node << endl;
#endif
            capacities[take_trade_node][trade_node] = give_volume;
            capacities[trade_node][give_trade_node] = 1;

            adjacency_list[take_trade_node].push_back(trade_node);
            adjacency_list[trade_node].push_back(give_trade_node);
            trade_node++;
        }

#ifdef LOG
        cout << "End trade links" << endl;
#endif

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

            parents[master_source] = -2; // indicating the node is enqueued but no actual parent because this is the root
            bfs_queue.push(master_source);
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

                        if (neighbor == master_sink)
                        {
                            break;
                        }
                    }
                }
                if (parents[master_sink] != -1)
                {
                    break;
                }
            }

            if (parents[master_sink] == -1)
            {
                break;
            }
            else
            {
                // We have found an augmenting path, go through the path and find the max flow through this path
                int cur = master_sink;
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
                cur = master_sink;
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

        cout << "Case #" << test_case << ": " << total_flow << endl;
    }
    
    return 0;
}