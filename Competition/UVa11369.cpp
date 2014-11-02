#include "stdafx.h"

// http://uva.onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=2354

#include "UVa11369.h"

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int UVa11369()
{
    int number_of_cases;
    cin >> number_of_cases;
    for (int c = 0; c < number_of_cases; c++)
    {
        int num_items;
        cin >> num_items;
        vector<int> prices;
        for (int i = 0; i < num_items; i++)
        {
            int price;
            cin >> price;
            prices.push_back(-price); // a simple trick to make sort descending as we wish
        }
        sort(prices.begin(), prices.end());
        int discount = 0;
        for (unsigned int i = 2; i < prices.size(); i += 3)
        {
            discount -= prices[i]; // the numbers are negative
        }

        cout << discount << endl;
    }

    return 0;
}