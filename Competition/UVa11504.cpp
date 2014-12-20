#include "stdafx.h"

// TODO

#include "UVa11504.h"

#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

void UVa11504_dfs(int parent, int current, int& dfs_current_num, vector<vector<int> >& adjacency_list, vector<int>& colors, vector<int>& dfs_num, vector<int>& dfs_low, stack<int>& strongly_connected_nodes, vector<vector<int> >& result);

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
             adjacency_list[dst - 1].push_back(src - 1);
         }

        // Step 2: Run the strongly connected component algorithm
        vector<int> colors;
        vector<int> dfs_num; // The dfs visit number
        vector<int> dfs_low; // The lowest number reachable by the node without going through direct parent
        colors.resize(number_of_nodes);
        dfs_num.resize(number_of_nodes);
        dfs_low.resize(number_of_nodes);
        for (int i = 0; i < number_of_nodes; i++)
        {
            // white
            colors[i] = 0;
            dfs_num[i] = 0;
            dfs_low[i] = 0;
        }

        int dfs_current_num = 0;
        vector<vector<int> > result;
        for (int i = 0; i < number_of_nodes; i++)
        {            
            stack<int> strongly_connected_nodes;
            UVa11504_dfs(-1, i, dfs_current_num, adjacency_list, colors, dfs_num, dfs_low, strongly_connected_nodes, result);
        }
        cout << result.size() << endl;
    }

    return 0;
}

void UVa11504_dfs(int parent, int current, int& dfs_current_num, vector<vector<int> >& adjacency_list, vector<int>& colors, vector<int>& dfs_num, vector<int>& dfs_low, stack<int>& strongly_connected_nodes, vector<vector<int> >& result)
{
    if (colors[current] != 0)
    {
        return;
    }
    strongly_connected_nodes.push(current);
    colors[current] = 1; // gray
    dfs_num[current] = dfs_current_num;
    dfs_low[current] = dfs_current_num;
    dfs_current_num++;

    for (vector<int>::iterator ni = adjacency_list[current].begin(); ni != adjacency_list[current].end(); ni++)
    {
        int neighbor = *ni;
        if (colors[neighbor] == 0)
        {
#ifdef LOG
            cout << "Tree edge found:" << (current + 1) << "->" << (neighbor + 1) << endl;
#endif
            UVa11504_dfs(current, neighbor, dfs_current_num, adjacency_list, colors, dfs_num, dfs_low, strongly_connected_nodes, result);
            dfs_low[current] = min(dfs_low[current], dfs_low[neighbor]);
        }
        else
        {
            if (neighbor != parent && colors[neighbor] == 1)
            {
                // We are seeing a backedge here that does not go through direct parent
#ifdef LOG
                cout << "Back edge found:" << (current + 1) << "->" << (neighbor + 1) << endl;
#endif
                dfs_low[current] = min(dfs_low[current], dfs_num[neighbor]);
            }
        }
    }

    colors[current] = 2; // black

    if (dfs_low[current] == dfs_num[current])
    {
        vector<int> strongly_connected_component;
        while (true)
        {   
            strongly_connected_component.push_back(strongly_connected_nodes.top());
            if (strongly_connected_nodes.top() == current)
            {
                strongly_connected_nodes.pop();                    
                break;
            }
            strongly_connected_nodes.pop();

        }
        result.push_back(strongly_connected_component);
    }
}
