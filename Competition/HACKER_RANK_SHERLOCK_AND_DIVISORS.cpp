#include "stdafx.h"

// https://www.hackerrank.com/challenges/sherlock-and-divisors

#include "HACKER_RANK_SHERLOCK_AND_DIVISORS.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _HACKER_RANK_SHERLOCK_AND_DIVISORS
{
    int divisors(int n)
    {
        if (n % 2 != 0)
        {
            return 0;
        }
        n /= 2;
        int i = 2;
        int s = 1;
        while (i * i <= n)
        {
            int c = 0;
            while (n % i == 0)
            {
                c++;
                n /= i;
            }
            s *= (c + 1);
            i++;
        }
        if (n != 1)
        {
            s *= 2;
        }
        return s;
    }
};

using namespace _HACKER_RANK_SHERLOCK_AND_DIVISORS;

int HACKER_RANK_SHERLOCK_AND_DIVISORS()
{
    cout << divisors(9) << endl;
    cout << divisors(8) << endl;
    return 0;
}