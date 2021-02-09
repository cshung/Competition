#include "stdafx.h"

// https://leetcode.com/problems/shortest-distance-to-a-character/

#include "LEET_SHORTEST_DISTANCE_TO_A_CHARACTER.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_SHORTEST_DISTANCE_TO_A_CHARACTER
{
    class Solution
    {
    public:
        vector<int> shortestToChar(string s, char c)
        {
            vector<int> ld(s.length());
            vector<int> rd(s.length());
            vector<int> ans(s.length());
            int lseen = -1;
            int rseen = -1;
            int n = s.length();
            for (int i = 0; i < n; i++)
            {
                int lp = i;
                int rp = n - i - 1;
                if (s[lp] == c) { lseen = lp; }
                if (s[rp] == c) { rseen = rp; }
                ld[lp] = (lseen == -1) ? n : (lp - lseen);
                rd[rp] = (rseen == -1) ? n : (rseen - rp);
            }

            for (int i = 0; i < n; i++)
            {
                ans[i] = min(ld[i], rd[i]);
            }
            return ans;
        }
    };
};

using namespace _LEET_SHORTEST_DISTANCE_TO_A_CHARACTER;

int LEET_SHORTEST_DISTANCE_TO_A_CHARACTER()
{
    Solution solution;
    string s = "loveleetcode";
    char c = 'e';
    vector<int> answer = solution.shortestToChar(s, c);
    for (int i = 0; i < answer.size(); i++)
    {
        cout << answer[i] << " ";
    }
    cout << endl;
    return 0;
}
