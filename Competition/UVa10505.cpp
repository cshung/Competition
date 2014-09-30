#include "stdafx.h"

// http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1361

#include "UVa10505.h"

#include <iostream>
#include <list>
#include <map>
#include <queue>

using namespace std;

int UVa10505()
{
    int number_of_cases;
    cin >> number_of_cases;
    for (int c = 0; c < number_of_cases; c++)
    {
        list<pair<int, int> > input;

        int number_of_people;
        cin >> number_of_people;
        for (int i = 1; i <= number_of_people; i++) 
        {
            int number_of_enemies;
            cin >> number_of_enemies;
            for (int e = 0; e < number_of_enemies; e++)
            {
                int enemy;
                cin >> enemy;
                if (1 <= enemy && enemy <= number_of_people) // This should never happen - but who knows - the bipartite condition is broken - this might as well happen.
                {
                    input.push_back(pair<int, int>(i, enemy));
                }
            }
        }

        list<int>* adjacency_list = new list<int>[number_of_people];

        for (list<pair<int, int> >::iterator ii = input.begin(); ii != input.end(); ii++)
        {
            int from = ii->first;
            int to = ii->second;
            from--;
            to--;
            adjacency_list[from].push_back(to);
            adjacency_list[to].push_back(from);
        }

        int* visited = new int[number_of_people];
        for (int i = 0; i < number_of_people; i++)
        {
            visited[i] = 0;
        }
        int answer = 0;
        for (int i = 0; i < number_of_people; i++)
        {
            int trueCount = 0;
            int falseCount = 0;
            if (visited[i] == 0)
            {
                queue<pair<int, int> > bfsQueue;
                bfsQueue.push(pair<int, int>(i, 1));
                visited[i] = 1;
                bool bad = false;
                while (bfsQueue.size() > 0)
                {
                    pair<int, int> visiting = bfsQueue.front();
                    bfsQueue.pop();
                    if (visiting.second == 1)
                    {
                        trueCount++;
                    }
                    else
                    {
                        falseCount++;
                    }
                    for (list<int>::iterator ni = adjacency_list[visiting.first].begin(); ni != adjacency_list[visiting.first].end(); ni++)
                    {
                        if (visited[*ni] == 0)
                        {
                            visited[*ni] = -visiting.second;
                            bfsQueue.push(pair<int, int>(*ni, -visiting.second));
                        }
                        else if (visited[*ni] == visiting.second)
                        {
                            bad = true;
                        }
                    }
                }
                if (!bad)
                {
                    answer += max(trueCount, falseCount);
                }
            }
        }

        cout << answer << endl;
        delete[] visited;
        delete[] adjacency_list;
    }

    return 0;
}