#include "stdafx.h"

// http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=44

#include "UVa108.h"

#include <iostream>
#include <vector>

using namespace std;

int UVa108()
{
    int n;
    cin >> n;
    vector<vector<int> > input;
    input.resize(n);
    for (int row = 0; row < n; row++)
    {
        input[row].resize(n);
        for (int col = 0; col < n; col++)
        {
            cin >> input[row][col];
        }
    }

    // running_sum[i][j] = sum[0 .. (i - 1)][0 .. (j - 1)]
    // so running_sum[0][*] = running_sum[*][0] = 0
    vector<vector<int> > running_sum;
    running_sum.resize(n + 1);
    for (int row = 0; row < n + 1; row++)
    {
        running_sum[row].resize(n + 1);
        for (int col = 0; col < n + 1; col++)
        {
            if (row == 0 || col == 0)
            {
                running_sum[row][col] = 0;
            }
            else
            {
                // x x x x
                // x x D C
                // x x B A
                running_sum[row][col] = running_sum[row - 1][col] + running_sum[row][col - 1] - running_sum[row - 1][col - 1] + input[row - 1][col - 1];
            }
        }
    }

    bool first = true;
    int max_sum = 0;

    // 100 ^ 4 cases
    for (int sr = 0; sr < n; sr++)
    {
        for (int sc = 0; sc < n; sc++)
        {
            for (int er = sr; er < n; er++)
            {
                for (int ec = sc; ec < n; ec++)
                {
                    // x x x x x
                    // x x D x C
                    // x x x x x 
                    // x x B x A
                    int sum = running_sum[er + 1][ec + 1] - running_sum[sr][ec + 1] - running_sum[er + 1][sc] + running_sum[sr][sc];
                    if (first)
                    {
                        max_sum = sum;
                        first = false;
                    }
                    else
                    {
                        max_sum = max(sum, max_sum);
                    }
                }
            }
        }
    }
    cout << max_sum << endl;

    return 0;
}