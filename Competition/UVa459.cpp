#include "stdafx.h"

// http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=400

#include "UVa459.h"

#include <iostream>
#include <string>
#include <vector>

using namespace std;

int find(int* parents, int toFind)
{
    if (parents[toFind] < 0) 
    {
        return toFind;
    }
    else {
        return (parents[toFind] = find(parents, parents[toFind])); /* path compression */
    }
}

void union_sets(int* parents, int src, int dst)
{
    int srcRoot = find(parents, src);
    int dstRoot = find(parents, dst);
    if (srcRoot != dstRoot)
    {
        if (srcRoot < dstRoot) {
            parents[srcRoot] = parents[srcRoot] + parents[dstRoot]; /* updating sizes */
            parents[dstRoot] = srcRoot;
            
        }
        else {
            parents[dstRoot] = parents[srcRoot] + parents[dstRoot];
            parents[srcRoot] = dstRoot;
        }
    }
}

int UVa459()
{
    int number_of_cases;
    cin >> number_of_cases;

    for (int c = 0; c < number_of_cases; c++)
    {
        char max;
        cin >> max;
        int num_nodes = max - 'A' + 1;
        string line;
        getline(cin, line); /* consume the blank line */
        int* parents = new int[num_nodes];
        for (int i = 0; i < num_nodes; i++)
        {
            parents[i] = -1; /* indicate this is the root node with size 1 */
        }
        while (true)
        {
            getline(cin, line);
            if (line.length() == 0)
            {
                break;
            }
            else
            {
                int src = line[0] - 'A';
                int dst = line[1] - 'A';
                union_sets(parents, src, dst);
            }
        }
        int num_connected_components = 0;
        for (int i = 0; i < num_nodes; i++)
        {
            if (parents[i] < 0)
            {
                num_connected_components++;
            }
        }
        cout << num_connected_components << endl;
        if (c != number_of_cases - 1)
        {
            cout << endl;
        }

        delete[] parents;
    }
    return 0;
}