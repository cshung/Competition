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

        // 3rd, find the minimum dsi schedule

        vector<vector<vector<int>>> dsi_of_completed_lecture;
        vector<vector<int>> best_dsi_if_lecture_ends_with_topic;

        vector<vector<vector<bool>>> topic_can_ends;
        vector<vector<bool>> lecture_can_ends; 

        dsi_of_completed_lecture.resize(number_of_topics);
        best_dsi_if_lecture_ends_with_topic.resize(number_of_topics);
        lecture_can_ends.resize(number_of_topics);
        topic_can_ends.resize(number_of_topics);

        // Step 3.1 - just allocation
        for (int topic = 0; topic < number_of_topics; topic++)
        {
            dsi_of_completed_lecture[topic].resize(number_of_lectures);
            best_dsi_if_lecture_ends_with_topic[topic].resize(number_of_lectures);
            topic_can_ends[topic].resize(number_of_lectures);
            lecture_can_ends[topic].resize(number_of_lectures);
            for (int lecture = 0; lecture < number_of_lectures; lecture++)
            {
                dsi_of_completed_lecture[topic][lecture].resize(lecture_length + 1);
                topic_can_ends[topic][lecture].resize(lecture_length + 1);
            }
        }

        // Dynamic programming, with time proportional to num_topics * num_lecture * lecture_time
        //
        // TODO, maybe able to leverage the forward backward planning above to further reduce execution time
        // after all looping through the infeasible is meaningless
        //
        for (int topic = 0; topic < number_of_topics; topic++)
        {
            int topic_length = topic_lengths[topic];
            for (int lecture = 0; lecture < number_of_lectures; lecture++)
            {
                lecture_can_ends[topic][lecture] = false;
                for (int time = 0; time <= lecture_length; time++)
                {
                    topic_can_ends[topic][lecture][time] = false;
                    if (topic == 0)
                    {
                        if ((lecture == 0) && (time == topic_length))
                        {
                            dsi_of_completed_lecture[topic][lecture][time] = 0; 
                            best_dsi_if_lecture_ends_with_topic[topic][lecture] = current_lecture_dsi(lecture_length - time, c);

                            topic_can_ends[topic][lecture][time] = true;
                            lecture_can_ends[topic][lecture] = true;
#ifdef LOG
                            cout << "It is possible to end topic " << topic << " at lecture " << lecture << " at time " << time << "." << endl;
                            cout << "The accumulated dsi is " << dsi_of_completed_lecture[topic][lecture][time] << "." << endl;
                            cout << "If the lecture ends here, the best dsi will be " << best_dsi_if_lecture_ends_with_topic[topic][lecture] << endl;
                            cout << endl;
#endif
                        }
                    }
                    else
                    {
                        if (time >= topic_length)
                        {
                            if (topic_can_ends[topic - 1][lecture][time - topic_length])
                            {
                                dsi_of_completed_lecture[topic][lecture][time] = dsi_of_completed_lecture[topic - 1][lecture][time - topic_length];
                                int new_dsi_value = dsi_of_completed_lecture[topic][lecture][time] + current_lecture_dsi(lecture_length - time, c);
                                if (!lecture_can_ends[topic][lecture])
                                {
                                    best_dsi_if_lecture_ends_with_topic[topic][lecture] = new_dsi_value;
                                }
                                else
                                {
                                    best_dsi_if_lecture_ends_with_topic[topic][lecture] = min(best_dsi_if_lecture_ends_with_topic[topic][lecture], new_dsi_value); 
                                }

                                topic_can_ends[topic][lecture][time] = true;
                                lecture_can_ends[topic][lecture] = true;
#ifdef LOG
                                cout << "It is possible to end topic " << topic << " at lecture " << lecture << " at time " << time << "." << endl;
                                cout << "The accumulated dsi is " << dsi_of_completed_lecture[topic][lecture][time] << "." << endl;
                                cout << "If the lecture ends here, the best dsi will be " << best_dsi_if_lecture_ends_with_topic[topic][lecture] << endl;
                                cout << endl;
#endif
                            }
                            if (time == topic_length && lecture > 0 && lecture_can_ends[topic - 1][lecture - 1])
                            {
                                dsi_of_completed_lecture[topic][lecture][time] = best_dsi_if_lecture_ends_with_topic[topic - 1][lecture - 1];

                                int new_dsi_value = dsi_of_completed_lecture[topic][lecture][time] + current_lecture_dsi(lecture_length - time, c);
                                if (!lecture_can_ends[topic][lecture])
                                {
                                    best_dsi_if_lecture_ends_with_topic[topic][lecture] = new_dsi_value;
                                }
                                else
                                {
                                    best_dsi_if_lecture_ends_with_topic[topic][lecture] = min(best_dsi_if_lecture_ends_with_topic[topic][lecture], new_dsi_value); 
                                }

                                topic_can_ends[topic][lecture][time] = true;
                                lecture_can_ends[topic][lecture] = true;
#ifdef LOG
                                cout << "It is possible to end topic " << topic << " at lecture " << lecture << " at time " << time << "." << endl;
                                cout << "The accumulated dsi is " << dsi_of_completed_lecture[topic][lecture][time] << "." << endl;
                                cout << "If the lecture ends here, the best dsi will be " << best_dsi_if_lecture_ends_with_topic[topic][lecture] << endl;
                                cout << endl;
#endif
                            }
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
        cout << "Total dissatisfaction index: " << best_dsi_if_lecture_ends_with_topic[number_of_topics - 1][number_of_lectures - 1] << endl;
    }

    return 0;
}