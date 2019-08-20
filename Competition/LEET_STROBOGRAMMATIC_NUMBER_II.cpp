#include "stdafx.h"

// https://leetcode.com/problems/strobogrammatic-number-ii/

#include "LEET_STROBOGRAMMATIC_NUMBER_II.h"
#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_STROBOGRAMMATIC_NUMBER_II
{
    class Solution
    {
    public:
        vector<string> findStrobogrammatic(int n)
        {
            int map[] = { 0, 1, -1, -1, -1, -1, 9, -1, 8, 6 };
            int valid[] = { 0, 1, 6, 8, 9 };
            int mirror[] = { 0, 1, 8 };
            int half = n / 2;
            int m = 1;
            for (int i = 0; i < half; i++)
            {
                m *= 5;
            }
            if (n % 2 == 1)
            {
                m *= 3;
            }
            vector<string> result;
            for (int i = 0; i < m; i++)
            {
                vector<int> answer;
                int acc = i;
                if (n > 1 && acc % 5 == 0)
                {
                    continue;
                }
                for (int d = 0; d < half; d++)
                {
                    answer.push_back(acc % 5);
                    acc /= 5;
                }
                ostringstream oss;
                for (int i = 0; i < half; i++)
                {
                    oss << valid[answer[i]];
                }
                if (n % 2 == 1)
                {
                    oss << mirror[acc];
                }
                for (int i = 0; i < half; i++)
                {
                    oss << map[valid[answer[half - i - 1]]];
                }
                result.push_back(oss.str());
            }
            sort(result.begin(), result.end());
            return result;
        }
    };
};

using namespace _LEET_STROBOGRAMMATIC_NUMBER_II;

int LEET_STROBOGRAMMATIC_NUMBER_II()
{
    Solution solution;
    vector<string> answers = solution.findStrobogrammatic(2);
    for (auto answer : answers)
    {
        cout << answer << endl;
    }
    return 0;
}