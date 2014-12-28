#include "stdafx.h"

// http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1219

#include "UVa10278.h"

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

bool UVa10278_less(vector<int>& distances, vector<bool>& reachable, int one, int two);
void UVa10278_bubble_down(vector<int>& dijkstra_queue, vector<int>& distances, vector<bool>& reachable, vector<int>& node_index, int& queue_size, int parent_index);
int UVa10278_delete_min(vector<int>& dijkstra_queue, vector<int>& distances, vector<bool>& reachable, vector<int>& node_index, int& queue_size);
void UVa10278_change_key(vector<int>& dijkstra_queue, vector<int>& distances, vector<bool>& reachable, vector<int>& node_index, int& queue_size, int changed_node);
void UVa10278_dijkstra(int src, vector<vector<pair<int, int> > >& adjacency_list, vector<int>& distances);

int UVa10278()
{
    int number_of_test_cases;
    cin >> number_of_test_cases;
    for (int test_case = 1; test_case <= number_of_test_cases; test_case++)
    {
        // Step 1: Input
        int num_fire_stations;
        int num_intersections;
        cin >> num_fire_stations;
        cin >> num_intersections;

        // Modeling the graph as a virtual node 0 linking to all fire stations with no cost
        vector<vector<pair<int, int> > > adjacency_list;
        adjacency_list.resize(num_intersections + 1);

        for (int f = 0; f < num_fire_stations; f++)
        {
            int fire_station_number;
            cin >> fire_station_number;
            
            adjacency_list[0].push_back(pair<int, int>(fire_station_number, 0));
            adjacency_list[fire_station_number].push_back(pair<int, int>(0, 0));
        }

        string line;
        getline(cin, line); // consume the first endline

        while (true)
        {   
            getline(cin, line);
            if (cin.eof() || line == "")
            {
                break;
            }
            istringstream iss(line);
            int from, to, cost;
            iss >> from;
            iss >> to;
            iss >> cost;

            adjacency_list[from].push_back(pair<int, int>(to, cost));
            adjacency_list[to].push_back(pair<int, int>(from, cost));
        }

        int num_nodes = num_intersections + 1;

        int min_max_distance_so_far = -1;
        int best_fire_station = 0;

        
        for (int trial_fire_station = 1; trial_fire_station <= num_intersections; trial_fire_station++)
        {
            // Step 2.1: For each intersection, place a station by adding a link
            adjacency_list[0].push_back(pair<int, int>(trial_fire_station, 0));
            adjacency_list[trial_fire_station].push_back(pair<int, int>(0, 0));

            // Step 3: Dijkstra
            vector<int> distances;      // containing the distance values
            UVa10278_dijkstra(0, adjacency_list, distances);

            // Step 4: Minimize the maximum distance over all trial stations
            int max_distance = -1;
            for (int i = 0; i < num_nodes; i++)
            {
                max_distance = max(max_distance, distances[i]);
            }
            if (trial_fire_station == 1)
            {
                min_max_distance_so_far = max_distance;
                best_fire_station = trial_fire_station;
            }
            else
            {
                if (min_max_distance_so_far > max_distance)
                {
                    min_max_distance_so_far = max_distance;
                    best_fire_station = trial_fire_station;    
                }
            }
            
            // Step 2.2: When we are done remove the link
            adjacency_list[0].pop_back();
            adjacency_list[trial_fire_station].pop_back();
        }

        // Step 5: Output
        if (test_case != 1)
        {
            cout << endl;
        }
        cout << best_fire_station << endl;
    }

    return 0;
}

bool UVa10278_less(vector<int>& distances, vector<bool>& reachable, int one, int two)
{
    if (reachable[one])
    {
        if (reachable[two])
        {
            return distances[one] < distances[two];
        }
        else
        {
            return true;
        }
    }
    else
    {
        return false;
    }
}

void UVa10278_bubble_down(vector<int>& dijkstra_queue, vector<int>& distances, vector<bool>& reachable, vector<int>& node_index, int& queue_size, int parent_index)
{
    while (true)
    {
        int child2_index = (parent_index + 1) * 2;
        int child1_index = child2_index - 1;

        if (child2_index < queue_size)
        {
            int parent_value = dijkstra_queue[parent_index];
            int child1_value = dijkstra_queue[child1_index];
            int child2_value = dijkstra_queue[child2_index];

            if (UVa10278_less(distances, reachable, child1_value, child2_value))
            {
                if (UVa10278_less(distances, reachable, child1_value, parent_value))
                {
                    dijkstra_queue[parent_index] = child1_value;
                    dijkstra_queue[child1_index] = parent_value;
                    node_index[parent_value] = child1_index;
                    node_index[child1_value] = parent_index;
                    parent_index = child1_index;
                }
                else
                {
                    break;
                }
            }
            else
            {
                if (UVa10278_less(distances, reachable, child2_value, parent_value))
                {
                    dijkstra_queue[parent_index] = child2_value;
                    dijkstra_queue[child2_index] = parent_value;
                    node_index[parent_value] = child2_index;
                    node_index[child2_value] = parent_index;
                    parent_index = child2_index;
                }
                else
                {
                    break;
                }
            }
        }
        else if (child1_index < queue_size)
        {
            int parent_value = dijkstra_queue[parent_index];
            int child1_value = dijkstra_queue[child1_index];

            if (UVa10278_less(distances, reachable, child1_value, parent_value))
            {
                dijkstra_queue[parent_index] = child1_value;
                dijkstra_queue[child1_index] = parent_value;
                node_index[parent_value] = child1_index;
                node_index[child1_value] = parent_index;
                parent_index = child1_index;
            }
            else
            {
                break;
            }
        }
        else
        {
            break;
        }
    }
}

int UVa10278_delete_min(vector<int>& dijkstra_queue, vector<int>& distances, vector<bool>& reachable, vector<int>& node_index, int& queue_size)
{
    int u = dijkstra_queue[0];
    node_index[u] = -1;
    if (queue_size > 1)
    {
        dijkstra_queue[0] = dijkstra_queue[queue_size - 1];
        dijkstra_queue[queue_size - 1] = -1;
        node_index[dijkstra_queue[0]] = 0;
        queue_size--;
        UVa10278_bubble_down(dijkstra_queue, distances, reachable, node_index, queue_size, 0);
    }
    else
    {
        dijkstra_queue[queue_size - 1] = -1;
        queue_size--;        
    }
    return u;
}

void UVa10278_change_key(vector<int>& dijkstra_queue, vector<int>& distances, vector<bool>& reachable, vector<int>& node_index, int& queue_size, int changed_node)
{
    int child_index = node_index[changed_node];
    while (child_index != 0)
    {
        int parent_index = (child_index + 1) / 2 - 1;

        int child_value = dijkstra_queue[child_index];
        int parent_value = dijkstra_queue[parent_index];

        if (UVa10278_less(distances, reachable, child_value, parent_value))
        {
            dijkstra_queue[child_index] = parent_value;
            dijkstra_queue[parent_index] = child_value;
            node_index[parent_value] = child_index;
            node_index[child_value] = parent_index;
            child_index = parent_index;
        }
        else
        {
            break;
        }
    }
}

void UVa10278_dijkstra(int src, vector<vector<pair<int, int> > >& adjacency_list, vector<int>& distances)
{
    vector<int> dijkstra_queue; // containing the node numbers
    vector<bool> reachable;     // false if the node is unreachable
    vector<int> node_index;     // the priority queue position of the node in the queue
    int queue_size;
    int num_nodes = adjacency_list.size();
    dijkstra_queue.resize(num_nodes);
    distances.resize(num_nodes);
    reachable.resize(num_nodes);
    node_index.resize(num_nodes);
    queue_size = num_nodes;

    // Step 1: Initialize the nodes and get them into the queue
    int j = 1;
    for (int i = 0; i < num_nodes; i++)
    {
        if (i == src)
        {
            distances[i] = 0;
            reachable[i] = true;
            dijkstra_queue[0] = i;
            node_index[i] = 0;
        }
        else
        {
            distances[i] = -1;
            reachable[i] = false;
            dijkstra_queue[j] = i;
            node_index[i] = j;
            j++;
        }
    }

    // Step 2: Main Loop
    while (queue_size > 0)
    {
        int explored = UVa10278_delete_min(dijkstra_queue, distances, reachable, node_index, queue_size);

        if (reachable[explored])
        {
            for (unsigned int ni = 0; ni < adjacency_list[explored].size(); ni++)
            {
                pair<int, int> neighbor_edge = adjacency_list[explored][ni];
                int neighbor = neighbor_edge.first;
                int new_neighbor_distance = distances[explored] + neighbor_edge.second;
                if (!reachable[neighbor] || new_neighbor_distance < distances[neighbor])
                {
                    distances[neighbor] = new_neighbor_distance;
                    reachable[neighbor] = true;
                    UVa10278_change_key(dijkstra_queue, distances, reachable, node_index, queue_size, neighbor);
                }
            }
        }
        else
        {
            break;
        }
    }
}
