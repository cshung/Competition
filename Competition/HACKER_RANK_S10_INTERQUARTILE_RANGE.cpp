#include "stdafx.h"

// https://www.hackerrank.com/challenges/s10-interquartile-range

#include <iostream>
#include <iomanip>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

int HACKER_RANK_S10_INTERQUARTILE_RANGE()
{
    int n;
    int count = 0;
    cin >> n;
    vector<pair<int, int>> data;
    data.resize(n);
    for (int i = 0; i < n; i++)
    {
        cin >> data[i].first;
    }
    for (int i = 0; i < n; i++)
    {
        cin >> data[i].second;
        count += data[i].second;
    }
    sort(data.begin(), data.end());
    double answer = 0;
    if (count % 4 == 3)
    {
        int t1 = count / 4;
        int t2 = count / 2 + 1 + count / 4;
        int g1 = 0;
        int g2 = 0;
        int begin = 0;
        for (int i = 0; i < n; i++)
        {
            int end = begin + data[i].second;
            if (begin <= t1 && t1 < end) { g1 = data[i].first; }
            if (begin <= t2 && t2 < end) { g2 = data[i].first; break; }
            begin = end;
        }
        answer = g2 - g1;
    }
    else if (count % 4 == 2)
    {
        int t1 = count / 4;
        int t2 = count / 2 + count / 4;
        int g1 = 0;
        int g2 = 0;
        int begin = 0;
        for (int i = 0; i < n; i++)
        {
            int end = begin + data[i].second;
            if (begin <= t1 && t1 < end) { g1 = data[i].first; }
            if (begin <= t2 && t2 < end) { g2 = data[i].first; break; }
            begin = end;
        }
        answer = g2 - g1;
    }
    else if (count % 4 == 1)
    {
        int t1 = count / 4 - 1;
        int t2 = count / 4;
        int t3 = count / 2 + count / 4;
        int t4 = count / 2 + count / 4 + 1;

        int g1 = 0;
        int g2 = 0;
        int g3 = 0;
        int g4 = 0;
        int begin = 0;
        for (int i = 0; i < n; i++)
        {
            int end = begin + data[i].second;
            if (begin <= t1 && t1 < end) { g1 = data[i].first; }
            if (begin <= t2 && t2 < end) { g2 = data[i].first; }
            if (begin <= t3 && t3 < end) { g3 = data[i].first; }
            if (begin <= t4 && t4 < end) { g4 = data[i].first; break; }
            begin = end;
        }
        answer = (g3 + g4 - g2 - g1) / 2.0;
    }
    else if (count % 4 == 0)
    {
        int t1 = count / 4 - 1;
        int t2 = count / 4;
        int t3 = count / 2 + count / 4 - 1;
        int t4 = count / 2 + count / 4;

        int g1 = 0;
        int g2 = 0;
        int g3 = 0;
        int g4 = 0;
        int begin = 0;
        for (int i = 0; i < n; i++)
        {
            int end = begin + data[i].second;
            if (begin <= t1 && t1 < end) { g1 = data[i].first; }
            if (begin <= t2 && t2 < end) { g2 = data[i].first; }
            if (begin <= t3 && t3 < end) { g3 = data[i].first; }
            if (begin <= t4 && t4 < end) { g4 = data[i].first; break; }
            begin = end;
        }
        answer = (g3 + g4 - g2 - g1) / 2.0;
    }
    cout << fixed << setprecision(1) << answer << endl;

    return 0;
}
