#include "stdafx.h"

// https://leetcode.com/problems/word-ladder/

#include "LEET_WORD_LADDER.h"
#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <queue>

using namespace std;

namespace _LEET_WORD_LADDER
{
    class Solution
    {
    public:
        int ladderLength(string beginWord, string endWord, vector<string>& wordList)
        {
            wordList.push_back(beginWord);
            int n = wordList.size();
            int b = -1;
            int e = -1;
            int l = beginWord.length();
            vector<vector<int>> adjacency_list(n);
            for (int i = 0; i < n; i++)
            {
                string& si = wordList[i];
                if (si == beginWord)
                {
                    b = i;
                }
                else if (si == endWord)
                {
                    e = i;
                }
                for (int j = i + 1; j < n; j++)
                {
                    string& sj = wordList[j];
                    int mismatch = 0;
                    for (int c = 0; mismatch < 2 && c < l; c++)
                    {
                        if (si[c] != sj[c])
                        {
                            mismatch++;
                        }
                    }
                    if (mismatch == 1)
                    {
                        adjacency_list[i].push_back(j);
                        adjacency_list[j].push_back(i);
                    }
                }
            }

            if (b == -1 || e == -1)
            {
                return false;
            }
            if (b == e)
            {
                return 1;
            }
            queue<int> bfs;
            queue<int> lengths;
            vector<bool> enqueued(n, false);
            bfs.push(b);
            lengths.push(1);
            enqueued[b] = true;

            while (bfs.size() > 0)
            {
                int v = bfs.front();
                int length = lengths.front();
                bfs.pop();
                lengths.pop();
                for (int neighbor : adjacency_list[v])
                {
                    if (neighbor == e)
                    {
                        return length + 1;
                    }
                    if (!enqueued[neighbor])
                    {
                        enqueued[neighbor] = true;
                        bfs.push(neighbor);
                        lengths.push(length + 1);
                    }
                }
            }
            return 0;
        }
    };
}

using namespace _LEET_WORD_LADDER;

int LEET_WORD_LADDER()
{
    Solution s;
    string case1[]{ "hot", "dot", "dog", "lot", "log", "cog" };
    vector<string> words(case1, case1 + _countof(case1));
    cout << s.ladderLength("hit", "cog", words) << endl;
    return 0;
}