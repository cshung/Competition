#include "stdafx.h"

// https://www.hackerrank.com/challenges/flipping-the-matrix

#include "HACKER_RANK_FLIPPING_THE_MATRIX.h"

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int HACKER_RANK_FLIPPING_THE_MATRIX()
{
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    int q;
    cin >> q;
    for (int i = 0; i < q; i++)
    {
        int n;
        cin >> n;
        int matrix[256][256];
        for (int p = 0; p < 2 * n; p++)
        {
            for (int q = 0; q < 2 * n; q++)
            {
                cin >> matrix[p][q];
            }
        }
        int sum = 0;
        for (int p = 0; p < n; p++)
        {
            for (int q = 0; q < n; q++)
            {
                sum += max(max(max(matrix[p][q], matrix[2 * n - 1 - p][q]), matrix[p][2 * n - 1 - q]), matrix[2 * n - 1 - p][2 * n - 1 - q]);
            }
        }
        cout << sum << endl;
    }
    return 0;
}
