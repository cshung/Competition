#include "stdafx.h"

// http://uva.onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=531

// #define LOG

#include "UVa590.h"

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int UVa590()
{
    int test_case_number = 0;
    while (true)
    {
        test_case_number++;
        int number_of_cities, number_of_flights;
        cin >> number_of_cities;
        cin >> number_of_flights;
        if ((number_of_cities == 0) && (number_of_flights == 0))
        {
            break;
        }

        // Step 1: Allocation
        vector<vector<vector<int> > > flight_schedules;
        flight_schedules.resize(number_of_cities);
        for (int src = 0; src < number_of_cities; src++)
        {
            flight_schedules[src].resize(number_of_cities);
        }

        // Step 2: Read inputs
        for (int src = 0; src < number_of_cities; src++)
        {
            for (int dst = 0; dst < number_of_cities; dst++)
            {
                if (src != dst)
                {
                    int period;
                    cin >> period;
                    flight_schedules[src][dst].resize(period);
                    for (int p = 0; p < period; p++)
                    {
                        cin >> flight_schedules[src][dst][p];
                    }
                }
            }
        }

        // Step 3: Bellman-ford
        vector<int> old_cost;
        vector<bool> old_reachable;
        vector<int> new_cost;
        vector<bool> new_reachable;
        old_cost.resize(number_of_cities);
        new_cost.resize(number_of_cities);
        old_reachable.resize(number_of_cities);
        new_reachable.resize(number_of_cities);

        // Step 3.1: Initialize old_cost to be 0, only cities 0 is reachable
        for (int c = 0; c < number_of_cities; c++)
        {
            old_cost[c] = 0;
            old_reachable[c] = (c == 0);
        }
        
        // Step 3.2: Relaxation
        for (int k = 0; k < number_of_flights; k++)
        {
            for (int c = 0; c < number_of_cities; c++)
            {
                new_reachable[c] = false;
            }

            for (int dst = 0; dst < number_of_cities; dst++)
            {
                bool first = true;
                for (int src = 0; src < number_of_cities; src++)
                {
                    if (old_reachable[src] && src != dst)
                    {
                        int period = flight_schedules[src][dst].size();
                        int day_in_period = k % period;
                        int cost = flight_schedules[src][dst][day_in_period];
                        if (cost > 0)
                        {
                            new_reachable[dst] = true;
                            if (first)
                            {
                                new_cost[dst] = old_cost[src] + cost;
                                first = false;
                            }
                            else
                            {
                                new_cost[dst] = min(new_cost[dst], old_cost[src] + cost);
                            }
                        }
                    }
                }
            }

            // Copy new to old
            for (int c = 0; c < number_of_cities; c++)
            {
                old_cost[c] = new_cost[c];
                old_reachable[c] = new_reachable[c];
            }
#ifdef LOG
            cout << "On day " << k << " we have: ";
            for (int c = 0; c < number_of_cities; c++)
            {
                if (old_reachable[c])
                {
                    cout << old_cost[c] << " ";
                }
                else
                {
                    cout << "X" << " ";
                }
            }
            cout << endl;
#endif
        }

        // Step 4: Output
        cout << "Scenario #" << test_case_number << endl;
        if (old_reachable[number_of_cities - 1])
        {
            cout << "The best flight costs " << old_cost[number_of_cities - 1] << "." << endl;
        }
        else
        {
            cout << "No flight possible." << endl;
        }

        cout << endl;
    }
    return 0;
}