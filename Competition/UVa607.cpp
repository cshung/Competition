#include "stdafx.h"

// http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=548

#include "UVa607.h"

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int dsi(int remaining_time, int c)
{
    if (remaining_time == 0)
    {
        return 0;
    }
    else if (remaining_time <= 10)
    {
        return -c;
    }
    else
    {
        return (remaining_time - 10) * (remaining_time - 10);
    }
}

class UVa607_State
{
public:
    int scheduled_topics;
    int dsi;
    int lecture_index;
    int remaining_time;
};

int UVa607()
{
    int test_case_number = 0;
    while (true)
    {
        test_case_number++;

        int number_of_topics;
        int lecture_length;
        int c;
        vector<int> topic_lengths;

        cin >> number_of_topics;
        if (number_of_topics == 0)
        {
            break;
        }

        topic_lengths.resize(number_of_topics);
        cin >> lecture_length;
        cin >> c;
        for (int i = 0; i < number_of_topics; i++)
        {
            int topic_length;
            cin >> topic_length;
            topic_lengths[i] = topic_length;
        }

        // 1st, schedule the topics greedily forward, this gives the minimum lecture index for a topic
        vector<int> first_feasible_index;
        first_feasible_index.resize(number_of_topics);
        int lecture_index = 0;
        int remaining_lecture_time = lecture_length;
        for (int t = 0; t < number_of_topics; t++)
        {
            int topic_length = topic_lengths[t];
            if (remaining_lecture_time >= topic_lengths[t])
            {
                first_feasible_index[t] = lecture_index;
                remaining_lecture_time -= topic_length;
            }
            else
            {
                lecture_index++;
                first_feasible_index[t] = lecture_index;
                remaining_lecture_time = lecture_length - topic_length;
            }
        }

        int number_of_lectures = lecture_index + 1;

        // 2nd, schedule the topics greedily backwards, this gives the maximum lecture index for a topic
        vector<int> last_feasible_index;
        last_feasible_index.resize(number_of_topics);
        lecture_index = number_of_lectures - 1;
        remaining_lecture_time = lecture_length;
        for (int t = number_of_topics - 1; t >= 0; t--)
        {
            int topic_length = topic_lengths[t];
            if (remaining_lecture_time >= topic_lengths[t])
            {
                last_feasible_index[t] = lecture_index;
                remaining_lecture_time -= topic_length;
            }
            else
            {
                lecture_index--;
                last_feasible_index[t] = lecture_index;
                remaining_lecture_time = lecture_length - topic_length;
            }
        }

        /*
        for (int t = 0; t < number_of_topics; t++)
        {
            cout << first_feasible_index[t] << " ";
        }
        cout << endl;

        for (int t = 0; t < number_of_topics; t++)
        {
            cout << last_feasible_index[t] << " ";
        }
        cout << endl;
        */

        bool first = true;
        int minimum_dsi = 0;

        // 3rd, model the scheduling as a graph
        queue<UVa607_State*> bfs_queue;
        UVa607_State* initial_state = new UVa607_State();
        initial_state->scheduled_topics = 0;
        initial_state->lecture_index = 0;
        initial_state->remaining_time = lecture_length;
        initial_state->dsi = 0;
        bfs_queue.push(initial_state);
        while (bfs_queue.size() > 0)
        {
            UVa607_State* current_state = bfs_queue.front();
            bfs_queue.pop();
            if (current_state->scheduled_topics == 0)
            {
                // For the 1st topic, we have to schedule it in the 1st lecture
                UVa607_State* next_state = new UVa607_State();
                next_state->lecture_index = 0;
                next_state->scheduled_topics = 1;
                next_state->remaining_time = lecture_length - topic_lengths[0];
                next_state->dsi = 0;
                // cout << next_state->lecture_index << ", " << next_state->scheduled_topics << ", " << next_state->remaining_time << ", " << next_state->dsi << endl;
                bfs_queue.push(next_state);
            }
            else
            {
                int topic_index = current_state->scheduled_topics;
                if (topic_index < number_of_topics)
                {
                    int topic_length = topic_lengths[topic_index];
                    // Is it feasible to schedule the next lecture on the current lecture?
                    if ((first_feasible_index[topic_index] <= current_state->lecture_index) && (current_state->lecture_index <= last_feasible_index[topic_index]))
                    {
                        if (current_state->remaining_time >= topic_length)
                        {
                            UVa607_State* next_state = new UVa607_State();
                            next_state->lecture_index = current_state->lecture_index;
                            next_state->scheduled_topics = current_state->scheduled_topics + 1;
                            next_state->remaining_time = current_state->remaining_time - topic_length;
                            next_state->dsi = current_state->dsi;
                            // cout << next_state->lecture_index << ", " << next_state->scheduled_topics << ", " << next_state->remaining_time << ", " << next_state->dsi << endl;
                            bfs_queue.push(next_state);
                        }
                    }
                    if ((first_feasible_index[topic_index] <= (current_state->lecture_index + 1)) && ((current_state->lecture_index + 1) <= last_feasible_index[topic_index]))
                    {
                        UVa607_State* next_state = new UVa607_State();
                        next_state->lecture_index = current_state->lecture_index + 1;
                        next_state->scheduled_topics = current_state->scheduled_topics + 1;
                        next_state->remaining_time = lecture_length - topic_length;
                        next_state->dsi = current_state->dsi + dsi(current_state->remaining_time, c);
                        // cout << next_state->lecture_index << ", " << next_state->scheduled_topics << ", " << next_state->remaining_time << ", " << next_state->dsi << endl;
                        bfs_queue.push(next_state);
                    }
                }
                else
                {
                    int total_dsi = current_state->dsi + dsi(current_state->remaining_time, c);
                    if (first)
                    {
                        minimum_dsi = total_dsi;
                        first = false;
                    }
                    else
                    {
                        if (total_dsi < minimum_dsi)
                        {
                            minimum_dsi = total_dsi;
                        }
                    }
                }
            }
        }

        if (test_case_number != 1)
        {
            cout << endl;
        }
        cout << "Case " << test_case_number << ":" << endl;
        cout << "Minimum number of lectures: " << number_of_lectures << endl;
        cout << "Total dissatisfaction index: " << minimum_dsi << endl;
    }

    return 0;
}