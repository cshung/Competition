#include "stdafx.h"

// http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=548

#include "UVa607.h"

#include <iostream>
#include <vector>
#include <queue>

#define LOG

using namespace std;

int current_lecture_dsi(int remaining_time, int c)
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
        vector<int> first_lecture_index;
        first_lecture_index.resize(number_of_topics);
        int lecture_index = 0;
        int remaining_lecture_time = lecture_length;
        for (int t = 0; t < number_of_topics; t++)
        {
            int topic_length = topic_lengths[t];
            if (remaining_lecture_time >= topic_lengths[t])
            {
                first_lecture_index[t] = lecture_index;
                remaining_lecture_time -= topic_length;
            }
            else
            {
                lecture_index++;
                first_lecture_index[t] = lecture_index;
                remaining_lecture_time = lecture_length - topic_length;
            }
        }

        int number_of_lectures = lecture_index + 1;

        // 2nd, schedule the topics greedily backwards, this gives the maximum lecture index for a topic
        vector<int> last_lecture_index;
        last_lecture_index.resize(number_of_topics);
        lecture_index = number_of_lectures - 1;
        remaining_lecture_time = lecture_length;
        for (int t = number_of_topics - 1; t >= 0; t--)
        {
            int topic_length = topic_lengths[t];
            if (remaining_lecture_time >= topic_lengths[t])
            {
                last_lecture_index[t] = lecture_index;
                remaining_lecture_time -= topic_length;
            }
            else
            {
                lecture_index--;
                last_lecture_index[t] = lecture_index;
                remaining_lecture_time = lecture_length - topic_length;
            }
        }

#ifdef LOG
        for (int t = 0; t < number_of_topics; t++)
        {
            cout << first_lecture_index[t] << " ";
        }
        cout << endl;

        for (int t = 0; t < number_of_topics; t++)
        {
            cout << last_lecture_index[t] << " ";
        }
        cout << endl;
#endif
        // 3rd, pre compute topic length sum to avoid calculating that later

        vector<int> topic_length_sums;
        topic_length_sums.resize(number_of_topics + 1);
        int topic_length_sum = 0;
        for (int topic = 0; topic < number_of_topics; topic++)
        {
            topic_length_sums[topic] = topic_length_sum;
            topic_length_sum += topic_lengths[topic];
        }
        topic_length_sums[number_of_topics] = topic_length_sum;


        vector<vector<bool> > lecture_can_ends;
        vector<vector<int> > best_dsi_if_ends;
        lecture_can_ends.resize(number_of_topics);
        best_dsi_if_ends.resize(number_of_topics);
        for (int topic = 0; topic < number_of_topics; topic++)
        {
            lecture_can_ends[topic].resize(number_of_lectures);
            best_dsi_if_ends[topic].resize(number_of_lectures);
        }

        for (int topic = 0; topic < number_of_topics; topic++)
        {
            for (int lecture = first_lecture_index[topic]; lecture <= last_lecture_index[topic]; lecture++)
            {
                lecture_can_ends[topic][lecture] = false;
                if (lecture != (number_of_lectures - 1) && topic != (number_of_topics - 1))
                {
                    if ((first_lecture_index[topic + 1] <= lecture + 1) && (lecture + 1 <= last_lecture_index[topic + 1]))
                    {
                        // This is not the last lecture, last topic, 
                        // so it is feasible to end the current lecture with the current topic
                        // if it is feasible to start the next lecture with the next topic
                        lecture_can_ends[topic][lecture] = true;
                    }
                }
                else
                {
                    if (topic == number_of_topics - 1)
                    {
                        // The last lecture has to end with the last topic
                        lecture_can_ends[topic][lecture] = true;
                    }
                }

                if (lecture_can_ends[topic][lecture])
                {
#ifdef LOG
                    cout << "Topic " << topic << " can ends lecture " << lecture << endl;
#endif
                    if (lecture == 0)
                    {
                        int used_time = topic_length_sums[topic + 1];
                        int dsi = current_lecture_dsi(lecture_length - used_time, c);
                        best_dsi_if_ends[topic][lecture] = dsi;
#ifdef LOG
                        cout << "The best dsi ending lecture " << lecture << " with topic " << topic << " is " << best_dsi_if_ends[topic][lecture] << endl;
#endif
                        
                    }
                    else
                    {
                        bool first = true;
                        int best_dsi = 10086;
                        // TODO: consider indexing instead of looping through
                        for (int last_ending_topic = 0; last_ending_topic < number_of_topics; last_ending_topic++)
                        {
                            if (lecture_can_ends[last_ending_topic][lecture - 1])
                            {
                                // Consiedr the current lecture runs from last_ending_topic + 1 to topic
                                int used_time = topic_length_sums[topic + 1] - topic_length_sums[last_ending_topic + 1];
                                if (used_time <= lecture_length)
                                {
                                    int dsi = best_dsi_if_ends[last_ending_topic][lecture - 1] + current_lecture_dsi(lecture_length - used_time, c);
                                    if (first)
                                    {
                                        best_dsi = dsi;
                                        first = false;
                                    }
                                    else
                                    {
                                        best_dsi = min(dsi, best_dsi);
                                    }
                                }
                            }
                        }
                        if (!first)
                        {
                            best_dsi_if_ends[topic][lecture] = best_dsi;
#ifdef LOG
                            cout << "The best dsi ending lecture " << lecture << " with topic " << topic << " is " << best_dsi_if_ends[topic][lecture] << endl;
#endif
                        }
                    }
                }
            }
        }
        

        int minimum_dsi = best_dsi_if_ends[number_of_topics - 1][number_of_lectures - 1];

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