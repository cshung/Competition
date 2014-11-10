#include "stdafx.h"

// http://uva.onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=931

#include "UVa990.h"

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <bitset>

using namespace std;

int UVa990()
{
    int case_number = 0;
    while (true)
    {
        int time_available;
        cin >> time_available;
        if (cin.eof())
        {
            break;
        }
        int w;
        cin >> w;
        int num_treasures;
        cin >> num_treasures;

        vector<pair<int, int> > treasures;
        for (int i = 0; i < num_treasures; i++)
        {
            int treasure_depth;
            cin >> treasure_depth;
            int treasure_value;
            cin >> treasure_value;
            int treasure_time = treasure_depth; // in 3w units
            treasures.push_back(pair<int, int>(treasure_time, treasure_value));
        }

        vector<int> last_values;
        vector<int> last_taken;
        vector<int> values;
        vector<int> taken;

        // Optimization - make time runs in 3w units - even a treasure of depth 1 need 3w time any way
        time_available = time_available / (3 * w);
        last_values.resize(time_available + 1);
        last_taken.resize(time_available + 1);
        values.resize(time_available + 1);
        taken.resize(time_available + 1);
        
        // Initialization - one achieve no value, however much time, if he consider no treasure
        for (int t = 0; t <= time_available; t++)
        {
            last_values[t] = 0;
            last_taken[t] = 0;
        }

        for (int i = 0; i < num_treasures; i++)
        {
            int current_treasure_time = treasures[i].first;
            int current_treasure_value = treasures[i].second;

            for (int t = 0; t <= time_available; t++)
            {
                if (t - current_treasure_time >= 0)
                {
                    int take_value = current_treasure_value + last_values[t - current_treasure_time];
                    if (take_value > last_values[t])
                    {
                        values[t] = take_value;
                        taken[t] = last_taken[t - current_treasure_time] | (1 << i);
                    }
                    else
                    {
                        values[t] = last_values[t];
                        taken[t] = last_taken[t];
                    }
                }
            }

            for (int t = 0; t <= time_available; t++)
            {
                last_values[t] = values[t];
                last_taken[t] = taken[t];
            }
        }

        if (case_number != 0)
        {
            cout << endl;
        }
        case_number++;

        cout << values[time_available] << endl;
        int count = 0;
        for (int i = 0; i < num_treasures; i++)
        {
            if ((taken[time_available] & 1 << i) != 0)
            {
                count++;
            }
        }
        cout << count << endl;
        for (int i = 0; i < num_treasures; i++)
        {
            if ((taken[time_available] & 1 << i) != 0)
            {
                cout << treasures[i].first << " " << treasures[i].second << endl;
            }
        }
    }

    return 0;
}