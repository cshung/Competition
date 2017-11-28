#include "stdafx.h"

// https://leetcode.com/problems/sentence-similarity-ii

#include "LEET_SENTENCE_SIMILARITY_II.h"
#include <map>
#include <iostream>
#include <set>
#include <vector>
#include <string>
#include <queue>

using namespace std;

namespace _LEET_SENTENCE_SIMILARITY_II
{
    class Solution {
    public:
        bool areSentencesSimilar(vector<string>& words1, vector<string>& words2, vector<pair<string, string>> pairs)
        {
            if (words1.size() != words2.size())
            {
                return false;
            }

            map<string, int> numbers;
            map<int, string> strings;
            map<string, int> canon;
            map<int, set<int>> graph;
            for (auto&& p : pairs)
            {
                int n1;
                auto probe1 = numbers.find(p.first);
                if (probe1 == numbers.end())
                {
                    n1 = numbers.size();
                    numbers.insert(make_pair(p.first, n1));
                    strings.insert(make_pair(n1, p.first));
                }
                else
                {
                    n1 = probe1->second;
                }
                int n2;
                auto probe2 = numbers.find(p.second);
                if (probe2 == numbers.end())
                {
                    n2 = numbers.size();
                    numbers.insert(make_pair(p.second, n2));
                    strings.insert(make_pair(n2, p.second));
                }
                else
                {
                    n2 = probe2->second;
                }
                auto probe3 = graph.find(n1);
                if (probe3 == graph.end())
                {
                    graph.insert(make_pair(n1, set<int>()));
                }
                graph[n1].insert(n2);
                auto probe4 = graph.find(n2);
                if (probe4 == graph.end())
                {
                    graph.insert(make_pair(n2, set<int>()));
                }
                graph[n2].insert(n1);
            }

            vector<bool> enqueued;
            enqueued.resize(numbers.size());
            for (int i = 0; i < numbers.size(); i++)
            {
                enqueued[i] = false;
            }

            int cc = 0;
            queue<int> bfs;
            for (int i = 0; i < numbers.size(); i++)
            {
                if (!enqueued[i])
                {
                    enqueued[i] = true;
                    bfs.push(i);
                    while (!bfs.empty())
                    {
                        int v = bfs.front();
                        bfs.pop();
                        canon.insert(make_pair(strings[v], cc));
                        for (auto&& neighbor : graph[v])
                        {
                            if (!enqueued[neighbor])
                            {
                                enqueued[neighbor] = true;
                                bfs.push(neighbor);
                            }
                        }
                    }
                    cc++;
                }
            }

            for (int i = 0; i < words1.size(); i++)
            {
                if (words1[i] == words2[i])
                {
                    continue;
                }
                auto probe1 = canon.find(words1[i]);
                if (probe1 == canon.end())
                {
                    return false;
                }
                auto probe2 = canon.find(words2[i]);
                if (probe2 == canon.end())
                {
                    return false;
                }
                if (probe1->second != probe2->second)
                {
                    return false;
                }
            }

            return true;
        }
    };
};

using namespace _LEET_SENTENCE_SIMILARITY_II;

int LEET_SENTENCE_SIMILARITY_II()
{
    Solution s;
    vector<string> words1;
    words1.push_back("great");
    words1.push_back("acting");
    words1.push_back("skills");
    vector<string> words2;
    words2.push_back("fine");
    words2.push_back("drama");
    words2.push_back("talent");
    vector<pair<string, string>> pairs;
    pairs.push_back(make_pair("great", "good"));
    pairs.push_back(make_pair("fine", "good"));
    pairs.push_back(make_pair("acting", "drama"));
    pairs.push_back(make_pair("skills", "talent"));
    cout << s.areSentencesSimilar(words1, words2, pairs) << endl;
    return 0;
}