#include "stdafx.h"

// https://leetcode.com/problems/shortest-word-distance-ii/

#include "LEET_SHORTEST_WORD_DISTANCE_II.h"
#include <unordered_map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_SHORTEST_WORD_DISTANCE_II
{
    class WordDistance
    {
    public:
        WordDistance(vector<string>& words)
        {
            for (auto word : words)
            {
                auto probe = word_to_id.find(word);
                int word_id;
                if (probe == word_to_id.end())
                {
                    word_id = word_to_id.size();
                    word_to_id.insert(make_pair(word, word_id));
                }
                else
                {
                    word_id = probe->second;
                }
                word_ids.push_back(word_id);
            }
        }

        int shortest(string word1, string word2)
        {
            int word_id_1 = word_to_id[word1];
            int word_id_2 = word_to_id[word2];
            int last1 = -1;
            int last2 = -1;
            int min_dist = -1;
            for (int i = 0; i < word_ids.size(); i++)
            {
                if (word_ids[i] == word_id_1)
                {
                    last1 = i;
                    if (last2 != -1)
                    {
                        int dist = last1 - last2;
                        if (min_dist == -1 || dist < min_dist)
                        {
                            min_dist = dist;
                        }
                    }
                }
                else if (word_ids[i] == word_id_2)
                {
                    last2 = i;
                    if (last1 != -1)
                    {
                        int dist = last2 - last1;
                        if (min_dist == -1 || dist < min_dist)
                        {
                            min_dist = dist;
                        }
                    }
                }
            }
            return min_dist;
        }
    private:
        unordered_map<string, int> word_to_id;
        vector<int> word_ids;
    };

};

using namespace _LEET_SHORTEST_WORD_DISTANCE_II;

int LEET_SHORTEST_WORD_DISTANCE_II()
{
    string test_array[] = { "practice", "makes", "perfect", "coding", "makes" };
    vector<string> test(test_array, test_array + _countof(test_array));
    WordDistance solution(test);
    cout << solution.shortest("coding", "practice") << endl;
    cout << solution.shortest("makes", "coding") << endl;
    return 0;
}