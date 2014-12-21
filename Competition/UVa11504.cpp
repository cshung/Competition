#include "stdafx.h"

// http://uva.onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=2499

#include "UVa11504.h"

#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

void UVa11504_dfs(int parent, int current, vector<vector<int> >& adjacency_list, vector<int>& colors, stack<int>* order);

int UVa11504()
{
    int number_of_test_case;
    cin >> number_of_test_case;
    for (int c = 0; c < number_of_test_case; c++)
    {
         int number_of_nodes;
         int number_of_edges;
         cin >> number_of_nodes;
         cin >> number_of_edges;
         vector<vector<int> > adjacency_list;
         adjacency_list.resize(number_of_nodes);
         for (int e = 0; e < number_of_edges; e++)
         {
             int src, dst;
             cin >> src >> dst;
             adjacency_list[src - 1].push_back(dst - 1);
         }

        // Step 2: DFS once and order the nodes with decreasing finishing times
        vector<int> colors;
        colors.resize(number_of_nodes);
        for (int i = 0; i < number_of_nodes; i++)
        {
            // white
            colors[i] = 0;
        }

        stack<int> order;
        for (int i = 0; i < number_of_nodes; i++)
        {
            UVa11504_dfs(-1, i, adjacency_list, colors, &order);
        }

        // Step 3: DFS twice by going through the list in decreasing finishing times order
        for (int i = 0; i < number_of_nodes; i++)
        {
            // white
            colors[i] = 0;
        }

        int result = 0;
        while (order.size() > 0)
        {
            if (colors[order.top()] == 0)
            {
                result++;
            }
            UVa11504_dfs(-1, order.top(), adjacency_list, colors, NULL);
            order.pop();
        }

        // Step 4: Output
        cout << result << endl;
    }

    return 0;
}

void UVa11504_dfs(int parent, int current, vector<vector<int> >& adjacency_list, vector<int>& colors, stack<int>* order)
{
    if (colors[current] != 0)
    {
        return;
    }
    colors[current] = 1; // gray

    for (vector<int>::iterator ni = adjacency_list[current].begin(); ni != adjacency_list[current].end(); ni++)
    {
        int neighbor = *ni;
        if (colors[neighbor] == 0)
        {
            UVa11504_dfs(current, neighbor, adjacency_list, colors, order);
        }
    }

    colors[current] = 2; // black

    if (order != NULL)
    {
        order->push(current);
    }
}
