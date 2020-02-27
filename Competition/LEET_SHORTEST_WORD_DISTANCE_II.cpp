#include "stdafx.h"

// https://leetcode.com/problems/shortest-word-distance-ii/

#include "LEET_SHORTEST_WORD_DISTANCE_II.h"
#include <unordered_map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

namespace _LEET_SHORTEST_WORD_DISTANCE_II
{
    class WordDistance
    {
    public:
        WordDistance(vector<string>& words)
        {
            for (int i = 0; i < words.size(); i++)
            {
                auto probe = word_to_positions.find(words[i]);
                if (probe == word_to_positions.end())
                {
                    vector<int> list;
                    list.push_back(i);
                    word_to_positions.insert(make_pair(words[i], list));
                }
                else
                {
                    probe->second.push_back(i);
                }
            }
        }

        int shortest(string word1, string word2)
        {
            int min_dist = -1;
            int p1 = 0;
            int p2 = 0;
            int last_1 = -1;
            int last_2 = -1;
            vector<int>& list_1 = word_to_positions[word1];
            vector<int>& list_2 = word_to_positions[word2];
            while (true)
            {
                int curr_1 = -1;
                int curr_2 = -1;
                if (p1 == list_1.size() && p2 == list_2.size())
                {
                    break;
                }
                else if (p1 == list_1.size())
                {
                    curr_2 = list_2[p2++];
                }
                else if (p2 == list_2.size())
                {
                    curr_1 = list_1[p1++];
                }
                else
                {
                    if (list_1[p1] < list_2[p2])
                    {
                        curr_1 = list_1[p1++];
                    }
                    else
                    {
                        curr_2 = list_2[p2++];
                    }
                }
                if (last_1 != -1 && curr_2 != 1)
                {
                    int dist = curr_2 - last_1;
                    min_dist = (min_dist == -1) ? dist : min(min_dist, dist);
                }
                else if (last_2 != -1 && curr_1 != -1)
                {
                    int dist = curr_1 - last_2;
                    min_dist = (min_dist == -1) ? dist : min(min_dist, dist);
                }
                last_1 = curr_1;
                last_2 = curr_2;
            }
            return min_dist;
        }
    private:
        unordered_map<string, vector<int>> word_to_positions;
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