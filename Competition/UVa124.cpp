#include "stdafx.h"

// http://uva.onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=60

#include "UVa124.h"

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <algorithm>

using namespace std;

void UVa124_recursive(set<int>& free, vector<int>& indegree, vector<char>& variables, vector<set<int> >& adjacency_list, vector<int>& result);

int UVa124()
{
    int test_case_number = 0;
    while (true)
    {
        test_case_number++;
        // Step 1: Read input
        string line;
        getline(cin, line); 
        if (cin.eof())
        {
            break;
        }
        istringstream iss1(line);

        vector<char> variables;
        map<char, int> numberings;

        while (true)
        {
            char c;
            iss1 >> c;
            if (iss1.eof()){
                break;
            }
            variables.push_back(c);
        }
        
        sort(variables.begin(), variables.end());
        for (unsigned int i = 0; i < variables.size(); i++)
        {
            numberings.insert(pair<char, int>(variables[i], i));
        }

        int number_of_nodes = variables.size();

        vector<set<int> > adjacency_list;
        adjacency_list.resize(number_of_nodes);

        getline(cin, line);
        istringstream iss2(line);
        while (true)
        {
            char b, l;
            iss2 >> b >> l;
            if (iss2.eof()){
                break;
            }
            adjacency_list[numberings[b]].insert(numberings[l]);
        }

        // Step 2: All topological sort orders
        vector<int> indegree;
        set<int> free;
        indegree.resize(number_of_nodes);

        for (int i = 0; i < number_of_nodes; i++)
        {
            indegree[i] = 0;
        }

        for (int i = 0; i < number_of_nodes; i++)
        {
            for (set<int>::iterator ai = adjacency_list[i].begin(); ai != adjacency_list[i].end(); ai++)
            {
                indegree[*ai]++;
            }
        }

        for (int i = 0; i < number_of_nodes; i++)
        {
            if (indegree[i] == 0)
            {
                free.insert(i);
            }
        }

        vector<int> result;
        
        if (test_case_number != 1)
        {
            cout << endl;
        }

        UVa124_recursive(free, indegree, variables, adjacency_list, result);

    }

    return 0;
}

void UVa124_recursive(set<int>& free, vector<int>& indegree, vector<char>& variables, vector<set<int> >& adjacency_list, vector<int>& result)
{
    vector<int> clone;
    for (set<int>::iterator fi = free.begin(); fi != free.end(); fi++)
    {
        clone.push_back(*fi);
    }
    if (clone.size() == 0)
    {
        bool first = true;
        for (vector<int>::iterator ri = result.begin(); ri != result.end(); ri++)
        {
            cout << variables[*ri];
        }
        cout << endl;
    }
    for (vector<int>::iterator ci = clone.begin(); ci != clone.end(); ci++)
    {
        int v = *ci;
        result.push_back(v);
        free.erase(v);

        for (set<int>::iterator ai = adjacency_list[v].begin(); ai != adjacency_list[v].end(); ai++)
        {
            int neighbor = *ai;
            indegree[neighbor]--;
            if (indegree[neighbor] == 0)
            {
                free.insert(neighbor);
            }
        }

        UVa124_recursive(free, indegree, variables, adjacency_list, result);

        for (set<int>::iterator ai = adjacency_list[v].begin(); ai != adjacency_list[v].end(); ai++)
        {
            int neighbor = *ai;
            if (indegree[neighbor] == 0)
            {
                free.erase(neighbor);
            }
            indegree[neighbor]++;
        }

        free.insert(v);
        result.erase(result.end() - 1);
    }
}