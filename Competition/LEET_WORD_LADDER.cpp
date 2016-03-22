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
        int ladderLength(string beginWord, string endWord, unordered_set<string>& wordList)
        {
            int n = 0;
            unordered_map<string, int> wordMap;
            vector<string> strings;

            for (unordered_set<string>::iterator wi = wordList.begin(); wi != wordList.end(); wi++)
            {
                strings.push_back(*wi);
                wordMap.insert(pair<string, int>(*wi, n++));
            }

            wordMap.erase(beginWord);
            wordMap.erase(endWord);
            wordMap.insert(pair<string, int>(beginWord, n));
            wordMap.insert(pair<string, int>(endWord, n + 1));
            strings.push_back(beginWord);
            strings.push_back(endWord);

            queue<int> bfs_queue;

            vector<bool> enqueued(n + 2);
            vector<int> lengths(n + 2);
            for (int i = 0; i < n; i++)
            {
                enqueued[i] = false;
                lengths[i] = 0;
            }

            lengths[n] = 1;
            enqueued[n] = true;
            bfs_queue.push(n);

            while (bfs_queue.size() > 0)
            {
                int current_id = bfs_queue.front();
                bfs_queue.pop();
                string current = strings[current_id];
                int length = lengths[current_id];

                for (int c = 0; c < current.length(); c++)
                {
                    char backup = current[c];
                    for (char a = 'a'; a <= 'z'; a++)
                    {
                        current[c] = a;
                        unordered_map<string, int>::iterator probe = wordMap.find(current);
                        if (probe != wordMap.end())
                        {
                            int neighbor_id = probe->second;
                            if (neighbor_id == (n + 1))
                            {
                                return length + 1;
                            }
                            if (!enqueued[neighbor_id])
                            {
                                lengths[neighbor_id] = length + 1;
                                enqueued[neighbor_id] = true;
                                bfs_queue.push(neighbor_id);
                            }
                        }
                    }
                    current[c] = backup;
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
    unordered_set<string> words;
    words.insert("a");
    words.insert("b");
    words.insert("c");
    cout << s.ladderLength("a", "c", words) << endl;
    return 0;
}