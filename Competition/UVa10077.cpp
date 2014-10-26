#include "stdafx.h"

// http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1018

#include "UVa10077.h"

#include <iostream>
#include <string>
#include <map>

using namespace std;

int UVa10077()
{
    while (true)
    {
        int m, n;
        cin >> m >> n;
        if (m == 1 && n == 1)
        {
            break;
        }
        int prev_m = 0;
        int prev_n = 1;
        int next_m = 1;
        int next_n = 0;
        while (true)
        {
            int middle_m = prev_m + next_m;
            int middle_n = prev_n + next_n;

            if (middle_m == m && middle_n == n)
            {
                break;
            }
            else
            {
                if (middle_m * n > middle_n * m)
                {
                    cout << "L";
                    next_m = middle_m;
                    next_n = middle_n;
                }
                else
                {
                    cout << "R";
                    prev_m = middle_m;
                    prev_n = middle_n;
                }
            }
        }
        cout << endl;
    }

    return 0;
}