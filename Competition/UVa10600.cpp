#include "stdafx.h"

// http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1541

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
        return edge1.weight < edge2.weight;
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

        vector<UVa10600_Edge> edges;
        for (int e = 0; e < number_of_edges; e++)
        {
            int from;
            int to;
            int cost;
            cin >> from;
            cin >> to;
            cin >> cost;
            edges.push_back(UVa10600_Edge(from - 1, to - 1, cost, -1));
        }
        
        // Step 2: Kruskal's: Sort the edges
        sort(edges.begin(), edges.end(), UVa10600_Edge_Less());

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
        int current_edge_index = 0;
        while (num_edge_added != number_of_nodes - 1)
        {
            UVa10600_Edge edge = edges[current_edge_index];
            if (UVa10600_union(edge.src, edge.dst, disjoint_sets))
            {
                minimal_spanning_tree_cost += edge.weight;
                edges[current_edge_index].edge_id = num_edge_added;
                num_edge_added++;
            }
            current_edge_index++;
        }

        // Step 4: Second best
        int second_best_minimal_spanning_tree_cost = 0;
        bool first = true;
        for (int i = 0; i < number_of_nodes - 1; i++)
        {
            // Step 4.1: Reset the disjoint sets
            for (int p = 0; p < number_of_nodes; p++)
            {
                disjoint_sets[p] = -1;
            }

            int num_edge_added = 0;
            int current_minimal_spanning_tree_cost = 0;
            current_edge_index = 0;
            while ((num_edge_added != number_of_nodes - 1) && (current_edge_index < number_of_edges))
            {
                UVa10600_Edge edge = edges[current_edge_index];

                if (edge.edge_id != i)
                {
                    if (UVa10600_union(edge.src, edge.dst, disjoint_sets))
                    {
                        current_minimal_spanning_tree_cost += edge.weight;
                        num_edge_added++;
                    }
                }
                current_edge_index++;
            }

            if (num_edge_added == number_of_nodes - 1)
            {
                if (first)
                {
                    second_best_minimal_spanning_tree_cost = current_minimal_spanning_tree_cost;
                    first = false;
                }
                else
                {
                    second_best_minimal_spanning_tree_cost = min(second_best_minimal_spanning_tree_cost, current_minimal_spanning_tree_cost);
                }
            }
        }

        cout << minimal_spanning_tree_cost << " " << second_best_minimal_spanning_tree_cost << endl;
    }

    return 0;
}