#include "stdafx.h"

// http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=2678

#include "UVa11631.h"

#include <iostream>
#include <vector>
#include <map>

using namespace std;

bool UVa11631_less(vector<int>& priority_values, vector<bool>& priority_is_positive_infinity, int one, int two);
void UVa11631_bubble_down(vector<int>& priority_queue, vector<int>& priority_values, vector<bool>& priority_is_positive_infinity, vector<int>& node_index, int& queue_size, int parent_index);
int UVa11631_delete_min(vector<int>& priority_queue, vector<int>& priority_values, vector<bool>& priority_is_positive_infinity, vector<int>& node_index, int& queue_size);
void UVa11631_change_key(vector<int>& priority_queue, vector<int>& priority_values, vector<bool>& priority_is_positive_infinity, vector<int>& node_index, int& queue_size, int changed_node);
int UVa11631_Prim(vector<vector<pair<int, int>>>& adjacency_list);

int UVa11631()
{
    while (true)
    {
        // Step 1: Read input and build adjacency list
        int number_of_nodes;
        int number_of_edges;
        cin >> number_of_nodes;
        cin >> number_of_edges;
        if (number_of_nodes == 0 && number_of_edges == 0)
        {
            break;
        }

        vector<vector<pair<int, int>>> adjacency_list;
        adjacency_list.resize(number_of_nodes);
        int total_edge_weight = 0;
        for (int e = 0; e < number_of_edges; e++)
        {
            int src;
            int dst;
            int weight;
            cin >> src;
            cin >> dst;
            cin >> weight;
            adjacency_list[src].push_back(pair<int, int>(dst, weight));
            adjacency_list[dst].push_back(pair<int, int>(src, weight));
            total_edge_weight += weight;
        }


        int sum_weights = UVa11631_Prim(adjacency_list);
        cout << (total_edge_weight - sum_weights) << endl;
    }

    return 0;
}

bool UVa11631_less(vector<int>& priority_values, vector<bool>& priority_is_positive_infinity, int one, int two)
{
    if (priority_is_positive_infinity[one])
    {
        if (priority_is_positive_infinity[two])
        {
            return priority_values[one] < priority_values[two];
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

void UVa11631_bubble_down(vector<int>& priority_queue, vector<int>& priority_values, vector<bool>& priority_is_positive_infinity, vector<int>& node_index, int& queue_size, int parent_index)
{
    while (true)
    {
        int child2_index = (parent_index + 1) * 2;
        int child1_index = child2_index - 1;

        if (child2_index < queue_size)
        {
            int parent_value = priority_queue[parent_index];
            int child1_value = priority_queue[child1_index];
            int child2_value = priority_queue[child2_index];

            if (UVa11631_less(priority_values, priority_is_positive_infinity, child1_value, child2_value))
            {
                if (UVa11631_less(priority_values, priority_is_positive_infinity, child1_value, parent_value))
                {
                    priority_queue[parent_index] = child1_value;
                    priority_queue[child1_index] = parent_value;
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
                if (UVa11631_less(priority_values, priority_is_positive_infinity, child2_value, parent_value))
                {
                    priority_queue[parent_index] = child2_value;
                    priority_queue[child2_index] = parent_value;
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
            int parent_value = priority_queue[parent_index];
            int child1_value = priority_queue[child1_index];

            if (UVa11631_less(priority_values, priority_is_positive_infinity, child1_value, parent_value))
            {
                priority_queue[parent_index] = child1_value;
                priority_queue[child1_index] = parent_value;
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

int UVa11631_delete_min(vector<int>& priority_queue, vector<int>& priority_values, vector<bool>& priority_is_positive_infinity, vector<int>& node_index, int& queue_size)
{
    int u = priority_queue[0];
    node_index[u] = -1;
    if (queue_size > 1)
    {
        priority_queue[0] = priority_queue[queue_size - 1];
        priority_queue[queue_size - 1] = -1;
        node_index[priority_queue[0]] = 0;
        queue_size--;
        UVa11631_bubble_down(priority_queue, priority_values, priority_is_positive_infinity, node_index, queue_size, 0);
    }
    else
    {
        priority_queue[queue_size - 1] = -1;
        queue_size--;
    }
    return u;
}

void UVa11631_change_key(vector<int>& priority_queue, vector<int>& priority_values, vector<bool>& priority_is_positive_infinity, vector<int>& node_index, int& queue_size, int changed_node)
{
    int child_index = node_index[changed_node];
    while (child_index != 0)
    {
        int parent_index = (child_index + 1) / 2 - 1;

        int child_value = priority_queue[child_index];
        int parent_value = priority_queue[parent_index];

        if (UVa11631_less(priority_values, priority_is_positive_infinity, child_value, parent_value))
        {
            priority_queue[child_index] = parent_value;
            priority_queue[parent_index] = child_value;
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

int UVa11631_Prim(vector<vector<pair<int, int>>>& adjacency_list)
{
    // Step 1: Initialize the data structures
    vector<int> priority_queue;
    vector<int> node_index;
    vector<int> priority_values;
    vector<bool> priority_is_positive_infinity;
    vector<int> parents;
    int number_of_nodes = adjacency_list.size();
    priority_queue.resize(number_of_nodes);
    node_index.resize(number_of_nodes);
    priority_values.resize(number_of_nodes);
    priority_is_positive_infinity.resize(number_of_nodes);
    parents.resize(number_of_nodes);
    for (int n = 0; n < number_of_nodes; n++)
    {
        priority_queue[n] = n;
        node_index[n] = n;
        priority_values[n] = (n == 0) ? 0 : -1;
        priority_is_positive_infinity[n] = (n == 0);
        parents[n] = -1;
    }

#ifdef LOG
    cout << "digraph{" << endl;
#endif
    int sum_weights = 0;
    // Step 2: Prim's loop
    int queue_size = number_of_nodes;
    for (int e = 0; e < number_of_nodes; e++)
    {
        int src = UVa11631_delete_min(priority_queue, priority_values, priority_is_positive_infinity, node_index, queue_size);
        if (parents[src] != -1)
        {
#ifdef LOG
            cout << parents[src] << "->" << src << "[label=\"" << priority_values[src] << "\"];" << endl;
#endif
            sum_weights += priority_values[src];
        }
        for (vector<pair<int, int>>::iterator ni = adjacency_list[src].begin(); ni != adjacency_list[src].end(); ni++)
        {
            int dst = ni->first;
            if (node_index[dst] != -1) // If the node is still in the other side
            {
                int cut_cost = ni->second;
                if (!priority_is_positive_infinity[dst] || cut_cost < priority_values[dst])
                {
                    priority_is_positive_infinity[dst] = true;
                    priority_values[dst] = cut_cost;
                    parents[dst] = src;
                    UVa11631_change_key(priority_queue, priority_values, priority_is_positive_infinity, node_index, queue_size, dst);
                }
            }
        }
    }
#ifdef LOG
    cout << "}" << endl;
#endif

    return sum_weights;
}