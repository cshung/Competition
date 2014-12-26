#include "stdafx.h"

// http://uva.onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=2169

#include "UVa11228.h"

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <queue>
#include <cmath>
#include <iomanip>

using namespace std;

int UVa11228_find(int item, vector<int>& sets)
{
    if (sets[item] < 0)
    {
        return item;
    }
    else
    {
        return sets[item] = UVa11228_find(sets[item], sets);
    }
}

bool UVa11228_union(int item1, int item2, vector<int>& sets)
{
    int set1 = UVa11228_find(item1, sets);
    int set2 = UVa11228_find(item2, sets);
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

class UVa11228_Edge
{
public:
    UVa11228_Edge(int _src, int _dst, double _weight) : src(_src), dst(_dst), weight(_weight) {}
    int src;
    int dst;
    double weight;
};

class UVa11228_Edge_Less
{
public:
    bool operator()(UVa11228_Edge edge1, UVa11228_Edge edge2)
    {
        return edge1.weight > edge2.weight;
    }
};

int UVa11228()
{
    int number_of_test_case;
    cin >> number_of_test_case;
    for (int test_case = 1; test_case <= number_of_test_case; test_case++)
    {
        // Step 1: Input
        int number_of_cities;
        cin >> number_of_cities;
        int threshold;
        cin >> threshold;
        vector<pair<int, int> > cities;
        for (int i = 0; i < number_of_cities; i++)
        {
            int cx;
            int cy;
            cin >> cx;
            cin >> cy;
            cities.push_back(pair<int, int>(cx, cy));
        }

        // Step 2.1: Kruskal's 1: Push all edges to priority queue
        priority_queue<UVa11228_Edge, vector<UVa11228_Edge>, UVa11228_Edge_Less> edges;
        for (int src = 0; src < number_of_cities; src++)
        {
            for (int dst = src + 1; dst < number_of_cities; dst++)
            {
                double src_x = cities[src].first;
                double src_y = cities[src].second;
                double dst_x = cities[dst].first;
                double dst_y = cities[dst].second;
                double diff_x = src_x - dst_x;
                double diff_y = src_y - dst_y;
                double dist = sqrt(diff_x * diff_x + diff_y * diff_y);
                edges.push(UVa11228_Edge(src, dst, dist));
            }
        }

        // Step 2.2: Kruskal's 2: Setup disjoint set union find
        vector<int> disjoint_sets;
        disjoint_sets.resize(number_of_cities);
        for (int f = 0; f < number_of_cities; f++)
        {
            disjoint_sets[f] = -1;
        }

        // Step 2.3: Kruskal's 3: For each edge, if not create cycle, add
        int num_edge_added = 0;
        double road_weight = 0;
        double rail_weight = 0;
        int num_states = 1;
        while (num_edge_added != number_of_cities - 1)
        {
            UVa11228_Edge edge = edges.top();
            edges.pop();
            if (UVa11228_union(edge.src, edge.dst, disjoint_sets))
            {
                num_edge_added++;
                if (edge.weight > threshold)
                {
                    num_states++;
                    rail_weight += edge.weight;
                }
                else
                {
                    road_weight += edge.weight;
                }
            }
        }

        cout << "Case #" << test_case << ": " << num_states << " " << (int)(road_weight + 0.5) << " " << (int)(rail_weight + 0.5) << endl;
    }
    return 0;
}