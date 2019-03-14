#include "stdafx.h"

// https://leetcode.com/problems/unique-letter-string/

#include "LEET_UNIQUE_LETTER_STRING.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_UNIQUE_LETTER_STRING
{
    class Solution
    {
    public:
        int uniqueLetterString(string S)
        {
            vector<vector<int>> indices;
            indices.resize(26);
            for (int i = 0; i < 26; i++)
            {
                indices[i].push_back(-1);
            }
            for (int i = 0; i < S.length(); i++)
            {
                char c = S[i];
                int x = c - 'A';
                indices[x].push_back(i);
            }
            for (int i = 0; i < 26; i++)
            {
                indices[i].push_back(S.length());
            }
            long result = 0;
            for (int i = 0; i < 26; i++)
            {
                for (int j = 1; j < indices[i].size() - 1; j++)
                {
                    int p = indices[i][j - 1] + 1;
                    int q = indices[i][j];
                    int r = indices[i][j + 1] - 1;
                    int z = (q - p + 1) * (r - q + 1);
                    result += z;
                    result = result % 1000000007;
                }
            }
            return (int)result;
        }
    };
};

using namespace _LEET_UNIQUE_LETTER_STRING;

int LEET_UNIQUE_LETTER_STRING()
{
    Solution s;
    cout << s.uniqueLetterString("ABC") << endl;
    cout << s.uniqueLetterString("ABA") << endl;
    return 0;
}