#include "stdafx.h"

// http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1338

#include "UVa10397.h"

#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <cmath>
#include <iomanip>

using namespace std;

int UVa10397_find(int item, vector<int>& sets)
{
    if (sets[item] < 0)
    {
        return item;
    }
    else
    {
        return sets[item] = UVa10397_find(sets[item], sets);
    }
}

bool UVa10397_union(int item1, int item2, vector<int>& sets)
{
    int set1 = UVa10397_find(item1, sets);
    int set2 = UVa10397_find(item2, sets);
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

class UVa10397_Edge
{
public:
    UVa10397_Edge(int _src, int _dst, double _weight) : src(_src), dst(_dst), weight(_weight) {}
    int src;
    int dst;
    double weight;
};

class UVa10397_Edge_Less
{
public:
    bool operator()(UVa10397_Edge edge1, UVa10397_Edge edge2)
    {
        return edge1.weight > edge2.weight;
    }
};

int UVa10397()
{
    while(true)
    {
        // Step 1.1: Read buildings
        int number_of_buildings;
        cin >> number_of_buildings;
        if (cin.eof())
        {
            break;
        }
        vector<pair<int, int> > buildings;
        buildings.resize(number_of_buildings);
        for (int c = 0; c < number_of_buildings; c++)
        {
            int x;
            int y;
            cin >> x;
            cin >> y;
            buildings[c] = pair<int, int>(x, y);
        }
        
        // Step 2.2: Kruskal's 2: Setup disjoint set union find
        vector<int> disjoint_sets;
        disjoint_sets.resize(number_of_buildings);
        for (int f = 0; f < number_of_buildings; f++)
        {
            disjoint_sets[f] = -1;
        }

        // Step 1.2: Read links - we need to perform it after setting up the disjoint sets 
        // to avoid storing them separately
        int number_of_existing_links;
        cin >> number_of_existing_links;
        int number_of_remaining_links = number_of_buildings - 1;
        for (int h = 0; h < number_of_existing_links; h++)
        {
            int src;
            int dst;
            cin >> src;
            cin >> dst;
            // Step 2.3: Kruskal's: merge buildings already joined by highway
            if (UVa10397_union(src - 1, dst - 1, disjoint_sets))
            {
                number_of_remaining_links--;
            }
        }

        if (number_of_remaining_links == 0)
        {
            cout << "0.00" << endl;
        }
        else
        {
            // Step 2.1: Kruskal's: Push all edges to priority queue
            // This is an optimization - just in case no new highway is needed there is no point to go 
            // through all pairs of buildings
            priority_queue<UVa10397_Edge, vector<UVa10397_Edge>, UVa10397_Edge_Less> edges;
            for (int src = 0; src < number_of_buildings; src++)
            {
                for (int dst = src + 1; dst < number_of_buildings; dst++)
                {
                    double src_x = buildings[src].first;
                    double src_y = buildings[src].second;
                    double dst_x = buildings[dst].first;
                    double dst_y = buildings[dst].second;
                    double diff_x = src_x - dst_x;
                    double diff_y = src_y - dst_y;
                    double dist = sqrt(diff_x * diff_x + diff_y * diff_y);
                    edges.push(UVa10397_Edge(src, dst, dist));
                }
            }

            // Step 2.4: Kruskal's: For each edge, if not create cycle, add
            int num_edge_added = 0;
            double total_edge_weights = 0;
            while (num_edge_added != number_of_remaining_links)
            {
                UVa10397_Edge edge = edges.top();
                edges.pop();
                if (UVa10397_union(edge.src, edge.dst, disjoint_sets))
                {
                    total_edge_weights += edge.weight;
                    num_edge_added++;
                }
            }

            cout << fixed << showpoint << setprecision(2);
            cout << total_edge_weights << endl;
        }
    }

    return 0;
}