#include "stdafx.h"

// http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=945

#include "UVa10004.h"

#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <queue>

using namespace std;

int UVa10004()
{
    while (true)
    {
        int number_of_nodes;
        cin >> number_of_nodes;
        if (number_of_nodes == 0)
        {
            break;
        }
        int number_of_edges;
        cin >> number_of_edges;

        vector<set<int> > adjacency_list;
        adjacency_list.resize(number_of_nodes);
        for (int e = 0; e < number_of_edges; e++)
        {
            int src;
            int dst;
            cin >> src;
            cin >> dst;
            adjacency_list[src].insert(dst);
            adjacency_list[dst].insert(src);
        }

        vector<int> colors;
        colors.resize(number_of_nodes);
        for (int i = 0; i < number_of_nodes; i++)
        {
            colors[i] = -1;
        }

        colors[0] = 0;
        queue<int> bfs_queue;
        bfs_queue.push(0);
        bool valid = true;
        while (bfs_queue.size() > 0 && valid)
        {
            int v = bfs_queue.front();
            bfs_queue.pop();
            for (set<int>::iterator ni = adjacency_list[v].begin(); ni != adjacency_list[v].end(); ni++)
            {
                int n = *ni;
                if (colors[n] == -1)
                {
                    colors[n] = 1 - colors[v];
                    bfs_queue.push(n);
                } 
                else if (colors[n] != 1 - colors[v])
                {
                    valid = false;
                }
            }
        }

        if (valid)
        {
            cout << "BICOLORABLE." << endl;
        }
        else
        {
            cout << "NOT BICOLORABLE." << endl;
        }
    }
    return 0;
}