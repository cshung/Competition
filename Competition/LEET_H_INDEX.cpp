#include "stdafx.h"

// https://leetcode.com/problems/h-index/

#include "LEET_H_INDEX.h"
#include <stack>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_H_INDEX
{
    class Solution {
    public:
        int hIndex(vector<int>& citations)
        {
            if (citations.size() == 0)
            {
                return 0;
            }
            vector<int> counters;
            counters.resize(citations.size() + 1);
            for (unsigned int i = 0; i < citations.size() + 1; i++)
            {
                counters[i] = 0;
            }

            for (unsigned int i = 0; i < citations.size(); i++)
            {
                unsigned int cites = citations[i];
                if (cites > citations.size())
                {
                    cites = citations.size();
                }
                if (cites > 0)
                {
                    counters[cites - 1]++;
                }
            }

            for (unsigned int i = citations.size(); i > 0; i--)
            {
                counters[i - 1] = counters[i] + counters[i - 1];
                if (counters[i - 1] >= i)
                {
                    return i;
                }
            }

            return 0;
        }
    };
};

using namespace _LEET_H_INDEX;

int LEET_H_INDEX()
{
    int case1[] = { 3, 0, 6, 1, 5 };
    int case2[] = { 1 };
    int case3[] = { 1, 1 };
    Solution solution;
    cout << solution.hIndex(vector<int>(case3, case3 + _countof(case3))) << endl;
    return 0;
}
