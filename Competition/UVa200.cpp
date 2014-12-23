#include "stdafx.h"

// http://uva.onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=136

#include "UVa200.h"

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <stack>

using namespace std;

void UVa200_dfs(int current, vector<int>& colors, vector<set<int> > adjacency_list, stack<int>& finishing_order);

int UVa200()
{
    // Step 1: Read input
    string line;
    vector<string> index;
    while (true)
    {
        getline(cin, line);
        if (line == "#")
        {
            break;
        }
        index.push_back(line);
    }

    // Step 2: Numbering the characters
    map<char, int> numbering;
    map<int, char> naming;

    for (unsigned int i = 0; i < index.size(); i++)
    {
        string s = index[i];
        for (unsigned int c = 0; c < s.length(); c++)
        {
            if (numbering.find(s[c]) == numbering.end())
            {
                int n = numbering.size();
                numbering.insert(pair<char, int>(s[c], n));
                naming.insert(pair<int, char>(n, s[c]));
            }
        }
    }

    // Step 3: Build the precedence graph
    int number_of_nodes = numbering.size();
    vector<set<int> > adjacency_list;
    adjacency_list.resize(number_of_nodes);

    for (unsigned int i = 1; i < index.size(); i++)
    {
        string prev = index[i - 1];
        string next = index[i];
        for (unsigned int c = 0; c < prev.length() && c < next.length(); c++)
        {
            if (prev[c] != next[c])
            {
                adjacency_list[numbering[prev[c]]].insert(numbering[next[c]]);
                break;
            }
        }
    }

    // Step 4: DFS for topological sort
    vector<int> colors;
    stack<int> finishing_order;
    colors.resize(number_of_nodes);
    for (int i = 0; i < number_of_nodes; i++)
    {
        colors[i] = 0;
    }

    for (int i = 0; i < number_of_nodes; i++)
    {
        if (colors[i] == 0)
        {
            UVa200_dfs(i, colors, adjacency_list, finishing_order);
        }
    }

    while (finishing_order.size() > 0)
    {
        cout << naming[finishing_order.top()];
        finishing_order.pop();
    }
    cout << endl;

    return 0;
}

void UVa200_dfs(int current, vector<int>& colors, vector<set<int> > adjacency_list, stack<int>& finishing_order)
{
    colors[current] = 1;
    for (set<int>::iterator ni = adjacency_list[current].begin(); ni != adjacency_list[current].end(); ni++)
    {
        int neighbor = *ni;
        if (colors[neighbor] == 0)
        {
            UVa200_dfs(neighbor, colors, adjacency_list, finishing_order);
        }
    }
    colors[current] = 2;
    finishing_order.push(current);
}