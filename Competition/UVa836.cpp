#include "stdafx.h"

// http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=777

#include "UVa836.h"

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int UVa836()
{
    int num_cases;
    cin >> num_cases;
    for (int ca = 0; ca < num_cases; ca++)
    {
        string line;
        cin >> line;
        int n = line.length();
        vector<vector<int> > input;
        input.resize(n);
        input[0].resize(n);
        for (int i = 0; i < n; i++)
        {
            input[0][i] = line[i] - '0';
        }
        for (int r = 1; r < n; r++)
        {
            input[r].resize(n);
            cin >> line;
            for (int c = 0; c < n; c++)
            {
                input[r][c] = line[c] - '0';
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

        int max_size = 0;

        // 25 ^ 4 cases
        for (int sr = 0; sr < n; sr++)
        {
            for (int sc = 0; sc < n; sc++)
            {
                for (int er = sr; er < n; er++)
                {
                    for (int ec = sc; ec < n; ec++)
                    {
                        int size = (er - sr + 1) * (ec - sc + 1);
                        // x x x x x
                        // x x D x C
                        // x x x x x 
                        // x x B x A
                        int sum = running_sum[er + 1][ec + 1] - running_sum[sr][ec + 1] - running_sum[er + 1][sc] + running_sum[sr][sc];
                        if (sum == size)
                        {
                            max_size = max(size, max_size);
                        } 
                    }
                }
            }
        }

        if (ca != 0)
        {
            cout << endl;
        }

        cout << max_size << endl;
    }

    return 0;
}