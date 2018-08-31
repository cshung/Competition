#include "stdafx.h"

#include <stdio.h>

// http://www.spoj.com/problems/SAMER08F/

int SPOJ_SAMER08F()
{
    int c;
    while (true)
    {
        scanf("%d", &c);
        if (c == 0)
        {
            break;
        }
        printf("%d\n", c * (c + 1) * (2 * c + 1) / 6);
    }

    return 0;
}