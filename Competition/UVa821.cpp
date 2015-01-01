#include "stdafx.h"

// http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=762

#include "UVa821.h"

#include <iostream>
#include <vector>
#include <map>
#include <iomanip>

using namespace std;

int UVa821_assign_node_number(map<int, int>& node_numbers, map<int, int>& node_namings, int node_name);

int UVa821()
{
    int test_case = 0;
    while (true)
    {
        test_case++;
        // Step 1: Read input
        vector<pair<int, int>> edges;
        map<int, int> node_namings;
        map<int, int> node_numbers;
        while (true)
        {
            int src_name;
            int dst_name;
            cin >> src_name;
            cin >> dst_name;
            if (src_name == 0 && dst_name == 0)
            {
                break;
            }

            int src_number = UVa821_assign_node_number(node_numbers, node_namings, src_name);
            int dst_number = UVa821_assign_node_number(node_numbers, node_namings, dst_name);

            edges.push_back(pair<int, int>(src_number, dst_number));
        }
        if (edges.size() == 0)
        {
            break;
        }

        // Step 2: Produce the data structures for Floyd Warshall
        int number_of_nodes = node_numbers.size();

        vector<vector<int> > adjacency_matrix;
        vector<vector<int> > distances;
        vector<vector<bool> > reachable;
        vector<vector<int> > path;
        adjacency_matrix.resize(number_of_nodes);
        distances.resize(number_of_nodes);
        reachable.resize(number_of_nodes);
        path.resize(number_of_nodes);
        for (int src = 0; src < number_of_nodes; src++)
        {
            adjacency_matrix[src].resize(number_of_nodes);
            distances[src].resize(number_of_nodes);
            reachable[src].resize(number_of_nodes);
            path[src].resize(number_of_nodes);

            for (int dst = 0; dst < number_of_nodes; dst++)
            {
                adjacency_matrix[src][dst] = 0;
                distances[src][dst] = -1;
                reachable[src][dst] = false;
                path[src][dst] = -1;
            }
        }

        for (unsigned int e = 0; e < edges.size(); e++)
        {
            pair<int, int> edge = edges[e];
            int src = edge.first;
            int dst = edge.second;

            // Beware of the input could have multiple edges!
            adjacency_matrix[src][dst] = 1;
            distances[src][dst] = 1;
            reachable[src][dst] = true;
            path[src][dst] = dst;
        }

        for (int k = 0; k < number_of_nodes; k++)
        {
            for (int src = 0; src < number_of_nodes; src++)
            {
                for (int dst = 0; dst < number_of_nodes; dst++)
                {
                    if (reachable[src][k] && reachable[k][dst]) // relaxation is possible if the proposal is valid
                    {
                        int current_distance = distances[src][dst];
                        int propose_distance = distances[src][k] + distances[k][dst];
                        if (!reachable[src][dst] || propose_distance < current_distance)
                        {
                            distances[src][dst] = propose_distance;
                            reachable[src][dst] = true;
                            path[src][dst] = path[src][k];
                        }
                    }
                }
            }
        }

        int sum = 0;
        int count = 0;
        for (int src = 0; src < number_of_nodes; src++)
        {
            for (int dst = 0; dst < number_of_nodes; dst++)
            {
                if (src != dst)
                {
                    sum += distances[src][dst];
                    count++;
                }
            }
        }
        cout << "Case " << test_case << ": average length between pages = " << setprecision(3) << fixed << ((double)sum) / count << " clicks" << endl;
    }

    return 0;
}

int UVa821_assign_node_number(map<int, int>& node_numbers, map<int, int>& node_namings, int node_name)
{
    int node_number;
    map<int, int>::iterator probe = node_numbers.find(node_name);
    if (probe == node_numbers.end())
    {
        node_number = node_numbers.size();
        node_numbers.insert(pair<int, int>(node_name, node_number));
        node_namings.insert(pair<int, int>(node_number, node_name));
    }
    else
    {
        node_number = probe->second;
    }

    return node_number;
}