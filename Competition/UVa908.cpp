#include "stdafx.h"

// http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=849

#include "UVa908.h"

#include <iostream>
#include <list>
#include <map>

using namespace std;

// DFS - but searching in a tree can omit the visited flags
void find_cycle(list<pair<int, int> >* adjacency_list, int last, int from, int to, int heavyFrom, int heavyTo, int maxCost, int& resultFrom, int& resultTo, int& resultCost)
{
    for (list<pair<int, int> >::iterator ni = adjacency_list[from].begin(); ni != adjacency_list[from].end(); ni++)
    {
        pair<int, int> edge = *ni;
        if (edge.first != last)
        {
            if (edge.second > maxCost)
            {
                maxCost = edge.second;
                heavyFrom = from;
                heavyTo = edge.first;
            }

            if (edge.first == to)
            {
                resultFrom = heavyFrom;
                resultTo = heavyTo;
                resultCost = maxCost;
                return;
            }
            else
            {
                find_cycle(adjacency_list, from, edge.first, to, heavyFrom, heavyTo, maxCost, resultFrom, resultTo, resultCost);
            }
        }
    }
}

int UVa908()
{
    bool first_case = true;
    while (true)
    {
        int number_of_nodes;
        cin >> number_of_nodes;
        if (cin.eof())
        {
            break;
        }

        int original_cost = 0;
        list<pair<int, int> >* adjacency_list = new list<pair<int, int> >[number_of_nodes];
        for (int i = 0; i < number_of_nodes - 1; i++)
        {
            int from, to, cost;
            cin >> from;
            cin >> to;
            cin >> cost;
            from--;
            to--;
            adjacency_list[from].push_back(pair<int, int>(to, cost));
            adjacency_list[to].push_back(pair<int, int>(from, cost));
            original_cost += cost;
        }

        int number_of_new_links;
        cin >> number_of_new_links;

        int new_cost = original_cost;
        for (int i = 0; i < number_of_new_links; i++)
        {
            int from, to, cost;
            cin >> from;
            cin >> to;
            cin >> cost;
            from--;
            to--;
            int heavyFrom;
            int heavyTo;
            int heavyCost;
            find_cycle(adjacency_list, -1, from, to, -1, -1, -1, heavyFrom, heavyTo, heavyCost);
            if (cost < heavyCost)
            {
                // Since the list need to update, make it a direct acces data structure?
                adjacency_list[heavyFrom].remove(pair<int, int>(heavyTo, heavyCost)); // Bad - this could be O(n)
                adjacency_list[heavyTo].remove(pair<int, int>(heavyFrom, heavyCost)); // Bad again
                adjacency_list[from].push_back(pair<int, int>(to, cost));
                adjacency_list[to].push_back(pair<int, int>(from, cost));
                new_cost -= heavyCost;
                new_cost += cost;
            }
        }

        int number_of_original_lines;
        cin >> number_of_original_lines;

        for (int i = 0; i < number_of_original_lines; i++)
        {
            int from, to, cost;
            cin >> from;
            cin >> to;
            cin >> cost;
            // Original line are useless;
        }

        if (first_case)
        {
            first_case = false;
        }
        else
        {
            cout << endl;
        }

        cout << original_cost << endl;
        cout << new_cost << endl;

        delete[] adjacency_list;
    }
    return 0;
}