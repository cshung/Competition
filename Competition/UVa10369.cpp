#include "stdafx.h"

// http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1310

#include "UVa10369.h"

#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <cmath>
#include <iomanip>

using namespace std;

int UVa10369_find(int item, vector<int>& sets)
{
    if (sets[item] < 0)
    {
        return item;
    }
    else
    {
        return sets[item] = UVa10369_find(sets[item], sets);
    }
}

bool UVa10369_union(int item1, int item2, vector<int>& sets)
{
    int set1 = UVa10369_find(item1, sets);
    int set2 = UVa10369_find(item2, sets);
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

class UVa10369_Edge
{
public:
    UVa10369_Edge(int _src, int _dst, double _weight) : src(_src), dst(_dst), weight(_weight) {}
    int src;
    int dst;
    double weight;
};

class UVa10369_Edge_Less
{
public:
    bool operator()(UVa10369_Edge edge1, UVa10369_Edge edge2)
    {
        return edge1.weight > edge2.weight;
    }
};

int UVa10369()
{
    int number_of_test_cases;
    cin >> number_of_test_cases;
    for (int test_case = 1; test_case <= number_of_test_cases; test_case++)
    {
        // Step 1: Read inputs
        int number_of_satellite_channels;
        cin >> number_of_satellite_channels;
        int number_of_outposts;
        cin >> number_of_outposts;
        vector<pair<int, int> > outposts;
        for (int p = 0; p < number_of_outposts; p++)
        {
            int x;
            int y;
            cin >> x;
            cin >> y;
            outposts.push_back(pair<int, int>(x, y));
        }

        // Step 2: Just in case
        if (number_of_satellite_channels == number_of_outposts)
        {
            cout << 0 << endl;
            continue;
        }

        // Step 3.1: Kruskal's: Push all edges to priority queue
        priority_queue<UVa10369_Edge, vector<UVa10369_Edge>, UVa10369_Edge_Less> edges;
        for (int src = 0; src < number_of_outposts; src++)
        {
            for (int dst = src + 1; dst < number_of_outposts; dst++)
            {
                double src_x = outposts[src].first;
                double src_y = outposts[src].second;
                double dst_x = outposts[dst].first;
                double dst_y = outposts[dst].second;
                double diff_x = src_x - dst_x;
                double diff_y = src_y - dst_y;
                double dist = sqrt(diff_x * diff_x + diff_y * diff_y);
                edges.push(UVa10369_Edge(src, dst, dist));
            }
        }

        // Step 3.2: Kruskal's 2: Setup disjoint set union find
        vector<int> disjoint_sets;
        disjoint_sets.resize(number_of_outposts);
        for (int p = 0; p < number_of_outposts; p++)
        {
            disjoint_sets[p] = -1;
        }

        // Step 3.3: Kruskal's: For each edge, if not create cycle, add
        // stop when we reach the right number of connected components
        int num_edge_added = 0;
        double max_edge_weight = -1;
        while (num_edge_added != number_of_outposts - number_of_satellite_channels)
        {
            UVa10369_Edge edge = edges.top();
            edges.pop();
            if (UVa10369_union(edge.src, edge.dst, disjoint_sets))
            {
                max_edge_weight = max(max_edge_weight, edge.weight);
                num_edge_added++;
            }
        }

        cout << setprecision(2) << fixed << max_edge_weight << endl;
    }

    return 0;
}