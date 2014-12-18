#include "stdafx.h"

// http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=251

#include "UVa315.h"

#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

// #define LOG

using namespace std;

void UVa315_dfs(int parent, int current, int& dfs_current_num, vector<vector<int> >& adjacency_list, vector<int>& colors, vector<int>& dfs_num, vector<int>& dfs_low, int& num_articulation_points)
{
    colors[current] = 1; // black
#ifdef LOG
    cout << "Visiting " << current << " as " << dfs_current_num << endl;
#endif
    dfs_num[current] = dfs_current_num;
    dfs_low[current] = dfs_current_num;
    dfs_current_num++;
    int num_children = 0;
    bool has_bigger_child = false;
    for (unsigned int i = 0; i < adjacency_list[current].size(); i++)
    {
        int neighbor = adjacency_list[current][i];
        if (colors[neighbor] == 0)
        {
            num_children++;

            UVa315_dfs(current, neighbor, dfs_current_num, adjacency_list, colors, dfs_num, dfs_low, num_articulation_points);
            if (dfs_low[neighbor] > dfs_num[current])
            {
                has_bigger_child = true;
            }

            dfs_low[current] = min(dfs_low[current], dfs_low[neighbor]);
        }
        else
        {
            if (neighbor != parent)
            {
                // We are seeing a backedge here that does not go through direct parent
#ifdef LOG
                cout << "Backedge found:" << current << " " << neighbor << endl;
#endif
                dfs_low[current] = min(dfs_low[current], neighbor);
            }
        }
    }

    if (parent == -1)
    {
        if (num_children > 1)
        {
#ifdef LOG
            cout << current << " is an articulation point" << endl;
#endif
            num_articulation_points++;
        }
    }
    else
    {
        if (num_children > 0)
        {
            if (has_bigger_child)
            {
#ifdef LOG
                cout << current << " is an articulation point" << endl;
#endif
                num_articulation_points++;
            }
        }
    }

    colors[current] = 2; // black
}

int UVa315()
{
    while (true)
    {
        // Step 1: Read input
        string line;
        int number_of_nodes;
        cin >> number_of_nodes;
        if (number_of_nodes == 0)
        {
            break;
        }
        getline(cin, line); // just to consume the endline after number_of_nodes
        vector<vector<int> > adjacency_list;
        adjacency_list.resize(number_of_nodes);

        while (true)
        {
            getline(cin, line);
            istringstream iss(line);
            int src;
            int dst;
            iss >> src;
            if (src == 0)
            {
                break;
            }
            while (iss >> dst)
            {
                // let's name to nodes in 0 based index for convenience
                adjacency_list[src - 1].push_back(dst - 1);
                adjacency_list[dst - 1].push_back(src - 1);
            }
        }

        // Step 2: Run the articulation point algorithm
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
        int num_articulation_points = 0;

        UVa315_dfs(-1, 0, dfs_current_num, adjacency_list, colors, dfs_num, dfs_low, num_articulation_points);
        cout << num_articulation_points << endl;
    }

    return 0;
}