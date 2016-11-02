#include "stdafx.h"

// https://leetcode.com/problems/edit-distance/

#include "LEET_EDIT_DISTANCE.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

namespace _LEET_EDIT_DISTANCE
{
    class Solution
    {
    public:
        int minDistance(string word1, string word2)
        {
            // m("","") = 0
            // m(x, "") = m("", x) = |x|
            // m(aX, aY) = m(X, Y)
            // m(aX, bY) = min(m(aX, Y) + 1, m(X, bY) + 1, m(X, Y) + 1))
            vector<vector<int>> m;
            m.resize(word1.length() + 1);
            for (int i = 0; i <= word1.length(); i++)
            {
                m[i].resize(word2.length() + 1);
            }

            for (int i = 0; i <= word1.length(); i++)
            {
                m[i][0] = i;
            }
            for (int i = 0; i <= word2.length(); i++)
            {
                m[0][i] = i;
            }

            for (int i = 0; i < word1.length(); i++)
            {
                for (int j = 0; j < word2.length(); j++)
                {
                    if (word1[i] == word2[j])
                    {
                        m[i + 1][j + 1] = m[i][j];
                    }
                    else
                    {
                        m[i + 1][j + 1] = min(min(m[i][j], m[i + 1][j]), m[i][j + 1]) + 1;
                    }
                }
            }
#ifdef LOG
            for (int i = 0; i <= word1.length(); i++)
            {
                for (int j = 0; j <= word2.length(); j++)
                {
                    cout << m[i][j] << " ";
                }
                cout << endl;
            }
#endif
            return m[word1.length()][word2.length()];
        }
    };
};

using namespace _LEET_EDIT_DISTANCE;

int LEET_EDIT_DISTANCE()
{
    Solution solution;
    cout << solution.minDistance("10086", "12580") << endl;
    return 0;
}