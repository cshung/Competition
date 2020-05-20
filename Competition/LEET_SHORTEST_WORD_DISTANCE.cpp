#include "stdafx.h"

// https://leetcode.com/problems/shortest-word-distance/

#include "LEET_SHORTEST_WORD_DISTANCE.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_SHORTEST_WORD_DISTANCE
{
    class Solution
    {
    public:
        int shortestDistance(vector<string>& words, string word1, string word2)
        {
            int last1 = -1;
            int last2 = -1;
            int min_dist = -1;
            for (int i = 0; i < words.size(); i++)
            {
                if (words[i] == word1)
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
                else if (words[i] == word2)
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
    };
};

using namespace _LEET_SHORTEST_WORD_DISTANCE;

int LEET_SHORTEST_WORD_DISTANCE()
{
    Solution solution;
    string test_array[] = { "practice", "makes", "perfect", "coding", "makes" };
    vector<string> test(test_array, test_array + _countof(test_array));
    cout << solution.shortestDistance(test, "coding", "practice") << endl;
    cout << solution.shortestDistance(test, "makes", "coding") << endl;
    return 0;
}