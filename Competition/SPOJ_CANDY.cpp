#include "stdafx.h"

// https://www.spoj.com/problems/CANDY/

#include <stdio.h>

int SPOJ_CANDY()
{
    int candies[10000];
    while (true)
    {
        int N;
        scanf("%d", &N);
        if (N == -1)
        {
            break;
        }
        int sum = 0;
        for (int i = 0; i < N; i++)
        {
            scanf("%d", &candies[i]);
            sum += candies[i];
        }
        if (sum % N == 0)
        {
            int mean = sum / N;
            int move = 0;
            for (int i = 0; i < N; i++)
            {
                if (candies[i] < mean)
                {
                    move += mean - candies[i];
                }
            }
            printf("%d\n", move);
        }
        else
        {
            printf("-1\n");
        }
    }
    return 0;
}