#include "stdafx.h"

// http://uva.onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=1544

// #define LOG

#include "UVa10603.h"

#include <iostream>
#include <vector>
#include <map>

using namespace std;

class UVa10603_implicit_graph;

bool UVa10603_less(vector<int>& distances, vector<bool>& reachable, int one, int two);
void UVa10603_bubble_down(vector<int>& dijkstra_queue, vector<int>& distances, vector<bool>& reachable, vector<int>& node_index, int& queue_size, int parent_index);
int UVa10603_delete_min(vector<int>& dijkstra_queue, vector<int>& distances, vector<bool>& reachable, vector<int>& node_index, int& queue_size);
void UVa10603_change_key(vector<int>& dijkstra_queue, vector<int>& distances, vector<bool>& reachable, vector<int>& node_index, int& queue_size, int changed_node);
void UVa10063_solve(int a, int b, int c, int d);
void UVa10603_dijkstra(int src, UVa10603_implicit_graph* implicit_graph);

int UVa10603()
{
    int number_of_test_cases;
    cin >> number_of_test_cases;
    for (int test_case = 1; test_case <= number_of_test_cases; test_case++)
    {
        int a, b, c, d;
        cin >> a;
        cin >> b;
        cin >> c;
        cin >> d;
        UVa10063_solve(a, b, c, d);
    }

    return 0;
}

bool UVa10603_less(vector<int>& distances, vector<bool>& reachable, int one, int two)
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

void UVa10603_bubble_down(vector<int>& dijkstra_queue, vector<int>& distances, vector<bool>& reachable, vector<int>& node_index, int& queue_size, int parent_index)
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

            if (UVa10603_less(distances, reachable, child1_value, child2_value))
            {
                if (UVa10603_less(distances, reachable, child1_value, parent_value))
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
                if (UVa10603_less(distances, reachable, child2_value, parent_value))
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

            if (UVa10603_less(distances, reachable, child1_value, parent_value))
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

// In order to avoid building the graph, an implicit graph is used
// The graph, however, knows the maximum number of nodes, which fit this particular case
// General implicit graph might not have this privilege
class UVa10603_implicit_graph
{
public:
    UVa10603_implicit_graph(int _a, int _b, int _c, int _d) : a(_a), b(_b), c(_c), d(_d), best_volume_achieved(0), archieving_distance(0)
    {
    }

    int size()
    {
        return 201 * 201;
    }

    // A node is presented as a base 201 number
    // representing the volume of water in a and b respectively
    vector<pair<int, int> > get_neighbors(int node)
    {
        int a_curr_volume = node / 201;
        int b_curr_volume = node % 201;
        int c_curr_volume = c - a_curr_volume - b_curr_volume;

        vector<pair<int, int> > result;

        int a_next_volume = -1;
        int b_next_volume = -1;
        int c_next_volume = -1;
        int poured_volume = -1;
        int neighbor = -1;

        if (a_curr_volume > 0)
        {
            pour(a_curr_volume, b_curr_volume, b, &a_next_volume, &b_next_volume, &poured_volume);
            c_next_volume = c - a_next_volume - b_next_volume;
            neighbor = a_next_volume * 201 + b_next_volume;
#ifdef LOG
            log_neighbor(node, neighbor, poured_volume);
#endif
            result.push_back(pair<int, int>(neighbor, poured_volume));

            pour(a_curr_volume, c_curr_volume, c, &a_next_volume, &c_next_volume, &poured_volume);
            b_next_volume = c - a_next_volume - c_next_volume;
            neighbor = a_next_volume * 201 + b_next_volume;
#ifdef LOG
            log_neighbor(node, neighbor, poured_volume);
#endif
            result.push_back(pair<int, int>(neighbor, poured_volume));
        }

        if (b_curr_volume > 0)
        {
            pour(b_curr_volume, a_curr_volume, a, &b_next_volume, &a_next_volume, &poured_volume);
            c_next_volume = c - a_next_volume - b_next_volume;
            neighbor = a_next_volume * 201 + b_next_volume;
#ifdef LOG
            log_neighbor(node, neighbor, poured_volume);
#endif
            result.push_back(pair<int, int>(neighbor, poured_volume));

            pour(b_curr_volume, c_curr_volume, c, &b_next_volume, &c_next_volume, &poured_volume);
            a_next_volume = c - b_next_volume - c_next_volume;
            neighbor = a_next_volume * 201 + b_next_volume;
#ifdef LOG
            log_neighbor(node, neighbor, poured_volume);
#endif
            result.push_back(pair<int, int>(neighbor, poured_volume));
        }

        if (c_curr_volume > 0)
        {
            pour(c_curr_volume, a_curr_volume, a, &c_next_volume, &a_next_volume, &poured_volume);
            b_next_volume = c - a_next_volume - c_next_volume;
            neighbor = a_next_volume * 201 + b_next_volume;
#ifdef LOG
            log_neighbor(node, neighbor, poured_volume);
#endif
            result.push_back(pair<int, int>(neighbor, poured_volume));

            pour(c_curr_volume, b_curr_volume, b, &c_next_volume, &b_next_volume, &poured_volume);
            a_next_volume = c - b_next_volume - c_next_volume;
            neighbor = a_next_volume * 201 + b_next_volume;
#ifdef LOG
            log_neighbor(node, neighbor, poured_volume);
#endif
            result.push_back(pair<int, int>(neighbor, poured_volume));
        }
#ifdef LOG
        cout << endl;
#endif
        return result;
    }

    bool on_node_explored(int node, int distance)
    {
        int a_curr_volume = node / 201;
        int b_curr_volume = node % 201;
        int c_curr_volume = c - a_curr_volume - b_curr_volume;

        if (a_curr_volume == d || b_curr_volume == d || c_curr_volume == d)
        {
            best_volume_achieved = d;
            archieving_distance = distance;
            return true;
        }
        else
        {
            if (a_curr_volume < d && a_curr_volume > best_volume_achieved)
            {
                best_volume_achieved = a_curr_volume;
                archieving_distance = distance;
            }
            if (b_curr_volume < d && b_curr_volume > best_volume_achieved)
            {
                best_volume_achieved = b_curr_volume;
                archieving_distance = distance;
            }
            
            if (c_curr_volume < d && c_curr_volume > best_volume_achieved)
            {
                best_volume_achieved = c_curr_volume;
                archieving_distance = distance;
            }
            return false;
        }
    }

    void conclude()
    {
        cout << archieving_distance << " " << best_volume_achieved << endl;
    }

#ifdef LOG
    void log_neighbor(int from, int to, int cost)
    {
        int from_a = from / 201;
        int from_b = from % 201;
        int from_c = c - from_a - from_b;

        int to_a = to / 201;
        int to_b = to % 201;
        int to_c = c - to_a - to_b;

        cout << "(" << from_a << ", " << from_b << ", " << from_c << "):" << from << " -" << cost << "-> (" << to_a << ", " << to_b << ", " << to_c << "):" << to << endl;
    }
#endif

private:
    int a; 
    int b;
    int c;
    int d;

    int best_volume_achieved;
    int archieving_distance;

    void pour(int src_cur_volume, int dst_cur_volume, int dst_max_volume, int* src_result_volume, int* dst_result_volume, int* poured_volume)
    {
        int dst_avail_volume = dst_max_volume - dst_cur_volume;
        if (src_cur_volume <= dst_avail_volume)
        {
            // dst have enough space to hold them all
            *src_result_volume = 0;
            *dst_result_volume = dst_cur_volume + src_cur_volume;
            *poured_volume = src_cur_volume;
        }
        else
        {
            // dst don't have enought space to hold them all
            *src_result_volume = src_cur_volume - dst_avail_volume;
            *dst_result_volume = dst_cur_volume + dst_avail_volume;
            *poured_volume = dst_avail_volume;
        }
    }
};

int UVa10603_delete_min(vector<int>& dijkstra_queue, vector<int>& distances, vector<bool>& reachable, vector<int>& node_index, int& queue_size)
{
    int u = dijkstra_queue[0];
    node_index[u] = -1;
    if (queue_size > 1)
    {
        dijkstra_queue[0] = dijkstra_queue[queue_size - 1];
        dijkstra_queue[queue_size - 1] = -1;
        node_index[dijkstra_queue[0]] = 0;
        queue_size--;
        UVa10603_bubble_down(dijkstra_queue, distances, reachable, node_index, queue_size, 0);
    }
    else
    {
        dijkstra_queue[queue_size - 1] = -1;
        queue_size--;        
    }
    return u;
}

void UVa10603_change_key(vector<int>& dijkstra_queue, vector<int>& distances, vector<bool>& reachable, vector<int>& node_index, int& queue_size, int changed_node)
{
    int child_index = node_index[changed_node];
    while (child_index != 0)
    {
        int parent_index = (child_index + 1) / 2 - 1;

        int child_value = dijkstra_queue[child_index];
        int parent_value = dijkstra_queue[parent_index];

        if (UVa10603_less(distances, reachable, child_value, parent_value))
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

void UVa10603_dijkstra(int src, UVa10603_implicit_graph* implicit_graph)
{
    vector<int> dijkstra_queue; // containing the node numbers
    vector<bool> reachable;     // false if the node is unreachable
    vector<int> node_index;     // the priority queue position of the node in the queue
    vector<int> distances;       
    int queue_size;
    int num_nodes = implicit_graph->size();
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
        int explored = UVa10603_delete_min(dijkstra_queue, distances, reachable, node_index, queue_size);

        if (reachable[explored])
        {
            if(implicit_graph->on_node_explored(explored, distances[explored]))
            {
                break;
            };

            vector<pair<int, int> > neighbors = implicit_graph->get_neighbors(explored);
            for (unsigned int ni = 0; ni < neighbors.size(); ni++)
            {
                pair<int, int> neighbor_edge = neighbors[ni];
                int neighbor = neighbor_edge.first;
                int new_neighbor_distance = distances[explored] + neighbor_edge.second;
                if (!reachable[neighbor] || new_neighbor_distance < distances[neighbor])
                {
                    distances[neighbor] = new_neighbor_distance;
                    reachable[neighbor] = true;
                    UVa10603_change_key(dijkstra_queue, distances, reachable, node_index, queue_size, neighbor);
                }
            }
        }
        else
        {
            break;
        }
    }
}

void UVa10063_solve(int a, int b, int c, int d)
{
    UVa10603_implicit_graph* graph = new UVa10603_implicit_graph(a, b, c, d);
    UVa10603_dijkstra(0, graph);
    graph->conclude();
    delete graph;
}