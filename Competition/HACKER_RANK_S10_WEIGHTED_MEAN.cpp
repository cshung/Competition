#include "stdafx.h"

// https://www.hackerrank.com/challenges/s10-weighted-mean

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <iomanip>
#include <algorithm>
using namespace std;

int HACKER_RANK_S10_WEIGHTED_MEAN()
{
    int n;
    cin >> n;
    vector<int> x;
    vector<int> w;
    x.resize(n);
    w.resize(n);
    for (int i = 0; i < n; i++)
    {
        cin >> x[i];
    }
    for (int i = 0; i < n; i++)
    {
        cin >> w[i];
    }
    double numerator = 0;
    double denominator = 0;
    for (int i = 0; i < n; i++)
    {
        numerator += x[i] * w[i];
        denominator += w[i];
    }
    cout << fixed << setprecision(1) << (numerator / denominator);
    return 0;
}