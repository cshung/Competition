#include "stdafx.h"

// https://leetcode.com/problems/partition-labels/

#include "LEET_PARTITION_LABELS.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_PARTITION_LABELS
{
    class Solution
    {
    public:
        vector<int> partitionLabels(string s)
        {
            vector<int> last(26);
            vector<int> result;
            for (int i = 0; i < s.length(); i++)
            {
                last[s[i] - 'a'] = i;
            }
            bool started = false;
            int l;
            int r;
            for (int i = 0; i < s.length(); i++)
            {
                if (!started)
                {
                    started = true;
                    l = i;
                    r = 0;
                }
                r = max(last[s[i] - 'a'], r);
                if (r == i)
                {
                    started = false;
                    result.push_back(r - l + 1);
                }
            }
            return result;
        }
    };
};

using namespace _LEET_PARTITION_LABELS;

int LEET_PARTITION_LABELS()
{
    Solution s;
    auto answers = s.partitionLabels("ababcbacadefegdehijhklij");
    for (auto answer : answers)
    {
        cout << answer << " ";
    }
    return 0;
}