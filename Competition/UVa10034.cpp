#include "stdafx.h"

// http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=975

#include "UVa10034.h"

#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <iomanip>
#include <cmath>

using namespace std;

int UVa10034_find(int item, vector<int>& sets)
{
    if (sets[item] < 0)
    {
        return item;
    }
    else
    {
        return sets[item] = UVa10034_find(sets[item], sets);
    }
}

class UVa10034_Edge
{
public:
    UVa10034_Edge(int _src, int _dst, double _weight) : src(_src), dst(_dst), weight(_weight) {}
    int src;
    int dst;
    double weight;
};

class UVa10034_Edge_Less
{
public:
    bool operator()(UVa10034_Edge edge1, UVa10034_Edge edge2)
    {
        return edge1.weight > edge2.weight;
    }
};

int UVa10034()
{
    int number_of_test_cases;
    cin >> number_of_test_cases;
    for (int test_case = 1; test_case <= number_of_test_cases; test_case++)
    {
        // Step 1: Read input
        int number_of_freckles;
        cin >> number_of_freckles;
        vector<pair<double, double> > freckle_coordinates;
        for (int f = 0; f < number_of_freckles; f++)
        {
            double x, y;
            cin >> x;
            cin >> y;
            freckle_coordinates.push_back(pair<double, double>(x, y));
        }

        // Step 2.1: Kruskal's 1: Push all edges to priority queue
        priority_queue<UVa10034_Edge, vector<UVa10034_Edge>, UVa10034_Edge_Less> edges;
        for (int src = 0; src < number_of_freckles; src++)
        {
            for (int dst = src + 1; dst < number_of_freckles; dst++)
            {
                double src_x = freckle_coordinates[src].first;
                double src_y = freckle_coordinates[src].second;
                double dst_x = freckle_coordinates[dst].first;
                double dst_y = freckle_coordinates[dst].second;
                double diff_x = src_x - dst_x;
                double diff_y = src_y - dst_y;
                double dist = sqrt(diff_x * diff_x + diff_y * diff_y);
                edges.push(UVa10034_Edge(src, dst, dist));
            }
        }

        // Step 2.2: Kruskal's 2: Setup disjoint set union find
        vector<int> disjoint_sets;
        disjoint_sets.resize(number_of_freckles);
        for (int f = 0; f < number_of_freckles; f++)
        {
            disjoint_sets[f] = -1;
        }

        // Step 2.3: Kruskal's 2: For each edge, if not create cycle, add
        int num_edge_added = 0;
        double weight = 0;
        while (num_edge_added != number_of_freckles - 1)
        {
            UVa10034_Edge edge = edges.top();
            edges.pop();
            int src_set = UVa10034_find(edge.src, disjoint_sets);
            int dst_set = UVa10034_find(edge.dst, disjoint_sets);
            if (src_set != dst_set)
            {
                num_edge_added++;
                weight += edge.weight;
                
                // Union 
                if (disjoint_sets[src_set] < disjoint_sets[dst_set]) // src_set is larger
                {
                    disjoint_sets[src_set] = disjoint_sets[src_set] + disjoint_sets[dst_set]; // size increased
                    disjoint_sets[dst_set] = src_set;                                         // union
                }
                else
                {
                    disjoint_sets[dst_set] = disjoint_sets[src_set] + disjoint_sets[dst_set]; // size increased
                    disjoint_sets[src_set] = dst_set;                                         // union
                }
            }
        }
        if (test_case != 1)
        {
            cout << endl;
        }
        cout << setprecision(2) << fixed;
        cout << weight << endl;
    }
    return 0;
}
