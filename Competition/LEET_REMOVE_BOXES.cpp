#include "stdafx.h"

// https://leetcode.com/problems/remove-boxes

#include "LEET_REMOVE_BOXES.h"
#include <map>
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_REMOVE_BOXES
{
    class Solution
    {
    public:
        int removeBoxes(vector<int>& boxes)
        {
            if (boxes.size() == 0)
            {
                return 0;
            }

            int n = (int)boxes.size();

            vector<vector<vector<pair<int, int>>>> answers;
            vector<vector<int>> best;
            answers.resize(n);
            best.resize(n);
            for (int i = 0; i < n; i++)
            {
                answers[i].resize(n);
                best[i].resize(n);
                for (int j = 0; j < n; j++)
                {
                    best[i][j] = 0;
                }
            }

            for (int i = 0; i < n; i++)
            {
                answers[i][i].push_back(make_pair(1, 1));
                best[i][i] = 1;
            }

            for (int l = 2; l <= n; l++)
            {
                for (int s = 0; s + l - 1 < n; s++)
                {
                    int e = s + l - 1;
                    if (boxes[e] == boxes[e - 1])
                    {
                        for (auto d : answers[s][e - 1])
                        {
                            int len = d.first;
                            int pts = d.second;

                            int new_len = len + 1;
                            int new_pts = pts + 2 * len + 1;
                            answers[s][e].push_back(make_pair(new_len, new_pts));
                            best[s][e] = max(best[s][e], new_pts);
                        }
                    }
                    else
                    {
                        answers[s][e].push_back(make_pair(1, best[s][e - 1] + 1));
                        best[s][e] = best[s][e - 1] + 1;
                        for (int pe = e - 2; pe >= s; pe--)
                        {
                            if (boxes[e] == boxes[pe])
                            {
                                for (auto d : answers[s][pe])
                                {
                                    int len = d.first;
                                    int pts = d.second;

                                    int new_len = len + 1;
                                    int new_pts = best[pe + 1][e - 1] + pts + 2 * len + 1;
                                    answers[s][e].push_back(make_pair(new_len, new_pts));
                                    best[s][e] = max(best[s][e], new_pts);
                                }
                            }
                        }
                    }
                }
            }

            return best[0][n - 1];
        }
    };
};

using namespace _LEET_REMOVE_BOXES;

int LEET_REMOVE_BOXES()
{
    Solution solution;
    int test_array[] = { 1, 3, 2, 2, 2, 3, 4, 3, 1 };
    vector<int> test(test_array, test_array + _countof(test_array));
    cout << solution.removeBoxes(test) << endl;
    return 0;
}