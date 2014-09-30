#include "stdafx.h"
#pragma warning(disable : 4996)

// http://uva.onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=2498

#include "UVa11503.h"

#include <iostream>
#include <string>
#include <map>
#include <cstdlib>
#include <stdio.h>
#include <vector>
#include <list>

using namespace std;

int find(vector<int>& social_network, int id)
{
    if (social_network[id] < 0)
    {
        return id;
    } 
    else
    {
        list<int> path;
        while (social_network[id] >= 0)
        {
            path.push_back(id);
            id = social_network[id];
        }
        for (list<int>::iterator pi = path.begin(); pi != path.end(); pi++)
        {
            social_network[*pi] = id;
        }
        return id;
    }
}

int UVa11503()
{
    int number_of_cases;
    cin >> number_of_cases;
    for (int c = 0; c < number_of_cases; c++)
    {
        int number_of_friendship;
        cin >> number_of_friendship;
        map<string, int> names;
        vector<int> social_network;
        for (int f = 0; f < number_of_friendship; f++)
        {
            char name1Buffer[20];
            char name2Buffer[20];
            scanf("%s %s", name1Buffer, name2Buffer);
            string name1(name1Buffer);
            string name2(name2Buffer);
            int id1;
            int id2;
            map<string, int>::iterator probe1 = names.find(name1);
            if (probe1 == names.end())
            {
                names.insert(pair<string, int>(name1, id1 = social_network.size()));
                social_network.push_back(-1); /* a new person is a network of size 1 */
            }
            else
            {
                id1 = probe1->second;
            }
            map<string, int>::iterator probe2 = names.find(name2);
            if (probe2 == names.end())
            {
                names.insert(pair<string, int>(name2, id2 = social_network.size()));
                social_network.push_back(-1); /* a new person is a network of size 1 */
            }
            else
            {
                id2 = probe2->second;
            }
            int root1 = find(social_network, id1);
            int root2 = find(social_network, id2);
            if (root1 != root2)
            {
                // Union by size
                if (social_network[root1] < social_network[root2])
                {
                    social_network[root1] = social_network[root1] + social_network[root2];
                    social_network[root2] = root1;
                    printf("%d\n", -social_network[root1]);
                }
                else
                {
                    social_network[root2] = social_network[root1] + social_network[root2];
                    social_network[root1] = root2;
                    printf("%d\n", -social_network[root2]);
                }
            }
            else
            {
                printf("%d\n", -social_network[root1]);
            }
        }
    }
    return 0;
}