#include "stdafx.h"

// http://uva.onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=551

#include "UVa610.h"

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// #define LOG

void UVa610_dfs(int parent, int current, int& dfs_current_num, vector<vector<int> >& adjacency_list, vector<int>& colors, vector<int>& dfs_num, vector<int>& dfs_low)
{
    colors[current] = 1; // gray
    dfs_num[current] = dfs_current_num;
    dfs_low[current] = dfs_current_num;
    dfs_current_num++;
    int num_children = 0;
    for (vector<int>::iterator ni = adjacency_list[current].begin(); ni != adjacency_list[current].end(); ni++)
    {
        int neighbor = *ni;
        if (colors[neighbor] == 0)
        {
#ifdef LOG
            cout << "Tree edge found:" << (current + 1) << "->" << (neighbor + 1) << endl;
#endif
            cout << (current + 1) << " " << (neighbor + 1) << endl;
            num_children++;

            UVa610_dfs(current, neighbor, dfs_current_num, adjacency_list, colors, dfs_num, dfs_low);
            if (dfs_low[neighbor] > dfs_num[current])
            {
#ifdef LOG
                cout << (current + 1) << " -> " << (neighbor + 1) << " is a bridge" << endl;
#endif
                cout << (neighbor + 1) << " " << (current + 1) << endl;
            }

            dfs_low[current] = min(dfs_low[current], dfs_low[neighbor]);
        }
        else
        {
            if (neighbor != parent)
            {
                if (colors[neighbor] == 1)
                {
                    // We are seeing a backedge here that does not go through direct parent
#ifdef LOG
                    cout << "Back edge found:" << (current + 1) << "->" << (neighbor + 1) << endl;
#endif
                    dfs_low[current] = min(dfs_low[current], dfs_num[neighbor]);
                    cout << (current + 1) << " " << (neighbor + 1) << endl;
                }
            }
        }
    }
    colors[current] = 2; // black
}

int UVa610()
{
    int test_case_number = 0;
    while (true)
    {
        test_case_number++;
        // Step 1: Read input
        int number_of_nodes, number_of_edges;
        cin >> number_of_nodes;
        cin >> number_of_edges;
        if (number_of_nodes == 0 && number_of_edges == 0)
        {
            break;
        }
        vector<vector<int> > adjacency_list;
        adjacency_list.resize(number_of_nodes);
        for (int e = 0; e < number_of_edges; e++)
        {
            int src, dst;
            cin >> src;
            cin >> dst;
            adjacency_list[src - 1].push_back(dst - 1);
            adjacency_list[dst - 1].push_back(src - 1);
        }
        
        // Step 2: Run the bridge algorithm
        vector<int> colors;
        vector<int> dfs_num;
        vector<int> dfs_low;
        colors.resize(number_of_nodes);
        dfs_num.resize(number_of_nodes);
        dfs_low.resize(number_of_nodes);
        for (int i = 0; i < number_of_nodes; i++)
        {
            colors[i] = 0; // white
            dfs_num[i] = -1;
            dfs_low[i] = -1;
        }

        int dfs_current_num = 0;

        cout << test_case_number << endl << endl;
        UVa610_dfs(-1, 0, dfs_current_num, adjacency_list, colors, dfs_num, dfs_low);
        cout << "#" << endl;
        

#ifdef LOG
        for (int i = 0; i < number_of_nodes; i++)
        {
            for (int j = 0; j < number_of_nodes; j++)
            {
                if (dfs_num[j] == i)
                {
                    cout << (j + 1) << " : " << dfs_num[j];

                    for (int k = 0; k < number_of_nodes; k++)
                    {
                        if (dfs_num[k] == dfs_low[j])
                        {
                            cout << "/" << dfs_low[j] << " (" << (k + 1) << ")" << endl;
                        }
                    }
                }
            }
        }

#endif

    }
    return 0;
}