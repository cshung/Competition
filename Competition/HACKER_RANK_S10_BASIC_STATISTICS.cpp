#include "stdafx.h"

// https://www.hackerrank.com/challenges/s10-basic-statistics

#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>
using namespace std;

int HACKER_RANK_S10_BASIC_STATISTICS()
{
    int n;
    cin >> n;
    vector<int> v;
    v.resize(n);
    for (int i = 0; i < n; i++)
    {
        cin >> v[i];
    }

    sort(v.begin(), v.end());
    double sum = 0;
    for (int i = 0; i < n; i++)
    {
        sum += v[i];
    }
    cout << fixed << std::setprecision(1) << sum / n << endl;
    if (n % 2 == 1)
    {
        cout << fixed << std::setprecision(1) << v[n / 2] << endl;
    }
    else
    {
        cout << fixed << std::setprecision(1) << (v[n / 2 - 1] + v[n / 2]) / 2.0 << endl;
    }

    int last_number = v[0];
    int last_frequency = 1;
    int max_frequency_number = v[0];
    int max_frequency = 1;

    for (int i = 1; i < n; i++)
    {
        if (v[i] == last_number)
        {
            last_frequency++;
        }
        else
        {
            last_number = v[i];
            last_frequency = 1;
        }
        // Here we ensure the smallest one with the same frequency
        if (last_frequency > max_frequency)
        {
            max_frequency = last_frequency;
            max_frequency_number = last_number;
        }
    }

    cout << max_frequency_number << endl;

    return 0;
}