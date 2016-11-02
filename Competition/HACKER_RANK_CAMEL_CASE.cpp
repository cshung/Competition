#include "stdafx.h"

// https://www.hackerrank.com/challenges/camelcase

#include <string>
#include <iostream>

using namespace std;

int HACKER_RANK_CAMEL_CASE()
{
    string s;
    cin >> s;
    int c = 0;
    if (s.length() > 0)
    {
        c++;
    }
    for (size_t i = 0; i < s.length(); i++)
    {
        if ('A' <= s[i] && s[i] <= 'Z')
        {
            c++;
        }
    }
    cout << c;
    return 0;
}