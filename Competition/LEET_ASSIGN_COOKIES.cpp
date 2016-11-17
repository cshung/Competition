#include "stdafx.h"

// https://leetcode.com/problems/assign-cookies/

#include "LEET_ASSIGN_COOKIES.h"
#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_ASSIGN_COOKIES
{
    class Solution
    {
    public:
        int findContentChildren(vector<int>& g, vector<int>& s)
        {
            sort(g.begin(), g.end());
            sort(s.begin(), s.end());
            size_t gp = 0;
            size_t sp = 0;
            int c = 0;
            while (gp < g.size() && sp < s.size())
            {
                if (s[sp] >= g[gp])
                {
                    sp++;
                    gp++;
                    c++;
                }
                else
                {
                    sp++;
                }
            }

            return c;
        }
    };
};

using namespace _LEET_ASSIGN_COOKIES;

int LEET_ASSIGN_COOKIES()
{
    Solution solution;
    //int g_array[] = { 1, 2, 3 };
    //int s_array[] = { 1, 1 };
     int g_array[] = { 1, 2};
    int s_array[] = { 1, 2, 3 };
    vector<int> g(g_array, g_array + _countof(g_array));
    vector<int> s(s_array, s_array + _countof(s_array));
    cout << solution.findContentChildren(g, s) << endl;
    return 0;
}