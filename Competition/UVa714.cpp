#include "stdafx.h"

// http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=655

#include "UVa714.h"

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Greedy is wrong
// Recursive backtracking is too slow 
// Let's use the recursive backtracking to validate answer

void find_solution(vector<int>& number_of_pages, int number_of_scribers, vector<int>& splits, int starting, long long greedy_value, long long current_solution_value, long long remaining_sum, long long& best_value, vector<int>& best_splits)
{
    if (number_of_scribers == 1)
    {
        // The solution value is the max of the max of the batches before and the last batch
        current_solution_value = max(current_solution_value, remaining_sum);

        if (current_solution_value < best_value)
        {
            // current solution is better!
            best_value = current_solution_value;
            best_splits.clear();
            for (vector<int>::iterator si = splits.begin(); si != splits.end(); si++)
            {
                best_splits.push_back(*si);
            }
        }
    }
    else
    {
        // splits[0] represents the exclusive index of the first batch, say if 100, 200, 300, 400, 500 is the first batch, then split[0] = 5
        // one batch need at least one element, so the maximum split index is constrainted by the number of splits left
        // Suppose number of splits = 0, number of scribers = 3, number of books = 9, the first batch's size can at most be 7 = 9 - 2 
        long long sum = 0;
        for (int i = starting + 1; i <= number_of_pages.size() - (number_of_scribers - 1); i++)
        {
            
            remaining_sum -= number_of_pages[i - 1];
            sum += number_of_pages[i - 1];
            double remaining_ideal = (double)remaining_sum / (number_of_scribers - 1);
            if (sum <= greedy_value)
            {
                if (remaining_ideal <= greedy_value)
                {
                    /*cout << "Trying to split at " << i << " for the " << (splits.size() + 1) << " split" << endl;
                    cout << "At that point, the sum is " << sum << endl;*/

                    current_solution_value = max(sum, current_solution_value);
                    splits.push_back(i);
                    find_solution(number_of_pages, number_of_scribers - 1, splits, i, greedy_value, current_solution_value, remaining_sum, best_value, best_splits);
                    splits.pop_back();
                }
            }
            else
            {
                break;
            }
        }
    }
}

int UVa714()
{
    int number_of_cases;
    cin >> number_of_cases;
    for (int c = 0; c < number_of_cases; c++)
    {
        int number_of_books;
        int number_of_scribers;
        cin >> number_of_books;
        cin >> number_of_scribers;
        vector<int> number_of_pages;
        for (int b = 0; b < number_of_books; b++)
        {
            int number_of_page;
            cin >> number_of_page;
            number_of_pages.push_back(number_of_page);
        }

        int sum = 0;
        for (vector<int>::iterator pi = number_of_pages.begin(); pi != number_of_pages.end(); pi++)
        {
            sum += *pi;
        }

        double ideal = ((double)sum) / number_of_scribers;

        // Try the greedy algorithm - that will come up with some good estimate 
        long long total_sum = 0;
        long long current_sum = 0;
        int slash_count = 1;
        long long greedy_value = 0;
        for (vector<int>::iterator pi = number_of_pages.begin(); pi != number_of_pages.end(); pi++)
        {
            total_sum += *pi;
            if (slash_count == number_of_scribers)
            {
                // I have already done with the splitting, the remaining must group into the same group
                current_sum += *pi;
            }
            else
            {
                double take_slack = current_sum + *pi - ideal;
                if (take_slack <= 0)
                {
                    // Taking the item does not exceed ideal - take it anyway
                    current_sum += *pi;
                    // After this addition, current_sum should still be less than (or equals to) ideal.
                }
                else
                {
                    // Now taking it is going to exceed ideal, deciding whether or not to take it
                    // We try to minimize the slack, that is, the difference between the value and the ideal.
                    double drop_slack = ideal - current_sum;
                    if (take_slack < drop_slack)
                    {
                        current_sum += *pi;
                        if (current_sum > greedy_value)
                        {
                            greedy_value = current_sum;
                        }
                        current_sum = 0;
                    }
                    else
                    {
                        if (current_sum > greedy_value)
                        {
                            greedy_value = current_sum;
                        }
                        current_sum = *pi;
                    }
                    slash_count++;
                }
            }
        }

        if (current_sum > greedy_value)
        {
            greedy_value = current_sum;
        }

        vector<int> splits;
        vector<int> best_splits;
        long long best_value = total_sum + 1; // impossible to be the best
        find_solution(number_of_pages, number_of_scribers, splits, 0, greedy_value, 0, total_sum, best_value, best_splits);

        int j = 0;
        for (int i = 0; i < number_of_pages.size(); i++)
        {
            if (j < best_splits.size() && i == best_splits[j])
            {
                cout << "/ ";
                j++;
            }
            cout << number_of_pages[i] << " ";
        }
        cout << endl;
    }
    return 0;
}