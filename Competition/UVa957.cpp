#include "stdafx.h"

// http://uva.onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=898

#include "UVa957.h"

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int UVa957()
{
    while (true)
    {
        int period_length;
        int number_of_popes;
        cin >> period_length;
        if (cin.eof())
        {
            break;
        }
        cin >> number_of_popes;
        vector<int> years;
        for (int i = 0; i < number_of_popes; i++)
        {
            int year;
            cin >> year;
            years.push_back(year);
        }

        int maxFrom = -1;
        int maxTo = -1;
        int maxSize = -1;

        for (unsigned int i = 0; i < years.size(); i++)
        {
            int lower_year = years[i];
            int upper_year = lower_year + period_length - 1; // Inclusive index
            vector<int>::iterator upper_bound_pointer = upper_bound(years.begin(), years.end(), upper_year);
            int exclusive_upper_index = upper_bound_pointer - years.begin();

            int size = exclusive_upper_index - i;
            if (size > maxSize)
            {
                maxFrom = lower_year;
                maxTo = *(upper_bound_pointer - 1);
                maxSize = size;
            }
        }
        cout << maxSize << " " << maxFrom << " " << maxTo << endl;

    }

    return 0;
}
