#include "stdafx.h"

// uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1498

#include "UVa10557.h"

#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <queue>

using namespace std;

// #define LOG

bool UVa10557_solve(int src, vector<vector<pair<int, int > > >& adjacency_list);

int UVa10557()
{
    while (true)
    {
        // Step 1: Read input
        int number_of_rooms;
        cin >> number_of_rooms;
        if (number_of_rooms == -1)
        {
            break;
        }

        vector<int> energy_levels;
        vector<vector<int> > neighbors;
        energy_levels.resize(number_of_rooms);
        neighbors.resize(number_of_rooms);
        for (int r = 0; r < number_of_rooms; r++)
        {
            int energy_level;
            cin >> energy_level;
            energy_levels[r] = energy_level;
            int number_of_doorways;
            cin >> number_of_doorways;
            for (int d = 0; d < number_of_doorways; d++)
            {
                int neighbor;
                cin >> neighbor;
                neighbors[r].push_back(neighbor - 1);
            }
        }
        
        // Step 2: Convert that into a graph
        vector<vector<pair<int, int> > > adjacency_list;
        adjacency_list.resize(number_of_rooms);
        for (int r = 0; r < number_of_rooms; r++)
        {
            adjacency_list[r].resize(neighbors[r].size());
            for (unsigned int n = 0; n < neighbors[r].size(); n++)
            {
                adjacency_list[r][n].first = neighbors[r][n];
                adjacency_list[r][n].second = energy_levels[neighbors[r][n]];
            }
        }
        
        // Step 3: Solving the problem using a variant of bellman ford algorithm plus a reachability test
        if (UVa10557_solve(0, adjacency_list))
        {
            cout << "winnable" << endl;
        }
        else
        {
            cout << "hopeless" << endl;
        }
    }

    return 0;
}

bool UVa10557_solve(int src, vector<vector<pair<int, int > > >& adjacency_list)
{
    // Step 1: Initialize data structures
    int number_of_nodes = adjacency_list.size();
    
    vector<bool> reachable_1;
    vector<bool> reachable_2;
    vector<int>  energies_1;
    vector<int>  energies_2;
    
    reachable_1.resize(number_of_nodes);
    reachable_2.resize(number_of_nodes);
    energies_1.resize(number_of_nodes);
    energies_2.resize(number_of_nodes);

    // Without any moves, 0 is reachable with 100 energies, all other nodes are unreachable
    for (int i = 0; i < number_of_nodes; i++)
    {
        if (i == src)
        {
            reachable_1[i] = reachable_2[i] = true;
            energies_1[i] = energies_2[i] = 100;
        }
        else
        {
            reachable_1[i] = reachable_2[i] = false;
            energies_1[i] = energies_2[i] = -1;
        }
    }

    vector<bool>& old_reachable = reachable_1;
    vector<bool>& new_reachable = reachable_2;

    vector<int>&  old_energies = energies_1;
    vector<int>&  new_energies = energies_2;

    // Step 2: Relaxing all edges
    // If a node is relaxed after the n-1 relaxation, it's relaxation must due to cycle
    // A cycle is at most n edge long, so after n more relaxation after the n - 1 th relaxation
    // we should be sure we have found all nodes that can be relaxed by cycles
    set<int> relaxable_nodes;
    for (int relaxation_count = 1; relaxation_count <= number_of_nodes * 2; relaxation_count++)
    {
        for (int src = 0; src < number_of_nodes; src++)
        {
            new_reachable[src] = old_reachable[src];
            new_energies[src] = old_energies[src];
        }

        for (int src = 0; src < number_of_nodes; src++)
        {
            for (unsigned int ni = 0; ni < adjacency_list[src].size(); ni++)
            {
                pair<int, int> edge = adjacency_list[src][ni];
                int dst = edge.first;
                int energy = edge.second;

                int dst_energy = old_energies[src] + energy;

                if (dst_energy > 0)
                {
                    if (old_reachable[src])
                    {
                        if (!old_reachable[dst] || dst_energy > old_energies[dst])
                        {   
                            new_reachable[dst] = true;
                            new_energies[dst] = dst_energy;
                        }
                    }
                }
            }
        }

        if (new_reachable[number_of_nodes - 1])
        {
            return true;
        }

#ifdef LOG
        // After relaxing relaxation_count times
        for (int src = 0; src < number_of_nodes; src++)
        {
            if (new_reachable[src])
            {
                cout << "energies(" << (src + 1) << ", " << relaxation_count << ") = " << new_energies[src] << endl;
            }
            else
            {
                cout << "energies(" << (src + 1) << ", " << relaxation_count << ") = -inf" << endl;
            }
        }
#endif

        for (int src = 0; src < number_of_nodes; src++)
        {
            if (new_reachable[src])
            {
                if (old_reachable[src])
                {
                    if (old_energies[src] < new_energies[src])
                    {
#ifdef LOG
                        cout << (src + 1) << " is relaxed in the " << relaxation_count << "th relaxation." << endl;
#endif
                        if (relaxation_count >= number_of_nodes)
                        {
                            relaxable_nodes.insert(src);
                        }
                    }
                }
                else
                {
#ifdef LOG
                    cout << (src + 1) << " is relaxed in the " << relaxation_count << "th relaxation." << endl;
#endif
                    if (relaxation_count >= number_of_nodes)
                    {
                        relaxable_nodes.insert(src);
                    }
                }
            }
        }

#ifdef LOG
        cout << endl;
#endif

        // The whole relaxation process is over, now switch the roles
        vector<bool>& temp_reachable = old_reachable;
        old_reachable = new_reachable;
        new_reachable = temp_reachable;

        vector<int>& temp_energies = old_energies;
        old_energies = new_energies;
        new_energies = temp_energies;
    }

    // We cannot reach in 2n moves, let's hope that we can reach it from the relaxable nodes
    vector<int> colors;
    colors.resize(number_of_nodes);
    for (int i = 0; i < number_of_nodes; i++)
    {
        colors[i] = -1;
    }

    queue<int> bfs_queue;
    for (set<int>::iterator ri = relaxable_nodes.begin(); ri != relaxable_nodes.end(); ri++)
    {
        int r = *ri;
        colors[r] = 0;
        bfs_queue.push(r);
#ifdef LOG
        cout << "It is determined that " << (r + 1) << " can have as much energy as we want." << endl;
#endif
    }

    while (bfs_queue.size() > 0)
    {
        int v = bfs_queue.front();
        bfs_queue.pop();

        if (v == number_of_nodes - 1)
        {
            return true;
        }

        for (unsigned int ni = 0; ni < adjacency_list[v].size(); ni++)
        {
            int n = adjacency_list[v][ni].first;
            if (colors[n] != 0)
            {
                colors[n] = 0;
                bfs_queue.push(n);
            }
        }
    }

    return false;
}
