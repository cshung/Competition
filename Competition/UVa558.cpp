#include "stdafx.h"

// http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=499

#include "UVa558.h"

#include <iostream>
#include <vector>
#include <map>

using namespace std;

bool UVa558_bellman_ford(int src, vector<vector<pair<int, int > > >& adjacency_list, vector<bool>& reachable, vector<int>& distances, vector<int>& previous);

int UVa558()
{
    int number_of_test_cases;
    cin >> number_of_test_cases;
    for (int test_case = 1; test_case <= number_of_test_cases; test_case++)
    {
        // Step 1: Read input
        int number_of_star_systems;
        int number_of_worm_holes;
        cin >> number_of_star_systems;
        cin >> number_of_worm_holes;

        vector<vector<pair<int, int > > > adjacency_list;

        adjacency_list.resize(number_of_star_systems);
        for (int w = 0; w < number_of_worm_holes; w++)
        {
            int from;
            int to;
            int cost;
            cin >> from;
            cin >> to;
            cin >> cost;
            adjacency_list[from].push_back(pair<int, int>(to, cost));
        }

        vector<bool> reachable;
        vector<int> distances;
        vector<int> previous;
        if (UVa558_bellman_ford(0, adjacency_list, reachable, distances, previous))
        {
            cout << "possible" << endl;
        }
        else
        {
            cout << "not possible" << endl;
        }
    }

    return 0;
}

bool UVa558_bellman_ford(int src, vector<vector<pair<int, int > > >& adjacency_list, vector<bool>& reachable, vector<int>& distances, vector<int>& previous)
{
    // Step 1: Initialize data structures
    int number_of_nodes = adjacency_list.size();
    reachable.resize(number_of_nodes);
    distances.resize(number_of_nodes);
    previous.resize(number_of_nodes);
    for (int i = 0; i < number_of_nodes; i++)
    {
        if (i == src)
        {
            reachable[i] = true;
            distances[i] = 0;
        }
        else
        {
            reachable[i] = false;
            distances[i] = -1;
        }
        previous[i] = -1;
    }

    // Step 2: Relaxation for n times
    for (int i = 0; i < number_of_nodes; i++)
    {
        for (int src = 0; src < number_of_nodes; src++)
        {
            for (unsigned int ni = 0; ni < adjacency_list[src].size(); ni++)
            {
                pair<int, int> edge = adjacency_list[src][ni];
                int dst = edge.first;
                int cost = edge.second;
                if (reachable[src])
                {
                    if (!reachable[dst] || ((distances[src] + cost) < distances[dst]))
                    {
                        if (i < number_of_nodes - 1)
                        {
                            reachable[dst] = true;
                            distances[dst] = distances[src] + cost;
                            previous[dst] = src;
                        }
                        else
                        {
                            // The last relaxation is not real - if we can still relax, the graph have a negative cost cycle
                            return true;
                        }
                    }
                }
            }
        }
    }

    return false;
}
