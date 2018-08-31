#include "stdafx.h"

// http://uva.onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=870

#include "UVa929.h"

#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

bool UVa929_less(vector<int>& distances, vector<bool>& reachable, int one, int two);
void UVa929_bubble_down(vector<int>& dijkstra_queue, vector<int>& distances, vector<bool>& reachable, vector<int>& node_index, int& queue_size, int parent_index);
int UVa929_delete_min(vector<int>& dijkstra_queue, vector<int>& distances, vector<bool>& reachable, vector<int>& node_index, int& queue_size);
void UVa929_change_key(vector<int>& dijkstra_queue, vector<int>& distances, vector<bool>& reachable, vector<int>& node_index, int& queue_size, int changed_node);
void UVa929_dijkstra(int num_cells, int src, int dst, vector<int>& distances);

int grid[1000][1000];
int graph_next[1000000][5];
int graph_weight[1000000][5];

int UVa929()
{
    int number_of_test_cases;
    cin >> number_of_test_cases;
    for (int test_case = 1; test_case <= number_of_test_cases; test_case++)
    {
        char input;
        int num_rows;
        int num_cols;

        // Step 1: Read input
        scanf("%d %d",&num_rows,&num_cols);
        getchar();
        for (int r = 0; r < num_rows; r++)
        {
            for (int c = 0; c < num_cols; c++)
            {
                input = getchar();
                getchar();
                grid[r][c]=(int)input-48;
            }
        }

        // Step 2: Build graph
        int num_cells = num_rows * num_cols;
        for (int i = 0; i < num_cells; i++)
        {
            graph_next[i][0] = 0;
        }
        vector<pair<int, int> > neighbor_candidates;
        neighbor_candidates.resize(4);
        for (int src_row = 0; src_row < num_rows; src_row++)
        {
            for (int src_col = 0; src_col < num_cols; src_col++)
            {
                neighbor_candidates[0] = pair<int, int>(src_row - 1, src_col);
                neighbor_candidates[1] = pair<int, int>(src_row + 1, src_col);
                neighbor_candidates[2] = pair<int, int>(src_row, src_col - 1);
                neighbor_candidates[3] = pair<int, int>(src_row, src_col + 1);
                for (vector<pair<int, int> >::iterator nci = neighbor_candidates.begin(); nci != neighbor_candidates.end(); nci++)
                {
                    int dst_row = nci->first;
                    int dst_col = nci->second;
                    if (0 <= dst_row && dst_row < num_rows && 0 <= dst_col && dst_col < num_cols)
                    {
                        int src_cell = src_row * num_cols + src_col;
                        int dst_cell = dst_row * num_cols + dst_col;

                        int src_neighbor_index = ++graph_next[src_cell][0];
                        graph_next[src_cell][src_neighbor_index] = dst_cell;
                        graph_weight[src_cell][src_neighbor_index] = grid[dst_row][dst_col];
                    }
                }
            }
        }

        int dst = num_cells - 1;
        // Step 3: Dijkstra
        vector<int> distances;
        UVa929_dijkstra(num_cells, 0 , dst, distances);

        cout << grid[0][0] + distances[dst] << endl;
    }

    return 0;
}

bool UVa929_less(vector<int>& distances, vector<bool>& reachable, int one, int two)
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

void UVa929_bubble_down(vector<int>& dijkstra_queue, vector<int>& distances, vector<bool>& reachable, vector<int>& node_index, int& queue_size, int parent_index)
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

            if (UVa929_less(distances, reachable, child1_value, child2_value))
            {
                if (UVa929_less(distances, reachable, child1_value, parent_value))
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
                if (UVa929_less(distances, reachable, child2_value, parent_value))
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

            if (UVa929_less(distances, reachable, child1_value, parent_value))
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

int UVa929_delete_min(vector<int>& dijkstra_queue, vector<int>& distances, vector<bool>& reachable, vector<int>& node_index, int& queue_size)
{
    int u = dijkstra_queue[0];
    node_index[u] = -1;
    if (queue_size > 1)
    {
        dijkstra_queue[0] = dijkstra_queue[queue_size - 1];
        dijkstra_queue[queue_size - 1] = -1;
        node_index[dijkstra_queue[0]] = 0;
        queue_size--;
        UVa929_bubble_down(dijkstra_queue, distances, reachable, node_index, queue_size, 0);
    }
    else
    {
        dijkstra_queue[queue_size - 1] = -1;
        queue_size--;        
    }
    return u;
}

void UVa929_change_key(vector<int>& dijkstra_queue, vector<int>& distances, vector<bool>& reachable, vector<int>& node_index, int& queue_size, int changed_node)
{
    int child_index = node_index[changed_node];
    while (child_index != 0)
    {
        int parent_index = (child_index + 1) / 2 - 1;

        int child_value = dijkstra_queue[child_index];
        int parent_value = dijkstra_queue[parent_index];

        if (UVa929_less(distances, reachable, child_value, parent_value))
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

void UVa929_dijkstra(int num_cells, int src, int dst, vector<int>& distances)
{
    vector<int> dijkstra_queue; // containing the node numbers
    vector<bool> reachable;     // false if the node is unreachable
    vector<int> node_index;     // the priority queue position of the node in the queue
    int queue_size;
    dijkstra_queue.resize(num_cells);
    distances.resize(num_cells);
    reachable.resize(num_cells);
    node_index.resize(num_cells);
    queue_size = num_cells;

    // Step 1: Initialize the nodes and get them into the queue
    int j = 1;
    for (int i = 0; i < num_cells; i++)
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

    // Step 2: Initialize the nodes and get them into the queue
    while (queue_size > 0)
    {
        int explored = UVa929_delete_min(dijkstra_queue, distances, reachable, node_index, queue_size);

        if (explored == dst)
        {
            break;
        }

        if (reachable[explored])
        {
            for (int ni = 1; ni <= graph_next[explored][0]; ni++)
            {
                int neighbor = graph_next[explored][ni];
                int edge_weight = graph_weight[explored][ni];

                int new_neighbor_distance = distances[explored] + edge_weight;
                if (!reachable[neighbor] || new_neighbor_distance < distances[neighbor])
                {
                    distances[neighbor] = new_neighbor_distance;
                    reachable[neighbor] = true;
                    UVa929_change_key(dijkstra_queue, distances, reachable, node_index, queue_size, neighbor);
                }
            }
        }
        else
        {
            break;
        }
    }
}