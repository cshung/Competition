#include "stdafx.h"

// https://leetcode.com/problems/word-break-ii/

#include "LEET_WORD_BREAK_II.h"
#include <map>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_WORD_BREAK_II
{

    class TrieNode
    {
    public:
        unordered_map<char, TrieNode*> m_children;
        TrieNode* m_failure;
        TrieNode* m_output;
        int m_pattern;
        TrieNode()
        {
            m_failure = nullptr;
            m_output = nullptr;
            m_pattern = -1;
        }
        ~TrieNode()
        {
            for (auto&& c : m_children)
            {
                delete c.second;
            }
        }
        void add(string& s, int index)
        {
            this->add(0, s, index);
        }
        void add(int i, string& s, int index)
        {
            if (i == s.length())
            {
                this->m_pattern = index;
            }
            else
            {
                char first = s[i];
                auto probe = this->m_children.find(first);
                if (probe == this->m_children.end())
                {
                    this->m_children.insert(make_pair(first, new TrieNode()));
                }
                this->m_children[first]->add(i + 1, s, index);
            }
        }
        void bfs(TrieNode* root)
        {
            queue<TrieNode*> parent;
            queue<char> character;
            queue<TrieNode*> bfs;
            parent.push(nullptr);
            character.push(' ');
            bfs.push(root);
            while (!bfs.empty())
            {
                TrieNode* p = parent.front();
                char c = character.front();
                TrieNode* v = bfs.front();
                parent.pop();
                character.pop();
                bfs.pop();
                while (p != nullptr)
                {
                    if (p == root)
                    {
                        break;
                    }
                    auto probe = p->m_failure->m_children.find(c);
                    if (probe != p->m_failure->m_children.end())
                    {
                        v->m_failure = probe->second;
                        if (v->m_failure->m_pattern != -1)
                        {
                            v->m_output = v->m_failure;
                        }
                        else if (v->m_failure->m_output != nullptr)
                        {
                            v->m_output = v->m_failure->m_output;
                        }
                        break;
                    }
                    p = p->m_failure;
                }
                if (v->m_failure == nullptr)
                {
                    v->m_failure = root;
                }
                for (auto&& pair : v->m_children)
                {
                    parent.push(v);
                    character.push(pair.first);
                    bfs.push(pair.second);
                }
            }
        }
    };

    vector<pair<int, int>> aho_corasick(string& s, vector<string>& patterns)
    {
        vector<pair<int, int>> result;
        TrieNode* root = new TrieNode();
        for (int i = 0; i < patterns.size(); i++)
        {
            root->add(patterns[i], i);
        }
        root->bfs(root);
        TrieNode* cursor = root;
        int i = 0;
        while (true)
        {
            if (i == s.length())
            {
                break;
            }
            char c = s[i];
            auto probe = cursor->m_children.find(c);
            if (probe == cursor->m_children.end())
            {
                if (cursor == root)
                {
                    i++;
                }
                else
                {
                    cursor = cursor->m_failure;
                }
            }
            else
            {
                cursor = probe->second;
                i = i + 1;
                if (cursor->m_pattern != -1)
                {
                    result.push_back(make_pair(i - patterns[cursor->m_pattern].length(), (cursor->m_pattern)));
                }
                TrieNode* output_cursor = cursor->m_output;
                while (output_cursor != nullptr)
                {
                    result.push_back(make_pair(i - patterns[output_cursor->m_pattern].length(), (output_cursor->m_pattern)));
                    output_cursor = output_cursor->m_output;
                }
            }
        }
        delete root;
        return result;
    }

    class Solution {
    public:
        unordered_set<int> failed;
        vector<string> wordBreak(string s, vector<string>& wordDict) {
            auto matches = aho_corasick(s, wordDict);
            unordered_map<int, vector<int>> graph;
            for (auto&& match : matches)
            {
                auto probe = graph.find(match.first);
                if (probe == graph.end())
                {
                    graph.insert(make_pair(match.first, vector<int>()));
                }
                graph[match.first].push_back(match.second);
            }
            vector<string> answers;
            vector<int> prefix;
            paths(graph, 0, prefix, s.length(), wordDict, answers);
            return answers;
        }
        bool paths(unordered_map<int, vector<int>>& graph, int i, vector<int>& prefix, int target, vector<string>& wordDict, vector<string>& answers)
        {
            if (i == target)
            {
                ostringstream ostr;
                for (int i = 0; i < prefix.size(); i++)
                {
                    if (i != 0)
                    {
                        ostr << " ";
                    }
                    ostr << wordDict[prefix[i]];
                }
                answers.push_back(ostr.str());
                return true;
            }
            else
            {
                bool found = false;
                auto probe = graph.find(i);
                if (probe != graph.end())
                {
                    for (auto neighbor : probe->second)
                    {
                        prefix.push_back(neighbor);
                        int next = i + wordDict[neighbor].length();
                        if (failed.find(next) == failed.end())
                        {
                            bool result = paths(graph, next, prefix, target, wordDict, answers);
                            found = found || result;
                        }
                        prefix.pop_back();
                    }
                }
                if (!found)
                {
                    failed.insert(i);
                }
                return found;
            }
        }
    };

};

using namespace _LEET_WORD_BREAK_II;

int LEET_WORD_BREAK_II()
{
    string s = "catsanddog";
    vector<string> wordDict;
    wordDict.push_back("cat");
    wordDict.push_back("cats");
    wordDict.push_back("and");
    wordDict.push_back("sand");
    wordDict.push_back("dog");
    Solution solution;
    auto answers = solution.wordBreak(s, wordDict);
    for (auto answer : answers)
    {
        cout << answer << endl;
    }
    return 0;
}