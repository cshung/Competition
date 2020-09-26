#include "stdafx.h"

// https://leetcode.com/problems/task-scheduler/

#include "LEET_TASK_SCHEDULER.h"
#include <map>
#include <iostream>
#include <vector>
#include <stack>
#include <map>
#include <queue>
#include <string>

using namespace std;

namespace _LEET_TASK_SCHEDULER
{
    class Solution
    {
    public:
        int leastInterval(vector<char>& tasks, int n)
        {
            if (tasks.empty())
            {
                return 0;
            }
            int frequencies[26];
            for (int i = 0; i < 26; i++)
            {
                frequencies[i] = 0;
            }
            for (auto task : tasks)
            {
                int t = task - 'A';
                frequencies[t]++;
            }
            map<int, stack<int>> active_tasks_by_frequencies;
            for (int i = 0; i < 26; i++)
            {
                if (frequencies[i] != 0)
                {
                    auto probe = active_tasks_by_frequencies.find(frequencies[i]);
                    if (probe == active_tasks_by_frequencies.end())
                    {
                        active_tasks_by_frequencies.insert(make_pair(frequencies[i], stack<int>()));
                    }
                    active_tasks_by_frequencies[frequencies[i]].push(i);
                }
            }

            queue<int> cooling;
            int cooling_count = 0;
            int t = 0;
            while (true)
            {
                if (active_tasks_by_frequencies.size() > 0)
                {
                    int active_max_frequency = active_tasks_by_frequencies.rbegin()->first;
                    stack<int>& next_tasks = active_tasks_by_frequencies[active_max_frequency];
                    int next_task = next_tasks.top();
                    next_tasks.pop();
                    if (next_tasks.empty())
                    {
                        active_tasks_by_frequencies.erase(active_max_frequency);
                    }
                    frequencies[next_task]--;
                    if (frequencies[next_task] > 0)
                    {
                        cooling.push(next_task);
                        cooling_count++;
                    }
                    else
                    {
                        cooling.push(26);
                    }
                }
                else
                {
                    if (cooling_count == 0)
                    {
                        break;
                    }
                    cooling.push(26);
                }
                t++;
                if (cooling.size() > n)
                {
                    int cooled = cooling.front();
                    cooling.pop();
                    if (cooled != 26)
                    {
                        int frequency = frequencies[cooled];
                        auto probe = active_tasks_by_frequencies.find(frequency);
                        if (probe == active_tasks_by_frequencies.end())
                        {
                            active_tasks_by_frequencies.insert(make_pair(frequency, stack<int>()));
                        }
                        active_tasks_by_frequencies[frequency].push(cooled);
                        cooling_count--;
                    }
                }
            }
            return t;
        }
    };
};

using namespace _LEET_TASK_SCHEDULER;

int LEET_TASK_SCHEDULER()
{
    Solution solution;
    char case1_array[] = { 'A','A','A','B','B','B' };
    char case2_array[] = { 'A','A','A','B','B','B' };
    char case3_array[] = { 'A','A','A','A','A','A','B','C','D','E','F','G' };
    vector<char> case1(case1_array, case1_array + _countof(case1_array));
    vector<char> case2(case2_array, case2_array + _countof(case2_array));
    vector<char> case3(case3_array, case3_array + _countof(case3_array));
    cout << solution.leastInterval(case1, 2) << endl;
    cout << solution.leastInterval(case2, 0) << endl;
    cout << solution.leastInterval(case3, 2) << endl;
    return 0;
}