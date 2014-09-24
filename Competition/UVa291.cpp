#include "stdafx.h"

// http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=227

#include "UVa291.h"

#include <iostream>
#include <list>
#include <map>
#include <stack>

using namespace std;

void dfs(list<int>* adjacency_list, int last, int current, bool* edge_visited, int edgeVisited, stack<int>* node_visited)
{
    node_visited->push(current);
    if (edgeVisited == 8)
    {
        stack<int> temp;
        while (node_visited->size() > 0)
        {
            temp.push(node_visited->top());
            node_visited->pop();
        }
        while (temp.size() > 0)
        {
            cout << temp.top() + 1;
            node_visited->push(temp.top());
            temp.pop();
        }
        cout << endl;
    }
    else
    {   
        int edge_id_1 = last * 5 + current;
        int edge_id_2 = current * 5 + last;
        if (last != -1)
        {
            edge_visited[edge_id_1] = true;
            edge_visited[edge_id_2] = true;
        }
        for (list<int>::iterator ni = adjacency_list[current].begin(); ni != adjacency_list[current].end(); ni++)
        {
            int neighbor_node_id = *ni;
            int out_edge_id_1 = current * 5 + neighbor_node_id;
            if (!edge_visited[out_edge_id_1])
            {
                dfs(adjacency_list, current, neighbor_node_id, edge_visited, edgeVisited + 1, node_visited);
            }
        }
        if (last != -1)
        {
            edge_visited[edge_id_1] = false;
            edge_visited[edge_id_2] = false;
        }
    }
    node_visited->pop();
}

int UVa291()
{
    // Derived this 
    // 1: 2, 3, 5
    // 2: 1, 3, 5
    // 3: 1, 2, 4, 5
    // 4: 3, 5
    // 5: 1, 2, 3, 4

    // Just make my life easier, I don't want to compute -1 myself
    list<pair<int, int>> house_edges;
    house_edges.push_back(pair<int, int>(1, 2));
    house_edges.push_back(pair<int, int>(1, 3));
    house_edges.push_back(pair<int, int>(1, 5));
    house_edges.push_back(pair<int, int>(2, 1));
    house_edges.push_back(pair<int, int>(2, 3));
    house_edges.push_back(pair<int, int>(2, 5));
    house_edges.push_back(pair<int, int>(3, 1));
    house_edges.push_back(pair<int, int>(3, 2));
    house_edges.push_back(pair<int, int>(3, 4));
    house_edges.push_back(pair<int, int>(3, 5));
    house_edges.push_back(pair<int, int>(4, 3));
    house_edges.push_back(pair<int, int>(4, 5));
    house_edges.push_back(pair<int, int>(5, 1));
    house_edges.push_back(pair<int, int>(5, 2));
    house_edges.push_back(pair<int, int>(5, 3));
    house_edges.push_back(pair<int, int>(5, 4));

    list<int> adjacency_list[5];
    bool edge_visited[25];
    for (list<pair<int, int> >::iterator ei = house_edges.begin(); ei != house_edges.end(); ei++)
    {
        adjacency_list[ei->first - 1].push_back(ei->second - 1);
    }
    for (int i = 0; i < 25; i++)
    {
        edge_visited[i] = false;
    }
    stack<int> node_visited;
    dfs(adjacency_list, -1, 0, edge_visited, /* edge_visited = */0, &node_visited);

    return 0;
}