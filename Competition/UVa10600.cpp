#include "stdafx.h"

// TODO

#include "UVa10600.h"

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int UVa10600_find(int item, vector<int>& sets)
{
    if (sets[item] < 0)
    {
        return item;
    }
    else
    {
        return sets[item] = UVa10600_find(sets[item], sets);
    }
}

bool UVa10600_union(int item1, int item2, vector<int>& sets)
{
    int set1 = UVa10600_find(item1, sets);
    int set2 = UVa10600_find(item2, sets);
    if (set1 != set2)
    {
        // Union 
        if (sets[set1] < sets[set2])              // set1 is larger
        {
            sets[set1] = sets[set1] + sets[set2]; // size increased
            sets[set2] = set1;                    // union
        }
        else
        {
            sets[set2] = sets[set1] + sets[set2]; // size increased
            sets[set1] = set2;                    // union
        }

        return true;
    }
    else
    {
        return false;
    }
}

class UVa10600_Edge
{
public:
    UVa10600_Edge(int _src, int _dst, int _weight, int _edge_id) : src(_src), dst(_dst), weight(_weight), edge_id(_edge_id) { }
    int src;
    int dst;
    int weight;
    int edge_id;
};

class UVa10600_Edge_Less
{
public:
    bool operator()(UVa10600_Edge edge1, UVa10600_Edge edge2)
    {
        return edge1.weight > edge2.weight;
    }
};

int UVa10600()
{
    int number_of_test_cases;
    cin >> number_of_test_cases;

    // Read input 
    for (int test_case = 1; test_case <= number_of_test_cases; test_case++)
    {
        int number_of_nodes;
        int number_of_edges;
        cin >> number_of_nodes;
        cin >> number_of_edges;

        vector<int> edge_from;
        vector<int> edge_to;
        vector<int> edge_cost;
        vector<int> edge_id;
        edge_from.resize(number_of_edges);
        edge_to.resize(number_of_edges);
        edge_cost.resize(number_of_edges);
        edge_id.resize(number_of_edges);
        for (int e = 0; e < number_of_edges; e++)
        {
            int from;
            int to;
            int cost;
            cin >> from;
            cin >> to;
            cin >> cost;
            edge_from[e] = from - 1;
            edge_to[e] = to - 1;
            edge_cost[e] = cost;
            edge_id[e] = -1;
        }
        
        // Step 2: Kruskal's Push edges to priority queue
        priority_queue<UVa10600_Edge, vector<UVa10600_Edge>, UVa10600_Edge_Less> edges;
        for (int e = 0; e < number_of_edges; e++)
        {
            edges.push(UVa10600_Edge(edge_from[e], edge_to[e], edge_cost[e], e));
        }

        // Step 3: Kruskal's: Setup disjoint set union find
        vector<int> disjoint_sets;
        disjoint_sets.resize(number_of_nodes);
        for (int p = 0; p < number_of_nodes; p++)
        {
            disjoint_sets[p] = -1;
        }

        // Step 3: Kruskal's: For each edge, if not create cycle, add stop when we reach the right number of connected components
        int num_edge_added = 0;
        int minimal_spanning_tree_cost = 0;
        while (num_edge_added != number_of_nodes - 1)
        {
            UVa10600_Edge edge = edges.top();
            edges.pop();
            if (UVa10600_union(edge.src, edge.dst, disjoint_sets))
            {
                minimal_spanning_tree_cost += edge.weight;
                edge_id[edge.edge_id] = num_edge_added;
                num_edge_added++;
            }
        }

        // Step 4: Second best
        int second_best_minimal_spanning_tree_cost = 0;
        for (int i = 0; i < number_of_nodes - 2; i++)
        {
            // Step 4.1: Push all edges again
            priority_queue<UVa10600_Edge, vector<UVa10600_Edge>, UVa10600_Edge_Less> edges2;
            for (int e = 0; e < number_of_edges; e++)
            {
                edges2.push(UVa10600_Edge(edge_from[e], edge_to[e], edge_cost[e], edge_id[e]));
            }

            // Step 4.2: Reset the disjoint sets
            for (int p = 0; p < number_of_nodes; p++)
            {
                disjoint_sets[p] = -1;
            }

            int num_edge_added = 0;
            int current_minimal_spanning_tree_cost = 0;
            while (num_edge_added != number_of_nodes - 1)
            {
                UVa10600_Edge edge = edges2.top();
                edges2.pop();

                if (edge.edge_id != i)
                {
                    if (UVa10600_union(edge.src, edge.dst, disjoint_sets))
                    {
                        current_minimal_spanning_tree_cost += edge.weight;
                        edge.edge_id = num_edge_added;
                        num_edge_added++;
                    }
                }
            }

            if (i == 0)
            {
                second_best_minimal_spanning_tree_cost = current_minimal_spanning_tree_cost;
            }
            else
            {
                second_best_minimal_spanning_tree_cost = min(second_best_minimal_spanning_tree_cost, current_minimal_spanning_tree_cost);
            }
        }

        cout << minimal_spanning_tree_cost << " " << second_best_minimal_spanning_tree_cost << endl;
    }

    return 0;
}