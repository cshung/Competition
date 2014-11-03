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
    map<int, int> actual_event_rank;
    for (int event_id = 0; event_id < num_events; event_id++)
    {
        int event_rank;
        cin >> event_rank;
        actual_event_rank.insert(pair<int, int>(event_id, event_rank));
    }

    while (true)
    {
        vector<int> student_answer;
        map<int, int> student_event_id;
        for (int event_id = 0; event_id < num_events; event_id++)
        {
            int student_event_rank;
            cin >> student_event_rank;
            if (cin.eof())
            {
                return 0;
            }
            student_event_id.insert(pair<int, int>(student_event_rank, event_id));
        }
        for (int event_rank = 1; event_rank <= num_events; event_rank++)
        {
            student_answer.push_back(actual_event_rank[student_event_id[event_rank]]);
        }

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