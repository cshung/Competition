#include "stdafx.h"

// https://www.hackerrank.com/challenges/cavity-map

#include "HACKER_RANK_CAVITY_MAP.h"

#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <stdbool.h>

using namespace std;

int HACKER_RANK_CAVITY_MAP()
{
    int i, j, n;
    scanf("%d", &n);
    char** grid = (char**)malloc(sizeof(char*) * n);
    for (int grid_i = 0; grid_i < n; grid_i++)
    {
        grid[grid_i] = (char *)malloc(10240 * sizeof(char));
        scanf("%s", grid[grid_i]);
    }

    for (i = 1; i < n - 1; i++)
    {
        for (j = 1; j < n - 1; j++)
        {
            if (grid[i - 1][j] < grid[i][j] && grid[i + 1][j] < grid[i][j] && grid[i][j - 1] < grid[i][j] && grid[i][j + 1] < grid[i][j])
            {
                grid[i][j] = 'X';
            }
        }
    }

    for (int grid_i = 0; grid_i < n; grid_i++)
    {
        printf("%s\n", grid[grid_i]);
    }
    return 0;
}