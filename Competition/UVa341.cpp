#include "stdafx.h"

// http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=277

#include "UVa341.h"

#include <iostream>
#include <string>
#include <map>
#include <vector>

/*

5
2  3 3   4 6
3  1 2   3 7   5 6
1  4 5
0
1  4 7
2 4

2
1   2 5
1   1 6
1 2

7
4   2 5   3 13   4 8   5 18
2   3 7   6 14
1   6 6
2   3 5   5 9
3   6 2   7 9    4 6
1   7 2
0
1 7

0

*/

/*
Case 1: Path = 2 1 4; 8 second delay
Case 2: Path = 1 2; 5 second delay
Case 3: Path = 1 2 3 6 7; 20 second delay
*/

using namespace std;

bool UVa341_less(vector<int>& distances, vector<bool>& reachable, int one, int two)
{
    if (reachable[one])
    {
        if (reachable[two])
        {
            return distances[one] < distances[two];
        }
        else
        {
            return true;
        }
    }
    else
    {
        return false;
    }
}


// TODO: To be completed!
void UVa341_bubble_down(vector<int>& dijkstra_queue, vector<int>& distances, vector<bool>& reachable, vector<int>& node_index, int index)
{
    int child2_index = (index + 1) * 2;
    int child1_index = child2_index - 1;

    int child1 = dijkstra_queue[child1_index];
    int child2 = dijkstra_queue[child1_index];

    int min_child;

    if (UVa341_less(distances, reachable, child1, child2))
    {
        if (UVa341_less(distances, reachable, child1, index))
        {

        }
    }
    

}

int UVa341()
{
    while (true)
    {
        // Step 1: Read input 
        int num_intersections;
        cin >> num_intersections;
        if (num_intersections == 0)
        {
            break;
        }
        vector<vector<pair<int, int> > > graph;
        graph.resize(num_intersections);
        for (int src = 1; src <= num_intersections; src++)
        {
            int num_edge;
            cin >> num_edge;
            for (int e = 0; e < num_edge; e++)
            {
                int dst;
                int time;
                cin >> dst;
                cin >> time;
                graph[src - 1].push_back(pair<int, int>(dst, time));
            }
        }
        int src;
        int dst;
        cin >> src;
        cin >> dst;
        
        // Dijkstra
        vector<int> dijkstra_queue; // containing the node numbers
        vector<int> distances;      // containing the distance values
        vector<bool> reachable;     // false if the node is unreachable
        vector<int> node_index;     // the priority queue position of the node in the queue
        int queue_size;
        dijkstra_queue.resize(num_intersections);
        distances.resize(num_intersections);
        reachable.resize(num_intersections);
        node_index.resize(num_intersections);
        queue_size = num_intersections;

        // Dijkstra 1: Initialize the nodes and get them into the queue
        int j = 1;
        for (int i = 0; i < num_intersections; i++)
        {
            if (i == src)
            {
                distances[i] = 0;
                reachable[i] = true;
                dijkstra_queue[0] = i;
                node_index[i] = 0;
            }
            else
            {
                distances[i] = -1;
                reachable[i] = false;
                dijkstra_queue[j] = i;
                node_index[i] = j;
                j++;
            }
        }

        // Dijkstra 2: Main loop
        while (queue_size > 0)
        {
            // delete min
            int u = dijkstra_queue[0];
            node_index[u] = -1;
            dijkstra_queue[0] = dijkstra_queue[queue_size - 1];
            node_index[dijkstra_queue[0]] = 0;
            UVa341_bubble_down(dijkstra_queue, distances, reachable, node_index, 0);
        }
    }

    return 0;
}
