#include "stdafx.h"

// http://www.spoj.com/problems/FISHER/

// #define LOG

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

int SPOJ_FISHER()
{
    while (true)
    {
        int num_cities;
        int time_budget;
        vector<vector<int> > distances;
        vector<vector<int> > tolls;

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

        // Try Floyd Warshall
        // Denote the set of shortest paths from i to j going through {0,1,...k - 1} be shortest_paths[i][j][k], 
        // It is a set of shortest paths because there can be multiple shortest path with different time used.
        // We should record if using longer time can lead to lower cost
        // The first element in the pair is the cost, the second element in the pair is time used
        vector<vector<vector<vector<pair<int, int> > > > > shortest_paths;
        shortest_paths.resize(num_cities);
        for (int i = 0; i < num_cities; i++)
        {
            shortest_paths[i].resize(num_cities);
            for (int j = 0; j < num_cities; j++)
            {
                shortest_paths[i][j].resize(num_cities + 1);
            }
        }

        // Initialization - there is only one path without going through any node
        for (int i = 0; i < num_cities; i++)
        {
            for (int j = 0; j < num_cities; j++)
            {
#ifdef LOG
                cout << "  shortest_paths[" << i << "][" << j << "][" << 0 << "].push_back(" << tolls[i][j] << ", " << distances[i][j] << ");" << endl;
#endif
                shortest_paths[i][j][0].push_back(pair<int, int>(tolls[i][j], distances[i][j]));
            }
        }

        // Iteration - the shortest path
        for (int k = 1; k <= num_cities; k++)
        {
#ifdef LOG
            cout << "Processing " << k << endl;
#endif
            for (int i = 0; i < num_cities; i++)
            {
                for (int j = 0; j < num_cities; j++)
                {
                    if (i != j)
                    {
                        // Step 1: Generate all candidate shortest paths
                        map<pair<int, int>, bool> candidates;
                        for (vector<pair<int, int> >::iterator pi = shortest_paths[i][j][k - 1].begin(); pi != shortest_paths[i][j][k - 1].end(); pi++)
                        {
                            candidates.insert(pair<pair<int, int>, bool>(*pi, false));
                        }
                        for (vector<pair<int, int> >::iterator fi = shortest_paths[i][k - 1][k - 1].begin(); fi != shortest_paths[i][k - 1][k - 1].end(); fi++)
                        {
                            for (vector<pair<int, int> >::iterator si = shortest_paths[k - 1][j][k - 1].begin(); si != shortest_paths[k - 1][j][k - 1].end(); si++)
                            {
                                int first_path_cost = fi->first;
                                int first_path_time_used = fi->second;
                                int second_path_cost = si->first;
                                int second_path_time_used = si->second;

                                int new_path_cost = first_path_cost + second_path_cost;
                                int new_path_time_used = first_path_time_used + second_path_time_used;

                                if (new_path_time_used <= time_budget)
                                {
                                    candidates.insert(pair<pair<int, int>, bool>(pair<int, int>(new_path_cost, new_path_time_used), false));
                                }
                            }
                        }

                        vector<pair<pair<int, int>, bool> > candidates_list;
                        for (map<pair<int,int>, bool>::iterator ci = candidates.begin(); ci != candidates.end(); ci++)
                        {
                            candidates_list.push_back(*ci);
                        }

                        // Eliminate the bad ones
                        for (unsigned int p = 0; p < candidates_list.size(); p++)
                        {
                            for (unsigned int q = 0; q < candidates_list.size(); q++)
                            {
                                if (p != q)
                                {
                                    int first_path_cost = candidates_list[p].first.first;
                                    int first_path_time_used = candidates_list[p].first.second;
                                    int second_path_cost = candidates_list[q].first.first;
                                    int second_path_time_used = candidates_list[q].first.second;

                                    // First take less time and less cost than second, second is eliminated
                                    if (first_path_time_used <= second_path_time_used && first_path_cost <= second_path_cost)
                                    {
                                        candidates_list[q].second = true;
                                    }
                                }
                            }
                        }

                        for (unsigned int p = 0; p < candidates_list.size(); p++)
                        {
                            if (candidates_list[p].second == false)
                            {
#ifdef LOG
                                cout << "  shortest_paths[" << i << "][" << j << "][" << k << "].push_back(" << candidates_list[p].first.first << ", " << candidates_list[p].first.second << ");" << endl;
#endif
                                shortest_paths[i][j][k].push_back(candidates_list[p].first);
                            }
                        }
#ifdef LOG
                        cout << endl;
#endif
                    }
                }
            }
        }

        bool first = true;
        int best_cost = -1;
        int best_cost_time = -1;
        for (vector<pair<int, int> >::iterator pi = shortest_paths[0][num_cities - 1][num_cities].begin(); pi != shortest_paths[0][num_cities - 1][num_cities].end(); pi++)
        {
            if (first)
            {
                best_cost = pi->first;
                best_cost_time = pi->second;
                first = false;
            }
            else
            {
                if (pi->first < best_cost)
                {
                    best_cost = pi->first;
                    best_cost_time = pi->second;
                }
            }
        }
        cout << best_cost << " " << best_cost_time << endl;
    }

    return 0;

}
/*
4 7
0 5 2 3
5 0 2 3
3 1 0 2
3 3 2 0

0 2 2 7
2 0 1 2
2 2 0 5
7 2 5 0

0 0

*/