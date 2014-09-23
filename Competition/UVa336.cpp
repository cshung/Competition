#include "stdafx.h"

// http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=272

#include "UVa336.h"

#include <iostream>
#include <list>
#include <map>
#include <queue>

using namespace std;

int UVa336()
{

    int test_case_id = 1;

    while (true)
    {
        int number_of_edges;
        cin >> number_of_edges;
        if (number_of_edges == 0)
        {
            break;
        }

        // Step 1: Reading the graph and do node number mapping
        list<pair<int, int> > edges;
        map<int, int> node_number_to_id_map;

        // Debug
        map<int, int> node_id_to_number_map;

        int node_id = 0;
        for (int i = 0; i < number_of_edges; i++)
        {
            int source;
            int destination;
            cin >> source;
            cin >> destination;

            edges.push_back(pair<int, int>(source, destination));

            map<int, int>::iterator probe1 = node_number_to_id_map.find(source);
            if (probe1 == node_number_to_id_map.end())
            {
                node_number_to_id_map.insert(pair<int, int>(source, node_id++));

                // Debug
                node_id_to_number_map.insert(pair<int, int>(node_id - 1, source));
            }

            map<int, int>::iterator probe2 = node_number_to_id_map.find(destination);
            if (probe2 == node_number_to_id_map.end())
            {
                node_number_to_id_map.insert(pair<int, int>(destination, node_id++));

                // Debug
                node_id_to_number_map.insert(pair<int, int>(node_id - 1, destination));
            }
        }

        // Step 2: Build adjacency lists
        int number_of_nodes = node_id;
        list<int>* adjacency_list = new list<int>[number_of_nodes];
        for (list<pair<int, int> >::iterator ei = edges.begin(); ei != edges.end(); ei++)
        {
            pair<int, int> rawEdge = *ei;
            int source_id = node_number_to_id_map[rawEdge.first];
            int destination_id = node_number_to_id_map[rawEdge.second];
            adjacency_list[source_id].push_back(destination_id);
            adjacency_list[destination_id].push_back(source_id);
        }

        // Step 3: Process the queries
        while (true)
        {
            int start_node_number;
            int ttl;
            cin >> start_node_number;
            cin >> ttl;
            if (start_node_number == 0 && ttl == 0)
            {
                break;
            }

            // The BFS game begins
            int start_node_id = node_number_to_id_map[start_node_number];
            queue<pair<int, int> > bfs_queue;
            bfs_queue.push(pair<int, int>(start_node_id, ttl));

            bool* visited = new bool[number_of_nodes];
            for (int ni = 0; ni < number_of_nodes; ni++)
            {
                visited[ni] = false;
            }
            visited[start_node_id] = true;

            int reachable_node_count = 0;
            while (bfs_queue.size() > 0)
            {
                pair<int, int> current = bfs_queue.front();
                bfs_queue.pop();
                int current_node_id = current.first;
                int current_ttl = current.second;
                reachable_node_count++;
                int new_ttl = current_ttl - 1;
                
                // Debug
                // cout << "Reaching " << node_id_to_number_map[current_node_id] << " from " << start_node_number << endl;

                if (current_ttl > 0)
                {
                    for (list<int>::iterator ni = adjacency_list[current_node_id].begin(); ni != adjacency_list[current_node_id].end(); ni++)
                    {
                        int neighbor_node_id = *ni;
                        if (!visited[neighbor_node_id])
                        {
                            visited[neighbor_node_id] = true;
                            bfs_queue.push(pair<int, int>(neighbor_node_id, new_ttl));
                        }
                    }
                }
            }
            cout << "Case " << (test_case_id++) << ": " << (number_of_nodes - reachable_node_count) << " nodes not reachable from node " << start_node_number << " with TTL = " << ttl << "." << endl;
        }

        delete[] adjacency_list;
    }
    return 0;
}