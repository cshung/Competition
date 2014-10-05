#include "stdafx.h"

// http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=129

#include "UVa193.h"

#include <iostream>
#include <list>

using namespace std;

void find_coloring(list<int>* graph, int* color, int n, list<int>& solutionSoFar, list<int>& solution)
{
    bool found = false;
    for (int i = 0; i < n; i++)
    {
        if (color[i] == 0)
        {
            found = true;
            color[i] = 1;
            solutionSoFar.push_back(i);

            list<int> disabled_now;
            for (list<int>::iterator ni = graph[i].begin(); ni != graph[i].end(); ni++)
            {
                int should_be_disabled = *ni;
                if (color[should_be_disabled] == 0)
                {
                    disabled_now.push_back(should_be_disabled);
                    color[should_be_disabled] = 2;
                }
            }

            find_coloring(graph, color, n, solutionSoFar, solution);
            for (list<int>::iterator ri = disabled_now.begin(); ri != disabled_now.end(); ri++)
            {
                color[*ri] = 0;
            }
            color[i] = 0;
            solutionSoFar.pop_back();
        }
    }
    if (!found)
    {
        if (solutionSoFar.size() > solution.size())
        {
            solution.clear();
            for (list<int>::iterator si = solutionSoFar.begin(); si != solutionSoFar.end(); si++)
            {
                solution.push_back(*si);
            }
        }
    }
}

int UVa193()
{
    int number_of_graphs;
    cin >> number_of_graphs;
    for (int g = 0; g < number_of_graphs; g++)
    {
        int number_of_nodes;
        int number_of_edges;
        cin >> number_of_nodes;
        cin >> number_of_edges;
        
        list<int>* graph = new list<int>[number_of_nodes];
        for (int e = 0; e < number_of_edges; e++)
        {
            int node1;
            int node2;
            cin >> node1;
            cin >> node2;
            graph[node1 - 1].push_back(node2 - 1);
            graph[node2 - 1].push_back(node1 - 1);
        }

        int* color = new int[number_of_nodes];
        for (int n = 0; n < number_of_nodes; n++)
        {
            // 0 means not colored, 1 means colored black, 2 means cannot be colored black
            color[n] = 0;
        }
        list<int> solutionSoFar;
        list<int> solution;
        find_coloring(graph, color, number_of_nodes, solutionSoFar, solution);

        cout << solution.size() << endl;
        for (list<int>::iterator si = solution.begin(); si != solution.end(); si++)
        {
            if (si != solution.begin())
            {
                cout << " ";
            }
            cout << (*si + 1);
        }
        cout << endl;

        delete[] color;
        delete[] graph;
    }

    return 0;
}