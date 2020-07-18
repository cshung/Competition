#include "stdafx.h"

// https://leetcode.com/problems/course-schedule-ii/

#include "LEET_COURSE_SCHEDULE_II.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_COURSE_SCHEDULE_II
{
    class Solution
    {
    public:
        vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites)
        {
            vector<vector<int>> adjacency_list(numCourses);
            for (auto edge : prerequisites)
            {
                adjacency_list[edge[1]].push_back(edge[0]);
            }
            vector<int> visited(numCourses, 0);
            vector<int> result;
            bool hasCycle = false;
            for (int i = 0; i < numCourses; i++)
            {
                if (!visited[i])
                {
                    if (!dfs(adjacency_list, i, visited, result))
                    {
                        hasCycle = true;
                        break;
                    }
                }
            }
            if (hasCycle)
            {
                result.clear();
            }
            else
            {
                reverse(result.begin(), result.end());
            }
            return result;
        }
    private:
        bool dfs(vector<vector<int>>& adjacency_list, int i, vector<int>& visited, vector<int>& result)
        {
            visited[i] = 1;
            for (auto neighbor : adjacency_list[i])
            {
                if (visited[neighbor] == 0)
                {
                    if (!dfs(adjacency_list, neighbor, visited, result))
                    {
                        return false;
                    }
                }
                else if (visited[neighbor] == 1)
                {
                    return false;
                }
            }
            visited[i] = 2;
            result.push_back(i);
            return true;
        }
    };

};

using namespace _LEET_COURSE_SCHEDULE_II;

int LEET_COURSE_SCHEDULE_II()
{
    vector<vector<int>> prerequisites;
    Solution s;
    prerequisites.resize(4);
    prerequisites[0].push_back(1); prerequisites[0].push_back(0);
    prerequisites[1].push_back(2); prerequisites[1].push_back(0);
    prerequisites[2].push_back(3); prerequisites[2].push_back(1);
    prerequisites[3].push_back(3); prerequisites[3].push_back(2);
    for (auto answer : s.findOrder(4, prerequisites))
    {
        cout << answer << " ";
    }
    cout << endl;
    return 0;
}