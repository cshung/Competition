#include "stdafx.h"

// http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=655

#include "UVa714.h"

#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

typedef long long int64;

//#define GREEDY_DRIVEN_BRANCH_AND_BOUND
#define DYNAMIC_PROGRAMMING

#ifdef GREEDY_DRIVEN_BRANCH_AND_BOUND

void find_solution(vector<int64>& number_of_pages, int number_of_scribers, vector<int>& splits, int starting, int64 greedy_value, int64 current_solution_value, int64 remaining_sum, int64& best_value, vector<int>& best_splits)
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
        int64 sum = 0;
        for (unsigned int i = starting + 1; i <= number_of_pages.size() - (number_of_scribers - 1); i++)
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

#endif

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
        vector<int64> number_of_pages;
        for (int b = 0; b < number_of_books; b++)
        {
            int64 number_of_page;
            cin >> number_of_page;
            number_of_pages.push_back(number_of_page);
        }

#ifdef GREEDY_DRIVEN_BRANCH_AND_BOUND

        int64 sum = 0;
        for (vector<int64>::iterator pi = number_of_pages.begin(); pi != number_of_pages.end(); pi++)
        {
            sum += *pi;
        }

        double ideal = ((double)sum) / number_of_scribers;

        // Try the greedy algorithm - that will come up with some good estimate 
        int64 total_sum = 0;
        int64 current_sum = 0;
        int slash_count = 1;
        int64 greedy_value = 0;
        for (vector<int64>::iterator pi = number_of_pages.begin(); pi != number_of_pages.end(); pi++)
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
        int64 best_value = total_sum + 1; // impossible to be the best
        find_solution(number_of_pages, number_of_scribers, splits, 0, greedy_value, 0, total_sum, best_value, best_splits);

        unsigned int j = 0;
        for (unsigned int i = 0; i < number_of_pages.size(); i++)
        {
            if (j < best_splits.size() && i == best_splits[j])
            {
                cout << "/ ";
                j++;
            }
            cout << number_of_pages[i] << " ";
        }
        cout << endl;
#endif

#ifdef DYNAMIC_PROGRAMMING
        // Step 1: Pre-compute the running sum
        //         running_sums[n] = sum(i = 0 to n - 1) number_of_pages[i]
        // Therefore 
        //         sum(i = a to b) number_of_pages[i] 
        //       = sum(i = 0 to b) number_of_pages[i] - sum(i = 0 to a - 1) number_of_pages[i] 
        //       = running_sums[b + 1] - running_sum[a]
        vector<int64> running_sums;
        running_sums.push_back(0);
        int64 sum = 0;
        for (int b = 0; b < number_of_books; b++)
        {
            sum += number_of_pages[b];
            running_sums.push_back(sum);
        }

        // Step 2: Allocate the storage for optimal values
        //         optimal[p][q] = optimal cost for (q + 1) scribers to copy the last (p + 1) books, thanks to the stupid 0 based index convention
        int64** optimal = new int64*[number_of_books];
        for (int b = 0; b < number_of_books; b++)
        {
            optimal[b] = new int64[number_of_scribers];
        }

        // Step 3: Base case - 1 scriber must take all the remaining books
        for (int b = 0; b < number_of_books; b++)
        {
         // optimal[0][0] = sum(i = 8 to 8) number_of_pages[i] = running_sums[9] - running_sums[8];
         // optimal[1][0] = sum(i = 7 to 8) number_of_pages[i] = running_sums[9] - running_sums[7];
         // ...
            optimal[b][0] = running_sums[number_of_books] - running_sums[number_of_books - 1 - b];
        }

        // Step 4: Inductive step: 
        // I need to determine the formula for optimal[p][q]
        // I have (p + 1) books remaining, and (q + 1) scriber remaining
        // For the first scriber, it needs to take at least 1 book
        // The the remaining scribers, each of them need to take at least one book
        // There are n - p - 1 books already scribed, so the index of the first book is n - p - 1.
        // We must leave q books for the remaining q scribers, so we cannot take the n - q book
        // After taking i as the end index, there are n - i - 1 remaining books
        // Therefore, optimal[p][q] = min(over i in [n - p - 1, n - q)) max([sum(f = n - p - 1 to i) number_of_pages[f]]   , optimal[n - i - 2][q - 1]
        //                          = min(over i in [n - p - 1, n - q)) max([running_sums[i + 1] - running_sums[n - p - 1]], optimal[n - i - 2][q - 1]
        for (int q = 1; q < number_of_scribers; q++)
        {
            for (int p = 0; p < number_of_books; p++)
            {
                int64 currest_best_split_cost = running_sums[number_of_books] + 1;

                // We should be able to reduce this cost by using binary search
                for (int i = number_of_books - p - 1; i < number_of_books - q; i++)
                {
                    int64 cost_to_split_at_i = max(running_sums[i + 1] - running_sums[number_of_books - p - 1], optimal[number_of_books - i - 2][q - 1]);
                    currest_best_split_cost = min(currest_best_split_cost, cost_to_split_at_i);
                }
                optimal[p][q] = currest_best_split_cost;
            }
        }

        int64 solution = optimal[number_of_books - 1][number_of_scribers - 1];

        // Step 5: Find the splitting locations by Greedy
        //
        // The idea is to take as much book as I can 
        // I cannot take more book if my current value is larger than the solution, 
        // or if taking it will lead to insufficient book for the rest of the scribers
        // Do it from the back so that the first scriber will copy least
        // 
        // In fact I could have kept track of this in the dynamic programming algorithm
        // But this is just easier
        //
        stack<int> split_index;
        int64 current_sum = 0;
        int remaining_scriber_count = number_of_scribers - 1;
        for (int b = number_of_books - 1; b >= 0; b--)
        {
            if (current_sum + number_of_pages[b] <= solution && b >= remaining_scriber_count)
            {
                current_sum += number_of_pages[b];
            }
            else
            {
                remaining_scriber_count--;
                current_sum = 0;
                b++;
                split_index.push(b);
            }
        }


        // Step 6: Reverse and output
        int current_split_index = split_index.top();
        split_index.pop();
        for (int b = 0; b < number_of_books; b++)
        {
            if (b == current_split_index)
            {
                cout << "/ ";
                cout << number_of_pages[b];
                if (split_index.size() > 0)
                {
                    current_split_index = split_index.top();
                    split_index.pop();
                }
                else {
                    current_split_index = -1;
                }
            }
            else
            {
                cout << number_of_pages[b];
            }
            if (b != number_of_books - 1)
            {
                cout << " ";
            }
        }
        cout << endl;


        for (int b = 0; b < number_of_books; b++)
        {
            delete[] optimal[b];
        }
        delete[] optimal;

#endif
    }
    return 0;
}