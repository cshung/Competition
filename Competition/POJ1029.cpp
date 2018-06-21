#include "stdafx.h"

// http://poj.org/problem?id=1029

// #define LOG

#pragma warning(disable : 4996)

#include<stdio.h>

int POJ1029()
{
#pragma
    int n, k;
    scanf("%d %d", &n, &k);
    int* small = new int[n + 1];
    int* large = new int[n + 1];
    int* equal = new int[n + 1];
    int* data = new int[n + 1];
    int number_of_inequalities = 0;
    for (int i = 1; i <= n; i++)
    {
        small[i] = large[i] = equal[i] = 0;
    }
    for (int r = 0; r < k; r++)
    {
        int len;
        char sign;
        scanf("%d", &len);
        for (int j = 0; j < len * 2; j++)
        {
            scanf("%d", data + j);
        }
        scanf(" %c", &sign);
        switch (sign)
        {
        case '=':
            for (int j = 0; j < len * 2; j++)
            {
                equal[data[j]] = 1;
            }
            break;
        case '>':
            number_of_inequalities++;
            for (int j = 0; j < len; j++)
            {
                large[data[j]]++;
            }
            for (int j = len; j < len * 2; j++)
            {
                small[data[j]]++;
            }
            break;
        case '<':
            number_of_inequalities++;
            for (int j = 0; j < len; j++)
            {
                small[data[j]]++;
            }
            for (int j = len; j < len * 2; j++)
            {
                large[data[j]]++;
            }
            break;
        }
    }

    int small_solution = -1;
    int large_solution = -1;
    int equal_solution = -1;
    for (int i = 1; i <= n; i++)
    {
        if (equal[i] == 0)
        {
            if (small[i] == number_of_inequalities)
            {
                if (small_solution == -1)
                {
                    small_solution = i;
                }
                else
                {
                    small_solution = 0;
                }
            }
            if (large[i] == number_of_inequalities)
            {
                if (large_solution == -1)
                {
                    large_solution = i;
                }
                else
                {
                    large_solution = 0;
                }
            }
            if (equal_solution == -1)
            {
                equal_solution = i;
            }
            else
            {
                equal_solution = 0;
            }
        }
    }
    int answer = 0;
    if (number_of_inequalities == 0)
    {
        if (equal_solution > 0)
        {
            answer = equal_solution;
        }
    }
    else
    {
        if (small_solution > 0 && large_solution < 1)
        {
            answer = small_solution;
        }
        if (large_solution > 0 && small_solution < 1)
        {
            answer = large_solution;
        }
    }
    printf("%d\n", answer);
    delete[] small;
    delete[] large;
    delete[] equal;
    return 0;
}