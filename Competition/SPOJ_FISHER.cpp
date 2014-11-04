#include "stdafx.h"

// http://www.spoj.com/problems/FISHER/

#define LOG

#include "SPOJ_FISHER.h"

#include <iostream>
#include <vector>
#include <map>

using namespace std;

// Using global to avoid passing - bad coding :(
int num_cities;
int time_budget;
vector<vector<int> > distances;
vector<vector<int> > tolls;
map<pair<int, int>, pair<int, int> > memo;

// cost, time pair
pair<int, int> find_optimal_tour(int current_node, int time_budget, int level)
{
#ifdef LOG
    for (int indent = 0; indent < level; indent++) { cout << " "; }
    cout << "Calling find_optimal_tour(" << current_node << ", " << time_budget << ")" << endl;
#endif
    map<pair<int, int>, pair<int, int> >::iterator probe = memo.find(pair<int, int>(current_node, time_budget));
    if (probe != memo.end())
    {
#ifdef LOG
        for (int indent = 0; indent < level; indent++) { cout << " "; }
        cout << "Hit probe" << endl;
#endif
        return probe->second;
    }
    else
    {
#ifdef LOG
        for (int indent = 0; indent < level; indent++) { cout << " "; }
        cout << "Gone search" << endl;
#endif
    }

    bool first = true;
    int best_cost = -1;
    int best_used_time = -1;
    if (current_node == num_cities - 1)
    {
        return pair<int, int>(0, 0);
    }

    for (int i = 0; i < num_cities; i++)
    {
        if (i != current_node)
        {
            if (distances[current_node][i] < time_budget)
            {
                pair<int, int> remaining_result = find_optimal_tour(i, time_budget - distances[current_node][i], level + 4);
                if (remaining_result.first != -1)
                {
                    int used_cost = tolls[current_node][i] + remaining_result.first;
                    int used_time = distances[current_node][i] + remaining_result.second;

                    if (first)
                    {
                        best_cost = used_cost;
                        best_used_time = used_time;
                        first = false;
                    }
                    else if (used_cost < best_cost)
                    {
                        best_cost = used_cost;
                        best_used_time = used_time;
                    }
                }
            }
        }
    }

    for (int t = time_budget; t >= best_used_time && t >= 0; t--)
    {
#ifdef LOG
        for (int indent = 0; indent < level; indent++) { cout << " "; }
        cout << "Cached find_optimal_tour(" << current_node << ", " << t << ") = [" << best_cost << ", " << best_used_time << "]" << endl;
#endif
        memo[pair<int, int>(current_node, t)] = pair<int, int>(best_cost, best_used_time);
    }

    return pair<int, int>(best_cost, best_used_time);
}

int SPOJ_FISHER()
{
    while (true)
    {
        cin >> num_cities;
        cin >> time_budget;
        if (num_cities == 0 && time_budget == 0)
        {
            break;
        }
        distances.resize(num_cities);
        tolls.resize(num_cities);
        for (int i = 0; i < num_cities; i++)
        {
            distances[i].resize(num_cities);
            tolls[i].resize(num_cities);
        }
        for (int i = 0; i < num_cities; i++)
        {
            for (int j = 0; j < num_cities; j++)
            {
                int distance;
                cin >> distance;
                distances[i][j] = distance;
            }
        }
        for (int i = 0; i < num_cities; i++)
        {
            for (int j = 0; j < num_cities; j++)
            {
                int toll;
                cin >> toll;
                tolls[i][j] = toll;
            }
        }

        // Try the algorithm
        pair<int, int> result = find_optimal_tour(0, time_budget, 0);
        cout << result.first << " " << result.second << endl;
    }
    return 0;
}