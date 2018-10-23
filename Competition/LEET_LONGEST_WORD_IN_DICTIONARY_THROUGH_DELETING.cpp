#include "stdafx.h"

// https://leetcode.com/problems/longest-word-in-dictionary-through-deleting

#include "LEET_LONGEST_WORD_IN_DICTIONARY_THROUGH_DELETING.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_LONGEST_WORD_IN_DICTIONARY_THROUGH_DELETING
{
    class Solution
    {
    public:
        string findLongestWord(string s, vector<string>& d)
        {
            bool found = false;
            string answer = "";

            vector<int> p;
            p.resize(d.size());
            for (int i = 0; i < d.size(); i++) {
                p[i] = 0;
            }
            for (int i = 0; i < s.size(); i++) {
                for (int c = 0; c < d.size(); c++) {
                    if (p[c] < d[c].length())
                    {
                        if (d[c][p[c]] == s[i])
                        {
                            p[c]++;
                        }
                    }
                    if (p[c] == d[c].length())
                    {
                        if (!found) {
                            found = true;
                            answer = d[c];
                        }
                        else if (p[c] > answer.length())
                        {
                            answer = d[c];
                        }
                        else if (p[c] == answer.length() && d[c] < answer)
                        {
                            answer = d[c];
                        }
                    }
                }
            }
            return answer;
        }
    };
};

using namespace _LEET_LONGEST_WORD_IN_DICTIONARY_THROUGH_DELETING;

int LEET_LONGEST_WORD_IN_DICTIONARY_THROUGH_DELETING()
{
    Solution s;
    string d[] = { "aaa","aa","a" };
    cout << s.findLongestWord("aaa", vector<string>(d, d + _countof(d))) << endl;
    return 0;
}