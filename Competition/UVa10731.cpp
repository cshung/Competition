#include "stdafx.h"

// http://uva.onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=1672

#include "UVa10731.h"

#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

int UVa10731_number(map<char, int>& numbering, map<int, char>& naming, char c);
void UVa10731_add_edge(map<char, set<char> >& input_graph, char from, char to);
void UVa10731_dfs(int parent, int current, int& dfs_current_num, vector<vector<int> >& adjacency_list, vector<int>& colors, vector<int>& dfs_num, vector<int>& dfs_low, stack<int>& strongly_connected_nodes, map<int, char>& naming, vector<vector<char> >& result);
bool UVa10731_order(vector<char> first, vector<char> second);

int UVa10731()
{
    int test_case_number = 0;
    while (true)
    {
        test_case_number++;

        // Step 1: Read Input
        int number_of_questions;
        cin >> number_of_questions;
        if (number_of_questions == 0)
        {
            break;
        }

        map<char, set<char> > input_graph;
        map<char, int> numbering;
        map<int, char> naming;

        for (int q = 0; q < number_of_questions; q++)
        {
            char c1, c2, c3, c4, c5;
            char ans;
            cin >> c1 >> c2 >> c3 >> c4 >> c5 >> ans;

            // Map character to number 
            UVa10731_number(numbering, naming, c1);
            UVa10731_number(numbering, naming, c2);
            UVa10731_number(numbering, naming, c3);
            UVa10731_number(numbering, naming, c4);
            UVa10731_number(numbering, naming, c5);
            UVa10731_number(numbering, naming, ans);
            
            if (c1 != ans) { UVa10731_add_edge(input_graph, ans, c1); }
            if (c2 != ans) { UVa10731_add_edge(input_graph, ans, c2); }
            if (c3 != ans) { UVa10731_add_edge(input_graph, ans, c3); }
            if (c4 != ans) { UVa10731_add_edge(input_graph, ans, c4); }
            if (c5 != ans) { UVa10731_add_edge(input_graph, ans, c5); }
        }

        // Step 2: Copy the graph for running the algorithm
        int number_of_nodes = numbering.size();
        vector<vector<int> > numbered_graph;
        numbered_graph.resize(number_of_nodes);

        for (map<char, set<char> >::iterator gi = input_graph.begin(); gi != input_graph.end(); gi++)
        {
            int from = UVa10731_number(numbering, naming, gi->first);
            for (set<char>::iterator ni = gi->second.begin(); ni != gi->second.end(); ni++)
            {
                int to = UVa10731_number(numbering, naming, *ni);
                numbered_graph[from].push_back(to);
            }
        }

        // Step 3: Run the strongly connected component algorithm
        vector<int> colors;
        vector<int> dfs_num; // The dfs visit number
        vector<int> dfs_low; // The lowest number reachable by the node without going through direct parent
        colors.resize(number_of_nodes);
        dfs_num.resize(number_of_nodes);
        dfs_low.resize(number_of_nodes);
        for (int i = 0; i < number_of_nodes; i++)
        {
            // white
            colors[i] = 0;
            dfs_num[i] = 0;
            dfs_low[i] = 0;
        }

        int dfs_current_num = 0;
        vector<vector<char> > result;
        for (int i = 0; i < number_of_nodes; i++)
        {            
            stack<int> strongly_connected_nodes;
            UVa10731_dfs(-1, i, dfs_current_num, numbered_graph, colors, dfs_num, dfs_low, strongly_connected_nodes, naming, result);
        }

        // Step 4: Output
        for (vector<vector<char> >::iterator ri = result.begin(); ri != result.end(); ri++)
        {
            sort(ri->begin(), ri->end());
        }
        sort(result.begin(), result.end(), UVa10731_order);

        if (test_case_number != 1)
        {
            cout << endl;
        }
        for (vector<vector<char> >::iterator ri = result.begin(); ri != result.end(); ri++)
        {
            for (unsigned si = 0; si < ri->size(); si++)
            {
                if (si != 0)
                {
                    cout << " ";
                }
                cout << (*ri)[si];
            }
            cout << endl;
        }
    }
    return 0;
}

bool UVa10731_order(vector<char> first, vector<char> second)
{
    return first[0] < second[0];
}

void UVa10731_dfs(int parent, int current, int& dfs_current_num, vector<vector<int> >& adjacency_list, vector<int>& colors, vector<int>& dfs_num, vector<int>& dfs_low, stack<int>& strongly_connected_nodes, map<int, char>& naming, vector<vector<char> >& result)
{
    if (colors[current] != 0)
    {
        return;
    }
    strongly_connected_nodes.push(current);
    colors[current] = 1; // gray
    dfs_num[current] = dfs_current_num;
    dfs_low[current] = dfs_current_num;
    dfs_current_num++;

    for (vector<int>::iterator ni = adjacency_list[current].begin(); ni != adjacency_list[current].end(); ni++)
    {
        int neighbor = *ni;
        if (colors[neighbor] == 0)
        {
#ifdef LOG
            cout << "Tree edge found:" << (current + 1) << "->" << (neighbor + 1) << endl;
#endif
            UVa10731_dfs(current, neighbor, dfs_current_num, adjacency_list, colors, dfs_num, dfs_low, strongly_connected_nodes, naming, result);
            dfs_low[current] = min(dfs_low[current], dfs_low[neighbor]);
        }
        else
        {
            if (neighbor != parent && colors[neighbor] == 1)
            {
                // We are seeing a backedge here that does not go through direct parent
#ifdef LOG
                cout << "Back edge found:" << (current + 1) << "->" << (neighbor + 1) << endl;
#endif
                dfs_low[current] = min(dfs_low[current], dfs_num[neighbor]);
            }
        }
    }

    colors[current] = 2; // black

    if (dfs_low[current] == dfs_num[current])
    {
        vector<char> strongly_connected_component;
        while (true)
        {   
            strongly_connected_component.push_back(naming[strongly_connected_nodes.top()]);
            if (strongly_connected_nodes.top() == current)
            {
                strongly_connected_nodes.pop();                    
                break;
            }
            strongly_connected_nodes.pop();

        }
        result.push_back(strongly_connected_component);
    }
}

int UVa10731_number(map<char, int>& numbering, map<int, char>& naming, char c)
{
    map<char, int>::iterator probe = numbering.find(c);
    if (probe == numbering.end())
    {
        int number = numbering.size();
        numbering.insert(pair<char, int>(c, number));
        naming.insert(pair<int, char>(number, c));
        return number;
    }
    else
    {
        return probe->second;
    }
}

void UVa10731_add_edge(map<char, set<char> >& input_graph, char from, char to)
{
    map<char, set<char> >::iterator probe = input_graph.find(from);
    if (probe == input_graph.end())
    {
        set<char> neighbor;
        neighbor.insert(to);
        input_graph.insert(pair<char, set<char> >(from, neighbor));
    }
    else
    {
        probe->second.insert(to);
    }
}
