#include "stdafx.h"

// https://www.hackerrank.com/challenges/new-year-chaos

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int HACKER_RANK_NEW_YEAR_CHAOS()
{
    int t;
    cin >> t;
    for (int i = 0; i < t; i++)
    {
        int n;
        cin >> n;
        vector<int> expect_person;
        vector<int> expect_position;
        vector<int> actual;
        expect_person.resize(n);
        expect_position.resize(n);
        actual.resize(n);
        for (int j = 0; j < n; j++)
        {
            expect_person[j] = j;
            expect_position[j] = j;
            cin >> actual[j];
            actual[j]--;
        }
        bool good = true;
        int bribe_count = 0;
        for (int p = 0; p < n; p++)
        {
            int seen_person = actual[p];
            int position_difference = expect_position[seen_person] - p;
            if (position_difference > 2)
            {
                good = false;
                break;
            }
            bribe_count += position_difference;
            if (position_difference >= 1)
            {
                int current_position = expect_position[seen_person];
                int previous_position = current_position - 1;
                int previous_person = expect_person[previous_position];
                expect_person[previous_position] = seen_person;
                expect_position[seen_person] = previous_position;
                expect_person[current_position] = previous_person;
                expect_position[previous_person] = current_position;
            }
            if (position_difference == 2)
            {
                int current_position = expect_position[seen_person];
                int previous_position = current_position - 1;
                int previous_person = expect_person[previous_position];
                expect_person[previous_position] = seen_person;
                expect_position[seen_person] = previous_position;
                expect_person[current_position] = previous_person;
                expect_position[previous_person] = current_position;
            }
        }
        if (!good)
        {
            cout << "Too chaotic" << endl;
        }
        else
        {
            cout << bribe_count << endl;
        }
    }
    return 0;
}
