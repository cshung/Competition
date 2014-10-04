#include "stdafx.h"

// http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=465

#include "UVa524.h"

#include <iostream>
#include <list>
#include <map>

using namespace std;

void dfs(int visiting, list<int>* graph, bool* visited, list<int>& path, int n)
{
    visited[visiting] = true;

    path.push_back(visiting);
    if (path.size() == n)
    {
        for (list<int>::iterator ni = graph[visiting].begin(); ni != graph[visiting].end(); ni++)
        {
            if (*ni == *path.begin())
            {
                for (list<int>::iterator pi = path.begin(); pi != path.end(); pi++)
                {
                    if (pi != path.begin())
                    {
                        cout << " ";
                    }
                    cout << (*pi + 1) ;
                }
                cout << endl;
            }
        }
    }

    for (list<int>::iterator ni = graph[visiting].begin(); ni != graph[visiting].end(); ni++)
    {
        if (!visited[*ni])
        {
            dfs(*ni, graph, visited, path, n);
        }
    }
    path.pop_back();
    visited[visiting] = false;
}

int UVa524()
{
    int c = 1;

    while (true)
    {
        int n;
        cin >> n;
        if (cin.fail())
        {
            break;
        }

        map<int, bool> prime;

        // Step 1: Build a map of prime numbers
        for (int i = 2; i <= 2 * n - 1; i++)
        {
            bool is_prime = true;

            // n <= 16 - just too small to justify the use of sieve
            for (int j = 2; j < i && is_prime; j++)
            {
                if (i % j == 0)
                {
                    is_prime = false;
                }
            }
            if (is_prime)
            {
                prime.insert(pair<int, bool>(i, true));
            }
        }

        // Step 2: Build a graph of prime edges
        list<int>* graph = new list<int>[n];
        for (int i = 0; i < n; i++)
        {
            for (int j = i + 1; j < n; j++)
            {
                int sum = (i + 1) + (j + 1);
                if (prime.find(sum) != prime.end())
                {
                    graph[i].push_back(j);
                    graph[j].push_back(i);
                }
            }
        }

        // Step 3: Finding all cycles with DFS
        bool* visited = new bool[n];
        for (int i = 0; i < n; i++)
        {
            visited[i] = false;
        }
        list<int> path;
        if (c != 1)
        {
            cout << endl;
        }
        cout << "Case " << c++ << ":" << endl;
        dfs(0, graph, visited, path, n);
        delete[] graph;
    }
    return 0;
}