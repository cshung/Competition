#include "stdafx.h"

// http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1704

#include "UVa10763.h"

#include <iostream>
#include <map>

using namespace std;

int UVa10763()
{
    while (true)
    {
        int num_candidates;
        cin >> num_candidates;
        if (num_candidates == 0)
        {
            break;
        }
        map<pair<int, int>, int> expectations;
        for (int c = 0; c < num_candidates; c++)
        {
            int src, dst;
            cin >> src;
            cin >> dst;
            map<pair<int, int>, int>::iterator probe1 = expectations.find(pair<int, int>(src, dst));
            if (probe1 == expectations.end())
            {
                map<pair<int, int>, int>::iterator probe2 = expectations.find(pair<int, int>(dst, src));
                if (probe2 == expectations.end())
                {
                    expectations.insert(pair<pair<int, int>, int>(pair<int, int>(dst, src), 1));
                }
                else
                {
                    probe2->second++;
                }
            }
            else
            {
                if (--probe1->second == 0)
                {
                    expectations.erase(probe1);
                }
            }
        }

        cout << (expectations.size() == 0 ? "YES" : "NO") << endl;
    }
    return 0;
}