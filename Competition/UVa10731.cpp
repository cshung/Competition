#include "stdafx.h"

// http://uva.onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=1672

#include "UVa10731.h"

// #define LOG

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
void UVa10731_dfs(int parent, int current, int& dfs_current_num, vector<vector<int> >& adjacency_list, vector<int>& colors, vector<int>& dfs_num, vector<int>& dfs_low, stack<int>& strongly_connected_nodes, vector<bool>& inStack, map<int, char>& naming, vector<vector<char> >& result);
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
        vector<vector<int> > adjacency_list;
        adjacency_list.resize(number_of_nodes);

        for (map<char, set<char> >::iterator gi = input_graph.begin(); gi != input_graph.end(); gi++)
        {
            int from = UVa10731_number(numbering, naming, gi->first);
            for (set<char>::iterator ni = gi->second.begin(); ni != gi->second.end(); ni++)
            {
                int to = UVa10731_number(numbering, naming, *ni);
                adjacency_list[from].push_back(to);
            }
        }

#ifdef LOG
        cout << "digraph{" << endl;
        for (unsigned int src = 0; src < adjacency_list.size(); src++)
        {
            for (unsigned int dst_index = 0; dst_index < adjacency_list[src].size(); dst_index++)
            {
                int dst = adjacency_list[src][dst_index];
                cout << naming[src] << "->" << naming[dst] << ";" << endl;
            }
        }
        cout << "}" << endl;
#endif

        // Step 3: Run the strongly connected component algorithm
        vector<int> colors;
        vector<bool> inStack;
        vector<int> dfs_num; // The dfs visit number
        vector<int> dfs_low; // The lowest number reachable by the node by following tree edges and at most one edges in stack
        colors.resize(number_of_nodes);
        inStack.resize(number_of_nodes);
        dfs_num.resize(number_of_nodes);
        dfs_low.resize(number_of_nodes);
        for (int i = 0; i < number_of_nodes; i++)
        {
            // white
            colors[i] = 0;
            inStack[i] = false;
            dfs_num[i] = 0;
            dfs_low[i] = 0;
        }

        int dfs_current_num = 0;
        vector<vector<char> > result;
        for (int i = 0; i < number_of_nodes; i++)
        {            
            stack<int> strongly_connected_nodes;
            UVa10731_dfs(-1, i, dfs_current_num, adjacency_list, colors, dfs_num, dfs_low, strongly_connected_nodes, inStack, naming, result);
        }

#ifdef LOG
        for (int i = 0; i < number_of_nodes; i++)
        {
            for (int j = 0; j < number_of_nodes; j++)
            {
                if (dfs_num[j] == i)
                {
                    cout << naming[j] << " : " << dfs_num[j];

                    for (int k = 0; k < number_of_nodes; k++)
                    {
                        if (dfs_num[k] == dfs_low[j])
                        {
                            cout << "/" << dfs_low[j] << " (" << naming[k] << ")" << endl;
                        }
                    }
                }
            }
        }
#endif

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

void UVa10731_dfs(int parent, int current, int& dfs_current_num, vector<vector<int> >& adjacency_list, vector<int>& colors, vector<int>& dfs_num, vector<int>& dfs_low, stack<int>& strongly_connected_nodes, vector<bool>& inStack, map<int, char>& naming, vector<vector<char> >& result)
{
    if (colors[current] != 0)
    {
        return;
    }
    strongly_connected_nodes.push(current);
    inStack[current] = true;

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
            cout << "Tree edge found:" << naming[current] << "->" << naming[neighbor] << ";" << endl;
#endif
            UVa10731_dfs(current, neighbor, dfs_current_num, adjacency_list, colors, dfs_num, dfs_low, strongly_connected_nodes, inStack, naming, result);
            dfs_low[current] = min(dfs_low[current], dfs_low[neighbor]);
        }
        else if (inStack[neighbor])
        {
#ifdef LOG
            cout << "Back edge found:" << naming[current] << "->" << naming[neighbor] << endl;
#endif
            dfs_low[current] = min(dfs_low[current], dfs_num[neighbor]);
        }
        else
        {
#ifdef LOG
            cout << "Forward/cross edge found:" << naming[current] << "->" << naming[neighbor] << endl;
#endif
        }
    }

    colors[current] = 2; // black

    if (dfs_low[current] == dfs_num[current])
    {
        vector<char> strongly_connected_component;
        while (true)
        {   
            int top = strongly_connected_nodes.top();
            strongly_connected_component.push_back(naming[top]);
            inStack[top] = false;
            strongly_connected_nodes.pop();
            if (top == current)
            {
                break;
            }
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
