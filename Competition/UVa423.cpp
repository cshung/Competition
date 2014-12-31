#include "stdafx.h"

// http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=364

#include "UVa423.h"

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

bool UVa423_less(vector<int>& distances, vector<bool>& reachable, int one, int two);
void UVa423_bubble_down(vector<int>& dijkstra_queue, vector<int>& distances, vector<bool>& reachable, vector<int>& node_index, int& queue_size, int parent_index);
int UVa423_delete_min(vector<int>& dijkstra_queue, vector<int>& distances, vector<bool>& reachable, vector<int>& node_index, int& queue_size);
void UVa423_change_key(vector<int>& dijkstra_queue, vector<int>& distances, vector<bool>& reachable, vector<int>& node_index, int& queue_size, int changed_node);
void UVa423_dijkstra(int src, vector<vector<pair<int, int> > >& adjacency_list, vector<int>& distances);

int UVa423()
{
    // Step 1: Read input
    int number_of_nodes;
    cin >> number_of_nodes;
    string entry;
    vector<vector<pair<int, int>>> adjacency_list;
    adjacency_list.resize(number_of_nodes);
    for (int src = 0; src < number_of_nodes; src++)
    {
        for (int dst = 0; dst < src; dst++)
        {
            cin >> entry;
            if (entry != "x")
            {
                int cost = stoi(entry);
                adjacency_list[src].push_back(pair<int, int>(dst, cost));
                adjacency_list[dst].push_back(pair<int, int>(src, cost));
            }
        }   
    }

    // Step 2: Dijkstra
    vector<int> distances;
    UVa423_dijkstra(0, adjacency_list, distances);

    cout << *max_element(distances.begin(), distances.end()) << endl;

    return 0;
}


bool UVa423_less(vector<int>& distances, vector<bool>& reachable, int one, int two)
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

void UVa423_bubble_down(vector<int>& dijkstra_queue, vector<int>& distances, vector<bool>& reachable, vector<int>& node_index, int& queue_size, int parent_index)
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

            if (UVa423_less(distances, reachable, child1_value, child2_value))
            {
                if (UVa423_less(distances, reachable, child1_value, parent_value))
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
                if (UVa423_less(distances, reachable, child2_value, parent_value))
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

            if (UVa423_less(distances, reachable, child1_value, parent_value))
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

int UVa423_delete_min(vector<int>& dijkstra_queue, vector<int>& distances, vector<bool>& reachable, vector<int>& node_index, int& queue_size)
{
    int u = dijkstra_queue[0];
    node_index[u] = -1;
    if (queue_size > 1)
    {
        dijkstra_queue[0] = dijkstra_queue[queue_size - 1];
        dijkstra_queue[queue_size - 1] = -1;
        node_index[dijkstra_queue[0]] = 0;
        queue_size--;
        UVa423_bubble_down(dijkstra_queue, distances, reachable, node_index, queue_size, 0);
    }
    else
    {
        dijkstra_queue[queue_size - 1] = -1;
        queue_size--;
    }
    return u;
}

void UVa423_change_key(vector<int>& dijkstra_queue, vector<int>& distances, vector<bool>& reachable, vector<int>& node_index, int& queue_size, int changed_node)
{
    int child_index = node_index[changed_node];
    while (child_index != 0)
    {
        int parent_index = (child_index + 1) / 2 - 1;

        int child_value = dijkstra_queue[child_index];
        int parent_value = dijkstra_queue[parent_index];

        if (UVa423_less(distances, reachable, child_value, parent_value))
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

void UVa423_dijkstra(int src, vector<vector<pair<int, int> > >& adjacency_list, vector<int>& distances)
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
        int explored = UVa423_delete_min(dijkstra_queue, distances, reachable, node_index, queue_size);

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
                    UVa423_change_key(dijkstra_queue, distances, reachable, node_index, queue_size, neighbor);
                }
            }
        }
        else
        {
            break;
        }
    }
}
