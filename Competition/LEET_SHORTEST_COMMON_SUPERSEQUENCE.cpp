#include "stdafx.h"

// https://leetcode.com/problems/shortest-common-supersequence/

#include "LEET_SHORTEST_COMMON_SUPERSEQUENCE.h"
#include <stack>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_SHORTEST_COMMON_SUPERSEQUENCE
{
    class Solution
    {
    public:
        string shortestCommonSupersequence(string str1, string str2) {
            vector<vector<int>> choice;
            vector<vector<int>> cost;
            choice.resize(str1.size() + 1);
            cost.resize(str1.size() + 1);
            for (int i = 0; i <= str1.length(); i++)
            {
                choice[i].resize(str2.length() + 1);
                cost[i].resize(str2.length() + 1);
            }
            for (int j = 1; j <= str2.length(); j++)
            {
                choice[0][j] = 2;
                cost[0][j] = j;
            }
            for (int i = 1; i <= str1.length(); i++)
            {
                choice[i][0] = 1;
                cost[i][0] = i;
            }
            choice[0][0] = 0;
            cost[0][0] = 0;

            for (int i = 1; i <= str1.length(); i++)
            {
                for (int j = 1; j <= str2.length(); j++)
                {
                    if (str1[i - 1] == str2[j - 1])
                    {
                        choice[i][j] = 0;
                        cost[i][j] = cost[i - 1][j - 1] + 1;
                    }
                    else
                    {
                        if (cost[i][j - 1] < cost[i - 1][j])
                        {
                            choice[i][j] = 2;
                            cost[i][j] = cost[i][j - 1] + 1;
                        }
                        else
                        {
                            choice[i][j] = 1;
                            cost[i][j] = cost[i - 1][j] + 1;
                        }
                    }
                }
            }
            stack<char> answer;
            int i = (int)str1.length();
            int j = (int)str2.length();
            while (i > 0 || j > 0)
            {
                if (choice[i][j] == 1)
                {
                    i--;
                    answer.push(str1[i]);
                }
                else if (choice[i][j] == 2)
                {
                    j--;
                    answer.push(str2[j]);
                }
                else
                {
                    i--;
                    j--;
                    answer.push(str1[i]);
                }
            }
            ostringstream oss;
            while (answer.size() > 0)
            {
                oss << answer.top();
                answer.pop();
            }
            return oss.str();
        }
    };


};

using namespace _LEET_SHORTEST_COMMON_SUPERSEQUENCE;

int LEET_SHORTEST_COMMON_SUPERSEQUENCE()
{
    Solution solution;
    cout << solution.shortestCommonSupersequence("abac", "cab") << endl;
    return 0;
}