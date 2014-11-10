#include "stdafx.h"

// http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=503

#include "UVa562.h"

#include <iostream>
#include <vector>

using namespace std;

int UVa562()
{
    int number_of_test_cases;
    cin >> number_of_test_cases;
    for (int c = 0; c < number_of_test_cases; c++)
    {
        int num_items;
        cin >> num_items;
        vector<int> item_values;
        item_values.resize(num_items);
        int item_value_sum = 0;
        for (int i = 0; i < num_items; i++)
        {
            int item_value;
            cin >> item_value;
            item_values[i] = item_value;
            item_value_sum += item_value; 
        }

        int best_lower_value = item_value_sum / 2;

        vector<bool> last_achievable;
        vector<bool> achievable;

        last_achievable.resize(best_lower_value + 1);
        achievable.resize(best_lower_value + 1);

        // Initialization - with no coin at all, the only achievable value is 0
        for (int v = 0; v <= best_lower_value; v++)
        {
            last_achievable[v] = (v == 0);
        }
        
        for (int i = 0; i < num_items; i++)
        {
            int current_item_value = item_values[i];
            
            // Initialization - before we consider the coin, we can already achieve what was achievable
            for (int v = 0; v <= best_lower_value; v++)
            {
                achievable[v] = last_achievable[v];
            }

            for (int v = 0; v <= best_lower_value; v++)
            {
                if (last_achievable[v])
                {
                    int next_achievable_value = v + current_item_value;
                    if (next_achievable_value <= best_lower_value)
                    {
                        achievable[next_achievable_value] = true;
                    }
                }
            }
            
            for (int v = 0; v <= best_lower_value; v++)
            {
                last_achievable[v] = achievable[v];
            }
        }

        int achievable_best_lower_value = -1;
        for (int v = best_lower_value; v >= 0; v--)
        {
            if (achievable[v])
            {
                achievable_best_lower_value = v;
                break;
            }
        }
        cout << item_value_sum - achievable_best_lower_value - achievable_best_lower_value << endl;
    }

    return 0;
}