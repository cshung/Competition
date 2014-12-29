#include "stdafx.h"

// http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1088

#include "UVa10147.h"

#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <cmath>

using namespace std;

int UVa10147_find(int item, vector<int>& sets)
{
    if (sets[item] < 0)
    {
        return item;
    }
    else
    {
        return sets[item] = UVa10147_find(sets[item], sets);
    }
}

bool UVa10147_union(int item1, int item2, vector<int>& sets)
{
    int set1 = UVa10147_find(item1, sets);
    int set2 = UVa10147_find(item2, sets);
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

class UVa10147_Edge
{
public:
    UVa10147_Edge(int _src, int _dst, double _weight) : src(_src), dst(_dst), weight(_weight) {}
    int src;
    int dst;
    double weight;
};

class UVa10147_Edge_Less
{
public:
    bool operator()(UVa10147_Edge edge1, UVa10147_Edge edge2)
    {
        return edge1.weight > edge2.weight;
    }
};

int UVa10147()
{
    int number_of_test_cases;
    cin >> number_of_test_cases;
    for (int test_case = 1; test_case <= number_of_test_cases; test_case++)
    {
        // Step 1.1: Read cities
        int number_of_cities;
        cin >> number_of_cities;
        vector<pair<int, int> > cities;
        cities.resize(number_of_cities);
        for (int c = 0; c < number_of_cities; c++)
        {
            int x;
            int y;
            cin >> x;
            cin >> y;
            cities[c] = pair<int, int>(x, y);
        }
        
        // Step 2.2: Kruskal's 2: Setup disjoint set union find
        vector<int> disjoint_sets;
        disjoint_sets.resize(number_of_cities);
        for (int f = 0; f < number_of_cities; f++)
        {
            disjoint_sets[f] = -1;
        }

        // Step 1.2: Read highways - we need to perform it after setting up the disjoint sets 
        // to avoid storing them separately
        int number_of_existing_highways;
        cin >> number_of_existing_highways;
        int number_of_remaining_highways = number_of_cities - 1;
        for (int h = 0; h < number_of_existing_highways; h++)
        {
            int src;
            int dst;
            cin >> src;
            cin >> dst;
            // Step 2.3: Kruskal's: merge cities already joined by highway
            if (UVa10147_union(src - 1, dst - 1, disjoint_sets))
            {
                number_of_remaining_highways--;
            }
        }

        if (test_case != 1)
        {
            cout << endl;
        }

        if (number_of_remaining_highways == 0)
        {
            cout << "No new highways need" << endl;
        }
        else
        {
            // Step 2.1: Kruskal's: Push all edges to priority queue
            // This is an optimization - just in case no new highway is needed there is no point to go 
            // through all pairs of cities
            priority_queue<UVa10147_Edge, vector<UVa10147_Edge>, UVa10147_Edge_Less> edges;
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
                    edges.push(UVa10147_Edge(src, dst, dist));
                }
            }

            // Step 2.4: Kruskal's: For each edge, if not create cycle, add
            int num_edge_added = 0;
            while (num_edge_added != number_of_remaining_highways)
            {
                UVa10147_Edge edge = edges.top();
                edges.pop();
                if (UVa10147_union(edge.src, edge.dst, disjoint_sets))
                {
                    cout << (edge.src + 1) << " " << (edge.dst + 1) << endl;
                    num_edge_added++;
                }
            }
        }
    }

    return 0;
}