#include "stdafx.h"

// http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1832

#include "UVa10891.h"

#define LOG

#include <iostream>
#include <vector>

using namespace std;


struct UVa10891_strategy
{
    int start_index;
    int end_index;
    int strategy_value;
};

int UVa10891()
{
    while (true)
    {
        // Step 1: Input
        int number_of_elements;
        cin >> number_of_elements;
        if (number_of_elements == 0)
        {
            break;
        }

        vector<int> elements;
        elements.resize(number_of_elements);
        for (int i = 0; i < number_of_elements; i++)
        {
            int element;
            cin >> element;
            elements[i] = element;
        }

        // Step 2: Pre compute running sum
        vector<int> element_sums;
        element_sums.resize(number_of_elements + 1);
        int element_sum = 0;
        for (int i = 0; i < number_of_elements; i++)
        {
            element_sums[i] = element_sum;
            element_sum += elements[i];
        }
        element_sums[number_of_elements] = element_sum;

        // element_sums[b + 1] - element_sums[a] = sum(i = a to b) elements[i]

        // Step 3: Dynamic programming
        vector<vector<UVa10891_strategy> > optimal_strategies;
        optimal_strategies.resize(number_of_elements);
        for (int start = 0; start < number_of_elements; start++)
        {
            optimal_strategies[start].resize(number_of_elements);
        }

        for (int length = 1; length <= number_of_elements; length++)
        {
            for (int start = 0; (start + length - 1) < number_of_elements; start++)
            {
                int end = start + length - 1;
                if (length == 1)
                {
                    // There is only one element - we have no choice but to pick this number
                    optimal_strategies[start][end].start_index = start;
                    optimal_strategies[start][end].end_index = start;
                    optimal_strategies[start][end].strategy_value = elements[start];
#ifdef LOG
                    cout << "optimal_strategies[" << start << "][" << end << "] = (" << optimal_strategies[start][end].start_index << ", " << optimal_strategies[start][end].end_index << ") = " << optimal_strategies[start][end].strategy_value << endl;
#endif
                }
                else
                {
                    bool first = true;
                    optimal_strategies[start][end].start_index = start;
                    optimal_strategies[start][end].end_index = end;
                    optimal_strategies[start][end].strategy_value = element_sums[end + 1] - element_sums[start];
                    for (int p = start; p < end; p++)
                    {
                        // Consider I am choosing [start, p]
                        int strategy_value = element_sums[p + 1] - element_sums[start];
                        UVa10891_strategy opponent_strategy = optimal_strategies[p + 1][end];
                        if (opponent_strategy.start_index == p + 1)
                        {
                            // opponent is choosing [p + 1, opponent_strategy.end_index]
                            if (opponent_strategy.end_index != end)
                            {
                                strategy_value += optimal_strategies[opponent_strategy.end_index + 1][end].strategy_value;
                            }
                        }
                        else
                        {
                            // opponent is choosing [opponent.start_index, end]
                            if (opponent_strategy.start_index != p + 1)
                            {
                                strategy_value += optimal_strategies[p + 1][opponent_strategy.start_index - 1].strategy_value;
                            }
                        }
                        if (strategy_value > optimal_strategies[start][end].strategy_value)
                        {
                            optimal_strategies[start][end].strategy_value = strategy_value;
                            optimal_strategies[start][end].start_index = start;
                            optimal_strategies[start][end].end_index = p;
                        }
                    }
                    for (int q = end; q > start; q--)
                    {
                        // Consider I am choosing [q, end]
                        int strategy_value = element_sums[end + 1] - element_sums[q];
                        UVa10891_strategy opponent_strategy = optimal_strategies[start][q - 1];
                        if (opponent_strategy.start_index == start)
                        {
                            // opponent is choosing [start, opponent_strategy.end_index]
                            if (opponent_strategy.end_index != q - 1)
                            {
                                strategy_value += optimal_strategies[opponent_strategy.end_index + 1][q - 1].strategy_value;
                            }
                        }
                        else
                        {
                            // opponent is choosing [opponent_strategy.start_index, q - 1]
                            if (opponent_strategy.start_index != start)
                            {
                                strategy_value += optimal_strategies[start][opponent_strategy.start_index - 1].strategy_value;
                            }
                        }
                        if (strategy_value > optimal_strategies[start][end].strategy_value)
                        {
                            optimal_strategies[start][end].strategy_value = strategy_value;
                            optimal_strategies[start][end].start_index = q;
                            optimal_strategies[start][end].end_index = end;
                        }
                    }
#ifdef LOG
                    cout << "optimal_strategies[" << start << "][" << end << "] = (" << optimal_strategies[start][end].start_index << ", " << optimal_strategies[start][end].end_index << ") = " << optimal_strategies[start][end].strategy_value << endl;
#endif
                }
            }
        }

        UVa10891_strategy optimal_strategy = optimal_strategies[0][number_of_elements - 1];
        if (optimal_strategy.start_index == 0)
        {
            if (optimal_strategy.end_index != number_of_elements - 1)
            {
                cout << optimal_strategy.strategy_value - optimal_strategies[optimal_strategy.end_index + 1][number_of_elements - 1].strategy_value << endl;
            }
            else
            {
                cout << optimal_strategy.strategy_value << endl;
            }
        }
        else
        {
            if (optimal_strategy.start_index != 0)
            {
                cout << optimal_strategy.strategy_value - optimal_strategies[0][optimal_strategy.end_index - 1].strategy_value << endl;
            }
            else
            {
                cout << optimal_strategy.strategy_value << endl;
            }
        }
        
    }
    return 0;
}