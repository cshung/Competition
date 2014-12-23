#include "stdafx.h"

// http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=319

#include "UVa383.h"

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <set>
#include <queue>

using namespace std;

int UVa383()
{
    cout << "SHIPPING ROUTES OUTPUT" << endl << endl;
    int num_test_cases;
    cin >> num_test_cases;
    for (int test_case_number = 1; test_case_number <= num_test_cases; test_case_number++)
    {
        cout << "DATA SET  " << test_case_number << endl << endl;
        int num_warehouses;
        cin >> num_warehouses;
        int num_legs;
        cin >> num_legs;
        int num_requests;
        cin >> num_requests;
        map<string, int> numbering;
        map<int, string> naming;
        for (int w = 0; w < num_warehouses; w++)
        {
            string name;
            cin >> name;
            int number = numbering.size();
            numbering.insert(pair<string, int>(name, number));
            naming.insert(pair<int, string>(number, name));
        }

        vector<set<int> > adjacency_list;
        adjacency_list.resize(num_warehouses);
        for (int l = 0; l < num_legs; l++)
        {
            string w1;
            string w2;

            cin >> w1;
            cin >> w2;
            adjacency_list[numbering[w1]].insert(numbering[w2]);
            adjacency_list[numbering[w2]].insert(numbering[w1]);
        }

        for (int r = 0; r < num_requests; r++)
        {
            int size;
            string w1;
            string w2;

            cin >> size;
            cin >> w1;
            cin >> w2;

            int wn1 = numbering[w1];
            int wn2 = numbering[w2];

            vector<int> distance;
            queue<int> bfs_queue;
            distance.resize(num_warehouses);
            for (int w = 0; w < num_warehouses; w++)
            {
                distance[w] = -1;
            }

            distance[wn1] = 0;
            bfs_queue.push(wn1);

            while (bfs_queue.size() > 0)
            {
                int visiting = bfs_queue.front();
                bfs_queue.pop();
                for (set<int>::iterator ni = adjacency_list[visiting].begin(); ni != adjacency_list[visiting].end(); ni++)
                {
                    int neighbor = *ni;
                    if (distance[neighbor] == -1)
                    {
                        distance[neighbor] = distance[visiting] + 1;
                        bfs_queue.push(neighbor);
                    }
                }
            }

            if (distance[wn2] == -1)
            {
                cout << "NO SHIPMENT POSSIBLE" << endl;
            }
            else
            {
                cout << "$" << size * distance[wn2] * 100 << endl;
            }
        }

        cout << endl;
    }

    cout << "END OF OUTPUT" << endl;

    return 0;
}