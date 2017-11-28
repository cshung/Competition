#include "stdafx.h"

// https://leetcode.com/problems/sentence-similarity

#include "LEET_SENTENCE_SIMILARITY.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_SENTENCE_SIMILARITY
{
    class Solution
    {
    public:
        bool areSentencesSimilar(vector<string>& words1, vector<string>& words2, vector<pair<string, string>> pairs)
        {
            if (words1.size() != words2.size())
            {
                return false;
            }

            for (int i = 0; i < words1.size(); i++)
            {
                string& word1 = words1[i];
                string& word2 = words2[i];
                if (word1 == word2)
                {
                    continue;
                }
                bool found = false;
                for (int j = 0; j < pairs.size(); j++)
                {
                    if (pairs[j].first == word1 && pairs[j].second == word2)
                    {
                        found = true;
                        break;
                    }
                    if (pairs[j].first == word2 && pairs[j].second == word1)
                    {
                        found = true;
                        break;
                    }
                }
                if (!found)
                {
                    return false;
                }
            }
            return true;
        }
    };
};

using namespace _LEET_SENTENCE_SIMILARITY;

int LEET_SENTENCE_SIMILARITY()
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
    pairs.push_back(make_pair("great", "fine"));
    pairs.push_back(make_pair("drama", "acting"));
    pairs.push_back(make_pair("skills", "talent"));
    cout << s.areSentencesSimilar(words1, words2, pairs) << endl;
    return 0;
}