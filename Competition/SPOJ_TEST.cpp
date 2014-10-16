#include "stdafx.h"

// http://www.spoj.com/problems/TEST/

#include <iostream>

using namespace std;

int SPOJ_TEST()
{
    while (true)
    {
        int x;
        cin >> x;
        if (x != 42)
        {
            cout << x << endl;
        }
        else
        {
            break;
        }
    }

    return 0;
}