#include "stdafx.h"

// http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1783

#include "UVa10842.h"

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int UVa10842_find(int item, vector<int>& sets)
{
    if (sets[item] < 0)
    {
        return item;
    }
    else
    {
        return sets[item] = UVa10842_find(sets[item], sets);
    }
}

bool UVa10842_union(int item1, int item2, vector<int>& sets)
{
    int set1 = UVa10842_find(item1, sets);
    int set2 = UVa10842_find(item2, sets);
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

class UVa10842_Edge
{
public:
    UVa10842_Edge(int _src, int _dst, int _weight) : src(_src), dst(_dst), weight(_weight) {}
    int src;
    int dst;
    int weight;
};

class UVa10842_Edge_Less
{
public:
    bool operator()(UVa10842_Edge edge1, UVa10842_Edge edge2)
    {
        // Note that the comparison direction is changed
        return edge1.weight < edge2.weight;
    }
};

int UVa10842()
{
    int number_of_test_cases;
    cin >> number_of_test_cases;
    for (int test_case = 1; test_case <= number_of_test_cases; test_case++)
    {
        // Step 1: Read Input
        int number_of_nodes;
        int number_of_edges;
        cin >> number_of_nodes;
        cin >> number_of_edges;

        // Step 2.1: Kruskal's: Push all edges to priority queue
        priority_queue<UVa10842_Edge, vector<UVa10842_Edge>, UVa10842_Edge_Less> edges;
        for (int e = 0; e < number_of_edges; e++)
        {
            int src;
            int dst;
            int weight;
            cin >> src;
            cin >> dst;
            cin >> weight;
            edges.push(UVa10842_Edge(src, dst, weight));
        }
        
        // Step 2.2: Kruskal's 2: Setup disjoint set union find
        vector<int> disjoint_sets;
        disjoint_sets.resize(number_of_nodes);
        for (int f = 0; f < number_of_nodes; f++)
        {
            disjoint_sets[f] = -1;
        }

        int num_edge_added = 0;
        int min_cost = 0;
        bool first = true;
        while (num_edge_added != number_of_nodes - 1)
        {
            UVa10842_Edge edge = edges.top();
            edges.pop();
            if (UVa10842_union(edge.src, edge.dst, disjoint_sets))
            {
                if (first)
                {
                    min_cost = edge.weight;
                    first = false;
                }
                else
                {
                    min_cost = min(min_cost, edge.weight);
                }
                num_edge_added++;
            }
        }

        cout << "Case #" << test_case << ": " << min_cost << endl;
    }
    return 0;
}