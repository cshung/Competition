#include "stdafx.h"

// http://uva.onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=1535

#include "UVa10594.h"

#include <iostream>
#include <vector>

typedef long long int64;

using namespace std;

int UVa10594()
{
    while (true)
    {
        int number_of_nodes;
        int number_of_edges;
        cin >> number_of_nodes;
        if (cin.eof())
        {
            break;
        }
        cin >> number_of_edges;

        vector<vector<pair<int, int64>>> adjacency_list;
        adjacency_list.resize(number_of_nodes);
        for (int e = 0; e < number_of_edges; e++)
        {
            int src;
            int dst;
            int64 time;
            cin >> src;
            cin >> dst;
            cin >> time;
            src--;
            dst--;
            adjacency_list[src].push_back(pair<int, int64>(dst, time));
            adjacency_list[dst].push_back(pair<int, int64>(src, time));
        }

        int64 total_volume;
        int64 link_capacity;
        cin >> total_volume;
        cin >> link_capacity;

        // Input is read - adding a virtual sink with total volume capacity and find a maximum flow
        // suppose the maximum flow reaches the total volume (note the last link constrainted it so it can reach at most this)
        // then it is feasible to send all those data

        // Next thing next - we will use the minimum mean weight cycle cancellation algorithm to find the minimum cost flow 
        // So much for today, gotta work now
    }

    return 0;
}