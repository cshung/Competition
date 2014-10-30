#include "stdafx.h"

// http://uva.onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=1381

#include "UVa10440.h"

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

struct UVa10440_state
{
public:
    UVa10440_state(int time, int processed_cars, int pending_cars, int trip_count) : time(time), processed_cars(processed_cars), pending_cars(pending_cars), trip_count(trip_count)
    {

    }
    int time;
    int processed_cars;
    int pending_cars;
    int trip_count;
};

// return 1  if left priority > right
// return 0  if left priority = right
// return -1 if left priority < right
int compare_priority(const UVa10440_state* left, const UVa10440_state* right)
{
    if (left->time < right->time)
    {
        return 1;
    }
    else if (left->time > right->time)
    {
        return -1;
    }
    if (left->trip_count < right->trip_count)
    {
        return 1;
    }
    else if (left->trip_count > right->trip_count)
    {
        return -1;
    }

    return 0;
}

void bubble_down(vector<UVa10440_state*>& priority_queue, int current_index, int& size)
{
    while (true)
    {
        int left_child_index = (current_index + 1) * 2 - 1;
        int right_child_index = left_child_index + 1;
        bool has_left = left_child_index < size;
        bool has_right = right_child_index < size;

        if (has_left && has_right)
        {
            if (compare_priority(priority_queue[left_child_index], priority_queue[right_child_index]) == 1)
            {
                if (compare_priority(priority_queue[left_child_index], priority_queue[current_index]) == 1)
                {
                    UVa10440_state* temp = priority_queue[current_index];
                    priority_queue[current_index] = priority_queue[left_child_index];
                    priority_queue[left_child_index] = temp;
                    current_index = left_child_index;
                }
                else
                {
                    break;
                }
            }
            else
            {
                if (compare_priority(priority_queue[right_child_index], priority_queue[current_index]) == 1)
                {
                    UVa10440_state* temp = priority_queue[current_index];
                    priority_queue[current_index] = priority_queue[right_child_index];
                    priority_queue[left_child_index] = temp;
                    current_index = right_child_index;
                }
                else
                {
                    break;
                }
            }
        }
        else if (has_left)
        {
            if (compare_priority(priority_queue[left_child_index], priority_queue[current_index]) == 1)
            {
                UVa10440_state* temp = priority_queue[current_index];
                priority_queue[current_index] = priority_queue[left_child_index];
                priority_queue[left_child_index] = temp;
                current_index = left_child_index;
            }
            else
            {
                break;
            }
        }
        else
        {
            break;
        }
    }
}

UVa10440_state* delete_min(vector<UVa10440_state*>& priority_queue, int& size)
{
    UVa10440_state* result = priority_queue[0];
    priority_queue[0] = priority_queue[size - 1];
    size--;
    bubble_down(priority_queue, 0, size);
    return result;
}

void insert(vector<UVa10440_state*>& priority_queue, int& size, UVa10440_state* new_item)
{
    if (priority_queue.size() == size)
    {
        priority_queue.push_back(new_item);
    }
    else
    {
        priority_queue[size] = new_item;
    }
    size++;

    int current_index = size - 1;
    while (current_index > 0)
    {
        int parent_index = (current_index + 1) / 2 - 1;
        int compare_result = compare_priority(priority_queue[current_index], priority_queue[parent_index]);

        if (compare_result == 1)
        {
            UVa10440_state* temp = priority_queue[current_index];
            priority_queue[current_index] = priority_queue[parent_index];
            priority_queue[parent_index] = temp;
            current_index = parent_index;
        }
        else if (compare_result == 0)
        {
            priority_queue[current_index] = priority_queue[size - 1];
            size--;
            bubble_down(priority_queue, current_index, size);
        }
        else
        {
            break;
        }
    }
}


int UVa10440()
{
    int number_of_test_cases = 0;
    cin >> number_of_test_cases;
    for (int c = 0; c < number_of_test_cases; c++)
    {
        int ferry_capacity;
        int trip_time;
        int number_of_cars;
        cin >> ferry_capacity;
        cin >> trip_time;
        cin >> number_of_cars;
        vector<int> arrival_times;
        for (int i = 0; i < number_of_cars; i++)
        {
            int arrival_time;
            cin >> arrival_time;
            arrival_times.push_back(arrival_time);
        }

        vector<UVa10440_state*> priority_queue;

        int size = 1;
        priority_queue.push_back(new UVa10440_state(-1, 0, 0, 0));

        while (size > 0)
        {
            // Step 1: Find the current best state
            UVa10440_state* current_best = delete_min(priority_queue, size);

            // cout << "Processing current best at time " << current_best->time << " with " << current_best->processed_cars << " processed and " << current_best->pending_cars << " pending with " << current_best->trip_count << " trips." << endl;

            if (current_best->processed_cars == number_of_cars)
            {
                cout << current_best->time - trip_time << " " << current_best->trip_count << endl;
                break;
            }

            // Step 2: What moves are available
            if (current_best->pending_cars > 0)
            {
                // In this case, we can consider moving right now
                int new_time = current_best->time + 2 * trip_time;
                int new_processed_cars = current_best->processed_cars + min(current_best->pending_cars, ferry_capacity);
                int new_unseen_cars = number_of_cars - (upper_bound(arrival_times.begin(), arrival_times.end(), new_time) - arrival_times.begin());
                int new_pending_cars = number_of_cars - new_processed_cars - new_unseen_cars;
                int new_trip_count = current_best->trip_count + 1;
                insert(priority_queue, size, new UVa10440_state(new_time, new_processed_cars, new_pending_cars, new_trip_count));
            }


            if (current_best->pending_cars < ferry_capacity)
            {
                // In this case we can consider waiting
                unsigned int next_move_index = upper_bound(arrival_times.begin(), arrival_times.end(), current_best->time) - arrival_times.begin();
                if (next_move_index < arrival_times.size())
                {
                    insert(priority_queue, size, new UVa10440_state(arrival_times[next_move_index], current_best->processed_cars, current_best->pending_cars + 1, current_best->trip_count));
                }
            }

            // cout << endl;
            // cout << "The priority queue has " << size << " elements after the moves." << endl;
            // for (unsigned int p = 0; p < priority_queue.size(); p++)
            // {
            //     if (priority_queue[p] == NULL)
            //     {
            //         cout << "(null)" << endl;
            //     }
            //     else
            //     {
            //         cout << priority_queue[p]->time << ", " << priority_queue[p]->processed_cars << ", " << priority_queue[p]->pending_cars << ", " << priority_queue[p]->trip_count << endl;
            //     }
            // }
            // cout << endl;
        }
    }
    return 0;
}

