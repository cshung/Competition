#include "stdafx.h"

// http://uva.onlinejudge.org/index.php?option=onlinejudge&Itemid=8&page=show_problem&problem=39

#include "UVa103.h"

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int UVa103()
{
    while (true)
    {
        int number_of_boxes;
        int dimension;
        cin >> number_of_boxes;
        if (cin.eof())
        {
            break;
        }
        cin >> dimension;
        vector<vector<int> > boxes;
        boxes.resize(number_of_boxes);
        for (int i = 0; i < number_of_boxes; i++)
        {
            boxes[i].resize(dimension);
            for (int d = 0; d < dimension; d++)
            {
                int length;
                cin >> length;
                boxes[i][d] = length;
            }
            sort(boxes[i].begin(), boxes[i].end());
        }

        // Step 1: Build DAG - larger box point to smaller box (so that the reverse longest path is smaller nested within largest)
        vector<vector<int> > adjacency_list;
        vector<int> indegree;
        adjacency_list.resize(number_of_boxes);
        indegree.resize(number_of_boxes);
        for (int i = 0; i < number_of_boxes; i++)
        {
            indegree[i] = 0;
        }
        for (int i = 0; i < number_of_boxes; i++)
        {
            for (int j = i + 1; j < number_of_boxes; j++)
            {
                int global_compare = 2;
                for (int d = 0; d < dimension; d++)
                {
                    int local_compare;
                    if (boxes[i][d] == boxes[j][d])
                    {
                        local_compare = 0;
                    }
                    else if (boxes[i][d] > boxes[j][d])
                    {
                        local_compare = 1;
                    }
                    else
                    {
                        local_compare = -1;
                    }
                    if (global_compare == 2)
                    {
                        global_compare = local_compare;
                    }
                    else if (global_compare != local_compare)
                    {
                        global_compare = 0;
                        break;
                    }
                }
                if (global_compare == 1)
                {
                    adjacency_list[i].push_back(j);
                    indegree[j]++;
                }
                else if (global_compare == -1)
                {
                    adjacency_list[j].push_back(i);
                    indegree[i]++;
                }
            }
        }

        // Step 2: Topological sort
        queue<int> nodes_with_zero_degree;
        for (int i = 0; i < number_of_boxes; i++)
        {
            if (indegree[i] == 0)
            {
                nodes_with_zero_degree.push(i);
            }
        }
        vector<int> topological_order;
        while (nodes_with_zero_degree.size() > 0)
        {
            int current_node = nodes_with_zero_degree.front();
            nodes_with_zero_degree.pop();
            topological_order.push_back(current_node);
            for (vector<int>::iterator ni = adjacency_list[current_node].begin(); ni != adjacency_list[current_node].end(); ni++)
            {
                int neighbor = *ni;
                if (--indegree[neighbor] == 0)
                {
                    nodes_with_zero_degree.push(neighbor);
                }
            }
        }

        // Step 3: Find longest path in this sequence
        vector<int> all_longest_path_length;
        vector<int> all_longest_path_parent;
        all_longest_path_length.resize(number_of_boxes);
        all_longest_path_parent.resize(number_of_boxes);
        all_longest_path_length[0] = 1;
        all_longest_path_parent[0] = -1;

        int longest_path_length = -1;
        int longest_path_index = -1;

        for (int i = 1; i < number_of_boxes; i++)
        {
            int best_path_length = 1;
            int best_path_index = -1;
            for (int j = 0; j < i; j++)
            {
                int last_path_length;
                last_path_length = all_longest_path_length[j];
                if (find(adjacency_list[topological_order[j]].begin(), adjacency_list[topological_order[j]].end(), topological_order[i]) != adjacency_list[topological_order[j]].end())
                {
                    int new_path_length = last_path_length + 1;

                    if (new_path_length > best_path_length)
                    {
                        best_path_length = new_path_length;
                        best_path_index = j;
                    }
                }
            }

            if (best_path_length > longest_path_length)
            {
                longest_path_length = best_path_length;
                longest_path_index = i;
            }

            all_longest_path_length[i] = best_path_length;
            all_longest_path_parent[i] = best_path_index;
        }

        cout << longest_path_length << endl;
        int longest_path_cursor = longest_path_index;
        while (longest_path_cursor != -1)
        {
            cout << (topological_order[longest_path_cursor] + 1);
            longest_path_cursor = all_longest_path_parent[longest_path_cursor];
            if (longest_path_cursor != -1)
            {
                cout << " ";
            }
        }

        cout << endl;

    }
    return 0;
}