#include "stdafx.h"

// http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=277

#include "UVa341.h"

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <stack>

using namespace std;

bool UVa341_less(vector<int>& distances, vector<bool>& reachable, int one, int two);
void UVa341_bubble_down(vector<int>& dijkstra_queue, vector<int>& distances, vector<bool>& reachable, vector<int>& node_index, int& queue_size, int parent_index);
int UVa341_delete_min(vector<int>& dijkstra_queue, vector<int>& distances, vector<bool>& reachable, vector<int>& node_index, int& queue_size);
void UVa341_change_key(vector<int>& dijkstra_queue, vector<int>& distances, vector<bool>& reachable, vector<int>& node_index, int& queue_size, int changed_node);
void UVa341_dijkstra(int src, vector<vector<pair<int, int> > >& adjacency_list, vector<int>& distances, vector<int>& previous);

int UVa341()
{
    int test_case = 0;
    while (true)
    {
        test_case++;

        // Step 1: Read input 
        int num_intersections;
        cin >> num_intersections;
        if (num_intersections == 0)
        {
            break;
        }
        vector<vector<pair<int, int> > > adjacency_list;
        adjacency_list.resize(num_intersections);
        for (int src = 1; src <= num_intersections; src++)
        {
            int num_edge;
            cin >> num_edge;
            for (int e = 0; e < num_edge; e++)
            {
                int dst;
                int time;
                cin >> dst;
                cin >> time;
                adjacency_list[src - 1].push_back(pair<int, int>(dst - 1, time));
            }
        }
        int src;
        int dst;
        cin >> src;
        cin >> dst;

        // Step 2: Dijkstra
        vector<int> distances;      // containing the distance values
        vector<int> previous;       // containing the previous node in the shortest path tree
        UVa341_dijkstra(src - 1, adjacency_list, distances, previous);
        
        // Step 3: Output - trace the path and reverse
        stack<int> path;
        int current = (dst - 1);
        while (true)
        {
            path.push(current + 1);
            if (current == (src - 1))
            {
                break;
            }
            current = previous[current];
        }

        cout << "Case " << test_case << ": Path =";
        while (path.size() > 0)
        {
            cout << " " << path.top();
            path.pop();
        }

        cout << "; " << distances[dst - 1] << " second delay" << endl;
    }

    return 0;
}

bool UVa341_less(vector<int>& distances, vector<bool>& reachable, int one, int two)
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

void UVa341_bubble_down(vector<int>& dijkstra_queue, vector<int>& distances, vector<bool>& reachable, vector<int>& node_index, int& queue_size, int parent_index)
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

            if (UVa341_less(distances, reachable, child1_value, child2_value))
            {
                if (UVa341_less(distances, reachable, child1_value, parent_value))
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
                if (UVa341_less(distances, reachable, child2_value, parent_value))
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

            if (UVa341_less(distances, reachable, child1_value, parent_value))
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

int UVa341_delete_min(vector<int>& dijkstra_queue, vector<int>& distances, vector<bool>& reachable, vector<int>& node_index, int& queue_size)
{
    int u = dijkstra_queue[0];
    node_index[u] = -1;
    if (queue_size > 1)
    {
        dijkstra_queue[0] = dijkstra_queue[queue_size - 1];
        dijkstra_queue[queue_size - 1] = -1;
        node_index[dijkstra_queue[0]] = 0;
        queue_size--;
        UVa341_bubble_down(dijkstra_queue, distances, reachable, node_index, queue_size, 0);
    }
    else
    {
        dijkstra_queue[queue_size - 1] = -1;
        queue_size--;        
    }
    return u;
}

void UVa341_change_key(vector<int>& dijkstra_queue, vector<int>& distances, vector<bool>& reachable, vector<int>& node_index, int& queue_size, int changed_node)
{
    int child_index = node_index[changed_node];
    while (child_index != 0)
    {
        int parent_index = (child_index + 1) / 2 - 1;

        int child_value = dijkstra_queue[child_index];
        int parent_value = dijkstra_queue[parent_index];

        if (UVa341_less(distances, reachable, child_value, parent_value))
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

void UVa341_dijkstra(int src, vector<vector<pair<int, int> > >& adjacency_list, vector<int>& distances, vector<int>& previous)
{
    vector<int> dijkstra_queue; // containing the node numbers
    vector<bool> reachable;     // false if the node is unreachable
    vector<int> node_index;     // the priority queue position of the node in the queue
    int queue_size;
    int num_nodes = adjacency_list.size();
    dijkstra_queue.resize(num_nodes);
    distances.resize(num_nodes);
    previous.resize(num_nodes);
    reachable.resize(num_nodes);
    node_index.resize(num_nodes);
    queue_size = num_nodes;

    // Step 1: Initialize the nodes and get them into the queue
    int j = 1;
    for (int i = 0; i < num_nodes; i++)
    {
        previous[i] = -1;
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
        int explored = UVa341_delete_min(dijkstra_queue, distances, reachable, node_index, queue_size);

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
                    previous[neighbor] = explored;
                    reachable[neighbor] = true;
                    UVa341_change_key(dijkstra_queue, distances, reachable, node_index, queue_size, neighbor);
                }
            }
        }
        else
        {
            break;
        }
    }
}

