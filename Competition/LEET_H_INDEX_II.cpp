#include "stdafx.h"

// https://leetcode.com/problems/h-index-ii/

#include "LEET_H_INDEX_II.h"
#include <map>
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_H_INDEX_II
{
    class Solution
    {
    public:
        int hIndex(vector<int>& citations)
        {
            int n = (int)citations.size();
            int l = 0;
            int r = n;
            int result = 0;
            while (true)
            {
                if (r <= l)
                {
                    break;
                }
                int m = (l + r) / 2;
                int h = n - m;
                if (citations[m] < h)
                {
                    l = m + 1;
                }
                else
                {
                    result = max(h, result);
                    r = m;
                }
            }
            return result;
        }
    };
};

using namespace _LEET_H_INDEX_II;

int LEET_H_INDEX_II()
{
    Solution solution;
    int citations_array[] = { 0, 1, 3, 5, 6 };
    vector<int> citations(citations_array, citations_array + _countof(citations_array));
    cout << solution.hIndex(citations) << endl;
    return 0;
}