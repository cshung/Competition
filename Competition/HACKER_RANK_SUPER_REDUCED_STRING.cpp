#include "stdafx.h"

#include <iostream>
#include <stack>
#include <string>
using namespace std;

// https://www.hackerrank.com/challenges/reduced-string

#include "HACKER_RANK_SUPER_REDUCED_STRING.h"

int HACKER_RANK_SUPER_REDUCED_STRING()
{
    stack<char> seen;
    string s;
    cin >> s;
    for (int i = 0; i < s.size(); i++)
    {
        char c = s[s.size() - 1 - i];
        if (seen.size() > 0 && seen.top() == c)
        {
            seen.pop();
        }
        else
        {
            seen.push(c);
        }
    }
    if (seen.size() > 0)
    {
        while (seen.size() > 0)
        {
            cout << seen.top();
            seen.pop();
        }
    }
    else
    {
        cout << "Empty String";
    }
    return 0;
}