#include "stdafx.h"

// http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=47

#include "UVa111.h"

#include <iostream>
#include <vector>
#include <map>

using namespace std;

int UVa111()
{
    int num_events;
    cin >> num_events;
    map<int, int> actual_order;
    for (int i = 0; i < num_events; i++)
    {
        int event_id;
        cin >> event_id;
        actual_order.insert(pair<int, int>(event_id, i));
    }

    while (true)
    {
        vector<int> student_answer;
        for (int i = 0; i < num_events; i++)
        {
            int student_answer_value;
            cin >> student_answer_value;
            if (cin.eof())
            {
                return 0;
            }
            student_answer.push_back(actual_order[student_answer_value]);
        }

        for (int i = 0; i < num_events; i++)
        {
            cout << student_answer[i] << " ";
        }
        cout << endl;

        vector<int> score;
        score.resize(num_events);
        score[0] = 1;
        int max_score = 1;
        for (int i = 1; i < num_events; i++)
        {
            int best_score = 1;
            for (int j = 0; j < i; j++)
            {
                if (student_answer[i] > student_answer[j])
                {
                    int current_score = score[j] + 1;
                    if (current_score > best_score)
                    {
                        best_score = current_score;
                    }
                }
            }
            score[i] = best_score;
            if (best_score > max_score)
            {
                max_score = best_score;
            }
        }
        cout << max_score << endl;
    }
}